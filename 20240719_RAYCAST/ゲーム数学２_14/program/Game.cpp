#include "Main.h"
#include "Game.h"
#include "Hit.h"
#include "Random.h"

//	円の半径
#define RADIUS	100.0f

//	マウス座標
Float2 mouse;

Float2 line_start;
Float2 line_goal;

Float2 near_pos;

bool hit_check;

//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
void GameInit()
{
	line_start.set( 200.0f, 300.0f );
	line_goal.set( 500.0f, 200.0f );

	hit_check = false;
}
//---------------------------------------------------------------------------------
//	更新処理
//---------------------------------------------------------------------------------
void GameUpdate()
{
	//	マウス座標の取得
	mouse.set( GetMouseX(), GetMouseY() );

	near_pos = GetFloat2LinePointNearPosition(line_start, line_goal, mouse);

	hit_check = false;
}
//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void GameRender()
{
	DrawLineAA( line_start.x, line_start.y, line_goal.x, line_goal.y, GetColor( 255, 255, 255 ) );

	//	マウス円の描画
	DrawCircleAA( mouse.x, mouse.y, RADIUS, 100, GetColor( 0, 255, 255 ), FALSE );

	if( hit_check ){
		DrawString( 16, 48, "→　当たっています", GetColor( 255, 255, 0 ) );
	}

	DrawString( 16, 16, "マウス座標を中心に円の描画", GetColor( 255, 255, 255 ) );
	DrawString( 16, 32, "マウス円と線の当たり判定", GetColor( 255, 255, 255 ) );
}
//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void GameExit()
{
}
