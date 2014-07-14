# -*- coding: cp936 -*-
import socket
import time
import struct
import ClientProtocol

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)  
#sock.connect(('192.168.20.134', 8500))
sock.connect(('192.168.1.34', 8500))
count = 1

    
verifyTokenAck = ClientProtocol.RequestVerifyToken(sock, 'test', 18147)
print "verifyTokenAck:" 
print verifyTokenAck
    
sock.close()  
