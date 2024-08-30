#include "Main.h"
#include "Game.h"
#include "Camera.h"

//	�J�����̌�����W����J�������W�܂ł̋���
#define CAMERA_LENGTH		10.0f
//	�J�����𓮂������߂̊�̊p�x�̉�]���x
#define CAMERA_ROT_SPEED	1.0f

//---------------------------------------------------------------------------------
//	����������
//---------------------------------------------------------------------------------
void Camera::Init()
{
	m_pos.set(0.0f, 20.0f, -30.0f);
	m_look.set(0.0f, 0.0f, 0.0f);
}
//---------------------------------------------------------------------------------
//	�X�V����
//---------------------------------------------------------------------------------
void Camera::Update(Float3& player_pos, Float3& player_rot)
{

	auto base = Float3{ 0,3.0f,-CAMERA_LENGTH };


	if (CheckHitKey(KEY_INPUT_A))
	{
		m_rot.y -= CAMERA_ROT_SPEED;
	}
	if (CheckHitKey(KEY_INPUT_D))
	{
		m_rot.y += CAMERA_ROT_SPEED;
	}

	if (CheckHitKey(KEY_INPUT_W))
	{
		m_rot.x += CAMERA_ROT_SPEED;
	}
	if (CheckHitKey(KEY_INPUT_S))
	{
		m_rot.x -= CAMERA_ROT_SPEED;
	}

	//player_pos_offset.
	{
		//MATRIX player_mat_x = MGetRotX(TO_RADIAN(player_rot.y));
		//Float3 back_pos = GetFloat3VTransform(base, player_mat_x);
		if (PushHitKey(KEY_INPUT_SPACE))
		{
			m_rot.y = player_rot.y;
		}
	}


	MATRIX mat_x = MGetRotX(TO_RADIAN(m_rot.x));
	MATRIX mat_y = MGetRotY(TO_RADIAN(m_rot.y));
	MATRIX mat = MMult(mat_x, mat_y);

	Float3 endPos = player_pos + GetFloat3VTransform(base, mat);

	m_pos = endPos;
	m_look = player_pos;

	//Float3 player_pos_offset = player_pos;
}
//---------------------------------------------------------------------------------
//	�`�揈��
//---------------------------------------------------------------------------------
void Camera::Render()
{
	//	�J�������W�Ƃ݂���W��n���ăJ�����ݒ�
	SetCameraPositionAndTarget_UpVecY(VGet(m_pos.x, m_pos.y, m_pos.z), VGet(m_look.x, m_look.y, m_look.z));
}
//---------------------------------------------------------------------------------
//	�I������
//---------------------------------------------------------------------------------
void Camera::Exit()
{
}
