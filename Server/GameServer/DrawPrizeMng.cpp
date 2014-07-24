#include "DrawPrizeMng.h"
#include "../tinyxml/tinyxml.h"
#include "../protocol/GameProtocol.h"
#include "../protocol/GameProtocol.pb.h"
#include "../protocol/ErrorCodes.h"
#include "../network/Utility.h"
#include "Player.h"

DrawPrizeMng::DrawPrizeMng()
{

}

DrawPrizeMng::~DrawPrizeMng()
{
	m_drawConfMap.clear();
	m_drawPrizePoolMap.clear();
}

bool DrawPrizeMng::LoadDrawPrzieConf()
{
	TiXmlDocument xmlDoc;
	if (!xmlDoc.LoadFile("./xml/DrawPrize.xml"))
	{
		return false;
	}

	TiXmlElement* pRoot = xmlDoc.RootElement();
	if (!pRoot)
	{
		return false;
	}

	// 读取奖池信息
	TiXmlElement* pPrizePools = pRoot->FirstChildElement("PrizePools");
	if (!pPrizePools)
	{
		return false;
	}
	TiXmlElement* pPool = pPrizePools->FirstChildElement("PrizePool");
	while (pPool)
	{
		uint32_t uPoolId = boost::lexical_cast<uint32_t>(pPool->Attribute("id"));
		DrawPrizePool prizePool;

		TiXmlElement* pPrize = pPool->FirstChildElement("prize");
		uint32_t uPreProb = 0;
		while (pPrize)
		{
			DrawPrizePool::PrizeConf prizeConf;
			prizeConf.uPrizeId	= boost::lexical_cast<uint32_t>(pPrize->Attribute("id"));
			prizeConf.uPrizeNum = boost::lexical_cast<uint32_t>(pPrize->Attribute("num"));
			prizeConf.uProbability = boost::lexical_cast<uint32_t>(pPrize->Attribute("probability")) + uPreProb;	// 计算累计的概率
			uPreProb = prizeConf.uProbability;
			prizePool.prizeVec.push_back(prizeConf);

			pPrize = pPrize->NextSiblingElement();
		}

		m_drawPrizePoolMap.insert(make_pair(uPoolId, prizePool));
		pPool = pPool->NextSiblingElement();
	} 

	// 读取抽奖信息
	TiXmlElement* pDrawPrize = pRoot->FirstChildElement("DrawPrize");
	if (!pDrawPrize)
	{
		return false;
	}
	TiXmlElement* pDraw = pDrawPrize->FirstChildElement("draw");
	while (pDraw)
	{
		DrawConf drawConf;
		drawConf.eDrawType = (EDrawType)boost::lexical_cast<uint32_t>(pDraw->Attribute("drawType"));
		drawConf.uDrawId = boost::lexical_cast<uint32_t>(pDraw->Attribute("id"));
		drawConf.eCostType = (EDrawCostType)boost::lexical_cast<uint32_t>(pDraw->Attribute("costType"));
		drawConf.uCostNum = boost::lexical_cast<uint32_t>(pDraw->Attribute("costNum"));
		drawConf.uDrawTimes = boost::lexical_cast<uint32_t>(pDraw->Attribute("drawTimes"));
		drawConf.nMaxDrawTimes = boost::lexical_cast<int32_t>(pDraw->Attribute("maxDrawTimes"));
		drawConf.uDeadline = boost::lexical_cast<int32_t>(pDraw->Attribute("deadline"));
		drawConf.uPoolId = boost::lexical_cast<int32_t>(pDraw->Attribute("poolId"));

		m_drawConfMap.insert(make_pair(drawConf.uDrawId, drawConf));
		pDraw = pDraw->NextSiblingElement();
	}

	return true;
}


bool DrawPrizeMng::GetDrawConf(uint32_t uDrawId, DrawConf& drawConf)
{
	map<uint32_t, DrawConf>::iterator drawIt = m_drawConfMap.find(uDrawId);
	if (drawIt == m_drawConfMap.end())
	{
		return false;
	}
	drawConf = drawIt->second;
	return true;
}

bool DrawPrizeMng::GetPrizePool(uint32_t uPoolId, DrawPrizePool& prizePool)
{
	map<uint32_t, DrawPrizePool>::iterator poolIt = m_drawPrizePoolMap.find(uPoolId);
	if (poolIt == m_drawPrizePoolMap.end())
	{
		return false;
	}
	prizePool = poolIt->second;
	return true;
}

vector<uint32_t> DrawPrizeMng::GetDrawList()
{
	vector<uint32_t> drawList;
	map<uint32_t, DrawConf>::iterator drawIt = m_drawConfMap.begin();
	map<uint32_t, DrawConf>::iterator drawItEnd = m_drawConfMap.end();
	for (; drawIt!=drawItEnd; drawIt++)
	{
		drawList.push_back(drawIt->first);
	}
	return drawList;
}

// 玩家进行抽奖
void DrawPrizeMng::Draw(Player* pPlayer, uint32_t uDrawId)
{
	ctos::ResponseDrawPrize drawPrizeAck;

	map<uint32_t, DrawConf>::iterator drawIt = m_drawConfMap.find(uDrawId);
	if (drawIt == m_drawConfMap.end())
	{
		return;
	}

	boost::shared_ptr<DrawPrize> pDrawPrize;
	const DrawConf& drawConf = drawIt->second;
	if (drawConf.eDrawType == DRAW_GOLD_ONCE)
	{
		pDrawPrize = boost::shared_ptr<DrawPrize>(new GoldDrawPrize());
		pDrawPrize->SetCostNum(drawConf.uCostNum);
		pDrawPrize->SetCostType(drawConf.eCostType);
		pDrawPrize->SetDrawTimes(drawConf.uDrawTimes);
		pDrawPrize->SetPoolId(drawConf.uPoolId);
	}
	else if (drawConf.eDrawType == DRAW_GOLD_TEN)
	{
		pDrawPrize = boost::shared_ptr<DrawPrize>(new GoldDrawPrize());
		pDrawPrize->SetCostNum(drawConf.uCostNum);
		pDrawPrize->SetCostType(drawConf.eCostType);
		pDrawPrize->SetDrawTimes(drawConf.uDrawTimes);
		pDrawPrize->SetPoolId(drawConf.uPoolId);
	}
	else
	{
		ERRORLOG("unknow draw type=[" << (uint32_t)drawConf.eDrawType << "], draw id=[" << uDrawId << "]");
		return;
	}

	vector<Goods> prizeList;
	int32_t nError = pDrawPrize->Draw(pPlayer, prizeList);			// 返回抽奖结果
	drawPrizeAck.set_errcode(nError);
	if (nError == ERROR_OP_SUCCESS)									// 抽奖成功
	{
		vector<Goods>::iterator prizeIt = prizeList.begin();
		vector<Goods>::iterator prizeItEnd = prizeList.end();
		for (; prizeIt!=prizeItEnd; prizeIt++)
		{
			ctos::PBDrawPrize* pPBDrawPrize = drawPrizeAck.mutable_prizelist()->Add();
			pPBDrawPrize->set_prizeid(prizeIt->uId);
			pPBDrawPrize->set_prizenum(prizeIt->uNum);
		}
	}

	string strMessage;
	BuildResponseProto<ctos::ResponseDrawPrize>(drawPrizeAck, strMessage, ID_ACK_ReponseDrawPrize);

	pPlayer->SendMsg(strMessage.c_str(), strMessage.size());
	return;
}