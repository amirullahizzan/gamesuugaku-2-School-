#pragma once

#include "Float3.h"

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
	Float3		m_rot;

	void Init();		//	����������
	void Update(Float3& player_pos, Float3& player_rot);		//	�X�V����
	void Render();		//	�`�揈��
	void Exit();		//	�I������
};
