#include "Main.h"
#include "Game.h"
#include "Random.h"
#include "Hit.h"
#include "Player.h"

//	�ړ��X�s�[�h
#define PLAYER_MOV_SPEED	0.05f
//	�_�b�V���J�n���̃X�s�[�h
#define PLAYER_DASH_SPEED	0.5f

//---------------------------------------------------------------------------------
//	����������
//---------------------------------------------------------------------------------
void Player::Init(int model)
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
	if (CheckMouseInput(MOUSE_INPUT_LEFT)) {
		//	�}�E�X�̈ړ��ʂ̎擾
		float x = (float)GetMouseMoveX();
		//	�v���C���[�̉�]�i�x���j�F�������ڂȉ�]
		m_rot.y += x * 0.2f;
	}

	//	�P�F�O�ς����߂邽�߂ɂQ�̃x�N�g����p��
	//	�P�ڂ̃x�N�g���̓v���C���[�̑O�����̃x�N�g��

	//	�v���C���[����]���Ă��Ȃ��Ƃ��̑O�����x�N�g��
	Float3 base(0.0f, 0.0f, 1.0f);
	//	���̃x�N�g�����v���C���[�̌����Ă���p�x����]��������
	//	��]�����邽�߂̍s����擾
	MATRIX mat = MGetRotY(TO_RADIAN(m_rot.y));
	//	���̍s����g���Ċ�̃x�N�g����ϊ��i�P�ڂ̃x�N�g���j
	Float3 front = GetFloat3VTransform(base, mat);

	//	�Q�ڂ̃x�N�g���F������̃x�N�g��
	Float3 up(0.0f, 1.0f, 0.0f);

	//	�Q�F���̂Q�̃x�N�g���i up front �j�̊O�ς��擾
	Float3 right = GetFloat3Cross(up, front);

	//	�`�c�L�[�ō��E�ړ��i������ς����Ɂj
	if (CheckHitKey(KEY_INPUT_D)) {
		//	�E�����x�N�g�����ړ��x�N�g���ɂ��܂�
		Float3 mov = right;
		mov.SetLength(PLAYER_MOV_SPEED);
		m_pos += mov;
	}
	if (CheckHitKey(KEY_INPUT_A)) {
		//	�������ړ��Ȃ�ł����E�����ړ��̋t�ɂȂ�܂�
		Float3 mov = right * -1.0f;
		mov.SetLength(PLAYER_MOV_SPEED);
		m_pos += mov;
	}

	//	�v�L�[�őO�����Ɉړ�
	if (CheckHitKey(KEY_INPUT_W)) 
	{
		//	�O�����̃x�N�g�����ړ��x�N�g���Ƃ��܂�
		Float3 mov = front;
		//	���̂܂܂��ƈړ��������̂� PLAYER_MOV_SPEED �̒����ɂ��܂�
		mov.SetLength(PLAYER_MOV_SPEED);
		//	�ړ��x�N�g�������W�ړ�
		m_pos += mov;
	}

	//	�p�d�L�[�ō��E�_�b�V��
	if (PushHitKey(KEY_INPUT_E))
	{
		m_dash = right;
		m_dash.SetLength(PLAYER_DASH_SPEED);
	}
	if (PushHitKey(KEY_INPUT_Q)) 
	{
		m_dash = right * -1;
		m_dash.SetLength(PLAYER_DASH_SPEED);
	}

	SetupCamera_Perspective(TO_RADIAN(perspective));

	m_pos += m_dash;
	m_dash *= 0.9f;
	
	float length = m_dash.GetLength();
	if (length > 0.1f)
	{
		if (perspective < 90.0f)
		{
			perspective += 1.0f;
		}
	}
	else
	{
		if (perspective > 45.0f)
		{
			perspective -= 0.1f;
		}
	}
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
