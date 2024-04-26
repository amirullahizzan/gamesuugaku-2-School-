#include "Main.h"
#include "Game.h"
#include "Hit.h"

#include "Camera.h"
#include "Ground.h"
#include "Player.h"
#include "Npc.h"

//	�e���f���f�[�^�p�̕ϐ�
//	�n�ʃ��f��
int ground_model;
//	�v���C���[���f��
int player_model;
//	�m�o�b���f��
int npc_model;

Float3* cameraPos;
Float3* cameraRot;

//	���ꂼ��̃N���X�̐錾
//	�J����
Camera	camera;
//	�n��
Ground	ground;
//	�v���C���[
Player	player;
//	�m�o�b
Npc		npc;

//---------------------------------------------------------------------------------
//	����������
//---------------------------------------------------------------------------------
void GameInit()
{
	//	�e���f���f�[�^�̓ǂݍ���
	ground_model = MV1LoadModel("data/ground.mqoz");
	player_model = MV1LoadModel("data/player.mqoz");
	npc_model = MV1LoadModel("data/npc.mqoz");

	//	�N���X�̏�����
	camera.Init();
	//	�ǂݍ��񂾃��f���f�[�^�ԍ���n���ăN���X�̏�����
	ground.Init(ground_model);
	player.Init(player_model);
	npc.Init(npc_model);

	cameraPos = &player.m_pos;
	cameraRot = &player.m_rot;
}
//---------------------------------------------------------------------------------
//	�X�V����
//---------------------------------------------------------------------------------
void GameUpdate()
{
	ground.Update();
	//	���E�L�[�ŉ�]�E��L�[�Ō����Ă�������Ɉړ�
	player.Update();
	//	��]���Ȃ���ړ�
	npc.Update();

	//	�v���C���[�̌�납��v���C���[������J����
	//	���W�ƌ�����n���܂�


	if (PushHitKey(KEY_INPUT_SPACE))
	{
		if (cameraPos != &npc.m_pos)
		{
			cameraPos = &npc.m_pos;
			cameraRot = &npc.m_rot;
		}
		else
		{
			cameraPos = &player.m_pos;
			cameraRot = &player.m_rot;
		}
	}


	camera.Update(*cameraPos, *cameraRot);
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

	DrawString(16, 16, "�����L�[�F�v���C���[�̉�]", GetColor(255, 255, 255));
	DrawString(16, 32, "���@�L�[�F�����Ă�������Ɉړ�", GetColor(255, 255, 255));

	DrawString(16, 48, "�`�c�L�[�F�J������]", GetColor(255, 255, 0));
	DrawString(16, 64, "�r�@�L�[�F�J�������v���C���[�̌���", GetColor(255, 255, 0));
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

	MV1DeleteModel(ground_model);
	MV1DeleteModel(player_model);
	MV1DeleteModel(npc_model);
}
