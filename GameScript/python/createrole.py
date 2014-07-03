import socket
import time
import struct
import GameProtocol_pb2
import ClientProtocol

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)  
#sock.connect(('192.168.20.134', 8500))
#sock.connect(('118.192.74.197', 8500))
sock.connect(('192.168.1.34', 8500))

count = 1

while True:
    ClientProtocol.RequestCreateRole(sock, 'test' + str(count), 'test' + str(count))
    
    count = count + 1
    print count
sock.close()
    #time.sleep(100)
      
