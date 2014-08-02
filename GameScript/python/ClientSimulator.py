# -*- coding: cp936 -*-

import httplib;
import socket
import time
import struct
import ClientProtocol 
import json

# 模拟客户端行为
class ClientSimulator:
    def __init__(self):
        return
    
    # 连接登陆服务器
    def connect_loginserver(self, ip, port):
        self.httpClient = httplib.HTTPConnection(ip, port, timeout=30)
    
    #连接GameServer
    def connect_gameserver(self, ip, port):
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)  
        self.sock.connect((ip, port))
        
    #注册
    def register(self, ptname, passwd):
        self.httpClient.request('GET', '/register?ptname=' + ptname + '&password=' + passwd)
        response = self.httpClient.getresponse()
        
        register_ret = response.read()
        jsonDecoder = json.JSONDecoder();
        ret = jsonDecoder.decode(register_ret)
        is_success = ret["register"]
        if is_success == "sucesss":
            return True
        return False
    
    #登陆
    def login(self, ptname, passwd):
        self.httpClient.request('GET', '/login?ptname=' + ptname + '&password=' + passwd)
        response = self.httpClient.getresponse()
        #print "login response=" + response
        
        login_ret = response.read()
        jsonDecoder = json.JSONDecoder();
        ret = jsonDecoder.decode(login_ret)
        self.ptname = ptname
        self.token = ret["token"]
        return self.token

    #获取区组列表
    def get_gamegroups(self):
        getGroupsAck = ClientProtocol.RequestGameGroup(self.sock);
        print "gamegroup:"
        print getGroupsAck
    
    #验证Token
    def verify_token(self):
        verifyTokenAck = ClientProtocol.RequestVerifyToken(self.sock, self.ptname, int(self.token))
        if verifyTokenAck.errCode != 0:
            return False
        return True
    
    # 创建角色
    def create_role(self, rolename):
        createRoleAck = ClientProtocol.RequestCreateRole(self.sock, self.ptname, rolename)
        print "create role ack:"
        print createRoleAck
        
    # 获取角色数据
    def get_roledata(self):
        roleDataAck = ClientProtocol.RequestRoleData(self.sock, self.ptname)
        # 保存userId
        self.userId = roleDataAck.roleData.baseInfo.userId
        print "get role data:"
        print roleDataAck
        
    # 请求进入关卡
    def enter_gate(self, gateId):
        enterGateAck = ClientProtocol.RequestEnterGate(self.sock, self.userId, gateId)
        print "enter gate ack:"
        print enterGateAck
        
    # 请求关卡奖励
    def finish_gate(self, gateId, result):
        finishGateAck = ClientProtocol.RequestFinishGate(self.sock, self.userId, gateId, result)
        print "finish gate ack:"
        print finishGateAck
        
    # 请求抽奖列表
    def get_drawlist(self):
        drawListAck = ClientProtocol.RequestDrawList(self.sock, self.userId)
        print "draw list ack:"
        print drawListAck
        
    # 请求抽奖
    def draw_prize(self, drawId):
        drawPrizeAck = ClientProtocol.RequestDrawPrize(self.sock, self.userId, drawId)
        print "draw prize ack:"
        print drawPrizeAck
    
    # 请求设置战斗阵容
    def set_lineup(self, lineupId, heroList):
        setLineupAck = ClientProtocol.RequestSetHeroLineup(self.sock, self.userId, lineupId, heroList)
        print "set lineup ack:"
        print setLineupAck
        
def TestClient():
    client = ClientSimulator()
    client.connect_loginserver('127.0.0.1', 8080) 
    client.connect_gameserver('192.168.1.134', 8500)
    
    print "login"
    token = client.login('test', 'pass')
    print "token=" + str(token)
    verify_ret = client.verify_token()
    print "verifytoken=" + str(verify_ret)
    
    client.create_role('testrole')
    client.get_roledata()
    #client.enter_gate(100001)
    #client.finish_gate(100001, 1)
    #client.get_drawlist()
    #client.draw_prize(1)
    client.set_lineup(0, [10001, 10002, 10003, 10004, 10005])
    
TestClient()