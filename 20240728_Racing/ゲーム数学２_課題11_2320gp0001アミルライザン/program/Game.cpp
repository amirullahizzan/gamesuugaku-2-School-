#include "Main.h"
#include "Game.h"
#include "Hit.h"

#include "Camera.h"
#include "Ground.h"
#include "Player.h"

int ground_model;
int player_model;

Camera	camera;
Ground	ground;
Player	player;

//	�|�C���g�̐�
#define POINT_MAX	6
//	�e�|�C���g�̍��W
Float3 point[POINT_MAX] =
{
	{ -25.0f, 0.01f, -15.0f },
	{ -25.0f, 0.01f,  25.0f },
	{   5.0f, 0.01f,  25.0f },
	{   5.0f, 0.01f,   5.0f },
	{  25.0f, 0.01f,   5.0f },
	{  25.0f, 0.01f, -15.0f },
};

//	�v���C���[�����ԋ߂����̔ԍ�
int near_line;

//---------------------------------------------------------------------------------
//	����������
//---------------------------------------------------------------------------------
void GameInit()
{
	ground_model = MV1LoadModel("data/ground.mqoz");
	player_model = MV1LoadModel("data/player.mqoz");

	camera.Init();
	ground.Init(ground_model);
	player.Init(player_model);

	//	�Ƃ肠�����O�Ԗڂ̐�����ԋ߂��Ƃ��Ă��܂�
	near_line = 0;
}
//---------------------------------------------------------------------------------
//	�X�V����
//---------------------------------------------------------------------------------
void GameUpdate()
{
	ground.Update();

	float near_length = 1000.0f;

	for (int i = 0; i < POINT_MAX; i++)
	{
		int p1 = i;
		int p2 = (i + 1) & POINT_MAX;

		float now_length = GetFloat3LinePointNearDistance(point[p1], point[p2], player.m_pos);

		if (now_length < near_length)
		{
			near_line = i;

			near_length = now_length;
		}

	}

	//	�ړ��x�N�g�����g�������W�ړ�
	player.Update(near_length);

	//	�K�v�ȏ���n���ăJ�����ݒ�
	//	�i���W�E�����E�ړ��x�N�g���j
	camera.Update(player.m_pos, player.m_rot, player.m_mov);
}
//---------------------------------------------------------------------------------
//	�`�揈��
//---------------------------------------------------------------------------------
void GameRender()
{
	camera.Render();

	ground.Render();

	//	�e�|�C���g������Ő��̕`��
	for (int i = 0; i < POINT_MAX; i++) {
		//	�P�_�ڂ̔ԍ�
		int p1 = i;
		//	�Q�_�ڂ̔ԍ�
		int p2 = (i + 1) % POINT_MAX;
		int color = GetColor(200, 200, 200);
		//	��ԋ߂����̐F��ς���
		if (i == near_line) {
			color = GetColor(255, 255, 0);
		}
		//	�Q�_�̍��W������Ő��̕`��
		DrawLine3D(point[p1].VGet(), point[p2].VGet(), color);
	}

	player.Render();

	int p1 = near_line;
	int p2 = (near_line + 1) % POINT_MAX;

	Float3 line_dir = point[p2] - point[p1];
	line_dir.normalize();

	Float3 player_front = player.m_mov;
	player_front.normalize();

	if (GetFloat3Dot(player_front, line_dir) < 0.0f)
	{
		DrawString(350, 200, "�t�����Ă�", GetColor(0, 255, 255));
	}

	DrawString(16, 16, "�\���L�[�F�v���C���[��]�E�ړ�", GetColor(255, 255, 255));
	DrawString(16, 32, "�@�e�P�L�[�F�S�̃J����", GetColor(255, 255, 255));
	DrawString(16, 48, "�@�e�Q�L�[�F�v���C���[�J�����i�y�}�C�i�X��������j", GetColor(255, 255, 255));
	DrawString(16, 64, "�@�e�R�L�[�F�v���C���[�̌��ɂ��Ă����悤�ȃJ����", GetColor(255, 255, 255));

	DrawString(16, 96, "�v���C���[�Ɉ�ԋ߂����C���̐F�̕ύX", GetColor(255, 255, 0));
	DrawString(16, 112, "�R�[�X�͎��v���ŁF�t��������x���\��", GetColor(255, 255, 0));
	DrawString(16, 128, "��ԋ߂����C�����痣�ꂷ������X�s�[�h�𗎂Ƃ�", GetColor(255, 255, 0));

	DrawString(16, 32 + 16 * camera.m_type, "��", GetColor(255, 255, 255));
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
