#pragma once

#include "Float3.h"

enum {
	TYPE_STAGE,
	TYPE_PLAYER,

	TYPE_FOLLOW,
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
	void Update( Float3 &player_pos, Float3 &player_rot, Float3 &player_mov );		//	�X�V����
	void Render();		//	�`�揈��
	void Exit();		//	�I������
};
