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
	case 0x0010:													// �Ϳͻ��˲���protobufͨ�ţ�����ɾ��
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
	case ID_REQ_Test_PingPong:										// ����ʹ�õ�ping-pongЭ��, �򵥵Ľ����ݰ�����
		{
			pConn->SendMsg(pBuf, uLen);
		}
		break;
	case ID_REQ_RequestProcGMCommand:								// ����ִ��GMָ��
		{
			_RequestGMCommand(pConn, pMsgHeader);
		}
		break;
	case ID_REQ_RequestVerifyToken:									// ������֤token
	case ID_REQ_RequestCreateRole:									// ���󴴽���ɫ
	case ID_REQ_RequestRoleData:									// �����ɫ����
		{
			gpPlayerMng->ProcReq(pConn, pMsgHeader);
		}
		break;
	case ID_REQ_RequestEnterGate:									// �������ؿ�
		{
			_RequestEnterGate(pConn, pMsgHeader);
		}
		break;
	case ID_REQ_RequestFinishGate:									// ��������ؿ�
		{
			_RequestFinishGate(pConn, pMsgHeader);
		}
		break;
	case ID_REQ_RequestHeroDressEquip:								// �����Ӣ�۴���װ��
		{
			_RequestHeroDressEquip(pConn, pMsgHeader);
		}
		break;
	case ID_REQ_RequestUpgradeHero:									// �����Ӣ������
		{
			_RequestHeroUpgrade(pConn, pMsgHeader);
		}
		break;
	case ID_REQ_RequestCompoundEquip:								// ����ϳ�װ��
		{
			_RequestCompoundEquip(pConn, pMsgHeader);
		}
		break;
	case ID_REQ_RequestDrawPrizeList:								// ����齱�б�
		{
			 _RequestDrawPrizeList(pConn, pMsgHeader);
		}
		break;
	case ID_REQ_RequestDrawPrize:									// ����齱
		{
			_RequestDrawPrize(pConn, pMsgHeader);
		}
		break;
	case ID_REQ_RequestSetHeroLineup:								// ������������
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
	
	// to do ���ִ�����������Ƿ��д�Ȩ��

	GMCommand gmCommand;
	gmCommand.ProcGMCommand(gmCommandReq.command());

	return;
}

// ����������ؿ�
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

// �����������ؿ�
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

// �����Ӣ�۴�װ��
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

// ����Ӣ��Ʒ������
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

// ����ϳ�װ��
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
	
	// �ϳ�װ������
	ctos::ResponseCompoundEquip compoundEquipAck;
	compoundEquipAck.set_errcode(nErrCode);

	string strMessage;
	BuildResponseProto<ctos::ResponseCompoundEquip>(compoundEquipAck, strMessage, ID_ACK_ResponseCompoundEquip);

	pConn->SendMsg(strMessage.c_str(), strMessage.size());
	return;
}

// ����齱�б�
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

	// ��ȡ�齱�б�
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

// ����齱
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

// ����Ӣ������
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

	// ����Ӣ������
	ctos::ResponseSetHeroLineup setLineupAck;
	int32_t uErrorCode = gpHeroMng->SetHeroLineup(pPlayer, setLineupReq.lineupid(), heroList);
	setLineupAck.set_errcode(uErrorCode);

	string strMessage;
	BuildResponseProto<ctos::ResponseSetHeroLineup>(setLineupAck, strMessage, ID_ACK_ResponseSetHeroLineup);

	pConn->SendMsg(strMessage.c_str(), strMessage.size());
	return;
}