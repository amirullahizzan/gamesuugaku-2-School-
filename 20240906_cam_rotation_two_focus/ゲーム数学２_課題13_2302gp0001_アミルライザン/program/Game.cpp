#include "Main.h"
#include "Game.h"
#include "Hit.h"
#include "Random.h"
#include "Float3.h"

#include "Camera.h"
#include "Ground.h"
#include "Player.h"
#include "Npc.h"

//	���ꂼ��̉~�̔��a
#define RADIUS	1.0f

//	���f���p�̕ϐ�
int ground_model;
int player_model;
int npc_model;
//	�N���X�̐錾
//	�v���C���[�Ƃm�o�b�����������ɉ�ʂɓ���悤�ȃJ����
Camera	camera;
Ground	ground;
//	�v���C���[�Ƃm�o�b�͈��ȏ�߂Â��Ȃ�
Player	player;
Npc		npc;


void CalculatePhysics()
{
	//	�P�F�v���C���[�Ƃm�o�b�̋���
	float distance = GetFloat3Distance(player.m_pos, npc.m_pos);

	//	�Q�F��̋����i�~�����傤�ǂ��Ă��鎞�̋����j
	float base_length = RADIUS * 2.0f;

	//	�R�F�Q�L�����̋�������̒������Z��������
	if (distance < base_length) {
		//	�S�F�ǂꂾ�����ɓ����Ă��邩
		//	�i���̒������~���d�Ȃ��Ă���j
		float in_length = base_length - distance;

		//	�T�F�ǂ��������ɂ��炷��
		//	�i�m�o�b����v���C���[�ւ̃x�N�g���j
		Float3 dir = player.m_pos - npc.m_pos;

		//	�U�F���̃x�N�g�����d�Ȃ��Ă��钷���ɂ��܂�
		//	�i����̓v���C���[�Ƃm�o�b�����ꂼ�ꓮ���������̂�
		//		�����̒����ɂ��܂��j
		dir.SetLength(in_length * 0.5f);

		//	�V�F�v���C���[�̍��W�����̃x�N�g����������
		player.m_pos += dir;
		//	�V�F�m�o�b�͔��Ε����ɓ�����
		npc.m_pos -= dir;
	}
}

//---------------------------------------------------------------------------------
//	����������
//---------------------------------------------------------------------------------
void GameInit()
{
	//	���f���̓ǂݍ���
	ground_model = MV1LoadModel("data/ground.mqoz");
	player_model = MV1LoadModel("data/player.mqoz");
	npc_model = MV1LoadModel("data/npc.mqoz");
	//	�N���X�̏�����
	camera.Init();
	ground.Init(ground_model);
	player.Init(player_model);
	npc.Init(npc_model);
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

	//	�v���C���[�Ƃm�o�b�͈����߂��ɂȂ�Ȃ�
	//	���ꂼ��̍X�V�������I����č��W�����܂����̂ŁA�����ŋ߂Â��Ȃ��ݒ�����܂�

	


		CalculatePhysics();
	//	�v���C���[���W�Ƃm�o�b���W��n���ăJ�����̍X�V����
	camera.Update(player.m_pos, npc.m_pos);
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

	//	�m�o�b�̕`��
	npc.Render();
	//	�m�o�b�̑����ɉ~�̕`��
	DrawCircle3D_XZ(npc.m_pos, RADIUS, GetColor(255, 128, 0));

	//	�v���C���[���f���̕`��
	player.Render();
	//	�v���C���[�~�̕`��
	DrawCircle3D_XZ(player.m_pos, RADIUS, GetColor(0, 128, 255));

	DrawString(16, 16, "�\���L�[�F�v���C���[��]�E�ړ�", GetColor(255, 255, 255));
	DrawString(16, 32, "�v���C���[�Ƃm�o�b�����������ɉ�ʂɓ���悤�ȃJ����", GetColor(255, 255, 255));
	DrawString(16, 48, "�e�P�L�[�F����̃J����", GetColor(255, 255, 0));
	DrawString(16, 64, "�e�Q�L�[�F�v���C���[����O�E�m�o�b�����ɂȂ�悤�ȃJ����", GetColor(255, 255, 0));
	DrawString(16, 80, "�e�R�L�[�F�v���C���[�����E�m�o�b���E�ɂȂ�悤�ȃJ����", GetColor(255, 255, 0));
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
