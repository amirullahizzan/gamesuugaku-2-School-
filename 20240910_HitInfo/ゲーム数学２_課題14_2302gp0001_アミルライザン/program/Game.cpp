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

bool draw_circle;
Float3 set_pos;

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
	//	�n�ʃ��f���i����͍������g�����������������Ǝv���܂��̂ŁA�N���̂���n�ʃ��f����ǂݍ���ł��܂��j
	ground_model = MV1LoadModel("data/ground.mqoz");
	player_model = MV1LoadModel("data/player.mqoz");

	//	�P�F�n�ʃ��f���Ƃ̓����蔻������悤�Ǝv���܂��̂œ���������쐬���܂�
	MV1SetupCollInfo(ground_model);

	//	�N���X�̏�����
	camera.Init();
	ground.Init(ground_model);
	player.Init(player_model);
}
//---------------------------------------------------------------------------------
//	�X�V����
//---------------------------------------------------------------------------------
void GameUpdate()
{
	//	�Q�F����������擾���邽�߂̏��̍X�V
	MV1RefreshCollInfo(ground_model);

	//	�n�ʂ̍X�V����
	ground.Update();
	//	�v���C���[�̍X�V�����i����̃v���W�F�N�g�ł͓��ɉ������Ă��܂���j
	player.Update();

	//	�v���C���[�̍��W�����܂����̂ł��̏�Ԃœ����蔻������܂�
	//	�R�F���f���Ɛ��œ����蔻��
	//	�R�|�P�F���̂��߂̂Q�̍��W��p�ӂ��܂��i����̓v���C���[�̏�Ɖ��j
	//	�J�n���W�̓v���C���[�̏�
	//	�i�J�n���W���v���C���[�̑����ɂ��Ă��܂��ƒn�ʂ̉��ł̔���ɂȂ�󋵂��������Ă��܂��̂Łj
	Float3 line_start = player.m_pos + Float3(0.0f, 100.0f, 0.0f);
	//	�S�[�����W�̓v���C���[�̉�
	Float3 line_goal = player.m_pos + Float3(0.0f, -100.0f, 0.0f);

	//	�R�|�Q�F�����蔻������āA�����������ʏ����擾
	MV1_COLL_RESULT_POLY hit_info = MV1CollCheck_Line(ground_model, -1, line_start.VGet(), line_goal.VGet());

	//	�n�ʂ̍����i�n�ʂƂ̓����蔻�肪���Ȃ������ꍇ�� 0.0f �Ƃ��悤�Ǝv���܂��j
	float ground_y = 0.0f;

	//	�S�F����������g���ăv���C���[��n�ʂ̍����ɂ�����
	//	�������Ă�����
	if (hit_info.HitFlag) {
		//	�������Ă�����W�̂x���W��n�ʂ̍����ɂ��܂�
		ground_y = hit_info.HitPosition.y;
	}

	//	�v���C���[�̂x���W���n�ʂ̍����������ɂ���Ƃ��͒n�ʂɖ��܂��Ă���Ƃ������Ȃ̂�
//	if( player.m_pos.y < ground_y ){
		//	�n�ʂ̍����ɂ��܂�
	player.m_pos.y = ground_y;
	//	}

	camera.Update();

	line_start = camera.m_pos;

	Float3 base(0.0f, 0.0f, 100.0f);
	MATRIX mat_x = MGetRotX(TO_RADIAN(camera.m_rot.x));
	MATRIX mat_y = MGetRotY(TO_RADIAN(camera.m_rot.y));
	MATRIX mat = MMult(mat_x, mat_y);
	Float3 change = GetFloat3VTransform(base, mat);

	line_goal = line_start + change;

	hit_info = MV1CollCheck_Line(ground_model, -1, line_start.VGet(), line_goal.VGet());

	if (hit_info.HitFlag)
	{
		draw_circle = true;
		set_pos.VSet(hit_info.HitPosition);
	}
	else
	{
		draw_circle = false;
	}

	if (PushHitKey(KEY_INPUT_SPACE) && draw_circle)
	{
		player.m_pos = set_pos;
	}
}
//---------------------------------------------------------------------------------
//	�`�揈��
//---------------------------------------------------------------------------------
void GameRender()
{
	camera.Render();
	ground.Render();
	player.Render();

	if (draw_circle)
	{
		float distance = GetFloat3Distance(camera.m_pos, set_pos);
		float rate = distance / 100.0f;
		rate = 1.0f - rate;
		float radius = 50.0f * rate;
		DrawCircle(SCREEN_W / 2, SCREEN_H / 2, radius, GetColor(255, 255, 0), FALSE);
	}

	DrawString(16, 16, "�\���L�[�F�J������]", GetColor(255, 255, 255));
	DrawString(16, 32, "�X�y�[�X�F�J�����̌��Ă����ƒn�ʂ��������Ă���ꏊ�Ƀv���C���[�ݒu", GetColor(255, 255, 0));
	DrawString(16, 48, "�J���������Ă�������̒����̐�ɒn�ʂ��Ȃ����͉~�̕`��͂��Ȃ��i�v���C���[�̐ݒu�����Ȃ��j", GetColor(255, 255, 0));
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
}
