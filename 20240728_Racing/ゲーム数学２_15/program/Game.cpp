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

#define POINT_MAX	6
Float3 point[POINT_MAX] =
{
	{ -25.0f, 0.01f, -15.0f },
	{ -25.0f, 0.01f,  25.0f },
	{   5.0f, 0.01f,  25.0f },
	{   5.0f, 0.01f,   5.0f },
	{  25.0f, 0.01f,   5.0f },
	{  25.0f, 0.01f, -15.0f },
};

//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
void GameInit()
{
	ground_model = MV1LoadModel( "data/ground.mqoz" );
	player_model = MV1LoadModel( "data/player.mqoz" );

	camera.Init();
	ground.Init( ground_model );
	player.Init( player_model );
}
//---------------------------------------------------------------------------------
//	更新処理
//---------------------------------------------------------------------------------
void GameUpdate()
{
	ground.Update();
	player.Update();

	camera.Update( player.m_pos, player.m_rot, player.m_mov );
}
//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void GameRender()
{
	camera.Render();

	ground.Render();

	for( int i = 0; i < POINT_MAX; i++ ){
		int p1 = i;
		int p2 = ( i + 1 ) % POINT_MAX;
		int color = GetColor( 200, 200, 200 );

		DrawLine3D( point[p1].VGet(), point[p2].VGet(), color );
	}

	player.Render();

	DrawString( 16,  16, "十字キー：プレイヤー回転・移動", GetColor( 255, 255, 255 ) );
	DrawString( 16,  32, "　Ｆ１キー：全体カメラ", GetColor( 255, 255, 255 ) );
	DrawString( 16,  48, "　Ｆ２キー：プレイヤーカメラ（Ｚマイナス方向から）", GetColor( 255, 255, 255 ) );
	DrawString( 16,  64, "　Ｆ３キー：プレイヤーの後ろについていくようなカメラ", GetColor( 255, 255, 255 ) );

	DrawString( 16, 32 + 16 * camera.m_type, "●", GetColor( 255, 255, 255 ) );
}
//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void GameExit()
{
	camera.Exit();
	ground.Exit();
	player.Exit();

	MV1DeleteModel( ground_model );
	MV1DeleteModel( player_model );
}
