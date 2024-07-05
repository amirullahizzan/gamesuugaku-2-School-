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

//---------------------------------------------------------------------------------
//	����������
//---------------------------------------------------------------------------------
void GameInit()
{
	//	�摜�̓ǂݍ���
	player_image = LoadGraph( "data/player.bmp" );
	npc_image = LoadGraph( "data/npc.bmp" );
	//	�N���X�̏�����
	player.Init( player_image );
	npc.Init( npc_image );
}
//---------------------------------------------------------------------------------
//	�X�V����
//---------------------------------------------------------------------------------
void GameUpdate()
{
	//	�\���L�[�ŉ�]�ƈړ�
	player.Update();

	npc.Update( player.m_pos );
}
//---------------------------------------------------------------------------------
//	�`�揈��
//---------------------------------------------------------------------------------
void GameRender()
{
	//	�m�o�b�̕`��
	npc.Render();
	//	�v���C���[�̕`��
	player.Render();

	DrawString( 16, 16, "�\���L�[�F�v���C���[��]�E�ړ�", GetColor( 255, 255, 255 ) );
	DrawString( 16, 32, "�m�o�b�͉�]���Ȃ�������Ă�������Ɉړ�", GetColor( 255, 255, 255 ) );
	DrawString( 16, 48, "���@����p���Ƀv���C���[���W����������~�܂�", GetColor( 255, 255, 255 ) );
}
//---------------------------------------------------------------------------------
//	�I������
//---------------------------------------------------------------------------------
void GameExit()
{
	player.Exit();
	npc.Exit();

	DeleteGraph( player_image );
	DeleteGraph( npc_image );
}
