#pragma once

#include "Base.h"

//---------------------------------------------------------------------------------
//	�v���C���[�N���X
//---------------------------------------------------------------------------------
class Player : public Base
{
public:

	void Init( int model );		//	����������
	void Update();		//	�X�V����
	void Render();		//	�`�揈��
	void Exit();		//	�I������

private: 
	int m_frame;
	Float3 m_mov;
};
