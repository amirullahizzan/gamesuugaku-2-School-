#include "Main.h"
#include "Game.h"
#include "Random.h"
#include "Float3.h"

//	地面モデル
int ground_model;

//	カメラ座標
Float3 camera_pos;
//	カメラの向き
Float3 camera_rot;

#define BALL_SPEED  1.0f

Float3 ball_pos;
Float3 ball_mov;

//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
void GameInit()
{
	//	カメラ座標と向きの初期設定
	camera_pos.set(0.0f, 5.0f, -20.0f);
	camera_rot.set(10.0f, 0.0f, 0.0f);

	//	地面モデルの読み込み
	ground_model = MV1LoadModel("data/ground.mqoz");

	//	当たり情報を作成
	MV1SetupCollInfo(ground_model);
}
//---------------------------------------------------------------------------------
//	更新処理
//---------------------------------------------------------------------------------
void GameUpdate()
{
	//	当たり情報の更新
	MV1RefreshCollInfo(ground_model);
	Float3 base;
	//	マウスを押している時
	if (CheckMouseInput())
	{
		//	マウスの移動量で
		float x = GetMouseMoveX();
		float y = GetMouseMoveY();

		if (CheckHitKey(KEY_INPUT_SPACE))
		{
			base.x = x * 0.1f;
			base.y = -y * 0.1f;
		}
		else
		{
			//	カメラの向きを変更します
			camera_rot.x += y * 0.2f;
			camera_rot.y += x * 0.2f;
		}
	}

	//	マウスホイールの回転量を取得
	float speed = GetMouseWheelRotVolF();

	base.z = speed;

	MATRIX mat_x = MGetRotX(TO_RADIAN(camera_rot.x));
	MATRIX mat_y = MGetRotX(TO_RADIAN(camera_rot.y));

	MATRIX mat = MMult(mat_x, mat_y);
	Float3 change = GetFloat3VTransform(base, mat);

	camera_pos += change;

	Float3 start = camera_pos + Float3(0.0f, 100.0f, 0.0f);
	Float3 goal = camera_pos + Float3(0.0f, -100.0f, 0.0f);

	MV1_COLL_RESULT_POLY hit_info;
	hit_info = MV1CollCheck_Line(ground_model, -1, start.VGet(), goal.VGet());

	float ground_y = 1.0f;

	if (hit_info.HitFlag)
	{
		ground_y = hit_info.HitPosition.y + 1.0f;
	}

	if (camera_pos.y < ground_y)
	{
		camera_pos.y = ground_y;
	}

	if (PushHitKey(KEY_INPUT_B))
	{
		ball_pos = camera_pos;

		base.set(0.0f, 0.0f, BALL_SPEED);

		change = GetFloat3VTransform(base,mat);

		ball_mov = change;
	}


	ball_pos += ball_mov;
}
//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void GameRender()
{
	//	カメラ座標と向きを渡してカメラ設定
	SetCameraPositionAndAngle(camera_pos.VGet(), TO_RADIAN(camera_rot.x), TO_RADIAN(camera_rot.y), TO_RADIAN(camera_rot.z));

	//	地面の描画
	MV1DrawModel(ground_model);

	DrawSphere3D(ball_mov.VGet(), 0.1f,100,GetColor(0,255,255), GetColor(255, 255, 255), true);

	DrawString(16, 16, "マウスドラッグ：カメラの向き変更", GetColor(255, 255, 255));
	DrawString(16, 32, "マウスホイール：カメラの向いている方向に移動", GetColor(255, 255, 0));
	DrawString(16, 48, "スペースキー押しながらマウスドラッグ：カメラの向いている方向に対して上下左右移動", GetColor(255, 255, 0));
	DrawString(16, 64, "カメラは地面に埋まらない（地面の高さ + 1.0 より下にならないようにしています）", GetColor(255, 255, 0));
}
//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void GameExit()
{
	MV1DeleteModel(ground_model);
}
