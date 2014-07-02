import socket
import time
import struct
import GameProtocol_pb2

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)  
#sock.connect(('192.168.20.134', 8500))
sock.connect(('192.168.1.34', 8500))
count = 1

#short_body = 'hello asio'
#middle_body = 'abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz'
#long_body = 'abcdefghijklmnopqrstuvwxyz1234567890abcdefghijklmnopqrstuvwxyz1234567890abcdefghijklmnopqrstuvwxyz1234567890abcdefghijklmnopqrstuvwxyz1234567890abcdefghijklmnopqrstuvwxyz1234567890abcdefghijklmnopqrstuvwxyz1234567890abcdefghijklmnopqrstuvwxyz1234567890abcdefghijklmnopqrstuvwxyz1234567890abcdefghijklmnopqrstuvwxyz1234567890abcdefghijklmnopqrstuvwxyz1234567890abcdefghijklmnopqrstuvwxyz1234567890abcdefghijklmnopqrstuvwxyz1234567890abcdefghijklmnopqrstuvwxyz1234567890abcdefghijklmnopqrstuvwxyz1234567890abcdefghijklmnopqrstuvwxyz1234567890abcdefghijklmnopqrstuvwxyz1234567890abcdefghijklmnopqrstuvwxyz1234567890abcdefghijklmnopqrstuvwxyz1234567890abcdefghijklmnopqrstuvwxyz1234567890abcdefghijklmnopqrstuvwxyz1234567890abcdefghijklmnopqrstuvwxyz1234567890abcdefghijklmnopqrstuvwxyz1234567890abcdefghijklmnopqrstuvwxyz1234567890abcdefghijklmnopqrstuvwxyz1234567890'
#body = long_body
while True:
    roleDataReq = GameProtocol_pb2.RequestRoleData()
    roleDataReq.ptName = 'test' + str(count)
    body = roleDataReq.SerializeToString()
    header = struct.pack('iii', 12+len(body), 0x1001, 0)
    sock.send(header+body)
    count += 1
    if count % 100 == 0:
        print count
    pbstr = sock.recv(1024)
    #role = test_pb2.role()
    #role.ParseFromString(pbstr)
    #print role
    time.sleep(1000)
sock.close()  
