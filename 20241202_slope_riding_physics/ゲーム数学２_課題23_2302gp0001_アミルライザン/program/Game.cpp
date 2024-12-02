#include "Main.h"
#include "Game.h"
#include "Hit.h"
#include "Random.h"
#include "Float3.h"

#include "Camera.h"
#include "Ground.h"
#include "Player.h"

//	���f���f�[�^�p�̕ϐ�
int ground_model;
int player_model;

//	�N���X�̐錾
Camera	camera;
Ground	ground;
Player	player;

//---------------------------------------------------------------------------------
//	����������
//---------------------------------------------------------------------------------
void GameInit()
{
	//	���f���f�[�^�̓ǂݍ���
	//	�i����͒n�ʂ̌X�����g�����������������̂ŋN���̂���n�ʃ��f����ǂݍ���ł��܂��j
	ground_model = MV1LoadModel( "data/ground.mqoz" );
	player_model = MV1LoadModel( "data/player.mqoz" );

	//	���f���f�[�^�̓���������쐬���܂�
	MV1SetupCollInfo( ground_model );

	//	�N���X�̏�����
	camera.Init();
	ground.Init( ground_model );
	player.Init( player_model );
}
//---------------------------------------------------------------------------------
//	�X�V����
//---------------------------------------------------------------------------------
void GameUpdate()
{
	ground.Update();
	//	�����蔻��̏��̍X�V���s���܂�
	MV1RefreshCollInfo( ground_model );

	//	�v���C���[�̍X�V����
	//	�\���L�[�Ō�����ς��Ĉړ��E�X�y�[�X�L�[�ŃW�����v
	//	�n�ʃ��f���ԍ���n���ăv���C���[�̍X�V����
	player.Update( ground_model );

	camera.Update();
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
	player.Render();

	DrawString( 16, 16, "�\���L�[�F�v���C���[�̉�]�E�ړ�", GetColor( 255, 255, 255 ) );
	DrawString( 16, 32, "�X�y�[�X�F�W�����v�i�n�ʂ̌X�������Ɂj", GetColor( 255, 255, 255 ) );
	DrawString( 16, 48, "�v���C���[���n�ʂɗ����Ă���Ƃ������W�����v", GetColor( 255, 255, 0 ) );
}
//---------------------------------------------------------------------------------
//	�I������
//---------------------------------------------------------------------------------
void GameExit()
{
	camera.Exit();
	ground.Exit();
	player.Exit();

	MV1DeleteModel( ground_model );
	MV1DeleteModel( player_model );
}
