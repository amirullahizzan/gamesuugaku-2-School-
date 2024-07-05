#include <algorithm>

#include "Main.h"
#include "Game.h"
#include "Npc.h"
#include "Random.h"

//	��̈ړ��X�s�[�h
#define NPC_MOV_SPEED	3.0f

//	�m�o�b�̎���p�i���ʂ���}�Q�O�x�j
#define VIEW_ANGLE	20.0f
//	���싗��
#define VIEW_LENGTH	250.0f
//	�m�o�b�̔��a
#define NPC_RADIUS	25.0f

//---------------------------------------------------------------------------------
//	����������
//---------------------------------------------------------------------------------
void Npc::Init(int image)
{
	m_image = image;

	m_pos.x = 600.0f;
	m_pos.y = 200.0f;
	m_rot = 180.0f;
}
//---------------------------------------------------------------------------------
//	�X�V����
//---------------------------------------------------------------------------------
void Npc::RandomizePos(EPos _pos)
{
	switch (_pos)
	{
	case Left:
		m_pos.x = -NPC_RADIUS;
		m_pos.y = GetRandomF(0, SCREEN_H);
		break;
	case Top:
		m_pos.x = GetRandomF(-NPC_RADIUS, SCREEN_W + NPC_RADIUS);
		m_pos.y = -NPC_RADIUS;
		break;
	case Right:
		m_pos.x = SCREEN_W + NPC_RADIUS;
		m_pos.y = GetRandomF(-NPC_RADIUS, SCREEN_H + NPC_RADIUS);
		break;
	case Bottom:
		m_pos.x = GetRandomF(-NPC_RADIUS, SCREEN_W + NPC_RADIUS);
		m_pos.y = SCREEN_H + NPC_RADIUS;
		break;
	}
}

void Npc::RandomizeRot(EPos _pos)
{
	float straightRot = 0.0f;
	switch (_pos)
	{
	case Left:
		straightRot = 0.0f;
		break;
	case Top:
		straightRot = 90.0f;
		break;
	case Right:
		straightRot = 180.0f;
		break;
	case Bottom:
		straightRot = 270.0f;
		break;
	}
	m_rot = GetRandomF(straightRot - 90.0f, straightRot + 90.0f);
}

void Npc::OOBHandler()
{
	bool isOOB = false;

	EPos currentOOBPos = Left;

	if (m_pos.x < -NPC_RADIUS)
	{
		isOOB = true;
		currentOOBPos = Left;
	}
	else if (m_pos.x > SCREEN_W + NPC_RADIUS)
	{
		isOOB = true;
		currentOOBPos = Right;
	}
	else if (m_pos.y < -NPC_RADIUS)
	{
		isOOB = true;
		currentOOBPos = Top;
	}
	else if (m_pos.y > SCREEN_H + NPC_RADIUS)
	{
		isOOB = true;
		currentOOBPos = Bottom;
	}

	if (isOOB)
	{
		EPos randomizeLocation = (EPos)GetRandomI(4);
		while (randomizeLocation == currentOOBPos)
		{
			randomizeLocation = (EPos)GetRandomI(4);
		}
		RandomizePos(randomizeLocation);
		RandomizeRot(randomizeLocation);

		isOOB = false;
	}
}

