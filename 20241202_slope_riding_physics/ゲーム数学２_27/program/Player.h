#pragma once

#include "Base.h"

//---------------------------------------------------------------------------------
//	�v���C���[�N���X
//---------------------------------------------------------------------------------
class Player : public Base
{
public:

	//	�W�����v�ړ���
	Float3		m_jump_mov;

	void Init( int model );		//	����������
	void Update( int ground_model );		//	�X�V����
	void Render();		//	�`�揈��
	void Exit();		//	�I������
};
