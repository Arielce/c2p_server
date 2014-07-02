# -*- coding: cp936 -*-
import socket
import time
import struct
import thread
import RoleData_pb2
import GameProtocol_pb2


count_lock = thread.allocate_lock()

count = 0
def run():
    global count
    print "thread start"
    
    while True:
        sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)  
        #sock.connect(('192.168.20.134', 8500))
        sock.connect(('192.168.1.34', 8500))

        count_lock.acquire()
        count += 1
        if count % 100 == 0:
            print count
        count_lock.release()
        
        roleDataReq = GameProtocol_pb2.RequestRoleData()
        roleDataReq.ptName = 'test' + str(count)
        body = roleDataReq.SerializeToString()
        header = struct.pack('iii', 12+len(body), 0x1001, 0)
        sock.send(header+body)
        
        pbstr = sock.recv(1024)


        roleDataAck = GameProtocol_pb2.ResponseRoleData()
        try:
            roleDataAck.ParseFromString(str(pbstr[12:]))            # 去除消息头12个字节
        except Exception as e:
            print e
        #print roleDataAck
        rolebase = roleDataAck.roleData
        #print "userid=" + str(rolebase.baseInfo.userId)

	#enter gate
        enterGateReq = GameProtocol_pb2.RequestEnterGate()
        enterGateReq.userId = rolebase.baseInfo.userId
        enterGateReq.gateId = 100001
        body = enterGateReq.SerializeToString()
        header = struct.pack('iii', 12+len(body), 0x1100, 0)
        #sock.send(header+body)

        #finish gate
        finishGate = GameProtocol_pb2.RequestFinishGate()
        finishGate.userId = rolebase.baseInfo.userId
        finishGate.gateId = 100001
        body = finishGate.SerializeToString()
        header = struct.pack('iii', 12+len(body), 0x1101, 0)
        #sock.send(header+body)

        #time.sleep(1)
        sock.close()

def doTest():
    i = 0
    while i < 10:
        i = i + 1
        thread.start_new_thread(run, ())

doTest()
