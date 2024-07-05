#include "Main.h"
#include "Game.h"
#include "Hit.h"
#include "Random.h"

#include "Player.h"
#include "Npc.h"

//	画像変数
int player_image;
int npc_image;

//	クラスの宣言
Player	player;
Npc		npc;

//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
void GameInit()
{
	//	画像の読み込み
	player_image = LoadGraph( "data/player.bmp" );
	npc_image = LoadGraph( "data/npc.bmp" );
	//	クラスの初期化
	player.Init( player_image );
	npc.Init( npc_image );
}
//---------------------------------------------------------------------------------
//	更新処理
//---------------------------------------------------------------------------------
void GameUpdate()
{
	//	十字キーで回転と移動
	player.Update();

	npc.Update( player.m_pos );
}
//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void GameRender()
{
	//	ＮＰＣの描画
	npc.Render();
	//	プレイヤーの描画
	player.Render();

	DrawString( 16, 16, "十字キー：プレイヤー回転・移動", GetColor( 255, 255, 255 ) );
	DrawString( 16, 32, "ＮＰＣは回転しながら向いている方向に移動", GetColor( 255, 255, 255 ) );
	DrawString( 16, 48, "→　視野角内にプレイヤー座標が入ったら止まる", GetColor( 255, 255, 255 ) );
}
//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void GameExit()
{
	player.Exit();
	npc.Exit();

	DeleteGraph( player_image );
	DeleteGraph( npc_image );
}
