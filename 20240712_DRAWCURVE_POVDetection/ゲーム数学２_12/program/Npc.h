#pragma once

#include "Base.h"

//---------------------------------------------------------------------------------
//	�m�o�b�N���X
//---------------------------------------------------------------------------------
class Npc : public Base
{
public:

	void Init( int image );		//	����������
	void Update( Float2 &target_pos );	//	�X�V����
	void Render();		//	�`�揈��
	void Exit();		//	�I������
};
