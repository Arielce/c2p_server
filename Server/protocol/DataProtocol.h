#ifndef NETWORK_DATAPROTOCOL_H
#define NETWORK_DATAPROTOCOL_H

/*
	0x9000 - 0xA000 GameServer��DataServerͨ��ʹ�õ�Э��
*/

enum 
{
	// ======================�ͻ���������Ϣ========================
	// ��¼ע�����Э��
	ID_SREQ_SRequestCreateRole = 0x9000,		// ���󴴽���ɫ
	ID_SREQ_SRequestGetRoleData	,				// �����ɫ����
	ID_SREQ_SRequestSaveRoleData,				// ���󱣴��ɫ����
	ID_SREQ_SRequestRoleDataVersion,			// �������ݰ汾

	// ======================��������Ϣ����==========================
	// ������Ϸ���Э��
	ID_SACK_SResponseCreateRole = 0x9000,		// ���ش�����ɫ���
	ID_SACK_SResponseGetRoleData,				// ���ؽ�ɫ����
	ID_SACK_SResponseSaveRoleData,				// ���ر������ݽ��
	ID_SACK_SResponseRoleDataVersion,			// �������ݰ汾
};

#endif