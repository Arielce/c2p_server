#include "ClientHandler.h"
#include "../protocol/GameProtocol.pb.h"
#include "../network/Utility.h"
#include "../protocol/GameProtocol.h"
#include "PlayerMng.h"
#include "GateController.h"
#include "HeroMng.h"
#include "GMCommand.h"
#include "GoodsMng.h"
#include "DrawPrizeMng.h"

void ClientHandler::HandleConnect(IConnection* pConn)
{
	TRACELOG("client connect=[" << pConn << "] ip=[" << pConn->GetRemoteIp() << "], port=[" << pConn->GetRemotePort() << "]");
}

void ClientHandler::HandleDisconnect(IConnection* pConn, const BoostErrCode& error)
{   
	TRACELOG("client " << pConn->GetRemoteIp() << " disconnect ");
	gpPlayerMng->ClientDisconnect(pConn);
}

void ClientHandler::HandleWrite(const boost::system::error_code& error, size_t bytes_transferred) 
{
	if (error)
	{
		ERRORLOG("handle write error, error=[" << boost::system::system_error(error).what() << "]");
	}
}

void ClientHandler::HandleRecv(IConnection* pConn, const char* pBuf, uint32_t uLen)
{
	if (!pBuf || uLen == 0)
	{
		ERRORLOG("message error");
		return;
	}
	
	MessageHeader* pMsgHeader = (MessageHeader*)pBuf;
	switch (pMsgHeader->uMsgCmd)
	{
	case 0x0010:													// 和客户端测试protobuf通信，后面删除
		{
			ctos::RequestTestProto testProtoReq;
			testProtoReq.ParseFromString(GetProtoData(pMsgHeader));
			cout << "test proto, msg=" << testProtoReq.desc() << endl;

			ctos::ResponseTestProto testProtoAck;
			testProtoAck.set_ret(testProtoReq.desc());
			string strMessage;
			BuildResponseProto<ctos::ResponseTestProto>(testProtoAck, strMessage, 0x0010);

			pConn->SendMsg(strMessage.c_str(), strMessage.size());
		}
	case ID_REQ_Test_PingPong:										// 测试使用的ping-pong协议, 简单的将数据包返回
		{
			pConn->SendMsg(pBuf, uLen);
		}
		break;
	case ID_REQ_RequestProcGMCommand:								// 请求执行GM指令
		{
			_RequestGMCommand(pConn, pMsgHeader);
		}
		break;
	case ID_REQ_RequestVerifyToken:									// 请求验证token
	case ID_REQ_RequestCreateRole:									// 请求创建角色
	case ID_REQ_RequestRoleData:									// 请求角色数据
		{
			gpPlayerMng->ProcReq(pConn, pMsgHeader);
		}
		break;
	case ID_REQ_RequestEnterGate:									// 请求进入关卡
		{
			_RequestEnterGate(pConn, pMsgHeader);
		}
		break;
	case ID_REQ_RequestFinishGate:									// 请求结束关卡
		{
			_RequestFinishGate(pConn, pMsgHeader);
		}
		break;
	case ID_REQ_RequestHeroDressEquip:								// 请求给英雄穿戴装备
		{
			_RequestHeroDressEquip(pConn, pMsgHeader);
		}
		break;
	case ID_REQ_RequestUpgradeHero:									// 请求给英雄升级
		{
			_RequestHeroUpgrade(pConn, pMsgHeader);
		}
		break;
	case ID_REQ_RequestCompoundEquip:								// 请求合成装备
		{
			_RequestCompoundEquip(pConn, pMsgHeader);
		}
		break;
	case ID_REQ_RequestDrawPrizeList:								// 请求抽奖列表
		{
			 _RequestDrawPrizeList(pConn, pMsgHeader);
		}
		break;
	case ID_REQ_RequestDrawPrize:									// 请求抽奖
		{
			_RequestDrawPrize(pConn, pMsgHeader);
		}
		break;
	case ID_REQ_RequestSetHeroLineup:								// 请求设置阵容
		{
			_RequestSetHeroLineup(pConn, pMsgHeader);
		}
		break;
	default:
		ERRORLOG("unknown client msg command=[" << hex << pMsgHeader->uMsgCmd << endl);
		break;
	}
}

