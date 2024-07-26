#include "Main.h"
#include "Game.h"
#include "Random.h"
#include "Camera.h"

//---------------------------------------------------------------------------------
//	����������
//---------------------------------------------------------------------------------
void Camera::Init()
{
	m_pos.set( 0.0f, 35.0f, -35.0f );
	m_look.set( 0.0f, 0.0f, -5.0f );

	m_type = TYPE_STAGE;
}
//---------------------------------------------------------------------------------
//	�X�V����
//---------------------------------------------------------------------------------
void Camera::Update( Float3 &player_pos, Float3 &player_rot, Float3 &player_mov )
{
	//	�S�̃J����
	if( PushHitKey( KEY_INPUT_F1 ) )	m_type = TYPE_STAGE;
	//	�v���C���[������J����
	if( PushHitKey( KEY_INPUT_F2 ) )	m_type = TYPE_PLAYER;
	//	�v���C���[�ɂ��Ă��������̃J����
	if( PushHitKey( KEY_INPUT_F3 ) )	m_type = TYPE_FOLLOW;

	switch( m_type ){
	case TYPE_STAGE:
		m_pos.set( 0.0f, 35.0f, -35.0f );
		m_look.set( 0.0f, 0.0f, -5.0f );
		break;

	case TYPE_PLAYER:
		//	������W�̓v���C���[���W
		m_look = player_pos;
		//	�J�������W�͂���������������ꂽ�Ƃ���
		m_pos = m_look + Float3( 0.0f, 5.0f, -10.0f );
		break;

	case TYPE_FOLLOW:	//	�v���C���[�ɂ��Ă��������̃J����
		{
			//	������W�̓v���C���[�̏�����
			m_look = player_pos + Float3( 0.0f, 1.0f, 0.0f );

			//	�ړ��x�N�g���̔��Ε����̃x�N�g�����쐬
			//	��������ړ��x�N�g���̒l�ɂ���
			Float3 reverse_dir = player_mov;
			//	���̃x�N�g�����t�����ɂ��܂�
			reverse_dir *= -1.0f;
			//	�J������ǂ������̏��ɒu�������̂�
			reverse_dir.SetLength( 5.0f );
			//	�K���ȍ����ɂ��܂�
			reverse_dir.y = 1.0f;

//			m_pos = m_look + reverse_dir;

			//	�v���C���[�̌������̃x�N�g��
			Float3 base( 0.0f, 1.0f, -5.0f );
			MATRIX mat = MGetRotY( TO_RADIAN( player_rot.y ) );
			Float3 behind_dir = GetFloat3VTransform( base, mat );

//			m_pos = m_look + behind_dir;

			//	�ړ��x�N�g�����傫���ق� reverse �̕���
			//	������������ behind �̕����g���������v�Z
			float reverse_rate = player_mov.GetLength() / 0.2f;	//	MOV_SPEED
			float behind_rate = 1.0f - reverse_rate;

			//	���ꂼ��̃x�N�g�������ꂼ��̊��������������̂��J�������W��
			m_pos = m_look + reverse_dir * reverse_rate + behind_dir * behind_rate;
		}
		break;
	}
}
//---------------------------------------------------------------------------------
//	�`�揈��
//---------------------------------------------------------------------------------
void Camera::Render()
{
	SetCameraPositionAndTarget_UpVecY( m_pos.VGet(), m_look.VGet() );
}
//---------------------------------------------------------------------------------
//	�I������
//---------------------------------------------------------------------------------
void Camera::Exit()
{
}
