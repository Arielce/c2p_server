# -*- coding: cp936 -*-
import socket
import time
import struct
import GameProtocol_pb2
import ServerCmd_pb2


sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)  
#sock.connect(('192.168.20.134', 8500))
sock.connect(('192.168.1.34', 8500))

createRoleReq = GameProtocol_pb2.RequestCreateRole()
createRoleReq.ptName = 'test'
createRoleReq.roleName = 'test'
body = createRoleReq.SerializeToString()

while True:
    header = struct.pack('iii', 12+len(body), 0x1002, 0)
    sock.send(header)
    sock.send(body)
    