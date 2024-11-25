#include "Main.h"
#include "Game.h"
#include "Random.h"
#include "Float2.h"
#include "Hit.h"

#define CIRCLE_RADIUS	15.0f

Float2	posA;
Float2	posB;
Float2	posC;

bool mouse_in;

//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
void GameInit()
{
	posA.set( 100.0f, 200.0f );
	posB.set( 500.0f,  50.0f );
	posC.set( 300.0f, 400.0f );

	mouse_in = false;
}
//---------------------------------------------------------------------------------
//	更新処理
//---------------------------------------------------------------------------------
void GameUpdate()
{
	if( CheckHitKey( KEY_INPUT_D ) )	posA.x += 10.0f;
	if( CheckHitKey( KEY_INPUT_A ) )	posA.x -= 10.0f;

	Float2 mouse;
	mouse.x = (float)GetMouseX();
	mouse.y = (float)GetMouseY();

	mouse_in = false;
}
//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void GameRender()
{
	int color = GetColor( 150, 150, 150 );
	if( mouse_in ){
		color = GetColor( 255, 255, 0 );
	}

	DrawLineAA( posA.x, posA.y, posB.x, posB.y, color );
	DrawLineAA( posB.x, posB.y, posC.x, posC.y, color );
	DrawLineAA( posC.x, posC.y, posA.x, posA.y, color );

	DrawCircleAA( posA.x, posA.y, CIRCLE_RADIUS, 100, GetColor( 255, 255, 255 ) );
	DrawCircleAA( posB.x, posB.y, CIRCLE_RADIUS, 100, GetColor( 255, 255, 255 ) );
	DrawCircleAA( posC.x, posC.y, CIRCLE_RADIUS, 100, GetColor( 255, 255, 255 ) );

	DrawStringF( posA.x - 3.0f, posA.y - 7.0f, "A", GetColor( 0, 0, 0 ) );
	DrawStringF( posB.x - 3.0f, posB.y - 7.0f, "B", GetColor( 0, 0, 0 ) );
	DrawStringF( posC.x - 3.0f, posC.y - 7.0f, "C", GetColor( 0, 0, 0 ) );

	DrawString( 16, 16, "マウスが三角形の中に入ると線の色が変わる", GetColor( 255, 255, 255 ) );
	DrawString( 16, 32, "ＡＤキー：円ＡのＸ座標の移動", GetColor( 255, 255, 255 ) );
}
//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void GameExit()
{
}
