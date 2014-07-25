# -*- coding: cp936 -*-

import httplib;
import socket
import time
import struct
import ClientProtocol 
import json
import ClientSimulator


def httplogin(): 
    httpClient = None
    
    try:
        httpClient = httplib.HTTPConnection('127.0.0.1', 8080, timeout=30)
        httpClient.request('GET', '/login?ptname=test&password=pass')
     
        response = httpClient.getresponse()
        print response.status
        print response.reason
        #print response.read()
        
        sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)  
        #sock.connect(('192.168.20.134', 8500))
        sock.connect(('192.168.1.134', 8500))
        
        token = response.read()
        print "token" + token
        jsonDecoder = json.JSONDecoder();
        resp = jsonDecoder.decode(token)
        print resp["token"]
        
        verifyTokenAck = ClientProtocol.RequestVerifyToken(sock, 'test', int(resp["token"]))
        #verifyTokenAck = ClientProtocol.RequestVerifyToken(sock, 'test', int(12222))            #错误的token
        print verifyTokenAck
        
    except Exception, e:
        print e
    finally:
        if httpClient:
            httpClient.close()


def httplogin2():
    print "httplogin2"
    client = ClientSimulator.ClientSimulator()
    client.connect_loginserver('127.0.0.1', 8080) 
    client.connect_gameserver('192.168.1.134', 8500)
    
    print "login"
    token = client.login('test', 'pass')
    print "token=" + str(token)
    verify_ret = client.verify_token()
    print "verifytoken=" + str(verify_ret)
    
    return

httplogin2()