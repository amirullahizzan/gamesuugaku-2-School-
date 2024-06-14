#include "Main.h"
#include "Game.h"
#include "Hit.h"
#include "Random.h"

#include "Player.h"
#include "Npc.h"

//	�摜�ϐ�
int player_image;
int npc_image;

//	�N���X�̐錾
Player	player;
Npc		npc;

#define AREA_RADIUS		200.0f

Float2 area;

#define FRONT_LENGTH	100.0f
#define FRONT_RADIUS	 50.0f

Float2 front;

//---------------------------------------------------------------------------------
//	����������
//---------------------------------------------------------------------------------
void GameInit()
{
	//	�摜�̓ǂݍ���
	player_image = LoadGraph("data/player.bmp");
	npc_image = LoadGraph("data/npc.bmp");
	//	�N���X�̏�����
	player.Init(player_image);
	npc.Init(npc_image);

	area.set(400.0f, 225.0f);
}

int draw_frame;
bool npc_in;

//---------------------------------------------------------------------------------
//	�X�V����
//---------------------------------------------------------------------------------
void GameUpdate()
{
	//	�\���L�[�ŉ�]�ƈړ�
	player.Update();
	//	������ς��Ȃ���ړ�
	npc.Update();

	float distance = GetFloat2Distance(area, player.m_pos);

	if (distance > AREA_RADIUS)
	{
		Float2 dir = area - player.m_pos;

		float length = distance - AREA_RADIUS;

		Float2 back = dir;

		back.SetLength(length);

		player.m_pos += back;
	}

	if (PushHitKey(KEY_INPUT_SPACE))
	{
		draw_frame = 60;
	}
	npc_in = false;
	if (draw_frame > 0)
	{
		if (GetFloat2Distance(front, npc.m_pos) < FRONT_RADIUS)
		{
			npc_in = true;
		}
	}

	draw_frame--;
	draw_frame = max(0, draw_frame);

	front.x = player.m_pos.x + FRONT_LENGTH * cosf(TO_RADIAN(player.m_rot));
	front.y = player.m_pos.y + FRONT_LENGTH * sinf(TO_RADIAN(player.m_rot));
}
//---------------------------------------------------------------------------------
//	�`�揈��
//---------------------------------------------------------------------------------
void GameRender()
{
	DrawCircleAA(area.x, area.y, AREA_RADIUS, 100, GetColor(255, 255, 0), FALSE);

	//	�m�o�b�̕`��
	npc.Render();
	//	�v���C���[�̕`��
	player.Render();


	if (draw_frame > 0)
	{
		DrawCircleAA(front.x, front.y, FRONT_RADIUS, 100, GetColor(0, 255, 255), FALSE);
	}

	float distance = GetFloat2Distance(player.m_pos, npc.m_pos);

	distance = min(distance, 200.0f);

	DrawFillBox(20, 150, 20 + (int)distance, 170, GetColor(0, 255, 0));

	DrawLineBox(20, 150, 220, 170, GetColor(255, 255, 255));

	DrawString(16, 16, "�\���L�[�F�v���C���[�̉�]�E�ړ�", GetColor(255, 255, 255));
	DrawString(16, 32, "���@�v���C���[�͉��F���~����o�Ȃ�", GetColor(255, 255, 255));

	DrawString(16, 64, "�X�y�[�X�F���~���v���C���[�̑O�Ɉ�莞�ԕ\��", GetColor(255, 255, 255));

	DrawString(16, 128, "�v���C���[�Ƃm�o�b�̋������o�[�ŕ\���i�ő�Q�O�O�j", GetColor(255, 255, 255));
}
//---------------------------------------------------------------------------------
//	�I������
//---------------------------------------------------------------------------------
void GameExit()
{
	player.Exit();
	npc.Exit();

	DeleteGraph(player_image);
	DeleteGraph(npc_image);
}
