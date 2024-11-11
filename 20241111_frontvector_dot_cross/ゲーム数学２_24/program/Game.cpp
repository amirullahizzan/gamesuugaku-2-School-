#include "Main.h"
#include "Game.h"
#include "Hit.h"
#include "Random.h"
#include "Float3.h"

#include "Camera.h"
#include "Ground.h"
#include "Player.h"
#include "Npc.h"

//	���f���f�[�^�p�̕ϐ�
int ground_model;
int player_model;
int npc_model;

//	�N���X�̐錾
Camera	camera;
Ground	ground;
Player	player;

#define NPC_MAX	100
Npc		npc[NPC_MAX];

//---------------------------------------------------------------------------------
//	����������
//---------------------------------------------------------------------------------
void GameInit()
{
	//	���f���f�[�^�̓ǂݍ���
	ground_model = MV1LoadModel( "data/ground.mqoz" );
	player_model = MV1LoadModel( "data/player.mqoz" );
	npc_model = MV1LoadModel( "data/npc.mqoz" );

	//	�N���X�̐錾
	camera.Init();
	ground.Init( ground_model );
	player.Init( player_model );
	for( int i = 0; i < NPC_MAX; i++ ){
		npc[i].Init( npc_model );
	}
}
//---------------------------------------------------------------------------------
//	�X�V����
//---------------------------------------------------------------------------------
void GameUpdate()
{
	ground.Update();
	//	�v���C���[�̍X�V����
	player.Update();
	for( int i = 0; i < NPC_MAX; i++ ){
		npc[i].Update();
	}
	//	�J�����̍X�V����
	camera.Update( player.m_pos, player.m_rot );
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
	for( int i = 0; i < NPC_MAX; i++ ){
		npc[i].Render();
	}
	player.Render();

	DrawString( 16, 16, "�}�E�X���h���b�O�F�v���C���[��]�i�v���C���[�̌����ɍ��킹�ăJ�������W������ݒ�j", GetColor( 255, 255, 255 ) );

	DrawString( 16, 48, "�v�L�[�@�F�v���C���[�O�����Ɉړ�", GetColor( 255, 255, 255 ) );
	DrawString( 16, 64, "�`�c�L�[�F�v���C���[�ړ��i������ς����ɍ��E�ړ��j", GetColor( 255, 255, 255 ) );
}
//---------------------------------------------------------------------------------
//	�I������
//---------------------------------------------------------------------------------
void GameExit()
{
	camera.Exit();
	ground.Exit();
	player.Exit();
	for( int i = 0; i < NPC_MAX; i++ ){
		npc[i].Exit();
	}

	MV1DeleteModel( ground_model );
	MV1DeleteModel( player_model );
	MV1DeleteModel( npc_model );
}
