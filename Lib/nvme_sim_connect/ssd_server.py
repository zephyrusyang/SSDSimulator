#!/usr/bin/env python3
# -*- coding:utf-8 -*-

import socket
import copy
from datetime import datetime
from time import sleep
from ctypes import Structure, c_uint8, c_uint16, c_uint32, c_uint64, cast, POINTER, sizeof
from nvme_define import *


class NvmeServer:
    "hanle connect/disconnect from qemu"
    def __init__(self, host_name = "localhost", port = 5000):
        # param
        self.sq_list = {}
        self.cq_list = {}
        self.is_cc_en = False

        # create TCP socket and bind
        print("create TCP socket and bind(%s, %d)" % (host_name, port))
        self.sock = socket.socket(
            socket.AF_INET,
            socket.SOCK_STREAM
        )
        self.sock.bind((host_name, port))

    def run(self):
        # wait for connect
        self.sock.listen(1)
        print("waiting connect from [qemu]...")
        self.client_socket, self.client_addr = self.sock.accept()
        print('receiving from ' + str(self.client_addr))
        # polling msg
        while True:
            try:
                # get sqid
                chunk = self.recv_from_client(sizeof(SqidCmd))
                sqid = cast(chunk, POINTER(SqidCmd))[0].sqid
                if sqid == 0x00010000:
                    # pcie
                    chunk = self.recv_from_client(sizeof(PcieCmd))
                    self.handle_pcie_msg(chunk)
                elif sqid == 0x00000000:
                    # nvme admin q
                    assert(self.is_cc_en)
                    chunk = self.recv_from_client(sizeof(NvmeCmd))
                    self.handle_admin_msg(sqid, chunk)
                else:
                    # nvme I/O q
                    assert(self.is_cc_en)
                    chunk = self.recv_from_client(sizeof(NvmeCmd))
                    self.handle_io_msg(sqid, chunk)

            except (socket.error):
                print(socket.error)
                break
        
        self.close()

    def send_to_client(self, msg, msg_size):
        assert(isinstance(msg, Structure))
        chunk = memoryview(msg).tobytes()
        totalsent = 0
        while totalsent < msg_size:
            sent = self.client_socket.send(chunk[totalsent:])
            if sent == 0:
                raise RuntimeError("socket connection broken")
            totalsent = totalsent + sent

    def recv_from_client(self, msg_size):
        chunks = []
        bytes_recd = 0
        while bytes_recd < msg_size:
            chunk = self.client_socket.recv(min(msg_size - bytes_recd, 2048))
            if chunk == b'':
                raise RuntimeError("socket connection broken")
            chunks.append(chunk)
            bytes_recd = bytes_recd + len(chunk)
        return b''.join(chunks)

    def close(self):
        self.client_socket.close()
        self.sock.close()

    def response_cqe(self, cqid, sqid, cid, result, status):
        cqid_cmd = CqidCmd()
        cqid_cmd.cqid = cqid
        self.send_to_client(cqid_cmd, sizeof(cqid_cmd))

        response = NvmeCqe()
        response.result = result
        response.sq_head = 0 #todo
        response.sq_id = sqid
        response.cid = cid
        response.status = status
        self.send_to_client(response, sizeof(response))

    def dummy_handler_no_response(self, sqid, chunk):
        print("dummy_handler_no_response")

    def dummy_handler_with_response(self, sqid, chunk):
        print("dummy_handler_with_response")
        nvme_cmd = cast(chunk, POINTER(NvmeCmd))[0]
        cqid = self.sq_list[sqid].cqid
        self.response_cqe(cqid, sqid, nvme_cmd.cid, result=0, status=0)    

    def read_handler(self, sqid, chunk):
        read_cmd = cast(chunk, POINTER(NvmeRwCmd))[0]
        cqid = self.sq_list[sqid].cqid
        print(" -- read_handler->{slba=0x%x, nlb=0x%x}" % (read_cmd.slba, read_cmd.nlb))
        self.response_cqe(cqid, sqid, read_cmd.cid, result=0, status=0)    

    def write_handler(self, sqid, chunk):
        write_cmd = cast(chunk, POINTER(NvmeRwCmd))[0]
        cqid = self.sq_list[sqid].cqid
        print(" -- write_handler->{slba=0x%x, nlb=0x%x}" % (write_cmd.slba, write_cmd.nlb))
        self.response_cqe(cqid, sqid, write_cmd.cid, result=0, status=0)    

    def create_sq_hander(self, sqid, chunk):
        create_q = cast(chunk, POINTER(NvmeCreateSq))[0]
        self.sq_list[create_q.sqid] = copy_cmd(NvmeCreateSq, create_q)

    def delete_sq_hander(self, sqid, chunk):
        delete_q = cast(chunk, POINTER(NvmeDeleteQ))[0]
        self.sq_list[delete_q.qid] = None

    def create_cq_hander(self, sqid, chunk):
        create_q = cast(chunk, POINTER(NvmeCreateCq))[0]
        self.cq_list[create_q.cqid] = copy_cmd(NvmeCreateCq, create_q)

    def delete_cq_hander(self, sqid, chunk):
        delete_q = cast(chunk, POINTER(NvmeDeleteQ))[0]
        self.cq_list[delete_q.qid] = None

    admin_cmd_handler = {
        0x00: delete_sq_hander,
        0x01: create_sq_hander,
        0x02: dummy_handler_no_response,
        0x04: delete_cq_hander,
        0x05: create_cq_hander,
        0x06: dummy_handler_no_response,
        0x08: dummy_handler_no_response,
        0x09: dummy_handler_no_response,
        0x0a: dummy_handler_no_response,
        0x0c: dummy_handler_no_response,
        0x10: dummy_handler_no_response,
        0x11: dummy_handler_no_response,
        0x80: dummy_handler_no_response,
        0x81: dummy_handler_no_response,
        0x82: dummy_handler_no_response,
    }

    io_cmd_handler = {
        0x00: dummy_handler_with_response,
        0x01: write_handler,
        0x02: read_handler,
        0x04: dummy_handler_with_response,
        0x05: dummy_handler_with_response,
        0x08: dummy_handler_with_response,
        0x09: dummy_handler_with_response,
    }


    def handle_io_msg(self, sqid, chunk):
        msg = cast(chunk, POINTER(NvmeCmd))[0]
        print("nvme io cmd ->{0x%x, %s}" % (msg.opcode, nvme_io_cmd_name[msg.opcode]))
        handler = self.io_cmd_handler[msg.opcode]
        assert(handler)
        handler(self, sqid, chunk)

    def handle_admin_msg(self, sqid, chunk):
        msg = cast(chunk, POINTER(NvmeCmd))[0]
        print("nvme admin cmd ->{0x%x, %s}" % (msg.opcode, nvme_admin_cmd_name[msg.opcode]))
        handler = self.admin_cmd_handler[msg.opcode]
        assert(handler)
        handler(self, sqid, chunk)

    def handle_pcie_msg(self, chunk):
        msg = cast(chunk, POINTER(PcieCmd))[0]
        print("pcie write bar ->{0x%x, 0x%x, 0x%x}" % (msg.offset, msg.data, msg.size))
        if msg.offset != 0x14:
            return
    
        if (msg.data & 0x0000000000000001) == 1:
            if self.is_cc_en == False:
                self.is_cc_en = True
        elif (msg.data & 0x0000000000000001) == 0:
            if self.is_cc_en == True:
                self.is_cc_en = False


def main():
    nvme_server = NvmeServer()
    nvme_server.run()

if __name__ == '__main__':
    main()
            
        
