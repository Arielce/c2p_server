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

    #验证Token
    def verify_token(self):
        verifyTokenAck = ClientProtocol.RequestVerifyToken(self.sock, self.ptname, int(self.token))
        if verifyTokenAck.errCode != 0:
            return False
        return True
    
    