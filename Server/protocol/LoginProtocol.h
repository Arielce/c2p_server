#ifndef NETWORK_LOGINPROTOCOL_H
#define NETWORK_LOGINPROTOCOL_H

/*
	0xA100 - 0xA200 GameServer��LoginServerAgentͨ��ʹ�õ�Э��
*/

enum 
{
	// ======================GameServer������Ϣ========================
	// ��¼ע�����Э��
	ID_SREQ_SRequestVerifyToken	= 0xA100,				// ������֤Token

	// ======================��������Ϣ����==========================
	// ������Ϸ���Э��
	ID_SACK_SRequestVerifyToken	= 0xA100,				// ����Token��֤���
};

#endif