#include "Main.h"
#include "Game.h"
#include "Hit.h"
#include "Random.h"
#include "Float2.h"
#include "Float3.h"

//	�{�[���̔��a
#define BALL_RADIUS		0.2f
//	�{�[�����o�Ă��鍕���~�̔��a
#define START_RADIUS	1.0f
//	�{�[���̈ړ��X�s�[�h
#define BALL_SPEED		0.5f

//	�o��G���A�~�̔��a
#define AREA_RADIUS		6.0f

//�o��G���A�̐�
#define AREA_MAX	6
//	�e�G���A�̒��S���W
Float3 area_pos[AREA_MAX] = {
	{   8.0f, 0.1f,   7.0f },
	{  -8.0f, 0.1f,   7.0f },
	{   8.0f, 0.1f, -13.0f },
	{  -8.0f, 0.1f, -13.0f },
	{  20.0f, 0.1f,  -3.0f },
	{ -20.0f, 0.1f,  -3.0f },
};

//	��ʂɂԂ������Ƃ��ɕ`�悷��y�C���g�摜
int paint_image;
//	���f��
int ground_model;

//	�J�������W�ƌ���
Float3 camera_pos;
Float3 camera_rot;

//	�{�[�����ˍ��W�i���[���h���W�j
Float3 start_pos;

//	�{�[���̍��W�i���[���h���W�j
Float3 ball_pos;
//	�{�[���̈ړ��x�N�g��
Float3 ball_mov;
//	�{�[�������ł���̂��ǂ���
bool ball_active;

//	�y�C���g�摜�̕\�����W�i�Q�c�̕`����W�F�w�E�x���g���ĕ`�悵�܂��j
Float2 paint_pos;

//	��莞�Ԃ𐔂���p�̕ϐ�
int frame_count;

int area_num;
int shake_frame;

float start_radius;
int paint_alpha;


