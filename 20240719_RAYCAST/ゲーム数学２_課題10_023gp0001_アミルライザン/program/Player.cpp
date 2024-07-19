#include "Main.h"
#include "Game.h"
#include "Player.h"

//	�ړ��X�s�[�h
#define PLAYER_MOV_SPEED	0.2f
//	��]�X�s�[�h�i�x�j
#define PLAYER_ROT_SPEED	3.0f

//---------------------------------------------------------------------------------
//	����������
//---------------------------------------------------------------------------------
void Player::Init( int model )
{
	m_model = model;

	m_pos.x		= -5.0f;
	m_pos.z		= -5.0f;
}
//---------------------------------------------------------------------------------
//	�X�V����
//---------------------------------------------------------------------------------
void Player::Update()
{
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		m_length += 3.0f;
	}
	else
	{
		m_length -= 3.0f;

		if (CheckHitKey(KEY_INPUT_RIGHT))	m_rot.y += PLAYER_ROT_SPEED;
		if (CheckHitKey(KEY_INPUT_LEFT))		m_rot.y -= PLAYER_ROT_SPEED;

		//	��L�[�Ō����Ă�������Ɉړ�
		if (CheckHitKey(KEY_INPUT_UP)) {
			//	���x�N�g�����쐬
			Float3 base(0.0f, 0.0f, PLAYER_MOV_SPEED);
			//	�x����]�s����쐬
			MATRIX mat = MGetRotY(TO_RADIAN(m_rot.y));
			//	���x�N�g�������̍s��ŕϊ����Ĉړ��x�N�g���쐬
			Float3 mov  = VTransform(base.VGet(), mat);
			//	���̈ړ��x�N�g���ō��W�ړ�
			m_pos += mov;
		}
	}

	m_length = max(0.0f,min(m_length, 20.0f));

	Float3 base(0.0f,0.0f,m_length);

	MATRIX mat = MGetRotY(TO_RADIAN(m_rot.y));
	//	���E�L�[�Ō����̕ύX
	Float3 dir = VTransform(base.VGet(), mat);
	//	���̈ړ��x�N�g���ō��W�ړ�
	m_front = m_pos + dir;
}
//---------------------------------------------------------------------------------
//	�`�揈��
//---------------------------------------------------------------------------------
void Player::Render()
{
	DrawLine3D(m_pos.VGet(), m_front.VGet(), GetColor(0,255,255));

	MV1SetPosition( m_model, VGet( m_pos.x, m_pos.y, m_pos.z ) );
	MV1SetRotationXYZ( m_model, VGet( TO_RADIAN( m_rot.x ), TO_RADIAN( m_rot.y ), TO_RADIAN( m_rot.z ) ) );
	MV1DrawModel( m_model );
}
//---------------------------------------------------------------------------------
//	�I������
//---------------------------------------------------------------------------------
void Player::Exit()
{
}
