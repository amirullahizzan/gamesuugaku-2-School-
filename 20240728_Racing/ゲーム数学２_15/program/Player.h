#pragma once

#include "Base.h"

//---------------------------------------------------------------------------------
//	�v���C���[�N���X
//---------------------------------------------------------------------------------
class Player : public Base
{
public:

	Float3	m_mov;

	void Init( int model );		//	����������
	void Update();		//	�X�V����
	void Render();		//	�`�揈��
	void Exit();		//	�I������
};
