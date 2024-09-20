#include "Main.h"
#include "Game.h"
#include "Random.h"
#include "Float3.h"

//	モデルデータの変数
int ground_model;
int player_model;
int npc_model;

//	カメラ座標
Float3 camera_pos;
//	カメラの向き
Float3 camera_rot;

//	プレイヤー座標
Float3	player_pos;
//	プレイヤーの向き
Float3	player_rot;

int light_handle;

//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
void GameInit()
{
	//	カメラ座標と向きの初期設定
	camera_pos.set( 0.0f, 3.0f, -10.0f );
	camera_rot.set( 10.0f, 0.0f, 0.0f );

	//	モデルデータの読み込み
	ground_model = MV1LoadModel( "data/ground.mqoz" );
	player_model = MV1LoadModel( "data/player.mqoz" );
	npc_model = MV1LoadModel( "data/npc.mqoz" );

	player_pos.set( 0.0f, 1.0f, -3.0f );

	SetLightDifColor( GetColorF( 0.2f, 0.2f, 0.2f, 1.0f ) );

	light_handle = CreateSpotLightHandle( player_pos.VGet(), VGet( 0.0f, 0.0f, 1.0f ), TO_RADIAN( 45.0f ), TO_RADIAN( 30.0f ), 100.0f, 1.0f, 0.0f, 0.01f );
}
//---------------------------------------------------------------------------------
//	更新処理
//---------------------------------------------------------------------------------
void GameUpdate()
{

	//	マウスを押している時
	if( CheckMouseInput() ){
		//	マウスの移動量で
		float x = GetMouseMoveX();
		float y = GetMouseMoveY();

		//	プレイヤーの向きを変更します
		player_rot.x += y * 0.2f;
		player_rot.y += x * 0.2f;
	}
}
//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void GameRender()
{
	//	カメラ座標と向きを渡してカメラ設定
	SetCameraPositionAndAngle( camera_pos.VGet(), TO_RADIAN( camera_rot.x ), TO_RADIAN( camera_rot.y ), TO_RADIAN( camera_rot.z ) );

	//	地面の描画
	MV1DrawModel( ground_model );

	for( int i = 0; i < 5; i++ ){
		MV1SetPosition( npc_model, VGet( -7.0f + i * 3.5f, 0.0f, 5.0f ) );
		MV1DrawModel( npc_model );
	}

	MV1SetPosition( player_model, VGet( player_pos.x, player_pos.y, player_pos.z ) );
	MV1SetRotationXYZ( player_model, VGet( TO_RADIAN( player_rot.x ), TO_RADIAN( player_rot.y ), TO_RADIAN( player_rot.z ) ) );
	MV1DrawModel( player_model );

	DrawString( 16, 16, "マウスドラッグ：プレイヤーの向き変更（その方向にスポットライト）", GetColor( 255, 255, 255 ) );
	DrawString( 16, 32, "マウスホイール：スポットライトの広がり変更", GetColor( 255, 255, 255 ) );
}
//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void GameExit()
{
	MV1DeleteModel( ground_model );
	MV1DeleteModel( player_model );
	MV1DeleteModel( npc_model );
}
