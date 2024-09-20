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

bool draw_circle;
Float3 set_pos;

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
	//	地面モデル（今回は高さを使った処理をしたいと思いますので、起伏のある地面モデルを読み込んでいます）
	ground_model = MV1LoadModel("data/ground.mqoz");
	player_model = MV1LoadModel("data/player.mqoz");

	//	１：地面モデルとの当たり判定をしようと思いますので当たり情報を作成します
	MV1SetupCollInfo(ground_model);

	//	クラスの初期化
	camera.Init();
	ground.Init(ground_model);
	player.Init(player_model);
}
//---------------------------------------------------------------------------------
//	更新処理
//---------------------------------------------------------------------------------
void GameUpdate()
{
	//	２：当たり情報を取得するための情報の更新
	MV1RefreshCollInfo(ground_model);

	//	地面の更新処理
	ground.Update();
	//	プレイヤーの更新処理（今回のプロジェクトでは特に何もしていません）
	player.Update();

	//	プレイヤーの座標が決まったのでこの状態で当たり判定をします
	//	３：モデルと線で当たり判定
	//	３－１：線のための２つの座標を用意します（今回はプレイヤーの上と下）
	//	開始座標はプレイヤーの上
	//	（開始座標をプレイヤーの足元にしてしまうと地面の下での判定になる状況が発生してしまうので）
	Float3 line_start = player.m_pos + Float3(0.0f, 100.0f, 0.0f);
	//	ゴール座標はプレイヤーの下
	Float3 line_goal = player.m_pos + Float3(0.0f, -100.0f, 0.0f);

	//	３－２：当たり判定をして、当たった結果情報を取得
	MV1_COLL_RESULT_POLY hit_info = MV1CollCheck_Line(ground_model, -1, line_start.VGet(), line_goal.VGet());

	//	地面の高さ（地面との当たり判定が取れなかった場合は 0.0f としようと思います）
	float ground_y = 0.0f;

	//	４：当たり情報を使ってプレイヤーを地面の高さにしたい
	//	当たっていたら
	if (hit_info.HitFlag) {
		//	当たっている座標のＹ座標を地面の高さにします
		ground_y = hit_info.HitPosition.y;
	}

	//	プレイヤーのＹ座標が地面の高さよりも下にあるときは地面に埋まっているという事なので
//	if( player.m_pos.y < ground_y ){
		//	地面の高さにします
	player.m_pos.y = ground_y;
	//	}

	camera.Update();

	line_start = camera.m_pos;

	Float3 base(0.0f, 0.0f, 100.0f);
	MATRIX mat_x = MGetRotX(TO_RADIAN(camera.m_rot.x));
	MATRIX mat_y = MGetRotY(TO_RADIAN(camera.m_rot.y));
	MATRIX mat = MMult(mat_x, mat_y);
	Float3 change = GetFloat3VTransform(base, mat);

	line_goal = line_start + change;

	hit_info = MV1CollCheck_Line(ground_model, -1, line_start.VGet(), line_goal.VGet());

	if (hit_info.HitFlag)
	{
		draw_circle = true;
		set_pos.VSet(hit_info.HitPosition);
	}
	else
	{
		draw_circle = false;
	}

	if (PushHitKey(KEY_INPUT_SPACE) && draw_circle)
	{
		player.m_pos = set_pos;
	}
}
//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void GameRender()
{
	camera.Render();
	ground.Render();
	player.Render();

	if (draw_circle)
	{
		float distance = GetFloat3Distance(camera.m_pos, set_pos);
		float rate = distance / 100.0f;
		rate = 1.0f - rate;
		float radius = 50.0f * rate;
		DrawCircle(SCREEN_W / 2, SCREEN_H / 2, radius, GetColor(255, 255, 0), FALSE);
	}

	DrawString(16, 16, "十字キー：カメラ回転", GetColor(255, 255, 255));
	DrawString(16, 32, "スペース：カメラの見ている先と地面が当たっている場所にプレイヤー設置", GetColor(255, 255, 0));
	DrawString(16, 48, "カメラが見ている方向の直線の先に地面がない時は円の描画はしない（プレイヤーの設置もしない）", GetColor(255, 255, 0));
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
