#include "header.h"
#include "DataThread.h"
#include "../protocol/RoleData.pb.h"
#include "../protocol/DataServer.pb.h"
#include "../protocol/DataProtocol.h"
#include "ServerConfig.h"

DataThread::DataThread()
{
	
}

bool DataThread::Init()
{
	m_playerDataMng.SetMysqlInfo(gpServerConfig->GetMysqlIp().c_str(), gpServerConfig->GetMysqlPort(), gpServerConfig->GetMysqlUser().c_str(), gpServerConfig->GetMysqlPwd().c_str(), gpServerConfig->GetMysqlDB().c_str());
	if (!m_playerDataMng.Init())
	{
		return false;
	}
	return true;
}

void DataThread::Push(const char* pBuf, int nLen)
{
	boost::lock_guard<boost::mutex> lock(m_mutex);
	m_msgQueue.push_back(string(pBuf, nLen));
	m_cond.notify_one();
}

void DataThread::Run()
{
	while (true)
	{
		string strMsg;
		{
			boost::lock_guard<boost::mutex> lock(m_mutex);
			if (m_msgQueue.empty())
			{
				m_cond.wait(m_mutex);
			}

			strMsg = m_msgQueue.front();
			m_msgQueue.pop_front();
		}

		if (strMsg.size() == 0)
		{
			ERRORLOG("error message info!!");
			break;
		}

		MessageHeader* pMsgHeader = (MessageHeader*)strMsg.c_str();
		switch (pMsgHeader->uMsgCmd)
		{
		case ID_SREQ_SRequestCreateRole:				// 请求创建角色数据
			{
				try
				{
					gtod::SRequestCreateRole createRoleReq;
					createRoleReq.ParseFromString(GetProtoData(pMsgHeader));
					m_playerDataMng.CreateRole(createRoleReq.ptname(), createRoleReq.rolename());
				}
				catch (google::protobuf::FatalException fe)
				{
					ERRORLOG("protobuf excetpion error=[" << fe.message() << "]");
				}
			}
			break;
		case ID_SREQ_SRequestGetRoleData:				// 请求角色数据
			{
				try
				{
					gtod::SRequestRoleData roleDataReq;
					roleDataReq.ParseFromString(GetProtoData(pMsgHeader));
					m_playerDataMng.GetPlayerData(roleDataReq.ptname());

				}
				catch (google::protobuf::FatalException fe)
				{
					ERRORLOG("protobuf excetpion error=[" << fe.message() << "]");
				}
			}
			break;
		case ID_SREQ_SRequestSaveRoleData:				// 获取角色数据
			{
				try
				{
					gtod::SRequestSaveRoleData saveRoleData;
					saveRoleData.ParseFromString(GetProtoData(pMsgHeader));
					m_playerDataMng.SavePlayerData(saveRoleData.ptname(), saveRoleData.roledata());
				}
				catch (google::protobuf::FatalException fe)
				{
					ERRORLOG("protobuf excetpion error=[" << fe.message() << "]");
				}
			}
			break;
		case ID_SREQ_SRequestRoleDataVersion:			// 获取角色数据版本
			{
				gtod::SRequestRoleDataVersion dataVersionReq;
				dataVersionReq.ParseFromString(GetProtoData(pMsgHeader));
				m_playerDataMng.GetDataVersion(dataVersionReq.ptname());
			}
			break;
		default:
			ERRORLOG("unknown msg cmd=[0x" << hex << pMsgHeader->uMsgCmd << "]");
			break;
		}
	}
}