# -*- coding: cp936 -*-
import socket
import time
import struct
import ClientProtocol

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)  
#sock.connect(('192.168.20.134', 8500))
sock.connect(('192.168.1.34', 8500))
count = 1

# 测试抽奖信息
while True:
    roleDataAck = ClientProtocol.RequestRoleData(sock, 'test' + str(count))
    print roleDataAck
    
    verifyTokenAck = ClientProtocol.RequestVerifyToken(sock, 'test' + str(count), 0)
    print verifyTokenAck
    
    drawListAck = ClientProtocol.RequestDrawList(sock, roleDataAck.roleData.baseInfo.userId)
    print drawListAck
    
    drawPrizeAck = ClientProtocol.RequestDrawPrize(sock, roleDataAck.roleData.baseInfo.userId, drawListAck.drawList[0])
    print drawPrizeAck
    
    time.sleep(1000)
sock.close()  