//---------------------------------------------------------------------------------
//	����������
//---------------------------------------------------------------------------------
void GameInit()
{
	//	�J�������W�̏����ݒ�
	camera_pos.set( 0.0f, 25.0f, -35.0f );
	//	�J�����̌���
	camera_rot.set( 37.0f, 0.0f, 0.0f );

	//	�y�C���g�摜�̓ǂݍ���
	paint_image = LoadGraph( "data/paint.bmp" );

	ground_model = MV1LoadModel( "data/ground.mqoz" );

	start_pos.set( 0.0f, 0.1f, 0.0f );
	frame_count = 0;

	//	�{�[���̏����ݒ�
	ball_pos.clear();
	ball_mov.clear();
	//	�{�[���͔��ł��Ȃ���Ԃ���J�n
	ball_active = false;

	//	�y�C���g�摜�̕\�����W
	paint_pos.set( 0.0f, 0.0f );
}
//---------------------------------------------------------------------------------
//	�X�V����
//---------------------------------------------------------------------------------
void GameUpdate()
{
	frame_count++;

	if (frame_count >= 0 && frame_count <= 20) start_radius += 0.05f;
	if (frame_count >= 250 && frame_count <= 270) start_radius += 0.05f;
	start_radius = max(0.0f, min(start_radius, START_RADIUS));

	if (frame_count >= 300) {
		frame_count = 0;

		//		start_pos.z = GetRandomF(-20.0f, 20.0f);
		//		start_pos.x = GetRandomF(-20.0f, 20.0f);

				//area_num += GetRandomI(1,AREA_MAX-1);
				//area_num %= AREA_MAX;

		float length = GetRandomF(AREA_RADIUS - START_RADIUS);

		float rot = GetRandomF(360.0f);

		start_pos.x = area_pos[area_num].x + length * sinf(TO_RADIAN(rot));
		start_pos.z = area_pos[area_num].x + length * sinf(TO_RADIAN(rot));
	}

	if (frame_count == 120)
	{
		ball_pos = start_pos;
		ball_mov = camera_pos - ball_pos;
		ball_mov.SetLength(BALL_SPEED);
		ball_active = true;

		area_num += GetRandomI(1, AREA_MAX - 1);
		area_num %= AREA_MAX;
	}

	if (ball_active)
	{
		ball_pos += ball_mov;
		float distance = GetFloat3Distance(ball_pos, camera_pos);
		if (distance < 2.0f)
		{
			VECTOR pos2d = ConvWorldPosToScreenPos(ball_pos.VGet());
			paint_pos.x = pos2d.x;
			paint_pos.y = pos2d.y;
			paint_alpha = 255;
			ball_active = false;
			shake_frame = 15;
		}

	}

	//ball_pos += ball_mov;
	paint_pos.y += 0.35f;
	paint_alpha -= 5;
	paint_alpha = max(0, paint_alpha);

	shake_frame--;
	shake_frame = max(0, shake_frame);

	if (PushMouseInput())
	{
		float x = GetMouseX();
		float y = GetMouseY();

		VECTOR start = ConvScreenPosToWorldPos(VGet(x, y, 0.0f));
		VECTOR goal = ConvScreenPosToWorldPos(VGet(x, y, 1.0f));

		Float3 line_start(start);
		Float3 line_goal(goal);
		if (CheckLineBallHit(line_start, line_goal, ball_pos, BALL_RADIUS))
		{
			ball_active = false;
		}

	}
}
//---------------------------------------------------------------------------------
//	�`�揈��
//---------------------------------------------------------------------------------
void GameRender()
{
	//	���W�ƌ�����n���ăJ�����̐ݒ�
		//	���W�ƌ�����n���ăJ�����̐ݒ�
	SetCameraPositionAndAngle(camera_pos.VGet(), TO_RADIAN(camera_rot.x), TO_RADIAN(camera_rot.y), TO_RADIAN(camera_rot.z));

	//	�n�ʃ��f���̕`��
	MV1DrawModel(ground_model);

	for (int i = 0; i < AREA_MAX; i++)
	{
		//	�{�[���̔��ˍ��W�ɉ~�̕`��
		if (i == area_num)
		{
			DrawCircle3D_XZ(area_pos[i], AREA_RADIUS, GetColor(0, 255, 255), true);

		}
		else
		{
			DrawCircle3D_XZ(area_pos[i], AREA_RADIUS, GetColor(255, 128, 128), true);
		}
	}

	if (ball_active)
	{
		//	���F���{�[���̕`��
		DrawSphere3D(ball_pos.VGet(), BALL_RADIUS, 32, GetColor(255, 255, 0), GetColor(255, 255, 0), TRUE);
	}

	//	�y�C���g�摜�̕`��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	DrawRotaGraphF(paint_pos.x, paint_pos.y, 1.0f, TO_RADIAN(0.0f), paint_image, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	int x = 0;
	int y = 0;
	if (shake_frame > 0)
	{
		x = GetRandomI(-3, 3);
		y = GetRandomI(-3, 3);
	}

	DrawString(16 + x, 16 + y, "���^�C�~���O�Œn�ʂ̉~����J�����Ƀ{�[������", GetColor( 255, 255, 255 ) );
	DrawString(16 + x, 32 + y, "�{�[�����J�����̋߂��ɂȂ�����Q�c��ʍ��W�ɉ摜��`��", GetColor( 255, 255, 255 ) );
	DrawString(16 + x, 48 + y, "�{�[�����o�Ă��鍕���~���A�o�Ă���Ƃ��Ə�����Ƃ��ɔ��a��ύX����", GetColor( 255, 255, 0 ) );
	DrawString(16 + x, 64 + y, "�����~�̓o��ꏊ��Ԃ��~�̒��̂ǂ��������_���Ɂi�Q��A�������~�ɂ͂Ȃ�Ȃ��j", GetColor( 255, 255, 0 ) );
	DrawString(16 + x, 80 + y, "��ʂɓ��������y�C���g�摜�͉��Ɉړ����Ȃ��瓧���ɂȂ��ď����Ă���", GetColor( 255, 255, 0 ) );
}
//---------------------------------------------------------------------------------
//	�I������
//---------------------------------------------------------------------------------
void GameExit()
{
	MV1DeleteModel( ground_model );
}