void ClientHandler::_RequestGMCommand(IConnection* pConn, MessageHeader* pMsgHeader)
{
	if (!pConn || !pMsgHeader)
	{
		return;
	}

	ctos::RequestProcGMCommand gmCommandReq;
	gmCommandReq.ParseFromString(GetProtoData(pMsgHeader));

	Player* pPlayer = gpPlayerMng->GetValidPlayer(gmCommandReq.userid(), pConn);
	if (!pPlayer)
	{
		ERRORLOG("request enter gate, cannot find valid user id=[" << gmCommandReq.userid() << "] in players");
		return;
	}
	
	// to do 检查执行命令的玩家是否有此权限

	GMCommand gmCommand;
	gmCommand.ProcGMCommand(gmCommandReq.command());

	return;
}

// 玩家请求进入关卡
void ClientHandler::_RequestEnterGate(IConnection* pConn, MessageHeader* pMsgHeader)
{
	if (!pConn || !pMsgHeader)
	{
		return;
	}
	ctos::RequestEnterGate enterGateReq;
	enterGateReq.ParseFromString(GetProtoData(pMsgHeader));

	Player* pPlayer = gpPlayerMng->GetValidPlayer(enterGateReq.userid(), pConn);
	if (!pPlayer)
	{
		ERRORLOG("request enter gate, cannot find user id=[" << enterGateReq.userid() << "] in players");
		return;
	}

	gpGateController->EnterGate(pPlayer, enterGateReq.gateid());
	return;
}

// 玩家请求结束关卡
void ClientHandler::_RequestFinishGate(IConnection* pConn, MessageHeader* pMsgHeader)
{      
	if (!pConn || !pMsgHeader)
	{
		return;
	}

	ctos::RequestFinishGate finishGateReq;
	finishGateReq.ParseFromString(GetProtoData(pMsgHeader));

	Player* pPlayer = gpPlayerMng->GetValidPlayer(finishGateReq.userid(), pConn);
	if (!pPlayer)
	{
		ERRORLOG("cannot find user id=" << finishGateReq.userid() << "in players");
		return;
	}

	gpGateController->FinishGate(pPlayer, finishGateReq.gateid(), finishGateReq.result());
	return;
}

// 请求给英雄穿装备
void ClientHandler::_RequestHeroDressEquip(IConnection* pConn, MessageHeader* pMsgHeader)
{
	if (!pConn || !pMsgHeader)
	{
		return;
	}

	ctos::RequestHeroDressEquip dressEquipReq;
	dressEquipReq.ParseFromString(GetProtoData(pMsgHeader));

	Player* pPlayer = gpPlayerMng->GetValidPlayer(dressEquipReq.userid(), pConn);
	if (!pPlayer)
	{
		ERRORLOG("cannot find user id=[" << dressEquipReq.userid() << "]");
		return;
	}
	
	int32_t nErrCode = gpHeroMng->HeroDressEquip(pPlayer, dressEquipReq.heroid(), dressEquipReq.equipid());

	ctos::ResponseHeroDressEquip dressEquipAck;
	dressEquipAck.set_errcode(nErrCode);
	string strMessage;
	BuildResponseProto<ctos::ResponseHeroDressEquip>(dressEquipAck, strMessage, ID_ACK_ResponseHeroDressEquip);

	pConn->SendMsg(strMessage.c_str(), strMessage.size());
	return;
}

// 请求英雄品质提升
void ClientHandler::_RequestHeroUpgrade(IConnection* pConn, MessageHeader* pMsgHeader)
{
	if (!pConn || !pMsgHeader)
	{
		return;
	}

	ctos::RequestUpgradeHero upgradeHeroReq;
	upgradeHeroReq.ParseFromString(GetProtoData(pMsgHeader));

	Player* pPlayer = gpPlayerMng->GetValidPlayer(upgradeHeroReq.userid(), pConn);
	if (!pPlayer)
	{
		ERRORLOG("cannot find user id=[" << upgradeHeroReq.userid() << "]");
		return;
	}

	int32_t nErrCode = gpHeroMng->HeroUpgrade(pPlayer, upgradeHeroReq.heroid());

	ctos::ResponseHeroDressEquip upgradeHeroAck;
	upgradeHeroAck.set_errcode(nErrCode);
	string strMessage;
	BuildResponseProto<ctos::ResponseHeroDressEquip>(upgradeHeroAck, strMessage, ID_ACK_ResponseUpgradeHero);

	pConn->SendMsg(strMessage.c_str(), strMessage.size());
	return;
}

