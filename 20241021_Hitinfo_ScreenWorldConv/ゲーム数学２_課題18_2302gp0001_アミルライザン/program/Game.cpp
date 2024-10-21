#include "Main.h"
#include "Game.h"
#include "Random.h"
#include "Float2.h"
#include "Float3.h"
#include "Hit.h"

//	���f���f�[�^�p�̕ϐ�
int ground_model;
int npc_model;
int block_model;	//	�u���b�N���f��
int panel_model;	//	�u���b�N��u���Ă��Ȃ��Ƃ���p�̃p�l�����f��

//	�J�������W�ƌ���
Float3 camera_pos;
Float3 camera_rot;

//	�m�o�b�ړ��X�s�[�h
#define NPC_SPEED	0.03f

//	�u���b�N�̑傫��
#define PANEL_SIZE	1.0f
//	�u���b�N�̔����̑傫���i�����蔻��ł��̒l���g���܂��j
#define HALF_SIZE	(PANEL_SIZE*0.5f)

//	�m�o�b���W�ƌ���
Float3 npc_pos;
Float3 npc_rot;
//	��̔����̑傫��������p�̕ϐ�
Float3 half_size;

//	�m�o�b�ƃ}�E�X���d�Ȃ��Ă��邩�ǂ���
bool mouse_hit;

//	�}�b�v�̃T�C�Y
#define MAP_W		20	//	��
#define	MAP_H		10	//	�c
//	�}�b�v�f�[�^�i�N���b�N�����n�ʂɍ��킹�Ă��̒l���P�ɂ������j
int MapData[MAP_H][MAP_W];
//	����̓u���b�N���W�ł͂Ȃ��Ă��̔z������ău���b�N��u���܂�

