#pragma once

#include "Base.h"

//---------------------------------------------------------------------------------
//	�v���C���[�N���X
//---------------------------------------------------------------------------------
class Player : public Base
{
public:
	Float3 m_dash;
	void Init( int model );		//	����������
	void Update();		//	�X�V����
	void Render();		//	�`�揈��
	void Exit();		//	�I������

private:
	float perspective = 45.0f;
};
