#!/usr/bin/env python3
# -*- coding:utf-8 -*-

import socket
from datetime import datetime
from time import sleep

s = socket.socket()

port = 5000
s.bind(('', port))

while True:
    print("listening...")
    s.listen(5)
    c, addr = s.accept()
    print('receiving from ' + str(addr))
    while True:
        try:
            print("receive:" + str(c.recv(4096,0)))
        except (socket.error):
            print(socket.error)
            break
        sleep(1)

    c.close()
s.close()
            
        
