#include "Main.h"
#include "Game.h"
#include "Random.h"
#include "Float2.h"
#include "Hit.h"

//	�~�̔��a
#define CIRCLE_RADIUS	15.0f

//	�|�C���g���W�̐�
#define POINT_MAX	6

//	�e�|�C���g�̊���W�i���W�ۑ�ŁA�X�y�[�X�L�[�����������͂��̍��W����Ƀ����_���Ɂj
Float2 base[POINT_MAX] = {
	{ 100.0f, 250.0f },
	{ 200.0f, 150.0f },
	{ 450.0f, 100.0f },
	{ 700.0f, 200.0f },
	{ 600.0f, 300.0f },
	{ 250.0f, 350.0f },
};
//	�e�|�C���g���W
Float2 point[POINT_MAX];

//	�}�E�X�����ɓ����Ă��邩
bool mouse_in;
bool check_ok;
int circle_num;

//---------------------------------------------------------------------------------
//	����������
//---------------------------------------------------------------------------------
void GameInit()
{
	//	�Ƃ肠�����������W�͊���W�ɂ��Ă��܂�
	for (int i = 0; i < POINT_MAX; i++) {
		point[i] = base[i];
	}
}
//---------------------------------------------------------------------------------
//	�X�V����
//---------------------------------------------------------------------------------
void GameUpdate()
{
	Float2 mouse;
	mouse.x = (float)GetMouseX();
	mouse.y = (float)GetMouseY();

	mouse_in = false;

	check_ok = true;

	if (PushMouseInput())
	{
		for (int i = 0; i < POINT_MAX; i++)
		{
			if (CheckPointCircleHit(mouse, point[i], CIRCLE_RADIUS))
			{
				circle_num = i;
			}
		}
	}

	if (CheckMouseInput())
	{
		if (circle_num >= 0)
		{
			point[circle_num].x += GetMouseMoveX();
			point[circle_num].y += GetMouseMoveY();
		}
		else
		{
			circle_num = -1;
		}
	}

	if (PushHitKey(KEY_INPUT_SPACE))
	{
		for (int i = 0; i < POINT_MAX; i++)
		{
			point[i].x = base[i].x + GetRandomF(-80.0f, 80.0f);
			point[i].y = base[i].y + GetRandomF(-80.0f, 80.0f);
		}
	}

	for (int p = 0; p < POINT_MAX; p++)
	{
		float cross[POINT_MAX];
		for (int i = 0; i < POINT_MAX; i++)
		{
			int n1 = p;
			int n2 = (p + 1) % POINT_MAX;
			int n3 = (p + 2) % POINT_MAX;

			Float2 dir12 = point[n2] - point[n1];
			Float2 dir13 = point[n3] - point[n1];

			cross[i] = GetFloat2Cross(dir12, dir13);
		}

		for (int i = 0; i < POINT_MAX; i++)
		{
			int n1 = i;
			int n2 = (i + 1) % POINT_MAX;
			if (cross[n1] * cross[n2] < 0.0f)
			{
				check_ok = false;
			}
		}

	}

	if (check_ok)
	{
		for (int i = 1; i < POINT_MAX - 1; i++)
		{
			Float2 t0 = point[0];
			Float2 t1 = point[i];
			Float2 t2 = point[i + 1];

			if (CheckPointTriangleHit(mouse, t0, t1, t2))
			{
				mouse_in = true;
			}
		}
	}
}
//---------------------------------------------------------------------------------
//	�`�揈��
//---------------------------------------------------------------------------------
void GameRender()
{
	//	�f�t�H���g�̐F
	int color = GetColor(150, 150, 150);
	if (mouse_in) {
		//	�}�E�X�������Ă��鎞�͉��F
		color = GetColor(255, 255, 0);
	}

	for (int i = 0; i < POINT_MAX; i++) {
		float x1 = point[i].x;
		float y1 = point[i].y;

		int n = (i + 1) % POINT_MAX;

		float x2 = point[n].x;
		float y2 = point[n].y;

		DrawLineAA(x1, y1, x2, y2, color);
	}

	//	�e�|�C���g���W��
	for (int i = 0; i < POINT_MAX; i++) {
		//	�~�̕`��
		DrawCircleAA(point[i].x, point[i].y, CIRCLE_RADIUS, 100, GetColor(255, 255, 255));
		//	�ꉞ�ԍ���������悤�ɕ�����ŕ`��
		DrawFormatStringF(point[i].x - 3.0f, point[i].y - 7.0f, GetColor(0, 0, 0), "%d", i);
	}

	DrawString(16, 16, "�e�|�C���g���W����Ō���", GetColor(255, 255, 0));
	DrawString(16, 32, "�}�E�X���Z�p�`�̒��ɓ���ƐF���ς��", GetColor(255, 255, 0));
}
//---------------------------------------------------------------------------------
//	�I������
//---------------------------------------------------------------------------------
void GameExit()
{
}
