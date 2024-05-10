#include "Main.h"
#include "Game.h"
#include "Hit.h"

#include "Player.h"

#define BALL_LENGTH 100.0f

int player_image;

//	�v���C���[�N���X
Player	player;

Float2	ball_pos;

//---------------------------------------------------------------------------------
//	����������
//---------------------------------------------------------------------------------
void GameInit()
{
	//	�v���C���[�摜��ǂݍ���
	player_image = LoadGraph("data/player.bmp");
	//	�摜��n���ď�����
	player.Init(player_image);

	ball_pos.set(500.0f, 200.0f);
}
//---------------------------------------------------------------------------------
//	�X�V����
//---------------------------------------------------------------------------------
Float2 dir;
void GameUpdate()
{
	player.Update();

	//�~�̍��W��ݒ艟������
	//
	dir = ball_pos - player.m_pos; //Range?
	
	//dir.SetLength(BALL_LENGTH);
	////////////////////////////////////
	//Normalize
	float magnitude = dir.GetLength();
	{
		if (magnitude > 0.0f)
		{
			dir /= magnitude;
		}
	}
	////////////////////////////////////
	dir *= BALL_LENGTH;
	ball_pos = player.m_pos + dir;
}
//---------------------------------------------------------------------------------
//	�`�揈��
//---------------------------------------------------------------------------------
void GameRender()
{
	clsDx();
	printfDx("length %.3f : %.3f", dir.x, dir.y);
	DrawLineAA(player.m_pos.x, player.m_pos.y, ball_pos.x, ball_pos.y, GetColor(255, 255, 255));
	DrawCircleAA(ball_pos.x, ball_pos.y, 10.0f, 50, GetColor(255, 255, 0));
	//	�v���C���[�̕`��
	player.Render();

	DrawString(16, 16, "�����L�[�F��]", GetColor(255, 255, 255));
	DrawString(16, 32, "���@�L�[�F�ړ�", GetColor(255, 255, 255));
}
//---------------------------------------------------------------------------------
//	�I������
//---------------------------------------------------------------------------------
void GameExit()
{
	player.Exit();

	DeleteGraph(player_image);
}
