#pragma once

#include "Base.h"

//---------------------------------------------------------------------------------
//	�v���C���[�N���X
//---------------------------------------------------------------------------------
class Player : public Base
{
public:

	//	�ړ��x�N�g���i���̕����ɐi�ށj
	Float3	m_mov;

	void Init( int model );		//	����������
	void Update(float near_length);		//	�X�V����
	void Render();		//	�`�揈��
	void Exit();		//	�I������
};
