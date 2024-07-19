#include "Main.h"
#include "Game.h"
#include "Hit.h"
#include "Random.h"

#include "Camera.h"
#include "Ground.h"
#include "Player.h"
#include "Npc.h"

int ground_model;
int player_model;
int npc_model;

Camera	camera;
Ground	ground;
Player	player;
Npc		npc;

//	線の開始座標
Float3 line_start;
//	線のゴール座標
Float3 line_goal;

//	プレイヤーはこの距離までしか離れない
#define LIMIT_LENGTH	3.0f
//	線分上のプレイヤーに一番近い座標
Float3 near_pos;

//	ＮＰＣの半径（発展用）
#define CHARA_RADIUS	1.0f

//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
void GameInit()
{
	//	モデルデータの読み込み
	ground_model = MV1LoadModel( "data/ground.mqoz" );
	player_model = MV1LoadModel( "data/player.mqoz" );
	npc_model = MV1LoadModel( "data/npc.mqoz" );
	//	クラスの初期化
	camera.Init();
	ground.Init( ground_model );
	player.Init( player_model );
	npc.Init( npc_model );
	//	線の開始座標とゴール座標の設定
	line_start.set( -10.0f, 0.0f, -8.0f );
	line_goal.set( 10.0f, 0.0f, -5.0f );
}
//---------------------------------------------------------------------------------
//	更新処理
//---------------------------------------------------------------------------------
void GameUpdate()
{
	ground.Update();
	//	十字キーで回転や移動
	player.Update();

	float distance = GetFloat3Distance(near_pos, player.m_pos);

	if (distance > LIMIT_LENGTH)
	{
		float length = distance - LIMIT_LENGTH;
		Float3 dir = near_pos - player.m_pos;
		dir.SetLength(length);
		player.m_pos += dir;
	}
	//	回転しているだけ
	npc.Update();

	if (CheckLineBallHit(player.m_pos,player.m_front,npc.m_pos,CHARA_RADIUS))
	{
		npc.m_pos.x = GetRandomF(-20.0f,20.0f);
		npc.m_pos.z = GetRandomF(0.0f,10.0f);
	}

	camera.Update();
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

	//	線分の描画
	DrawLine3D( line_start.VGet(), line_goal.VGet(), GetColor( 255, 255, 255 ) );

	//	プレイヤーと一番近い座標を線で描画
	DrawLine3D( player.m_pos.VGet(), near_pos.VGet(), GetColor( 0, 255, 0 ) );

	//	線分上の一番近い座標に球の描画
	DrawSphere3D( near_pos.VGet(), 0.3f, 10, GetColor( 255, 255, 0 ), GetColor( 255, 255, 0 ), TRUE );

	DrawString( 16, 16, "十字キー：プレイヤー回転・移動", GetColor( 255, 255, 255 ) );
	DrawString( 16, 32, "プレイヤーから一番近い線分上の座標を求める（その座標に小さな球の描画はしています）", GetColor( 255, 255, 0 ) );
	DrawString( 16, 48, "プレイヤーはその球から一定以上離れない", GetColor( 255, 255, 0 ) );
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
