#include "Main.h"
#include "Game.h"
#include "Hit.h"

#include "Camera.h"
#include "Ground.h"
#include "Player.h"
#include "Npc.h"

int ground_model;
int player_model;
int npc_model;

Camera	camera;
//	地面
Ground	ground;
//	プレイヤー（十字キーで回転と移動）
Player	player;
//	ＮＰＣ（適当に移動）
Npc		npc;

//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
void GameInit()
{
	ground_model = MV1LoadModel( "data/ground.mqoz" );
	player_model = MV1LoadModel( "data/player.mqoz" );
	npc_model = MV1LoadModel( "data/npc.mqoz" );

	camera.Init();
	ground.Init( ground_model );
	player.Init( player_model );
	npc.Init( npc_model );
}
//---------------------------------------------------------------------------------
//	更新処理
//---------------------------------------------------------------------------------
void GameUpdate()
{
	ground.Update();
	//	十字キーで回転や移動
	player.Update();
	//	常に回転しながら移動
	npc.Update();

	camera.Update( player.m_pos );
}
//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void GameRender()
{
	camera.Render();

	ground.Render();
	npc.Render();
	player.Render();

	DrawString( 16, 16, "十字キー：回転・移動", GetColor( 255, 255, 255 ) );

	DrawString( 16, 32, "プレイヤーについていく感じのカメラ", GetColor( 255, 255, 0 ) );
}
//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void GameExit()
{
	camera.Exit();
	ground.Exit();
	player.Exit();
	npc.Exit();

	MV1DeleteModel( ground_model );
	MV1DeleteModel( player_model );
	MV1DeleteModel( npc_model );
}
