#include "Main.h"
#include "Game.h"
#include "Random.h"
#include "Float2.h"
#include "Float3.h"
#include "Hit.h"

//	���f���f�[�^�p�̕ϐ�
int ground_model;
int npc_model;
int block_model;

//	�J�������W�ƌ���
Float3 camera_pos;
Float3 camera_rot;

#define NPC_SPEED	0.03f

#define PANEL_SIZE	1.0f
#define HALF_SIZE	(PANEL_SIZE*0.5f)

//	�m�o�b���W�ƌ���
Float3 npc_pos;
Float3 npc_rot;

Float3 half_size;

bool mouse_hit;

Float3 block_pos;

//---------------------------------------------------------------------------------
//	����������
//---------------------------------------------------------------------------------
void GameInit()
{
	//	�J�������W�̏����ݒ�
	camera_pos.set(10.0f, 15.0f, -5.5f);
	//	�J�����̌���
	camera_rot.set(50.0f, 0.0f, 0.0f);

	//	���f���f�[�^�̓ǂݍ���
	ground_model = MV1LoadModel("data/ground.mqoz");
	npc_model = MV1LoadModel("data/npc.mqoz");
	block_model = MV1LoadModel("data/block.mqoz");

	npc_pos.set(10.0f, 0.0f, 15.0f);
	npc_rot.set(0.0f, 180.0f, 0.0f);

	half_size.set(HALF_SIZE, HALF_SIZE, HALF_SIZE);

	mouse_hit = false;

	block_pos.set(0.0f, 0.0f, 0.0f);
}
//---------------------------------------------------------------------------------
//	�X�V����
//---------------------------------------------------------------------------------
void GameUpdate()
{
	npc_pos.z -= NPC_SPEED;

	//	�}�E�X���W�̎擾
	Float2 mouse;
	mouse.x = (float)GetMouseX();
	mouse.y = (float)GetMouseY();

	VECTOR vpos_start = ConvScreenPosToWorldPos(VGet(mouse.x, mouse.y, 0.0f));
	VECTOR vpos_goal = ConvScreenPosToWorldPos(VGet(mouse.x, mouse.y, 1.0f));

	MV1_COLL_RESULT_POLY hit_info = MV1CollCheck_Line(npc_model, -1, vpos_start, vpos_goal);

	if (hit_info.HitFlag)
	{
		mouse_hit = true;
	}
	else
	{
		mouse_hit = false;
	}

	if (PushMouseInput())
	{
		if (mouse_hit)
		{
		}
		else
		{
			hit_info = MV1CollCheck_Line(ground_model, -1, vpos_start, vpos_goal);

			Float3 pos(hit_info.HitPosition);

			if (pos.x >= 0.0f && pos.x <= 20.0f)
			{
				if (pos.z >= 0.0f && pos.z <= 10.0f)
				{
					block_pos = pos;
				}
			}
		}
	}

	if (CheckBoxHit3D(npc_pos, half_size, block_pos, half_size)) {
		npc_pos.x = GetRandomF(0.0f, 20.0f);
		npc_pos.z = 15.0f;
	}
}
//---------------------------------------------------------------------------------
//	�`�揈��
//---------------------------------------------------------------------------------
void GameRender()
{
	//	���W�ƌ�����n���ăJ�����̐ݒ�
	SetCameraPositionAndAngle(camera_pos.VGet(), TO_RADIAN(camera_rot.x), TO_RADIAN(camera_rot.y), TO_RADIAN(camera_rot.z));

	//	�n�ʃ��f���̕`��
	MV1DrawModel(ground_model);

	MV1SetPosition(block_model, VGet(block_pos.x, block_pos.y, block_pos.z));
	MV1DrawModel(block_model);

	//	�m�o�b�̃��f���̕`��
	MV1SetPosition(npc_model, VGet(npc_pos.x, npc_pos.y, npc_pos.z));
	MV1SetRotationXYZ(npc_model, VGet(TO_RADIAN(npc_rot.x), TO_RADIAN(npc_rot.y), TO_RADIAN(npc_rot.z)));
	MV1DrawModel(npc_model);

	DrawBox3D_XZ(Float3(10.0f, 0.0f, 5.0f), 10.0f, 5.0f, GetColor(255, 255, 0), FALSE);

	if (mouse_hit) {
		DrawString(16, 128, "�}�E�X�Ƃm�o�b���d�Ȃ��Ă��܂�", GetColor(255, 255, 0));
	}

	DrawString(16, 16, "�}�E�X�N���b�N�F�}�E�X�̐�̒n�ʂɃu���b�N�̃Z�b�g", GetColor(255, 255, 255));
	DrawString(16, 32, "�i�m�o�b�ƃ}�E�X���d�Ȃ��Ă��Ȃ��Ƃ��E���F���g�̒��j", GetColor(255, 255, 255));
	DrawString(16, 64, "�m�o�b�ƃu���b�N�œ����蔻�� �� ����������m�o�b���W�����_���ɍĐݒ�", GetColor(255, 255, 255));
}
//---------------------------------------------------------------------------------
//	�I������
//---------------------------------------------------------------------------------
void GameExit()
{
	MV1DeleteModel(ground_model);
	MV1DeleteModel(npc_model);
	MV1DeleteModel(block_model);
}
