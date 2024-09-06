#include "Main.h"
#include "Game.h"
#include "Hit.h"
#include "Player.h"

//	�ړ��X�s�[�h
#define PLAYER_MOV_SPEED	0.1f
//	��]�X�s�[�h
#define PLAYER_ROT_SPEED	3.0f

//---------------------------------------------------------------------------------
//	����������
//---------------------------------------------------------------------------------
void Player::Init( int model )
{
	m_model = model;

	m_pos.x		= -3.0f;
	m_pos.z		= -1.5f;
	m_rot.y		= 90.0f;
}
//---------------------------------------------------------------------------------
//	�X�V����
//---------------------------------------------------------------------------------
void Player::Update()
{
	//	���E�L�[�Ō����ύX
	if( CheckHitKey( KEY_INPUT_RIGHT ) )	m_rot.y += PLAYER_ROT_SPEED;
	if( CheckHitKey( KEY_INPUT_LEFT ) )		m_rot.y -= PLAYER_ROT_SPEED;
	//	��L�[�Ō����Ă�������Ɉړ�
	if( CheckHitKey( KEY_INPUT_UP ) ){
		//	���x�N�g�����쐬
		Float3 base( 0.0f, 0.0f, PLAYER_MOV_SPEED );
		//	�x����]�s����쐬
		MATRIX mat = MGetRotY( TO_RADIAN( m_rot.y ) );
		//	���x�N�g�������̍s��ŕϊ����Ĉړ��x�N�g���쐬
		Float3 mov = GetFloat3VTransform( base, mat );
		//	���̈ړ��x�N�g���ō��W�ړ�
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