// 请求合成装备
void ClientHandler::_RequestCompoundEquip(IConnection* pConn, MessageHeader* pMsgHeader)
{
	if (!pConn || !pMsgHeader)
	{
		return;
	}

	ctos::RequestCompoundEquip compoundEquipReq;
	compoundEquipReq.ParseFromString(GetProtoData(pMsgHeader));

	Player* pPlayer = gpPlayerMng->GetValidPlayer(compoundEquipReq.userid(), pConn);
	if (!pPlayer)
	{
		ERRORLOG("cannot find user id=[" << compoundEquipReq.userid() << "]");
		return;
	}

	int32_t nErrCode = gpGoodsMng->CompoundEquip(pPlayer, compoundEquipReq.targetequipid());
	
	// 合成装备返回
	ctos::ResponseCompoundEquip compoundEquipAck;
	compoundEquipAck.set_errcode(nErrCode);

	string strMessage;
	BuildResponseProto<ctos::ResponseCompoundEquip>(compoundEquipAck, strMessage, ID_ACK_ResponseCompoundEquip);

	pConn->SendMsg(strMessage.c_str(), strMessage.size());
	return;
}

// 请求抽奖列表
void ClientHandler::_RequestDrawPrizeList(IConnection* pConn, MessageHeader* pMsgHeader)
{
	if (!pConn || !pMsgHeader)
	{
		return;
	}
	
	ctos::RequestDrawPrizeList prizeListReq;
	prizeListReq.ParseFromString(GetProtoData(pMsgHeader));

	Player* pPlayer = gpPlayerMng->GetValidPlayer(prizeListReq.userid(), pConn);
	if (!pPlayer)
	{
		ERRORLOG("cannot find user id=[" << prizeListReq.userid() << "]");
		return;
	}

	// 获取抽奖列表
	vector<uint32_t> drawList = gpDrawPrizeMng->GetDrawList();
	ctos::ResponseDrawPrizeList prizeListAck;

	vector<uint32_t>::iterator drawIt = drawList.begin();
	vector<uint32_t>::iterator drawItEnd = drawList.end();
	for (; drawIt != drawItEnd; drawIt++)
	{
		prizeListAck.mutable_drawlist()->Add(*drawIt);
	}
	string strMessage;
	BuildResponseProto<ctos::ResponseDrawPrizeList>(prizeListAck, strMessage, ID_ACK_ResponseDrawPrizeList);

	pConn->SendMsg(strMessage.c_str(), strMessage.size());
	return;
}

// 请求抽奖
void ClientHandler::_RequestDrawPrize(IConnection* pConn, MessageHeader* pMsgHeader)
{
	if (!pConn || !pMsgHeader)
	{
		return;
	}

	ctos::RequestDrawPrize drawPrizeReq;
	drawPrizeReq.ParseFromString(GetProtoData(pMsgHeader));

	Player* pPlayer = gpPlayerMng->GetValidPlayer(drawPrizeReq.userid(), pConn);
	if (!pPlayer)
	{
		ERRORLOG("cannot find user id=[" << drawPrizeReq.userid() << "]");
		return;
	}

	gpDrawPrizeMng->Draw(pPlayer, drawPrizeReq.drawid());
	return;
}

// 设置英雄阵容
void ClientHandler::_RequestSetHeroLineup(IConnection* pConn, MessageHeader* pMsgHeader)
{
	if (!pConn || !pMsgHeader)
	{
		return;
	}

	ctos::RequestSetHeroLineup setLineupReq;
	setLineupReq.ParseFromString(GetProtoData(pMsgHeader));

	Player* pPlayer = gpPlayerMng->GetValidPlayer(setLineupReq.userid(), pConn);
	if (!pPlayer)
	{
		ERRORLOG("cannot find user id=[" << setLineupReq.userid() << "]");
		return;
	}

	vector<uint32_t> heroList;
	uint32_t uHeroNum = setLineupReq.heroid_size();
	for (uint32_t i=0; i<uHeroNum; i++)
	{
		heroList.push_back(setLineupReq.heroid(i));
	}

	// 设置英雄阵容
	ctos::ResponseSetHeroLineup setLineupAck;
	int32_t uErrorCode = gpHeroMng->SetHeroLineup(pPlayer, setLineupReq.lineupid(), heroList);
	setLineupAck.set_errcode(uErrorCode);

	string strMessage;
	BuildResponseProto<ctos::ResponseSetHeroLineup>(setLineupAck, strMessage, ID_ACK_ResponseSetHeroLineup);

	pConn->SendMsg(strMessage.c_str(), strMessage.size());
	return;
}