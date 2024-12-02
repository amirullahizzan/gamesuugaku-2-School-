#include "Main.h"
#include "Game.h"
#include "Hit.h"
#include "Player.h"

//	�v���C���[�̈ړ��X�s�[�h
#define MOV_SPEED	0.15f
//	�v���C���[�̉�]�X�s�[�h
#define ROT_SPEED	3.0f

#define JUMP_SPEED	0.5f

//---------------------------------------------------------------------------------
//	����������
//---------------------------------------------------------------------------------
void Player::Init( int model )
{
	m_model = model;

	m_pos.x		= -5.0f;
	m_pos.z		= -10.0f;
}
//---------------------------------------------------------------------------------
//	�X�V����
//---------------------------------------------------------------------------------
void Player::Update( int ground_model )
{
	//	���E�L�[�Ńv���C���[�̌����̕ύX
	if( CheckHitKey( KEY_INPUT_RIGHT ) )	m_rot.y += ROT_SPEED;
	if( CheckHitKey( KEY_INPUT_LEFT ) )		m_rot.y -= ROT_SPEED;
	//	��L�[�Ō����Ă�������Ɉړ�
	if( CheckHitKey( KEY_INPUT_UP ) ){
		Float3 base( 0.0f, 0.0f, MOV_SPEED );
		MATRIX mat = MGetRotY( TO_RADIAN( m_rot.y ) );
		Float3 xz_mov = GetFloat3VTransform( base, mat );
		m_pos += xz_mov;
	}

	//	���̊J�n���W�i�v���C���[���W�̏�����j
	Float3 start = m_pos + Float3( 0.0f, 10.0f, 0.0f );
	//	���̃S�[�����W�i�v���C���[���W�̏������j
	Float3 goal = m_pos + Float3( 0.0f, -10.0f, 0.0f );

	//	��Ō��߂��Q�_�̐��i start goal �j�ƒn�ʁi ground_model �j��
	//	�����蔻����������ʂ����Ƃ��Ď擾���܂�
	MV1_COLL_RESULT_POLY hit_info = MV1CollCheck_Line( ground_model, -1, start.VGet(), goal.VGet() );

	//	�������񂪎擾�o������i�n�ʂƓ������Ă�����j
	if( hit_info.HitFlag ){
		//	�n�ʂ̍������v���C���[�̂x���W�ɂ��܂�
		m_pos.y = hit_info.HitPosition.y;
	}

	//	�X�y�[�X�L�[����������W�����v�J�n
	if( PushHitKey( KEY_INPUT_SPACE ) ){
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
