#include "Main.h"
#include "Game.h"
#include "Player.h"

//	�ړ��X�s�[�h�i�����܂ŃX�s�[�h���グ��j
#define MOV_SPEED	0.2f
//	��]�X�s�[�h�i�x�j
#define ROT_SPEED	2.0f

//	�����X�s�[�h
#define ACCEL_SPEED	0.005f
//	�����X�s�[�h
#define BRAKE_SPEED	0.003f

//	��ԋ߂������炱�̋�����藣�ꂽ��X�s�[�h�𗎂Ƃ�
#define LIMIT_LENGTH	5.0f

//---------------------------------------------------------------------------------
//	����������
//---------------------------------------------------------------------------------
void Player::Init( int model )
{
	m_model = model;

	m_pos.set( -25.0f, 0.0f, 0.0f );
	m_rot.y = 0.0f;

	m_mov.set( 0.0f, 0.0f, 0.0f );
}
//---------------------------------------------------------------------------------
//	�X�V����
//---------------------------------------------------------------------------------
void Player::Update(float near_length)
{
	//	���E�L�[�Ō����̕ύX
	if( CheckHitKey( KEY_INPUT_RIGHT ) )	m_rot.y += ROT_SPEED;
	if( CheckHitKey( KEY_INPUT_LEFT ) )		m_rot.y -= ROT_SPEED;

	//	��L�[�������Ă��鎞
	if( CheckHitKey( KEY_INPUT_UP ) ){
		//	�v���C���[�������Ă�������ɉ����x�N�g�����쐬
		Float3 base( 0.0f, 0.0f, ACCEL_SPEED );
		//	���̃x�N�g�����v���C���[�̌����ɍ��킹�����̂ŉ�]�s��
		MATRIX mat = MGetRotY( TO_RADIAN( m_rot.y ) );
		//	�s��ϊ����ĉ����x�N�g���ɂ��܂�
		Float3 accel = GetFloat3VTransform( base, mat );

		//	�ړ��x�N�g���ɉ����x�N�g���𑫂��܂�
		m_mov += accel;
		//	�ړ��x�N�g���̑傫���͈ړ��X�s�[�h���傫�����Ȃ�
		if( m_mov.GetLength() > MOV_SPEED ){
			m_mov.SetLength( MOV_SPEED );
		}

		if (near_length > LIMIT_LENGTH)
		{
			float speed = m_mov.GetLength();

			speed -= BRAKE_SPEED * 3.0f;
			speed = max(MOV_SPEED * 0.2f, speed);

			m_mov.SetLength(speed);
		}
	}else{
		//	�L�[�������Ă��Ȃ��Ƃ�
		//	���X�ɃX�s�[�h�𗎂Ƃ��Ă����悤�ȏ���
		//	�ړ��x�N�g�������������Ă���
		float speed = m_mov.GetLength();
		//	���̃X�s�[�h�����炷
		speed -= BRAKE_SPEED;
		//	0.0f ���͏������������Ȃ�
		speed = max( 0.0f, speed );
		//	�ړ��x�N�g�������̑傫���ɂ���
		m_mov.SetLength( speed );
	}

	//	�ړ��x�N�g�������W�ړ�
	m_pos += m_mov;
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