int frame;
Float3 camera_offset;

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
	panel_model = MV1LoadModel("data/panel.mqoz");

	//	�}�E�X�̐�̐��ƒn�ʃ��f���œ����蔻����������@���@�Ȃ̂Œn�ʃ��f���̓���������쐬���܂�
	MV1SetupCollInfo(ground_model);
	//	�}�E�X�̐�̐��Ƃm�o�b���f���œ����蔻����������@���@�Ȃ̂łm�o�b���f���̓���������쐬���܂�
	MV1SetupCollInfo(npc_model);

	npc_pos.set(10.0f, 0.0f, 15.0f);
	npc_rot.set(0.0f, 180.0f, 0.0f);
	//	�����蔻��p�ɑ傫���p�̕ϐ���ݒ�
	half_size.set(HALF_SIZE, HALF_SIZE, HALF_SIZE);
	//	�d�Ȃ��Ă��Ȃ���Ԃ���J�n
	mouse_hit = false;

	//	�}�b�v�f�[�^�̏������i�S���O�Ŗ��߂���ԂŊJ�n�j
	for (int h = 0; h < MAP_H; h++) {
		for (int w = 0; w < MAP_W; w++) {
			MapData[h][w] = 0;
		}
	}
}
//---------------------------------------------------------------------------------
//	�X�V����
//---------------------------------------------------------------------------------
void GameUpdate()
{
	//	���f���Ɛ��œ����蔻������邽�߂ɓ�������̍X�V�����܂�
	MV1RefreshCollInfo(ground_model);
	MV1RefreshCollInfo(npc_model);

	//	����̓T���v���̂܂܉�ʎ�O�Ɉړ����Ă��܂��i�ۑ�Q�F�m�o�b�̌����ɍ��킹�Ĉړ��j
	//npc_pos.z -= NPC_SPEED;
	Float3 base(0.0f, 0.0f, NPC_SPEED);
	MATRIX mat = MGetRotY(TO_RADIAN(npc_rot.y));
	Float3 mov = GetFloat3VTransform(base, mat);
	npc_pos += mov;

	//	�}�E�X���W�̎擾
	Float2 mouse;
	mouse.x = (float)GetMouseX();
	mouse.y = (float)GetMouseY();

	//	�}�E�X���W�i��ʍ��W�j���R�c��ԍ��W�ɕϊ�
	//	�J�����ŉf����Ă��钆�̈�Ԏ�O�̂R�c��ԍ��W
	VECTOR wpos_start = ConvScreenPosToWorldPos(VGet(mouse.x, mouse.y, 0.0f));
	//	��ԉ��̍��W
	VECTOR wpos_goal = ConvScreenPosToWorldPos(VGet(mouse.x, mouse.y, 1.0f));

	//	��ŋ��߂��Q�_����Ƃ��Ăm�o�b���f���Ɠ����蔻��
	MV1_COLL_RESULT_POLY hit_info = MV1CollCheck_Line(npc_model, -1, wpos_start, wpos_goal);
	//	�������Ă�����
	if (hit_info.HitFlag) {
		//	�d�Ȃ��Ă���t���O�𗧂Ă܂��i��������ĕ�����`�悵�܂��j
		mouse_hit = true;
	}
	else {
		//	����Ȃ�������t���O�𗎂Ƃ�
		mouse_hit = false;
	}

	//	�}�E�X���N���b�N������A���̐�̒n�ʂɃu���b�N��u������
	if (PushMouseInput()) {
		if (mouse_hit) {
			//	�Ƃ肠�����m�o�b���W�������_���ɂ�������͂��Ă��܂�
			npc_pos.x = GetRandomF(0.0f, 20.0f);
			npc_pos.z = 15.0f;

			//	�ۑ�Q�F�m�o�b�̌����̐ݒ�
			Float3 goal;
			goal.x = GetRandomF(0.0f, 20.0f);
			goal.y = 0.0f;
			goal.z = GetRandomF(0.0f, 10.0f);

			float x = goal.x - npc_pos.x;
			float z = goal.z - npc_pos.z;

			npc_rot.y = TO_DEGREE(atan2f(x, z));
		}
		else {
			//	�}�E�X���ƒn�ʃ��f���œ����蔻������ē���������擾
			hit_info = MV1CollCheck_Line(ground_model, -1, wpos_start, wpos_goal);
			//	�������Ă�����
			if (hit_info.HitFlag) {
				//	�������Ă�����W�����߂�
				Float3 pos(hit_info.HitPosition);

				//	����̃u���b�N�͉��F���l�p�͈̔͂̒��ɂ����u���Ȃ�
				//	�w���W�� 0.0f �` 20.0f �̊�
				if (pos.x >= 0.0f && pos.x <= 20.0f) {
					//	�y���W�� 0.0f �` 10.0f �̊�
					if (pos.z >= 0.0f && pos.z <= 10.0f)
					{
						int w = (int)(pos.x / PANEL_SIZE);
						int h = (int)(pos.z / PANEL_SIZE);
						//	�ۑ�P�F�}�E�X�N���b�N�Ńu���b�N�z�u�i�n�ʂ̃}�X�ڂɍ��킹�āFMapData[][] ���g���āj
						MapData[h][w] = 1;
					}
				}
			}
		}
	}

	//	�}�b�v��̃u���b�N�Ƃm�o�b�œ����蔻��i�ۑ�R�F�m�o�b�Ɠ��������u���b�N�͏�����FMapData[][] ���g���āj
	for (int h = 0; h < MAP_H; h++) {

		for (int w = 0; w < MAP_W; w++) {
			if (MapData[h][w] == 1)
			{
				Float3 pos;
				pos.x = w * PANEL_SIZE + HALF_SIZE;
				pos.y = 0.0f;
				pos.z = h * PANEL_SIZE + HALF_SIZE;
				if (CheckBoxHit3D(npc_pos, half_size, pos, half_size))
				{
					MapData[h][w] == 0;

					frame = 10;
				}
			}
		}
	}
	if (frame > 0)
	{
		frame--;
		camera_offset.set(GetRandomF(-0.1f,0.1f), GetRandomF(-0.1f, 0.1f), GetRandomF(-0.1f, 0.1f));
	}
	else
	{
		camera_offset.clear();
	}
}
//---------------------------------------------------------------------------------
//	�`�揈��
//---------------------------------------------------------------------------------
void GameRender()
{
	Float3 pos = camera_pos + camera_offset;

	//	���W�ƌ�����n���ăJ�����̐ݒ�
	SetCameraPositionAndAngle(pos.VGet(), TO_RADIAN(camera_rot.x), TO_RADIAN(camera_rot.y), TO_RADIAN(camera_rot.z));

	//	�n�ʃ��f���̕`��
	MV1DrawModel(ground_model);

	//	�}�b�v�̕`��
	for (int h = 0; h < MAP_H; h++) {
		for (int w = 0; w < MAP_W; w++) {
			//	�`�悷�邽�߂̍��W��ݒ�iMapData[][] ���g���� BLOCK_SIZE ���炵�ĕ��ׂ܂��j
			Float3 pos;
			pos.x = w * PANEL_SIZE + HALF_SIZE;
			pos.y = 0.0f;
			pos.z = h * PANEL_SIZE + HALF_SIZE;
			//	���̃p�l�������͂��ׂĕ`�悵�Ă��܂�
			MV1SetPosition(panel_model, pos.VGet());
			MV1DrawModel(panel_model);


			//	�ۑ�P�F�}�E�X�N���b�N�Ńu���b�N�z�u�i�n�ʂ̃}�X�ڂɍ��킹�āFMapData[][] ���g���āj
			if (MapData[h][w] == 1)
			{
				MV1SetPosition(block_model, pos.VGet());
				MV1DrawModel(block_model);
			}
		}
	}

	//	�m�o�b�̃��f���̕`��
	MV1SetPosition(npc_model, VGet(npc_pos.x, npc_pos.y, npc_pos.z));
	MV1SetRotationXYZ(npc_model, VGet(TO_RADIAN(npc_rot.x), TO_RADIAN(npc_rot.y), TO_RADIAN(npc_rot.z)));
	MV1DrawModel(npc_model);

	//	�w���W 0.0f �` 20.0f�@�y���W 0.0f �` 10.0f �̎l�p�ł�
	DrawBox3D_XZ(Float3(10.0f, 0.0f, 5.0f), 10.0f, 5.0f, GetColor(255, 255, 0), FALSE);

	if (mouse_hit) {
		//	�}�E�X�Ƃm�o�b���d�Ȃ��Ă��鎞������̕`��
		DrawString(16, 128, "�}�E�X�Ƃm�o�b���d�Ȃ��Ă��܂�", GetColor(255, 255, 0));
	}

	DrawString(16, 16, "�}�E�X�N���b�N�F�}�E�X�̐�̒n�ʂɃu���b�N�̃Z�b�g", GetColor(255, 255, 255));
	DrawString(16, 32, "�i�m�o�b�ƃ}�E�X���d�Ȃ��Ă��Ȃ��Ƃ��E���F���g�̒��j", GetColor(255, 255, 255));
	DrawString(16, 48, "���@�n�ʂ̃}�X�ڂɍ��킹�ău���b�N�̃Z�b�g", GetColor(255, 255, 0));
	DrawString(16, 64, "�m�o�b�N���b�N�F�m�o�b���W�����_���ɍĐݒ�", GetColor(255, 255, 255));
	DrawString(16, 80, "���@���F���g���̃����_���ȍ��W�̕����Ɉړ�����i�Ȃ̂Ō������ς���j", GetColor(255, 255, 0));
	DrawString(16, 96, "���@�m�o�b�Ɠ��������u���b�N�͏�����", GetColor(255, 255, 0));
}
//---------------------------------------------------------------------------------
//	�I������
//---------------------------------------------------------------------------------
void GameExit()
{
	MV1DeleteModel(ground_model);
	MV1DeleteModel(npc_model);
	MV1DeleteModel(block_model);
	MV1DeleteModel(panel_model);
}
