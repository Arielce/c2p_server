import socket
import time
import struct

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)  
#sock.connect(('192.168.20.134', 8500))
sock.connect(('192.168.1.34', 8500))
count = 10

while True:
    body = ''
    header = struct.pack('iii', 12+len(body), 0x1002, 0)
    sock.send(header+body)
    pbstr = sock.recv(1024)
    
    time.sleep(1000)
sock.close()  
