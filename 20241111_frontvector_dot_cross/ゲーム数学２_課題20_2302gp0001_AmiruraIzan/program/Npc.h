#pragma once

#include "Base.h"

//---------------------------------------------------------------------------------
//	�m�o�b�N���X
//---------------------------------------------------------------------------------
class Npc : public Base
{
public:

	void Init( int model );		//	����������
	void Update(Float3& player_pos, Float3& camera_rot);
	void Render();		//	�`�揈��
	void Exit();		//	�I������

private:
	int m_frame = 0;
};
