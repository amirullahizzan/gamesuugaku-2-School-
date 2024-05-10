#include "Main.h"
#include "Game.h"
#include "Hit.h"

#include "Camera.h"
#include "Ground.h"
#include "Player.h"
#include "Npc.h"

int ground_model;
int player_model;
int npc_model;

//	�J�����i�v���C���[�Ɉ��������銴���̃J�����j
Float3 topFixedCameraPos;
Float3 worldMiddlePos;
Camera	camera;
//	�n��
Ground	ground;
//	�v���C���[�i�\���L�[�ŉ�]�ƈړ��j
Player	player;
//	�m�o�b�i�K���Ɉړ��j
Npc		npc;

int cameraMode = 0;

//---------------------------------------------------------------------------------
//	����������
//---------------------------------------------------------------------------------
void GameInit()
{
	ground_model = MV1LoadModel( "data/ground.mqoz" );
	player_model = MV1LoadModel( "data/player.mqoz" );
	npc_model = MV1LoadModel( "data/npc.mqoz" );

	camera.Init();
	ground.Init( ground_model );
	player.Init( player_model );
	npc.Init( npc_model );

	topFixedCameraPos = camera.m_pos;
	worldMiddlePos = { 0,0,0 };
}
//---------------------------------------------------------------------------------
//	�X�V����
//---------------------------------------------------------------------------------
void GameUpdate()
{
	ground.Update();
	//	�\���L�[�ŉ�]��ړ�
	player.Update();
	//	��ɉ�]���Ȃ���ړ�
	npc.Update();

	//	�v���C���[���W�Ƃm�o�b���W��n���ăJ�����̍X�V
	
	if (GetFloat3Distance(player.m_pos, npc.m_pos) <= 7.0f)
	{
	camera.Update( player.m_pos, npc.m_pos );
	}
	else
	{
	camera.Update(topFixedCameraPos, worldMiddlePos);
	}
}
//---------------------------------------------------------------------------------
//	�`�揈��
//---------------------------------------------------------------------------------
void GameRender()
{
	camera.Render();

	ground.Render();
	npc.Render();
	player.Render();

	DrawString( 16, 16, "�\���L�[�F��]�E�ړ�", GetColor( 255, 255, 255 ) );

	DrawString( 16, 32, "�^�[�Q�b�g�J�����i�v���C���[�z���ɂm�o�b������J�����j", GetColor( 255, 255, 0 ) );
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
