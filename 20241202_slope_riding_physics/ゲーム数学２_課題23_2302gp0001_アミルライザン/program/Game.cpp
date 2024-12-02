#include "Main.h"
#include "Game.h"
#include "Hit.h"
#include "Random.h"
#include "Float3.h"

#include "Camera.h"
#include "Ground.h"
#include "Player.h"

//	モデルデータ用の変数
int ground_model;
int player_model;

//	クラスの宣言
Camera	camera;
Ground	ground;
Player	player;

//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
void GameInit()
{
	//	モデルデータの読み込み
	//	（今回は地面の傾きを使った処理がしたいので起伏のある地面モデルを読み込んでいます）
	ground_model = MV1LoadModel( "data/ground.mqoz" );
	player_model = MV1LoadModel( "data/player.mqoz" );

	//	モデルデータの当たり情報を作成します
	MV1SetupCollInfo( ground_model );

	//	クラスの初期化
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
	//	当たり判定の情報の更新を行います
	MV1RefreshCollInfo( ground_model );

	//	プレイヤーの更新処理
	//	十字キーで向きを変えて移動・スペースキーでジャンプ
	//	地面モデル番号を渡してプレイヤーの更新処理
	player.Update( ground_model );

	camera.Update();
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
	player.Render();

	DrawString( 16, 16, "十字キー：プレイヤーの回転・移動", GetColor( 255, 255, 255 ) );
	DrawString( 16, 32, "スペース：ジャンプ（地面の傾き方向に）", GetColor( 255, 255, 255 ) );
	DrawString( 16, 48, "プレイヤーが地面に立っているときだけジャンプ", GetColor( 255, 255, 0 ) );
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
