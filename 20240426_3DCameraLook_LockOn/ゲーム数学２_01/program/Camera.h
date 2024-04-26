#pragma once

#include "Float3.h"

//---------------------------------------------------------------------------------
//	�J�����N���X
//---------------------------------------------------------------------------------
class Camera
{
public:
	Float3		m_pos;
	Float3		m_look;

	void Init();		//	����������
	void Update(Float3 &_playerPos, Float3 &_rot);		//	�X�V����
	void Render();		//	�`�揈��
	void Exit();		//	�I������
};
