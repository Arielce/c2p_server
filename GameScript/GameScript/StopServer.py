# -*- coding: cp936 -*-
import socket
import time
import struct
import ClientProtocol

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)  
#sock.connect(('192.168.20.134', 8500))
sock.connect(('192.168.1.34', 8501))

roleDataAck = ClientProtocol.RequestStopServer(sock, 1)