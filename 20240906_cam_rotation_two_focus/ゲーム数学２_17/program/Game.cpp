#include "Main.h"
#include "Game.h"
#include "Hit.h"
#include "Random.h"
#include "Float3.h"

#include "Camera.h"
#include "Ground.h"
#include "Player.h"
#include "Npc.h"

#define RADIUS	1.0f

//	モデル用の変数
int ground_model;
int player_model;
int npc_model;
//	クラスの宣言
Camera	camera;
Ground	ground;
Player	player;
Npc		npc;

//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
void GameInit()
{
	//	モデルの読み込み
	ground_model = MV1LoadModel( "data/ground.mqoz" );
	player_model = MV1LoadModel( "data/player.mqoz" );
	npc_model = MV1LoadModel( "data/npc.mqoz" );
	//	クラスの初期化
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
	//	十字キーで回転・移動
	player.Update();
	npc.Update();

	float distance = GetFloat3Distance(player.m_pos, npc.m_pos);

	float base_length = RADIUS * 2.0f;

	if (distance < base_length)
	{
		float in_length = base_length - distance;

		Float3 dir = player.m_pos - npc.m_pos;

		dir.SetLength(in_length * 0.5f);

		player.m_pos += dir;
		npc.m_pos -= dir;
	}

	//	プレイヤー座標とＮＰＣ座標を渡してカメラの更新処理
	camera.Update( player.m_pos, npc.m_pos );
}
//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void GameRender()
{
	//	カメラの設定
	camera.Render();
	//	モデルの描画
	ground.Render();

	npc.Render();
	DrawCircle3D_XZ( npc.m_pos, RADIUS, GetColor( 255, 128, 0 ) );

	player.Render();
	DrawCircle3D_XZ( player.m_pos, RADIUS, GetColor( 0, 128, 255 ) );

	DrawString( 16, 16, "十字キー：プレイヤー回転・移動", GetColor( 255, 255, 255 ) );
	DrawString( 16, 32, "プレイヤーとＮＰＣがいい感じに画面に入るようなカメラ", GetColor( 255, 255, 255 ) );
	DrawString( 16, 48, "プレイヤーとＮＰＣは一定より近づかない", GetColor( 255, 255, 255 ) );
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
