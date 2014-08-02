# -*- coding: cp936 -*-
import socket
import time
import struct
import GameProtocol_pb2
import ServerCmd_pb2

# 请求停止服务器
def RequestStopServer(sock, serverId):
    stopServerReq = ServerCmd_pb2.RequestStopServer()
    stopServerReq.serverId = serverId
    body = stopServerReq.SerializeToString()
    header = struct.pack('iii', 12+len(body), 0xA001, 0xA1B2C3D4)
    sock.send(header+body)

# 请求重载配置
def RequestReload(sock, fileName):
    reloadReq = ServerCmd_pb2.RequestReloadConf()
    reloadReq.confFile = fileName
    
    body = reloadReq.SerializeToString()
    header = struct.pack('iiI', 12+len(body), 0xA002, 0xA1B2C3D4)
    sock.send(header+body)
    pbstr = sock.recv(1024)
    reloadAck = ServerCmd_pb2.ResponseReloadConf()
    try:
        reloadAck.ParseFromString(str(pbstr[12:]))           
    except Exception as e:
        print e
    return reloadAck

# 请求区组列表
def RequestGameGroup(sock):
    gameGroupReq = GameProtocol_pb2.RequestGameGroups()
    gameGroupReq.clientType = 0
    body = gameGroupReq.SerializeToString()
    header = struct.pack('iiI', 12+len(body), 0x0100, 0xA1B2C3D4)
    sock.send(header+body)
    
    pbstr = sock.recv(1024)
    gameGroupAck = GameProtocol_pb2.ResponseGameGroups()
    try:
        gameGroupAck.ParseFromString(str(pbstr[12:]))           
    except Exception as e:
        print e
    return gameGroupAck

# 请求创建角色
def RequestCreateRole(sock, ptname, rolename):
    createRoleReq = GameProtocol_pb2.RequestCreateRole()
    createRoleReq.ptName = ptname
    createRoleReq.roleName = rolename
    body = createRoleReq.SerializeToString()
    header = struct.pack('iiI', 12+len(body), 0x1001, 0xA1B2C3D4)
    sock.send(header+body)
    
    pbstr = sock.recv(1024)
    createRoleAck = GameProtocol_pb2.ResponseCreateRole()
    try:
        createRoleAck.ParseFromString(str(pbstr[12:]))           
    except Exception as e:
        print e
    return createRoleAck

# 请求角色数据
def RequestRoleData(sock, ptname):
    roleDataReq = GameProtocol_pb2.RequestRoleData()
    roleDataReq.ptName = ptname
    body = roleDataReq.SerializeToString()
    header = struct.pack('iiI', 12+len(body), 0x1002, 0xA1B2C3D4)
    sock.send(header+body)
    pbstr = sock.recv(1024)
    roleDataAck = GameProtocol_pb2.ResponseRoleData()
    try:
        roleDataAck.ParseFromString(str(pbstr[12:]))           
    except Exception as e:
        print e
    return roleDataAck

# 请求验证玩家token
def RequestVerifyToken(sock, ptname, token):
    verifyTokenReq = GameProtocol_pb2.RequestVerifyToken()
    verifyTokenReq.ptName = ptname
    verifyTokenReq.token = token
    
    body = verifyTokenReq.SerializeToString()
    header = struct.pack('iiI', 12+len(body), 0x0901, 0xA1B2C3D4)
    sock.send(header+body)
    pbstr = sock.recv(1024)
    verifyTokenAck = GameProtocol_pb2.ResponseVerifyToken()
    try:
        verifyTokenAck.ParseFromString(str(pbstr[12:]))           
    except Exception as e:
        print e
    return verifyTokenAck

# 请求进入关卡
def RequestEnterGate(sock, userId, gateId):
    enterGateReq = GameProtocol_pb2.RequestEnterGate()
    enterGateReq.userId = userId
    enterGateReq.gateId = gateId
    body = enterGateReq.SerializeToString()
    header = struct.pack('iiI', 12+len(body), 0x1100, 0xA1B2C3D4)
    sock.send(header+body)
    
    pbstr = sock.recv(1024)
    enterGateAck = GameProtocol_pb2.ResponseEnterGate()
    try:
        enterGateAck.ParseFromString(str(pbstr[12:]))           
    except Exception as e:
        print e
    return enterGateAck

# 请求关卡奖励
def RequestFinishGate(sock, userId, gateId, result):
    finishGateReq = GameProtocol_pb2.RequestFinishGate()
    finishGateReq.userId = userId
    finishGateReq.gateId = gateId
    finishGateReq.result = result
    body = finishGateReq.SerializeToString()
    header = struct.pack('iiI', 12+len(body), 0x1101, 0xA1B2C3D4)
    sock.send(header+body)
    
    pbstr = sock.recv(1024)
    finishGateAck = GameProtocol_pb2.ResponseFinishiGate()
    try:
        finishGateAck.ParseFromString(str(pbstr[12:]))           
    except Exception as e:
        print e
    return finishGateAck

# 请求抽奖列表
def RequestDrawList(sock, userId):
    drawListReq = GameProtocol_pb2.RequestDrawPrizeList()
    drawListReq.userId = userId
    body = drawListReq.SerializeToString()
    header = struct.pack('iiI', 12+len(body), 0x1300, 0xA1B2C3D4)
    sock.send(header+body)
   
    pbstr = sock.recv(1024)
    
    drawListAck = GameProtocol_pb2.ResponseDrawPrizeList()
    try:
        drawListAck.ParseFromString(str(pbstr[12:]))           
    except Exception as e:
        print e
    return drawListAck

# 请求抽奖
def RequestDrawPrize(sock, userId, drawId):
    drawPrizeReq = GameProtocol_pb2.RequestDrawPrize()
    drawPrizeReq.userId = userId
    drawPrizeReq.drawId = drawId
    body = drawPrizeReq.SerializeToString()
    header = struct.pack('iiI', 12+len(body), 0x1301, 0xA1B2C3D4)
    sock.send(header+body)
   
    pbstr = sock.recv(1024)
    
    drawPrizeAck = GameProtocol_pb2.ResponseDrawPrize()
    try:
        drawPrizeAck.ParseFromString(str(pbstr[12:]))           
    except Exception as e:
        print e
    return drawPrizeAck

# 设置战斗阵容
def RequestSetHeroLineup(sock, userId, lineupId, heroList):
    setLineupReq = GameProtocol_pb2.RequestSetHeroLineup()
    setLineupReq.userId = userId
    setLineupReq.lineupId = lineupId
    for h in heroList:
        setLineupReq.heroId.append(h)
    body = setLineupReq.SerializeToString()
    header = struct.pack('iiI', 12+len(body), 0x1400, 0xA1B2C3D4)
    sock.send(header+body)
    
    pbstr = sock.recv(1024)
    
    setLineupAck = GameProtocol_pb2.ResponseSetHeroLineup()
    try:
        setLineupAck.ParseFromString(str(pbstr[12:]))           
    except Exception as e:
        print e
    return setLineupAck