void Npc::Update(Float2& target_pos)
{
	//	���������ǂ���
	bool find = false;

	//	�P�F�Q�̃x�N�g����p��
	//	�m�o�b�̑O�����̃x�N�g���i���ς���p�x�����߂����̂Œ����� 1.0f �Ɂj
	Float2 front;
	front.x = 1.0f * cosf(TO_RADIAN(m_rot));
	front.y = 1.0f * sinf(TO_RADIAN(m_rot));

	//	�m�o�b����v���C���[�ւ̃x�N�g��
	Float2 target = target_pos - m_pos;
	//	�Q�F�x�N�g���̐��K���i�x�N�g���̒����� 1.0 �ɂ��܂��j
	target.normalize();

	//	�R�F���̂Q�̃x�N�g���̓��ς����߂�
	float front_dot = GetFloat2Dot(front, target);

	//	�S�F���߂����ς̒l����p�x�����߂�
	//	���̓��ς̒l�i front_dot �j�� acosf �֐��ɓn�����ƂŊp�x���擾�ł��܂�
	//	acosf�F�A�[�N�R�T�C���֐��i cos �֐��̋t�֐��j�� ���W�A���p���Ԃ��Ă��܂�
	float target_radian = acosf(front_dot);
	//	���W�A���p���p�x�̓x�ɂ��܂�
	float target_degree = TO_DEGREE(target_radian);

	//	�T�F���߂��p�x�Ǝ���p�Ŕ�r
	if (target_degree < VIEW_ANGLE && GetFloat2Distance(m_pos, target_pos) <= VIEW_LENGTH) 
	{
		//	����p���ɓ����Ă���̂ŁA�������t���O�� true ��
		find = true;
	}

	if (!find)
	{
	//	�����Ă�������Ɉړ�
		//clsDx();
	m_pos.x += NPC_MOV_SPEED * cosf(TO_RADIAN(m_rot));
	m_pos.y += NPC_MOV_SPEED * sinf(TO_RADIAN(m_rot));
	}
	else
	{
		//printfDx("Found!");
	}

	OOBHandler();
}
//---------------------------------------------------------------------------------
//	�`�揈��
//---------------------------------------------------------------------------------
void Npc::Render()
{
	//	�m�o�b�̕`��
	DrawRotaGraphF(m_pos.x, m_pos.y, 1.0f, TO_RADIAN(m_rot), m_image, TRUE);

	//	����p�����ǂ����𕪂���₷�����邽�߂ɐ����Q�{�`��
	Float2 line1;
	//	���̐�̍��W�i�m�o�b�̌��� +VIEW_ANGLE �̕����ɒ��� VIEW_LENGTH ������̏ꏊ�j
	line1.x = m_pos.x + VIEW_LENGTH * cosf(TO_RADIAN(m_rot + VIEW_ANGLE));
	line1.y = m_pos.y + VIEW_LENGTH * sinf(TO_RADIAN(m_rot + VIEW_ANGLE));
	//	�m�o�b���W�Ƃ��̍��W����Ō���ŕ`��
	DrawLineAA(m_pos.x, m_pos.y, line1.x, line1.y, GetColor(255, 128, 128));

	Float2 line2;
	//	�m�o�b�̍��W����A�m�o�b�̌����u�[�P�O�x�v�̕����ɒ��� 1000.0f ������̍��W
	line2.x = m_pos.x + VIEW_LENGTH * cosf(TO_RADIAN(m_rot - VIEW_ANGLE));
	line2.y = m_pos.y + VIEW_LENGTH * sinf(TO_RADIAN(m_rot - VIEW_ANGLE));
	//	�m�o�b���W�Ƃ��̍��W����Ō���ŕ`��
	DrawLineAA(m_pos.x, m_pos.y, line2.x, line2.y, GetColor(255, 128, 128));

	//Float2 sinCurve;
	//sinCurve.x = sinf(VIEW_ANGLE);
	//const int LINE_NUM = 12;
	//for (int i = 0; i < LINE_NUM; i++)
	//{
	//	sinCurve.y = (float)sin(VIEW_ANGLE + (i + 1) * LINE_NUM);
	//	DrawLine(
	//		i * VIEW_LENGTH / LINE_NUM,
	//		sinCurve.x * VIEW_LENGTH + 240,
	//		(i + 1) * VIEW_LENGTH / LINE_NUM,
	//		sinCurve.y * VIEW_LENGTH + 240,
	//		GetColor(255, 255, 255)
	//	);
	//	sinCurve.x = sinCurve.y;
	//}
	// 
	

	//DrawCurve
	for (int angle = -VIEW_ANGLE ;angle < VIEW_ANGLE;angle++)
	{
		Float2 pos1;
		pos1.x = m_pos.x + VIEW_LENGTH * cosf(TO_RADIAN(m_rot + angle));
		pos1.y = m_pos.y + VIEW_LENGTH * sinf(TO_RADIAN(m_rot + angle));

		Float2 pos2;
		pos2.x = m_pos.x + VIEW_LENGTH * cosf(TO_RADIAN(m_rot + angle + 1.0f));
		pos2.y = m_pos.y + VIEW_LENGTH * sinf(TO_RADIAN(m_rot + angle + 1.0f));
		DrawLineAA(pos1.x, pos1.y, pos2.x, pos2.y, GetColor(200, 255, 0));
	}

	// 
	//DrawLineAA(line1.x, line1.y, line2.x, line2.y, GetColor(200, 128, 128));
}
//---------------------------------------------------------------------------------
//	�I������
//---------------------------------------------------------------------------------
void Npc::Exit()
{
}
