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

//	ポイントの数
#define POINT_MAX	6
//	各ポイントの座標
Float3 point[POINT_MAX] =
{
	{ -25.0f, 0.01f, -15.0f },
	{ -25.0f, 0.01f,  25.0f },
	{   5.0f, 0.01f,  25.0f },
	{   5.0f, 0.01f,   5.0f },
	{  25.0f, 0.01f,   5.0f },
	{  25.0f, 0.01f, -15.0f },
};

//	プレイヤーから一番近い線の番号
int near_line;

//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
void GameInit()
{
	ground_model = MV1LoadModel("data/ground.mqoz");
	player_model = MV1LoadModel("data/player.mqoz");

	camera.Init();
	ground.Init(ground_model);
	player.Init(player_model);

	//	とりあえず０番目の線を一番近いとしています
	near_line = 0;
}
//---------------------------------------------------------------------------------
//	更新処理
//---------------------------------------------------------------------------------
void GameUpdate()
{
	ground.Update();

	float near_length = 1000.0f;

	for (int i = 0; i < POINT_MAX; i++)
	{
		int p1 = i;
		int p2 = (i + 1) & POINT_MAX;

		float now_length = GetFloat3LinePointNearDistance(point[p1], point[p2], player.m_pos);

		if (now_length < near_length)
		{
			near_line = i;

			near_length = now_length;
		}

	}

	//	移動ベクトルを使った座標移動
	player.Update(near_length);

	//	必要な情報を渡してカメラ設定
	//	（座標・向き・移動ベクトル）
	camera.Update(player.m_pos, player.m_rot, player.m_mov);
}
//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void GameRender()
{
	camera.Render();

	ground.Render();

	//	各ポイントを結んで線の描画
	for (int i = 0; i < POINT_MAX; i++) {
		//	１点目の番号
		int p1 = i;
		//	２点目の番号
		int p2 = (i + 1) % POINT_MAX;
		int color = GetColor(200, 200, 200);
		//	一番近い線の色を変える
		if (i == near_line) {
			color = GetColor(255, 255, 0);
		}
		//	２点の座標を結んで線の描画
		DrawLine3D(point[p1].VGet(), point[p2].VGet(), color);
	}

	player.Render();

	int p1 = near_line;
	int p2 = (near_line + 1) % POINT_MAX;

	Float3 line_dir = point[p2] - point[p1];
	line_dir.normalize();

	Float3 player_front = player.m_mov;
	player_front.normalize();

	if (GetFloat3Dot(player_front, line_dir) < 0.0f)
	{
		DrawString(350, 200, "逆走してる", GetColor(0, 255, 255));
	}

	DrawString(16, 16, "十字キー：プレイヤー回転・移動", GetColor(255, 255, 255));
	DrawString(16, 32, "　Ｆ１キー：全体カメラ", GetColor(255, 255, 255));
	DrawString(16, 48, "　Ｆ２キー：プレイヤーカメラ（Ｚマイナス方向から）", GetColor(255, 255, 255));
	DrawString(16, 64, "　Ｆ３キー：プレイヤーの後ろについていくようなカメラ", GetColor(255, 255, 255));

	DrawString(16, 96, "プレイヤーに一番近いラインの色の変更", GetColor(255, 255, 0));
	DrawString(16, 112, "コースは時計回りで：逆走したら警告表示", GetColor(255, 255, 0));
	DrawString(16, 128, "一番近いラインから離れすぎたらスピードを落とす", GetColor(255, 255, 0));

	DrawString(16, 32 + 16 * camera.m_type, "●", GetColor(255, 255, 255));
}
//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void GameExit()
{
	camera.Exit();
	ground.Exit();
	player.Exit();

	MV1DeleteModel(ground_model);
	MV1DeleteModel(player_model);
}
