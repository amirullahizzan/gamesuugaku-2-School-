#include "Main.h"
#include "Player.h"

//	�v���C���[�̈ړ��X�s�[�h
#define PLAYER_MOV_SPEED	0.1f
//	�v���C���[�̉�]�X�s�[�h�i�x�j
#define PLAYER_ROT_SPEED	1.0f

//---------------------------------------------------------------------------------
//	����������
//---------------------------------------------------------------------------------
void Player::Init( int model )
{
	//	�n���ꂽ���f���f�[�^�ԍ����󂯎��
	m_model = model;
	//	�������W�̐ݒ�
	m_pos.set( 0.0f, 0.0f, -5.0f );
	//	���������̐ݒ�i�R���̉�]�p�x�j
	m_rot.set( 0.0f, 0.0f, 0.0f );
}
//---------------------------------------------------------------------------------
//	�X�V����
//---------------------------------------------------------------------------------
void Player::Update()
{
	//	�E�L�[�������Ă���Ƃ�
	if( CheckHitKey( KEY_INPUT_RIGHT ) ){
		//	�x���ŉ�]�i�E��]�F��]�������v���X�j
		m_rot.y += PLAYER_ROT_SPEED;
	}
	//	���L�[�������Ă���Ƃ�
	if( CheckHitKey( KEY_INPUT_LEFT ) ){
		//	����]������
		m_rot.y -= PLAYER_ROT_SPEED;
	}

	//	��L�[�������Ă���Ƃ�
	if( CheckHitKey( KEY_INPUT_UP ) ){
		//	�����Ă�������Ɉړ�����
		//	�i�w�y���ʏ���ړ�����̂łw�y�̍��W�ړ��j
		m_pos.x += PLAYER_MOV_SPEED * sinf( TO_RADIAN( m_rot.y ) );
		m_pos.z += PLAYER_MOV_SPEED * cosf( TO_RADIAN( m_rot.y ) );
	}
}
//---------------------------------------------------------------------------------
//	�`�揈��
//---------------------------------------------------------------------------------
void Player::Render()
{
	//	���̃��f���̍��W��ݒ�
	MV1SetPosition( m_model, VGet( m_pos.x, m_pos.y, m_pos.z ) );
	//	���̃��f���̌�����ݒ�
	MV1SetRotationXYZ( m_model, VGet( TO_RADIAN( m_rot.x ), TO_RADIAN( m_rot.y ), TO_RADIAN( m_rot.z ) ) );
	//	���̃��f����`��
	MV1DrawModel( m_model );
}
//---------------------------------------------------------------------------------
//	�I������
//---------------------------------------------------------------------------------
void Player::Exit()
{
}
