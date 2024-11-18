#include "Main.h"
#include "Game.h"
#include "Hit.h"
#include "Random.h"
#include "Float3.h"

#include "Camera.h"
#include "Ground.h"
#include "Player.h"

#define LINE_LENGTH		30.0f

//	データ用の変数
int ground_model;
int player_model;
int npc_model;

//	クラスの宣言
Camera	camera;
Ground	ground;
Player	player;

Float3 line_start;
Float3 line_goal;
float line_rot;

bool player_right;

//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
void GameInit()
{
	//	データの読み込み
	ground_model = MV1LoadModel( "data/ground.mqoz" );
	player_model = MV1LoadModel( "data/player.mqoz" );
	npc_model = MV1LoadModel( "data/npc.mqoz" );

	//	クラスの初期化
	camera.Init();
	ground.Init( ground_model );
	player.Init( player_model );

	line_start.set( -5.0f, 0.0f, -10.0f );
	line_goal.set( 0.0f, 0.0f, 0.0f );
	line_rot = 0.0f;

	player_right = false;
}
//---------------------------------------------------------------------------------
//	更新処理
//---------------------------------------------------------------------------------
void GameUpdate()
{
	ground.Update();
	//	十字キーで向きの変更と座標移動
	player.Update();

	camera.Update();

	if( CheckHitKey( KEY_INPUT_D ) )	line_rot += 2.0f;
	if( CheckHitKey( KEY_INPUT_A ) )	line_rot -= 2.0f;

	Float3 base( 0.0f, 0.0f, LINE_LENGTH );
	MATRIX mat = MGetRotY( TO_RADIAN( line_rot ) );
	Float3 change = GetFloat3VTransform( base, mat );
	line_goal = line_start + change;

}
//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void GameRender()
{
	camera.Render();

	ground.Render();
	player.Render();

	Float3 start = line_start + Float3( 0.0f, 0.1f, 0.0f );
	Float3 goal = line_goal + Float3( 0.0f, 0.1f, 0.0f );
	DrawLine3D( start.VGet(), goal.VGet(), GetColor( 255, 255, 0 ) );

	MV1SetPosition( npc_model, line_start.VGet() );
	MV1SetRotationXYZ( npc_model, VGet( 0.0f, TO_RADIAN( line_rot ), 0.0f ) );
	MV1DrawModel( npc_model );

	DrawSphere3D( goal.VGet(), 0.3f, 100, GetColor( 255, 255, 0 ), GetColor( 255, 255, 0 ), TRUE );

	if( player_right ){
		DrawString( 16, 48, "プレイヤーは線の右にいます", GetColor( 255, 255, 0 ) );
	}else{
		DrawString( 16, 48, "プレイヤーは線の左にいます", GetColor( 0, 255, 255 ) );
	}

	DrawString( 16, 16, "十字キー：プレイヤーの回転・移動", GetColor( 255, 255, 255 ) );
	DrawString( 16, 32, "ＡＤキー：線の回転角度変更", GetColor( 255, 255, 255 ) );

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
	MV1DeleteModel( npc_model );
}
