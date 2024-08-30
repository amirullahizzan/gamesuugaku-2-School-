#include "Main.h"
#include "Game.h"
#include "Random.h"
#include "Float3.h"

int ground_model;
int player_model;

//	プレイヤー座標
Float3	player_pos;
//	プレイヤーの向き
Float3	player_rot;

//	線の開始座標
Float3 line_start;
//	線のゴール座標
Float3 line_goal;

//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
void GameInit()
{
	SetCameraPositionAndTarget_UpVecY(VGet(0.0f, 3.0f, -10.0f), VGet(0.0f, 1.0f, 2.0f));

	ground_model = MV1LoadModel("data/ground.mqoz");
	player_model = MV1LoadModel("data/player.mqoz");

	//	プレイヤーの初期座標
	player_pos.set(0.0f, 1.0f, -3.0f);
	//	プレイヤーの初期向き
	player_rot.set(0.0f, 0.0f, 0.0f);

	line_start.clear();
	line_goal.clear();
}
//---------------------------------------------------------------------------------
//	更新処理
//---------------------------------------------------------------------------------
void GameUpdate()
{
	//	左右キーを押しているとき（プレイヤーのＹ軸回転）
	if (CheckHitKey(KEY_INPUT_RIGHT))	player_rot.y += 1.0f;
	if (CheckHitKey(KEY_INPUT_LEFT))		player_rot.y -= 1.0f;

	//	上下キーでプレイヤー回転
	if (CheckHitKey(KEY_INPUT_UP))
	{
		player_rot.x -= 1.0f;
	}
	if (CheckHitKey(KEY_INPUT_DOWN))
	{
		player_rot.x += 1.0f;
	}

	line_start = player_pos;

	Float3 base(0.0f, 0.0f, 10.0f);

	MATRIX mat_x = MGetRotX(TO_RADIAN(player_rot.x));
	MATRIX mat_y = MGetRotY(TO_RADIAN(player_rot.y));


	//method 1
	//Float3 dir_x = GetFloat3VTransform(base, mat_x);
	//Float3 change = GetFloat3VTransform(dir_x, mat_y);

	//method 2
	MATRIX mat = MMult(mat_x, mat_y);
	Float3 change = GetFloat3VTransform(base,mat);

	line_goal = player_pos + change;



}
//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void GameRender()
{
	//	地面の描画
	MV1DrawModel(ground_model);
	//	座標や向きを設定してプレイヤーモデルの描画
	MV1SetPosition(player_model, VGet(player_pos.x, player_pos.y, player_pos.z));
	MV1SetRotationXYZ(player_model, VGet(TO_RADIAN(player_rot.x), TO_RADIAN(player_rot.y), TO_RADIAN(player_rot.z)));
	MV1DrawModel(player_model);

	Float3 circle_pos = player_pos;

	circle_pos.y = 0.01f;

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	DrawCircle3D_XZ(circle_pos, 0.5f, GetColor(0, 0, 0), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	DrawLine3D(line_start.VGet(), line_goal.VGet(), GetColor(255, 255, 0));

	DrawString(16, 16, "十字キー：プレイヤーの向き変更", GetColor(255, 255, 255));
	DrawString(16, 32, "プレイヤーの前方に向かって線を描画", GetColor(255, 255, 255));
}
//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void GameExit()
{
	MV1DeleteModel(ground_model);
	MV1DeleteModel(player_model);
}
