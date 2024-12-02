#include "Main.h"
#include "Game.h"
#include "Hit.h"
#include "Player.h"

//	�v���C���[�̈ړ��X�s�[�h
#define MOV_SPEED	0.15f
//	�v���C���[�̉�]�X�s�[�h
#define ROT_SPEED	3.0f
//	�W�����v�X�s�[�h
#define JUMP_SPEED	0.5f

//---------------------------------------------------------------------------------
//	����������
//---------------------------------------------------------------------------------
void Player::Init( int model )
{
	m_model = model;

	m_pos.x		= -5.0f;
	m_pos.z		= -10.0f;
	m_stand = true;
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
		//	�w�y�����̈ړ��Ȃ̂ŁA�ϐ����� xz_mov �ɂ��Ă��܂�
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

	//	���n���ׂ��n�ʂ̍���
	float ground_y = 0.0f;

	//	�n�ʂ̌X�������̃x�N�g��
	//	�i�n�ʂ̏�񂪎��Ȃ������Ƃ��̂��߂ɂx���P�ɂ��Ƃ��܂��j
	Float3 ground_normal( 0.0f, 1.0f, 0.0f );

	//	�������񂪎擾�o������i�n�ʂƓ������Ă�����j
	if( hit_info.HitFlag ){
		//	�v���C���[�̂w�y���W����n�ʂ̍������擾
		ground_y = hit_info.HitPosition.y;
		//	�n�ʂ̖@�����擾���Ă����܂�
		ground_normal.VSet( hit_info.Normal );
	}

	//	�W�����v�ړ��ʂ�����ɍ��W�ړ�

	if (m_stand)
	{
		//	�X�y�[�X�L�[����������W�����v�J�n
		if (PushHitKey(KEY_INPUT_SPACE)) {
			//	�ʂ̌X���Ă�������i�@���x�N�g�������j�ɃW�����v���܂�
			m_jump_mov = ground_normal;
			//	���̃x�N�g���̒������W�����v�X�s�[�h�ɍ��킹�܂�
			m_jump_mov.SetLength(JUMP_SPEED);
			m_stand = false;
		}
	}
	
	m_pos += m_jump_mov;

	//	�v���C���[�̂x���W�͒n�ʂ������ɂȂ�Ȃ�
	if( m_pos.y < ground_y ){
		m_pos.y = ground_y;
		//	���n�����Ƃ������Ƃňړ��ʂ��O�ɂ��܂�
		m_jump_mov.clear();
		m_stand = true;
	}
	//	�x�ړ��ʂ����������炵�Ă����܂�
	m_jump_mov.y -= 0.02f;


	if (m_stand)
	{
		Float3 up(0.0f,1.0f,0.0f);
		Float3 right = GetFloat3Cross(up, ground_normal);
		Float3 down = GetFloat3Cross(right,ground_normal);
		Float3 slide = down;
		slide.SetLength(0.05f);

		m_pos += slide;
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
