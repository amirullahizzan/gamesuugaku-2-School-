#include "Main.h"
#include "Game.h"
#include "Player.h"

#define MOV_SPEED	0.2f
#define ROT_SPEED	2.0f

#define ACCEL_SPEED	0.005f
#define BRAKE_SPEED	0.003f

//---------------------------------------------------------------------------------
//	����������
//---------------------------------------------------------------------------------
void Player::Init(int model)
{
	m_model = model;

	m_pos.set(-25.0f, 0.0f, 0.0f);
	m_rot.y = 0.0f;

	m_mov.set(0.0f, 0.0f, 0.0f);
}
//---------------------------------------------------------------------------------
//	�X�V����
//---------------------------------------------------------------------------------
void Player::Update()
{
	if (CheckHitKey(KEY_INPUT_RIGHT))	m_rot.y += ROT_SPEED;
	if (CheckHitKey(KEY_INPUT_LEFT))		m_rot.y -= ROT_SPEED;

	if (CheckHitKey(KEY_INPUT_UP)) {
		//	�����Ă�������Ɉړ�
		Float3 base(0.0f, 0.0f, ACCEL_SPEED);

		MATRIX mat = MGetRotY(TO_RADIAN(m_rot.y));

		Float3 accel = GetFloat3VTransform(base, mat);
		m_pos += accel;

		if (m_mov.GetLength() > MOV_SPEED)
		{
			m_mov.SetLength(MOV_SPEED);
		}
	}
	else
	{
		float speed = m_mov.GetLength();
		speed -= BRAKE_SPEED;
		speed = max(0.0f,speed);
		m_mov.SetLength(speed);
	}

	m_pos += m_mov;
}
//---------------------------------------------------------------------------------
//	�`�揈��
//---------------------------------------------------------------------------------
void Player::Render()
{
	MV1SetPosition(m_model, VGet(m_pos.x, m_pos.y, m_pos.z));
	MV1SetRotationXYZ(m_model, VGet(TO_RADIAN(m_rot.x), TO_RADIAN(m_rot.y), TO_RADIAN(m_rot.z)));
	MV1DrawModel(m_model);
}
//---------------------------------------------------------------------------------
//	�I������
//---------------------------------------------------------------------------------
void Player::Exit()
{
}
