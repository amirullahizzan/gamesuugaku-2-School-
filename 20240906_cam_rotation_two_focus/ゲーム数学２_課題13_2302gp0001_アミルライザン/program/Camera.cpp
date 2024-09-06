#include "Main.h"
#include "Game.h"
#include "Camera.h"
#include "Random.h"

//	�J�����͂���ȏ�߂Â��Ȃ�����
#define NEAR_DISTANCE	5.0f
//	����ȏ㗣��Ȃ�
#define FAR_DISTANCE	30.0f

//---------------------------------------------------------------------------------
//	����������
//---------------------------------------------------------------------------------
void Camera::Init()
{
	//	�J�������W
	m_pos.set(0.0f, 5.0f, -10.0f);
	//	������W
	m_look.set(0.0f, 0.0f, 0.0f);
}
//---------------------------------------------------------------------------------
//	�X�V�����i�v���C���[�Ƃm�o�b�̍��W�����炦��悤�Ɉ�����ǉ��j
//---------------------------------------------------------------------------------
void Camera::Update(Float3& player_pos, Float3& npc_pos)
{
	//	�e�P�`�e�R�L�[�ŃJ�����^�C�v�̕ύX
	if (PushHitKey(KEY_INPUT_F1))	m_type = TYPE_NORMAL;	//	�T���v���Ŏ��������J����
	if (PushHitKey(KEY_INPUT_F2))	m_type = TYPE_FRONT;	//	�v���C���[����O�E�m�o�b�����ɂȂ�悤�ȃJ����
	if (PushHitKey(KEY_INPUT_F3))	m_type = TYPE_LEFT;		//	�v���C���[�����E�m�o�b���E�ɂȂ�悤�ȃJ����

	//	�P�F������W�̓v���C���[���W�Ƃm�o�b���W�̒���
	m_look = (player_pos + npc_pos) / 2.0f;

	//	�Q�F�v���C���[�Ƃm�o�b�̋���
	float distance = GetFloat3Distance(player_pos, npc_pos);
	

	//	���̋����̂܂܂��ƃv���C���[�Ƃm�o�b�̈ʒu�֌W�ɂ���Ă�
	//	�����[�ɍs���߂���\��������̂�
	//	�������������ɂ��܂��i����̃v���W�F�N�g�ł́j
	distance *= 1.5f;

	//	���̋����ɐ����������܂��i 5.0f �` 30.0f �j
	distance = max(NEAR_DISTANCE, min(distance, FAR_DISTANCE));

	Float3 dir;

	if (m_type == TYPE_NORMAL)
	{
		//	�R�F��̃x�N�g��
		dir = Float3(0.0f, 0.5f, -1.0f);
		dir.SetLength(distance);
	}
	else if (m_type == TYPE_FRONT)
	{

		dir = player_pos - npc_pos;
		dir.y = dir.GetLength() / 2.0f;
	}
	else if (m_type == TYPE_LEFT)
	{
		dir = player_pos - npc_pos;
		dir.y = dir.GetLength() / 2.0f;

		auto mat  = MGetRotY(-90);
		dir = GetFloat3VTransform(dir, mat);
	}

		dir.SetLength(distance);
		m_pos = m_look + dir;
	//	�S�F���̊�̃x�N�g�����������̒����ɂ��܂�

	//	�T�F�J�������W�́A������W���炱�̃x�N�g������̂Ƃ���
}
//---------------------------------------------------------------------------------
//	�`�揈��
//---------------------------------------------------------------------------------
void Camera::Render()
{
	//	�J�������W�ƌ�����W��n���ăJ�����ݒ�
	SetCameraPositionAndTarget_UpVecY(VGet(m_pos.x, m_pos.y, m_pos.z), VGet(m_look.x, m_look.y, m_look.z));
}
//---------------------------------------------------------------------------------
//	�I������
//---------------------------------------------------------------------------------
void Camera::Exit()
{
}
