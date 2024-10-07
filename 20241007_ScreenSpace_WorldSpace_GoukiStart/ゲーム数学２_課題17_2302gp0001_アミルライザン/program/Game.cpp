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

//	�J�[�\���~�̍��W�i�Q�c��ʍ��W�F�Q�c�Ȃ̂� Float2 �ł��j
Float2 cursor;

//	�{�[���̍��W�i�R�c��ԍ��W�F���[���h���W�j
Float3 ball_pos;
//	�{�[���̈ړ��x�N�g���i�R�c��Ԃ��ړ�����x�N�g���j
Float3 ball_mov;

float alpha_blend = 0.0f;

float displayTimer = 0.0f;

Float2 textPos;
float textPosOffsetY;

int mode = 0;

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
	//	�Ƃ肠�����O������
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

	//	�}�E�X���W�̎擾�i�Q�c��ʍ��W�j
	cursor.x = GetMouseX();
	cursor.y = GetMouseY();

	//	�}�E�X���N���b�N�����Ƃ�
	if (PushMouseInput()) {
		//	�}�E�X���W���R�c���W�ɕϊ����Ă�������{�[�����J��������}�E�X�̐�����Ɉړ���������
		//	�J�[�\�����W��ϊ����ĂR�c��Ԃ̍��W�Ɏ����Ă������߂�
		VECTOR pos2d = VGet(cursor.x, cursor.y, 0.0f);
		//	���̍��W��ϊ����܂��i�Q�c��ʍ��W���R�c��ԍ��W�i���[���h���W�j�ɕϊ��j
		VECTOR wpos = ConvScreenPosToWorldPos(pos2d);

		//	��ŋ��߂����W���{�[���̍��W�ɂ��܂�
		ball_pos.VSet(wpos);
		//	�{�[���̈ړ��x�N�g���͉�ʂ̉��ɍs���悤�ɂ������i�J�������W���獡���߂����W�̕����j
		ball_mov = ball_pos - camera.m_pos;
		//	�{�[���̈ړ��X�s�[�h�̐ݒ�
		ball_mov.SetLength(BALL_SPEED);
	}

	//	�{�[���̍��W�ړ�
	ball_pos += ball_mov;

	//	�{�[���Ƃm�o�b�̓����蔻��
	if (CheckBallHit(ball_pos, BALL_RADIUS, npc.m_pos, NPC_RADIUS))
	{
		//	����������m�o�b���ɁuHIT!!!�v�\�����J�n
	
		displayTimer = 20.0f;
		npc.speedMult = 10.0f;
		textPosOffsetY = 0.0f;
		mode = 0;
	}

	VECTOR worldPos = npc.m_pos.VGet();
	VECTOR screenPos = ConvWorldPosToScreenPos(worldPos);
	textPos = { screenPos.x - 5.0f,screenPos.y + 2.0f };

	switch (mode)
	{
	case 0 :
		if (displayTimer > 0.0f)
		{
			displayTimer--;
			textPosOffsetY -= 1.2f;

			if (alpha_blend < 255.0f)
			{
				alpha_blend += 20.0f;
			}
		}
		else
		{
			displayTimer = 20.0f;
			mode++;
		}
		break;
	case 1:
		if (displayTimer > 0.0f)
		{
			displayTimer--;
		}
		else
		{
			mode++;
		}
		break;
	case 2:
		if (alpha_blend > 0.0f)
		{
			textPosOffsetY -= 1.2f;
			alpha_blend -= 20.0f;
			displayTimer--;
		}
		else
		{
			mode++;
		}
		break;
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

	//	�{�[���̕`��
	DrawSphere3D(ball_pos.VGet(), BALL_RADIUS, 100, GetColor(255, 255, 0), GetColor(255, 255, 0), TRUE);

	if (alpha_blend > 0.0f)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha_blend);
		DrawString(textPos.x - 25.0f, textPos.y + textPosOffsetY, "HIT!!!", GetColor(255, 255, 255));
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

	//	�J�[�\���~�̕`��
	DrawCircleAA(cursor.x, cursor.y, 30.0f, 100, GetColor(255, 255, 0), FALSE);

	DrawString(16, 16, "�}�E�X���W�ɃJ�[�\��", GetColor(255, 255, 255));
	DrawString(16, 32, "�v�`�r�c�F�J������]", GetColor(255, 255, 255));
	DrawString(16, 48, "�N���b�N�F�{�[�����ˁi�}�E�X�̏�����R�c��Ԃ̉��Ɂj", GetColor(255, 255, 255));
	DrawString(16, 64, "���@�{�[�����m�o�b�ɓ���������uHIT!!!�v�\��", GetColor(255, 255, 0));
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
