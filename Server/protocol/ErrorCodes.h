#ifndef NETWORK_ERRORCODES_H
#define NETWORK_ERRORCODES_H

/*
	0x0000 - 0x8000 �ͻ��˺�LobbyCenter��GameServer֮��ͨ��ʹ�õ�Э��ŷ�Χ
*/

enum 
{
	ERROR_OP_SUCCESS			= 0,		// �ɹ�

	// ϵͳ�����
	ERROR_RELOAD_CONFIGURE_FAIL,			// ��������ʧ��

	// ��ɫ�����
	ERROR_PTNAME_HAS_CREATE_ROLE,			// �Ѿ���������ɫ��
	ERROR_ROLENAME_EXIST,					// ��ɫ���Ѿ�����
	ERROR_PLAYER_NOT_FOUND,					// ��Ҳ�����
	ERROR_VERIFY_TOKEN_FAIL,				// ��֤tokenʧ��

	// ��Ǯ�����
	ERROR_GOLD_NOT_ENOUGH,					// ��Ҳ���
	ERROR_DIAMOND_NOT_ENOUGH,				// ��ʯ����
	
	// װ�������
	ERROR_HERO_LEVEL_NOT_ENOUGH,			// �ȼ�����
	ERROR_EQUIP_NOT_EXIST,					// װ��������
	ERROR_EQUIP_NOT_ENOUGHT,				// װ������
	ERROR_COMPOUND_TARGET_NOT_EXIST,		// �ϳ�װ��Ŀ�겻����

	// Ӣ�������
	ERROR_HERO_NOT_EXIST,					// Ӣ�۲�����

	// �ؿ������
	ERROR_PLAYER_CAN_NOT_ENTER,				// ��Ҳ��ܽ���ָ���ؿ�
	ERROR_PLAYER_NEVER_ENTER,				// ���û�н�����ιؿ�

	// �齱�����
	ERROR_DRAW_CONF_NOT_EXIST,				// �˳齱��Ϣ������
	ERROR_DRAW_COST_NOT_ENOUGH,				// �齱���Ĳ���
	ERROR_DRAW_DEADLINE,					// �齱��Ϣ����
	ERROR_DRAW_MAX_TIMES,					// �Ѿ��ﵽ���齱����
};

#endif