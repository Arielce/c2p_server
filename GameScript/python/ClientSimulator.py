# -*- coding: cp936 -*-

import httplib;
import socket
import time
import struct
import ClientProtocol 
import json

# ģ��ͻ�����Ϊ
class ClientSimulator:
    def __init__(self):
        return
    
    # ���ӵ�½������
    def connect_loginserver(self, ip, port):
        self.httpClient = httplib.HTTPConnection(ip, port, timeout=30)
    
    #����GameServer
    def connect_gameserver(self, ip, port):
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)  
        self.sock.connect((ip, port))
        
    #ע��
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
    
    #��½
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

    #��֤Token
    def verify_token(self):
        verifyTokenAck = ClientProtocol.RequestVerifyToken(self.sock, self.ptname, int(self.token))
        if verifyTokenAck.errCode != 0:
            return False
        return True
    
    