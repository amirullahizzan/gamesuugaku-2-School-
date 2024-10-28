#include "Main.h"
#include "Game.h"
#include "Hit.h"
#include "Random.h"
#include "Float2.h"
#include "Float3.h"

#define BALL_RADIUS		0.2f
#define START_RADIUS	1.0f

//	ボールの移動スピード
#define BALL_SPEED		0.5f

//	画面にぶつかったときに描画するペイント画像
int paint_image;
//	モデル
int ground_model;

//	カメラ座標と向き
Float3 camera_pos;
Float3 camera_rot;

Float3 start_pos;

//	ボールの座標
Float3 ball_pos;
Float3 ball_mov;

Float2 paint_pos;

int frame_count;

//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
void GameInit()
{
	//	カメラ座標の初期設定
	camera_pos.set( 0.0f, 25.0f, -35.0f );
	//	カメラの向き
	camera_rot.set( 37.0f, 0.0f, 0.0f );

	//	ペイント画像の読み込み
	paint_image = LoadGraph( "data/paint.bmp" );

	ground_model = MV1LoadModel( "data/ground.mqoz" );

	start_pos.set( 0.0f, 0.1f, 0.0f );
	frame_count = 0;

	//	ボールの初期設定
	ball_pos.clear();
	ball_mov.clear();

	paint_pos.set( 0.0f, 0.0f );
}
//---------------------------------------------------------------------------------
//	更新処理
//---------------------------------------------------------------------------------
void GameUpdate()
{
	frame_count++;
	if( frame_count >= 300 ){
		frame_count = 0;

		start_pos.x = GetRandomF( -20.0f, 20.0f );
		start_pos.z = GetRandomF( -20.0f, 20.0f );
	}

	if( frame_count == 120 ){
	}

	ball_pos += ball_mov;
}
//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void GameRender()
{
	//	座標と向きを渡してカメラの設定
	SetCameraPositionAndAngle( camera_pos.VGet(), TO_RADIAN( camera_rot.x ), TO_RADIAN( camera_rot.y ), TO_RADIAN( camera_rot.z ) );

	//	地面モデルの描画
	MV1DrawModel( ground_model );

	//	ボールの発射座標に円の描画
	DrawCircle3D_XZ( start_pos, START_RADIUS, GetColor( 0, 0, 0 ), true );

	//	黄色いボールの描画
	DrawSphere3D( ball_pos.VGet(), BALL_RADIUS, 32, GetColor( 255, 255, 0 ), GetColor( 255, 255, 0 ), TRUE );

	//	ペイント画像の描画
	DrawRotaGraphF( paint_pos.x, paint_pos.y, 1.0f, TO_RADIAN( 0.0f ), paint_image, TRUE );

	DrawString( 16, 16, "一定タイミングで地面の円からカメラにボール発射", GetColor( 255, 255, 255 ) );
	DrawString( 16, 32, "ボールがカメラの近くになったら２Ｄ画面座標に画像を描画", GetColor( 255, 255, 255 ) );
}
//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void GameExit()
{
	MV1DeleteModel( ground_model );
}
