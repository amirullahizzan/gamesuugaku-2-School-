#include "Main.h"
#include "Game.h"
#include "Hit.h"
#include "Random.h"

//	�~�̔��a
#define RADIUS	100.0f

//	�}�E�X���W
Float2 mouse;

Float2 line_start;
Float2 line_goal;

Float2 near_pos;

bool hit_check;

//---------------------------------------------------------------------------------
//	����������
//---------------------------------------------------------------------------------
void GameInit()
{
	line_start.set( 200.0f, 300.0f );
	line_goal.set( 500.0f, 200.0f );

	hit_check = false;
}
//---------------------------------------------------------------------------------
//	�X�V����
//---------------------------------------------------------------------------------
void GameUpdate()
{
	//	�}�E�X���W�̎擾
	mouse.set( GetMouseX(), GetMouseY() );

	near_pos = GetFloat2LinePointNearPosition(line_start, line_goal, mouse);

	hit_check = false;
}
//---------------------------------------------------------------------------------
//	�`�揈��
//---------------------------------------------------------------------------------
void GameRender()
{
	DrawLineAA( line_start.x, line_start.y, line_goal.x, line_goal.y, GetColor( 255, 255, 255 ) );

	//	�}�E�X�~�̕`��
	DrawCircleAA( mouse.x, mouse.y, RADIUS, 100, GetColor( 0, 255, 255 ), FALSE );

	if( hit_check ){
		DrawString( 16, 48, "���@�������Ă��܂�", GetColor( 255, 255, 0 ) );
	}

	DrawString( 16, 16, "�}�E�X���W�𒆐S�ɉ~�̕`��", GetColor( 255, 255, 255 ) );
	DrawString( 16, 32, "�}�E�X�~�Ɛ��̓����蔻��", GetColor( 255, 255, 255 ) );
}
//---------------------------------------------------------------------------------
//	�I������
//---------------------------------------------------------------------------------
void GameExit()
{
}
