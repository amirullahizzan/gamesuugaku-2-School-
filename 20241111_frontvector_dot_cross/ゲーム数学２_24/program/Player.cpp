#include "Main.h"
#include "Game.h"
#include "Random.h"
#include "Hit.h"
#include "Player.h"

//	�ړ��X�s�[�h
#define PLAYER_MOV_SPEED	0.05f

//---------------------------------------------------------------------------------
//	����������
//---------------------------------------------------------------------------------
void Player::Init( int model )
{
	m_model = model;

	m_pos.x = 0.0f;
	m_pos.z = 0.0f;
}
//---------------------------------------------------------------------------------
//	�X�V����
//---------------------------------------------------------------------------------
void Player::Update()
{
	//	�}�E�X�̍��{�^���������Ă���Ƃ�
	if( CheckMouseInput( MOUSE_INPUT_LEFT ) )
	{
		float x = (float)GetMouseMoveX();
		m_rot.y += x * 0.2f;
	}

	Float3 base(0.0f, 0.0f, 1.0f);

	MATRIX mat = MGetRotY(TO_RADIAN(m_rot.y));

	Float3 front = GetFloat3VTransform(base,mat);

	//base.set(1.0f,0.0f,0.0f);
	//Float3 right = GetFloat3VTransform(base,mat);

	Float3 up = Float3(0.0f, 1.0f, 0.0f);
	Float3 right = GetFloat3Cross(up,front);

	//	�`�c�L�[�ō��E�ړ�
	if( CheckHitKey( KEY_INPUT_D ) ){

		Float3 mov = right;
		mov.SetLength(PLAYER_MOV_SPEED);

		m_pos += mov;
	}
	if( CheckHitKey( KEY_INPUT_A ) ){
		Float3 mov = right * -1;
		mov.SetLength(PLAYER_MOV_SPEED);

		m_pos += mov;
	}
	//	�v�L�[�őO�����Ɉړ�
	if( CheckHitKey( KEY_INPUT_W ) ){
		Float3 mov = front;

		mov.SetLength(PLAYER_MOV_SPEED);
		m_pos += mov;
	}
}
//---------------------------------------------------------------------------------
//	�`�揈��
//---------------------------------------------------------------------------------
void Player::Render()
{
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
