#pragma once

#include "Float3.h"

enum {
	TYPE_NORMAL,	//	�T���v���Ŏ��������J����
	TYPE_FRONT,		//	�v���C���[����O�E�m�o�b�����ɂȂ�悤�ȃJ����
	TYPE_LEFT,		//	�v���C���[�����E�m�o�b���E�ɂȂ�悤�ȃJ����
};

//---------------------------------------------------------------------------------
//	�J�����N���X
//---------------------------------------------------------------------------------
class Camera
{
public:
	//	�J�������W
	Float3		m_pos;
	//	������W
	Float3		m_look;

	//	�J�����^�C�v
	int			m_type;

	void Init();		//	����������

	//	�v���C���[�Ƃm�o�b�̍��W�����炦��悤�Ɉ�����ǉ�
	void Update( Float3 &player_pos, Float3 &npc_pos );		//	�X�V����

	void Render();		//	�`�揈��
	void Exit();		//	�I������
};
