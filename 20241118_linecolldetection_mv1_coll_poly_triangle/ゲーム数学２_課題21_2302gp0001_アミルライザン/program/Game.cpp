#include "Main.h"
#include "Game.h"
#include "Hit.h"
#include "Random.h"
#include "Float3.h"

#include "Camera.h"
#include "Ground.h"
#include "Player.h"

//	���̒���
#define LINE_LENGTH		30.0f

//	�f�[�^�p�̕ϐ�
int ground_model;
int player_model;
int npc_model;
int wall_model;

//	�N���X�̐錾
Camera	camera;
Ground	ground;
Player	player;

//	���̊J�n���W
Float3 line_start;
//	���̃S�[�����W
Float3 line_goal;
//	���̌����p�x�i�x�j�F�x���̉�]�p�x�Ƃ��Ďg���܂�
float line_rot;

//	�v���C���[�����̉E�ɂ��邩�ǂ���
bool player_right;

//---------------------------------------------------------------------------------
//	����������
//---------------------------------------------------------------------------------
void GameInit()
{
	//	�f�[�^�̓ǂݍ���
	ground_model = MV1LoadModel("data/ground.mqoz");
	player_model = MV1LoadModel("data/player.mqoz");
	//	����̂m�o�b���f���̓N���X�ł͂Ȃ����̊J�n���W�̖ڈ��Ƃ��ĕ`�悵�܂�
	npc_model = MV1LoadModel("data/npc.mqoz");
	wall_model = MV1LoadModel("data/wall.mqoz");

	MV1SetupCollInfo(wall_model);



	//	�N���X�̏�����
	camera.Init();
	ground.Init(ground_model);
	player.Init(player_model);

	//	���̊J�n���W�̐ݒ�
	line_start.set(-5.0f, 0.0f, -10.0f);
	//	�X�V�����ł����ɍ��W���ς��܂����ǁA�Ƃ肠����
	line_goal.set(0.0f, 0.0f, 0.0f);
	//	�O�x����J�n
	line_rot = 0.0f;

	player_right = false;
}

int draw_frame;
//---------------------------------------------------------------------------------
//	�X�V����
//---------------------------------------------------------------------------------
void GameUpdate()
{
	Float3 before_line_dir = line_goal - line_start;
	Float3 before_player_dir = player.m_pos - line_start;
	Float3 before_cross = GetFloat3Cross(before_line_dir, before_player_dir);

	ground.Update();
	player.Update();
	camera.Update();
	//	���̊p�x���X�V�i����̐��͎����ŉ�]�����Ă��܂��j
	line_rot += 2.0f;

	//	���̊p�x�̕����� LINE_LENGTH ����̂Ƃ���ɃS�[�����W��ݒ�
	Float3 base(0.0f, 0.0f, LINE_LENGTH);
	MATRIX mat = MGetRotY(TO_RADIAN(line_rot));
	Float3 change = GetFloat3VTransform(base, mat);
	line_goal = line_start + change;

	Float3 line_dir = line_goal - line_start;
	line_dir.y = 0.0f;
	Float3 player_dir = player.m_pos - line_start;
	player_dir.y = 0.0f;
	Float3 cross = GetFloat3Cross(line_dir, player_dir);

	MV1RefreshCollInfo(wall_model);

	MV1_COLL_RESULT_POLY hit_info = MV1CollCheck_Line(wall_model, -1, line_start.VGet(), line_goal.VGet());

	if (hit_info.HitFlag)
	{
		line_goal.VSet(hit_info.HitPosition);
	}

	Float3 dir_start = line_start - player.m_pos;
	Float3 dir_goal = line_goal - player.m_pos;

	if (GetFloat3Dot(dir_start, dir_goal) < 0.0f)
	{
		if (before_cross.y * cross.y <= 0.0f)
		{
			draw_frame = 60;
		}
	}

	draw_frame--;
}
//---------------------------------------------------------------------------------
//	�`�揈��
//---------------------------------------------------------------------------------
void GameRender()
{
	camera.Render();

	ground.Render();
	player.Render();
	//	���̕`��i���̂܂܂̍��W���Ɛ��̕`�悪�n�ʂɖ��܂��Ă��܂��ꍇ������̂ŏ�����ɂ����Ă��܂��j
	Float3 start = line_start + Float3(0.0f, 0.1f, 0.0f);
	Float3 goal = line_goal + Float3(0.0f, 0.1f, 0.0f);
	//	�J�n���W�ƃS�[�����W������Ő��̕`��
	DrawLine3D(start.VGet(), goal.VGet(), GetColor(255, 255, 0));

	//	���̊J�n���W�̖ڈ��Ƃ��Ă��̏ꏊ�Ɂi�������j�m�o�b���f���̕`�悾�����Ă��܂�
	MV1SetPosition(npc_model, line_start.VGet());
	MV1SetRotationXYZ(npc_model, VGet(0.0f, TO_RADIAN(line_rot), 0.0f));
	MV1DrawModel(npc_model);
	MV1DrawModel(wall_model);

	//	�S�[�����W�ɉ��F�����̕`��
	DrawSphere3D(goal.VGet(), 0.3f, 100, GetColor(255, 255, 0), GetColor(255, 255, 0), TRUE);

	Float3 pos1;
	Float3 pos2;
	Float3 pos3;

	Float3 dir1to2 = pos2 - pos1;
	Float3 dir1toPlayer = player.m_pos - pos1;

	Float3 dir2to3 = pos3 - pos2;
	Float3 dir2toPlayer = player.m_pos - pos2;

	Float3 dir3to1 = pos1 - pos3;
	Float3 dir3toPlayer = player.m_pos - pos3;

	bool triangle_in = false;
	Float3 cross1 = GetFloat3Cross(dir1to2, dir1toPlayer);
	Float3 cross2 = GetFloat3Cross(dir2to3, dir2toPlayer);
	Float3 cross3 = GetFloat3Cross(dir3to1, dir3toPlayer);

	if (cross1.y > 0.0f && cross2.y > 0.0f && cross3.y > 0.0f)
	{
		triangle_in = true;
	}
	if (cross1.y < 0.0f && cross2.y < 0.0f && cross3.y < 0.0f)
	{
		triangle_in = true;
	}

	DrawLine3D(pos1.VGet(), pos2.VGet(), GetColor(0, 255, 0));
	DrawLine3D(pos2.VGet(), pos3.VGet(), GetColor(0, 255, 0));
	DrawLine3D(pos3.VGet(), pos1.VGet(), GetColor(0, 255, 0));

	if (triangle_in)
	{
		DrawString(450, 270, "�O�p�̒��Ƀv���C���[�����܂�", GetColor(0, 255, 0));

	}

	if (draw_frame > 0)
	{
		DrawString(336, 350, "�����ʉ߂��܂���", GetColor(255, 255, 0));
	}

	DrawString(16, 16, "�\���L�[�F�v���C���[�̉�]�E�ړ�", GetColor(255, 255, 255));
	DrawString(16, 32, "�����ʉ߂������Ɉ�莞�ԕ�����̕`��", GetColor(255, 255, 0));
}
//---------------------------------------------------------------------------------
//	�I������
//---------------------------------------------------------------------------------
void GameExit()
{
	camera.Exit();
	ground.Exit();
	player.Exit();

	MV1DeleteModel(ground_model);
	MV1DeleteModel(player_model);
	MV1DeleteModel(npc_model);
}
