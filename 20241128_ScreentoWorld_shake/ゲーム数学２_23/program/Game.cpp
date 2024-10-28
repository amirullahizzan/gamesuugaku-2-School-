#include "Main.h"
#include "Game.h"
#include "Hit.h"
#include "Random.h"
#include "Float2.h"
#include "Float3.h"

#define BALL_RADIUS		0.2f
#define START_RADIUS	1.0f

//	�{�[���̈ړ��X�s�[�h
#define BALL_SPEED		0.5f

//	��ʂɂԂ������Ƃ��ɕ`�悷��y�C���g�摜
int paint_image;
//	���f��
int ground_model;

//	�J�������W�ƌ���
Float3 camera_pos;
Float3 camera_rot;

Float3 start_pos;

//	�{�[���̍��W
Float3 ball_pos;
Float3 ball_mov;

Float2 paint_pos;

int frame_count;

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

	paint_pos.set( 0.0f, 0.0f );
}
//---------------------------------------------------------------------------------
//	�X�V����
//---------------------------------------------------------------------------------
void GameUpdate()
{
	frame_count++;
	if( frame_count >= 300 ){
		frame_count = 0;

		start_pos.x = GetRandomF( -20.0f, 20.0f );
		start_pos.z = GetRandomF( -20.0f, 20.0f );
	}

	if( frame_count == 120 ){
	}

	ball_pos += ball_mov;
}
//---------------------------------------------------------------------------------
//	�`�揈��
//---------------------------------------------------------------------------------
void GameRender()
{
	//	���W�ƌ�����n���ăJ�����̐ݒ�
	SetCameraPositionAndAngle( camera_pos.VGet(), TO_RADIAN( camera_rot.x ), TO_RADIAN( camera_rot.y ), TO_RADIAN( camera_rot.z ) );

	//	�n�ʃ��f���̕`��
	MV1DrawModel( ground_model );

	//	�{�[���̔��ˍ��W�ɉ~�̕`��
	DrawCircle3D_XZ( start_pos, START_RADIUS, GetColor( 0, 0, 0 ), true );

	//	���F���{�[���̕`��
	DrawSphere3D( ball_pos.VGet(), BALL_RADIUS, 32, GetColor( 255, 255, 0 ), GetColor( 255, 255, 0 ), TRUE );

	//	�y�C���g�摜�̕`��
	DrawRotaGraphF( paint_pos.x, paint_pos.y, 1.0f, TO_RADIAN( 0.0f ), paint_image, TRUE );

	DrawString( 16, 16, "���^�C�~���O�Œn�ʂ̉~����J�����Ƀ{�[������", GetColor( 255, 255, 255 ) );
	DrawString( 16, 32, "�{�[�����J�����̋߂��ɂȂ�����Q�c��ʍ��W�ɉ摜��`��", GetColor( 255, 255, 255 ) );
}
//---------------------------------------------------------------------------------
//	�I������
//---------------------------------------------------------------------------------
void GameExit()
{
	MV1DeleteModel( ground_model );
}
