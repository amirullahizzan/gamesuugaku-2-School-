#include "Main.h"
#include "Game.h"
#include "Hit.h"
#include "Random.h"
#include "Float3.h"

#include "Camera.h"
#include "Ground.h"
#include "Player.h"
#include "Npc.h"

#define RADIUS	1.0f

//	���f���p�̕ϐ�
int ground_model;
int player_model;
int npc_model;
//	�N���X�̐錾
Camera	camera;
Ground	ground;
Player	player;
Npc		npc;

//---------------------------------------------------------------------------------
//	����������
//---------------------------------------------------------------------------------
void GameInit()
{
	//	���f���̓ǂݍ���
	ground_model = MV1LoadModel( "data/ground.mqoz" );
	player_model = MV1LoadModel( "data/player.mqoz" );
	npc_model = MV1LoadModel( "data/npc.mqoz" );
	//	�N���X�̏�����
	camera.Init();
	ground.Init( ground_model );
	player.Init( player_model );
	npc.Init( npc_model );
}
//---------------------------------------------------------------------------------
//	�X�V����
//---------------------------------------------------------------------------------
void GameUpdate()
{
	ground.Update();
	//	�\���L�[�ŉ�]�E�ړ�
	player.Update();
	npc.Update();

	float distance = GetFloat3Distance(player.m_pos, npc.m_pos);

	float base_length = RADIUS * 2.0f;

	if (distance < base_length)
	{
		float in_length = base_length - distance;

		Float3 dir = player.m_pos - npc.m_pos;

		dir.SetLength(in_length * 0.5f);

		player.m_pos += dir;
		npc.m_pos -= dir;
	}

	//	�v���C���[���W�Ƃm�o�b���W��n���ăJ�����̍X�V����
	camera.Update( player.m_pos, npc.m_pos );
}
//---------------------------------------------------------------------------------
//	�`�揈��
//---------------------------------------------------------------------------------
void GameRender()
{
	//	�J�����̐ݒ�
	camera.Render();
	//	���f���̕`��
	ground.Render();

	npc.Render();
	DrawCircle3D_XZ( npc.m_pos, RADIUS, GetColor( 255, 128, 0 ) );

	player.Render();
	DrawCircle3D_XZ( player.m_pos, RADIUS, GetColor( 0, 128, 255 ) );

	DrawString( 16, 16, "�\���L�[�F�v���C���[��]�E�ړ�", GetColor( 255, 255, 255 ) );
	DrawString( 16, 32, "�v���C���[�Ƃm�o�b�����������ɉ�ʂɓ���悤�ȃJ����", GetColor( 255, 255, 255 ) );
	DrawString( 16, 48, "�v���C���[�Ƃm�o�b�͈����߂Â��Ȃ�", GetColor( 255, 255, 255 ) );
}
//---------------------------------------------------------------------------------
//	�I������
//---------------------------------------------------------------------------------
void GameExit()
{
	camera.Exit();
	ground.Exit();
	player.Exit();
	npc.Exit();

	MV1DeleteModel( ground_model );
	MV1DeleteModel( player_model );
	MV1DeleteModel( npc_model );
}
