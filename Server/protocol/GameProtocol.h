#ifndef NETWORK_GAMEPROTOCOL_H
#define NETWORK_GAMEPROTOCOL_H

/*
	0x0000 - 0x8000 �ͻ��˺�LobbyCenter��GameServer֮��ͨ��ʹ�õ�Э��ŷ�Χ
*/

enum 
{
	// ======================�ͻ���������Ϣ========================
	// ����ʹ�õ�ping-pongЭ��
	ID_REQ_Test_PingPong			= 0x0001,

	// ��¼ע�����Э��
	ID_REQ_Lobby_RequestGameGroups	= 0x0100,		// �û����������б�

	ID_REQ_Lobby_RequestLogin		= 0x0200,		// �û���¼����
	ID_REQ_Lobby_RequestRegister,					// �û�����ע��
	ID_REQ_Lobby_RequestBindEmail,					// �û����������
	ID_REQ_Lobby_RequestChangePwd,					// �û������޸�����
	ID_REQ_Lobby_RequestFindPasswd,					// �û����������һ�

	// ����ִ��GMָ��
	ID_REQ_RequestProcGMCommand		= 0x0900,		// ����ִ��GMָ��
	ID_REQ_RequestVerifyToken,						// ��֤token

	// ������Ϸ���Э��
	ID_REQ_RequestLoginGame			= 0x1000,		// �ͻ������������Ϸ
	ID_REQ_RequestCreateRole,						// ���󴴽���ɫ
	ID_REQ_RequestRoleData,							// �����ɫ����

	// �ؿ���ز���
	ID_REQ_RequestEnterGate			= 0x1100,		// ����������ؿ�
	ID_REQ_RequestFinishGate,						// ��������ؿ�

	// װ����ز���
	ID_REQ_RequestHeroDressEquip	= 0x1200,		// �������Ӣ�۴�װ��
	ID_REQ_RequestUpgradeHero,						// �������Ӣ������
	ID_REQ_RequestCompoundEquip,					// �������ϳ�װ��

	// �齱��ز���
	ID_REQ_RequestDrawPrizeList		= 0x1300,		// ����齱�б�
	ID_REQ_RequestDrawPrize,						// ����齱

	// ======================��������Ϣ����==========================
	// ����ִ��GMָ��
	ID_ACK_ResponseProcGMCommand	= 0x0900,		// ����ִ��GMָ��
	ID_ACK_ResponseVerifyToken,						// ��֤token

	// ������Ϸ���Э��
	ID_ACK_ResponseLoginGame		= 0x1000,		// ���ؿͻ��˽�����Ϸ���
	ID_ACK_ResponseCreateRole,
	ID_ACK_ResponseRoleData,						// ���ؽ�ɫ���� 

	ID_ACK_ResponseEnterGate		= 0x1100,		// ����������ؿ�
	ID_ACK_ResponseFinishGate,						// ��������ؿ�

	// װ����ز���
	ID_ACK_ResponseHeroDressEquip	= 0x1200,		// �������Ӣ�۴�װ��
	ID_ACK_ResponseUpgradeHero,						// �������Ӣ������
	ID_ACK_ResponseCompoundEquip,					// �������ϳ�װ��

	// �齱��ز���
	ID_ACK_ResponseDrawPrizeList	= 0x1300,		// ����齱�б�
	ID_ACK_ReponseDrawPrize,						// ����齱


	// ======================������֪ͨ��Ϣ==========================
	// �㲥ר��Э��
	ID_NTY_NotifyBroadcast			= 0x8000,		// ���ڹ㲥��Ϣ��Э��

	// ��ɫ�������
	ID_NTY_NotifyRoleLevelUp		= 0x9000,		// ֪ͨ�������
};

#endif