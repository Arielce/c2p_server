#ifndef NETWORK_LOBBYPROTOCOL_H
#define NETWORK_LOBBYPROTOCOL_H

/*
	0x9000 - 0xA000 GameServer��DataServerͨ��ʹ�õ�Э��
*/

enum 
{
	// ======================�ͻ���������Ϣ========================
	// ��¼ע�����Э��
	ID_REQ_RequestGameGroup	= 0x0100,			// �ͻ���������Ϸ����

	// ======================��������Ϣ����==========================
	// ������Ϸ���Э��
	ID_ACK_ResponseGameGroup = 0x0100,			// ����������Ϣ


	// ======================GameServer������Ϣ========================
	// ��¼ע�����Э��
	ID_SREQ_SRequestGsReg	= 0xA000,				// GameServerע��

	// ======================��������Ϣ����==========================
	// ������Ϸ���Э��
	ID_SACK_SResponseGsReg	= 0xA000,				// ���ؽ�ɫ����
};

#endif