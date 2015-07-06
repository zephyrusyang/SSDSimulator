#!/usr/bin/python
import ctypes
from ctypes import c_void_p

class HostSim(object):
    def __init__(self):
        self.so =ctypes.CDLL("./libHostSim.so")
        self.so.HostSim_Create.restype = c_void_p
        self.pHostSim = self.so.HostSim_Create()
    def __del__(self):
        self.so.HostSim_Delete.argtypes = [c_void_p]
        self.so.HostSim_Delete(self.pHostSim)
    def SendNCQ(self):
        self.so.HostSim_SendNCQ()

if __name__ == '__main__':
    ob = HostSim()
    ob.SendNCQ()

