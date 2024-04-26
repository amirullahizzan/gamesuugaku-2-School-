#include "Main.h"
#include "Game.h"
#include "Camera.h"

//	�v���C���[����J�����܂ł̋���
#define CAMERA_LENGTH	10.0f
//	�`�c�L�[���������Ƃ��̉�]�X�s�[�h
#define CAMERA_ROT_SPEED	1.0f

//---------------------------------------------------------------------------------
//	����������
//---------------------------------------------------------------------------------
void Camera::Init()
{
	//	�J�����̏������W
	m_pos.set(0.0f, 20.0f, -30.0f);
	//	�J�����̌��鏉�����W
	m_look.set(0.0f, 0.0f, 0.0f);
	m_rot = 0.0f;
}
//---------------------------------------------------------------------------------
//	�X�V����
//---------------------------------------------------------------------------------
void Camera::Update(Float3& pos, Float3& rot)
{

	//	�`�c�L�[�ŃJ�����̎����Ă���p�x�ϐ����X�V
	if (CheckHitKey(KEY_INPUT_D))
	{
		//m_look.x += CAMERA_ROT_SPEED;
	//m_pos.x = m_look.x + CAMERA_LENGTH * sinf( TO_RADIAN( camera_rot ) );
		m_rot++;
	}
	if (CheckHitKey(KEY_INPUT_A))
	{
		m_rot--;
	}

	//	�r�L�[����������J���������Z�b�g�i�v���C���[�̌��Ɂj
	if (CheckHitKey(KEY_INPUT_S)) {
		m_rot = rot.y;
	}

	//	������W�͏�Ƀv���C���[���W�i�n����Ă������W�j
	m_look = pos;

	//	�J�������W���v���C���[�̌��ɂ�����
	//	�J�������W�͌�����W�i�v���C���[���W�j����
	//	�v���C���[�̌��̕����i�v���C���[�̌��� +180 �x�j��
	//	��苗�����ꂽ�Ƃ���
	float camera_rot = m_rot + 180.0f;

	//	�v���C���[�̌������̌��������߂�i�v���C���[���� + 180 �j

	//	���̌����Ɍ�����W���� CAMERA_LENGTH ���ړ�������
	m_pos.x = m_look.x + CAMERA_LENGTH * sinf(TO_RADIAN(camera_rot));
	m_pos.z = m_look.z + CAMERA_LENGTH * cosf(TO_RADIAN(camera_rot));

	//	���̂܂܂��ƃJ�������߂����ፂ���Ƃ���ɂ���̂�
	m_pos.y = m_look.y + 5.0f;
	//m_pos.x = m_look.x;
	//m_pos.z = m_look.z;
}
//---------------------------------------------------------------------------------
//	�`�揈��
//---------------------------------------------------------------------------------
void Camera::Render()
{
	//	�J�������W�ƌ�����W��n���ăJ�����̐ݒ�
	SetCameraPositionAndTarget_UpVecY(VGet(m_pos.x, m_pos.y, m_pos.z), VGet(m_look.x, m_look.y, m_look.z));
}
//---------------------------------------------------------------------------------
//	�I������
//---------------------------------------------------------------------------------
void Camera::Exit()
{
}
