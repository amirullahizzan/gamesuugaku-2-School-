#include "Main.h"
#include "Game.h"
#include "Hit.h"
#include "Random.h"
#include "Float3.h"
#include "Float2.h"

#include "Camera.h"
#include "Ground.h"
#include "Npc.h"

//	�{�[���̈ړ��X�s�[�h
#define BALL_SPEED		1.0f
//	�{�[���̔��a
#define BALL_RADIUS		0.1f
//	�m�o�b�̔��a
#define NPC_RADIUS		0.75f

//	���f���f�[�^�p�̕ϐ�
int ground_model;
int npc_model;

//	�N���X�̐錾
Camera camera;
Ground ground;
Npc	npc;

//	�J�[�\���~�̍��W
Float2 cursor;

//	�{�[���̍��W
Float3 ball_pos;
//	�{�[���̈ړ��x�N�g��
Float3 ball_mov;

//---------------------------------------------------------------------------------
//	����������
//---------------------------------------------------------------------------------
void GameInit()
{
	//	���f���f�[�^�̓ǂݍ���
	ground_model = MV1LoadModel("data/ground.mqoz");
	npc_model = MV1LoadModel("data/npc.mqoz");

	//	�N���X�̏�����
	camera.Init();
	ground.Init(ground_model);
	npc.Init(npc_model);

	ball_pos.clear();
	ball_mov.clear();
}
//---------------------------------------------------------------------------------
//	�X�V����
//---------------------------------------------------------------------------------
void GameUpdate()
{
	ground.Update();
	//	�m�o�b�̉�]
	npc.Update();
	//	�J�����̐ݒ�
	camera.Update();

	//	�}�E�X���W�̎擾
	cursor.x = GetMouseX();
	cursor.y = GetMouseY();

	//	�}�E�X���N���b�N�����Ƃ�
	if (PushMouseInput())
	{
		//ball_pos = camera.m_pos;
		//Float3 forward_vector = Float3(0.0f, 0.0f, 1.0f);
		//MATRIX mat_x = MGetRotX(TO_RADIAN(camera.m_rot.x));
		//MATRIX mat_y = MGetRotY(TO_RADIAN(camera.m_rot.y));
		//MATRIX mat = MMult(mat_x, mat_y);
		//ball_mov = GetFloat3VTransform(forward_vector, mat);
		//

	VECTOR worldPos = ConvScreenPosToWorldPos(VECTOR{ cursor.x, cursor.y, 0.0f });

	ball_pos.VSet(worldPos);

	ball_mov = ball_pos - camera.m_pos;
	

	ball_mov.SetLength(BALL_SPEED);
	}


	ball_pos += ball_mov;

	//	�{�[���Ƃm�o�b�̓����蔻��
	if (CheckBallHit(ball_pos, BALL_RADIUS, npc.m_pos, NPC_RADIUS)) {
		//	�m�o�b�̍��W���Đݒ�
		npc.SetRandom();
	}
}
//---------------------------------------------------------------------------------
//	�`�揈��
//---------------------------------------------------------------------------------
void GameRender()
{
	//	�J�����̐ݒ�
	camera.Render();

	ground.Render();
	npc.Render();

	DrawSphere3D(ball_pos.VGet(), BALL_RADIUS, 100, GetColor(255, 255, 0), GetColor(255, 255, 0), TRUE);

	//	�J�[�\���~�̕`��
	DrawCircleAA(cursor.x, cursor.y, 30.0f, 100, GetColor(255, 255, 0), FALSE);

	DrawString(16, 16, "�}�E�X���W�ɃJ�[�\��", GetColor(255, 255, 255));
	DrawString(16, 32, "�v�`�r�c�F�J������]", GetColor(255, 255, 255));
	DrawString(16, 48, "�N���b�N�F�{�[�����ˁi�}�E�X�̏�����R�c��Ԃ̉��Ɂj", GetColor(255, 255, 255));
	DrawString(16, 64, "���@�{�[�����m�o�b�ɓ�����������W���Đݒ�", GetColor(255, 255, 255));
}
//---------------------------------------------------------------------------------
//	�I������
//---------------------------------------------------------------------------------
void GameExit()
{
	camera.Exit();
	ground.Exit();
	npc.Exit();

	MV1DeleteModel(ground_model);
	MV1DeleteModel(npc_model);
}
