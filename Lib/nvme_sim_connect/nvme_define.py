#!/usr/bin/env python3
# -*- coding:utf-8 -*-

from ctypes import (Structure, 
                    c_uint8, c_uint16, c_uint32, c_uint64, 
                    cast, POINTER, sizeof, memmove, byref)


class SqidCmd(Structure):
    _fields_ = (
        ('sqid',   c_uint32),
        )

class CqidCmd(Structure):
    _fields_ = (
        ('cqid',   c_uint32),
        )

class NvmeCqe(Structure):
    _fields_ = (
        ('result',   c_uint32),
        ('rsvd',     c_uint32),
        ('sq_head',  c_uint16),
        ('sq_id',    c_uint16),
        ('cid',      c_uint16),
        ('status',   c_uint16),
        )

class PcieCmd(Structure):
    _fields_ = (
        ('offset', c_uint64),
        ('data',   c_uint64),
        ('size',   c_uint64),
        )
    
class NvmeCmd(Structure):
    _fields_ = (
        ('opcode', c_uint8),
        ('fuse',   c_uint8),
        ('cid',    c_uint16),
        ('nsid',   c_uint32),
        ('res1',   c_uint64),
        ('mptr',   c_uint64),
        ('prp1',   c_uint64),
        ('prp2',   c_uint64),
        ('cdw10',  c_uint32),
        ('cdw11',  c_uint32),
        ('cdw12',  c_uint32),
        ('cdw13',  c_uint32),
        ('cdw14',  c_uint32),
        ('cdw15',  c_uint32),
    )

class NvmeCreateSq(Structure):
    _fields_ = (
        ('opcode',   c_uint8),
        ('flags',    c_uint8),
        ('cid',      c_uint16),
        ('rsvd1',    c_uint32 * 5),
        ('prp1',     c_uint64),
        ('rsvd8',    c_uint64),
        ('sqid',     c_uint16),
        ('qsize',    c_uint16),
        ('sq_flags', c_uint16),
        ('cqid',     c_uint16),
        ('rsvd12',   c_uint32*4),
    )

class NvmeCreateCq(Structure):
    _fields_ = (
        ('opcode',     c_uint8),
        ('flags',      c_uint8),
        ('cid',        c_uint16),
        ('rsvd1',      c_uint32 * 5),
        ('prp1',       c_uint64),
        ('rsvd8',      c_uint64),
        ('cqid',       c_uint16),
        ('qsize',      c_uint16),
        ('cq_flags',   c_uint16),
        ('irq_vector', c_uint16),
        ('rsvd12',     c_uint32*4),
    )

class NvmeDeleteQ(Structure):
    _fields_ = (
        ('opcode',   c_uint8),
        ('flags',    c_uint8),
        ('cid',      c_uint16),
        ('rsvd1',    c_uint32 * 9),
        ('qid',      c_uint16),
        ('rsvd10',   c_uint16),
        ('rsvd11',   c_uint32*5),
    )

class NvmeRwCmd(Structure):
    _fields_ = (
        ('opcode',  c_uint8),
        ('flags',   c_uint8),
        ('cid',     c_uint16),
        ('nsid',    c_uint32),
        ('rsvd2',   c_uint64),
        ('mptr',    c_uint64),
        ('prp1',    c_uint64),
        ('prp2',    c_uint64),
        ('slba',    c_uint64),
        ('nlb',     c_uint16),
        ('control', c_uint16),
        ('dsmgmt',  c_uint32),
        ('reftag',  c_uint32),
        ('apptag',  c_uint16),
        ('appmask', c_uint16),
    )


nvme_admin_cmd_name = {
    0x00: "NVME_ADM_CMD_DELETE_SQ",
    0x01: "NVME_ADM_CMD_CREATE_SQ",
    0x02: "NVME_ADM_CMD_GET_LOG_PAGE",
    0x04: "NVME_ADM_CMD_DELETE_CQ",
    0x05: "NVME_ADM_CMD_CREATE_CQ",
    0x06: "NVME_ADM_CMD_IDENTIFY",
    0x08: "NVME_ADM_CMD_ABORT",
    0x09: "NVME_ADM_CMD_SET_FEATURES",
    0x0a: "NVME_ADM_CMD_GET_FEATURES",
    0x0c: "NVME_ADM_CMD_ASYNC_EV_REQ",
    0x10: "NVME_ADM_CMD_ACTIVATE_FW",
    0x11: "NVME_ADM_CMD_DOWNLOAD_FW",
    0x80: "NVME_ADM_CMD_FORMAT_NVM",
    0x81: "NVME_ADM_CMD_SECURITY_SEND",
    0x82: "NVME_ADM_CMD_SECURITY_RECV",
}

nvme_io_cmd_name = {
    0x00: "NVME_CMD_FLUSH",
    0x01: "NVME_CMD_WRITE",
    0x02: "NVME_CMD_READ",
    0x04: "NVME_CMD_WRITE_UNCOR",
    0x05: "NVME_CMD_COMPARE",
    0x08: "NVME_CMD_WRITE_ZEROS",
    0x09: "NVME_CMD_DSM",
}

def _copier_factory(typ):
    def f(a,b):
        memmove(a,b, sizeof(typ))
    f.argtypes = [POINTER(typ), POINTER(typ)]
    return f

def copy_cmd(cmd_type, msg_src):
    my_copy = _copier_factory(cmd_type)
    msg_dst = cmd_type()
    my_copy(byref(msg_dst), byref(msg_src))
    return msg_dst





