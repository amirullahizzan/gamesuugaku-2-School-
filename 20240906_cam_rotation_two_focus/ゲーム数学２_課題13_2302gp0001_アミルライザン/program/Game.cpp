#include "Main.h"
#include "Game.h"
#include "Hit.h"
#include "Random.h"
#include "Float3.h"

#include "Camera.h"
#include "Ground.h"
#include "Player.h"
#include "Npc.h"

//	それぞれの円の半径
#define RADIUS	1.0f

//	モデル用の変数
int ground_model;
int player_model;
int npc_model;
//	クラスの宣言
//	プレイヤーとＮＰＣがいい感じに画面に入るようなカメラ
Camera	camera;
Ground	ground;
//	プレイヤーとＮＰＣは一定以上近づかない
Player	player;
Npc		npc;


void CalculatePhysics()
{
	//	１：プレイヤーとＮＰＣの距離
	float distance = GetFloat3Distance(player.m_pos, npc.m_pos);

	//	２：基準の距離（円がちょうどついている時の距離）
	float base_length = RADIUS * 2.0f;

	//	３：２キャラの距離が基準の長さより短かったら
	if (distance < base_length) {
		//	４：どれだけ中に入っているか
		//	（この長さ分円が重なっている）
		float in_length = base_length - distance;

		//	５：どっち方向にずらすか
		//	（ＮＰＣからプレイヤーへのベクトル）
		Float3 dir = player.m_pos - npc.m_pos;

		//	６：このベクトルを重なっている長さにします
		//	（今回はプレイヤーとＮＰＣをそれぞれ動かしたいので
		//		半分の長さにします）
		dir.SetLength(in_length * 0.5f);

		//	７：プレイヤーの座標をこのベクトル分動かす
		player.m_pos += dir;
		//	７：ＮＰＣは反対方向に動かす
		npc.m_pos -= dir;
	}
}

//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
void GameInit()
{
	//	モデルの読み込み
	ground_model = MV1LoadModel("data/ground.mqoz");
	player_model = MV1LoadModel("data/player.mqoz");
	npc_model = MV1LoadModel("data/npc.mqoz");
	//	クラスの初期化
	camera.Init();
	ground.Init(ground_model);
	player.Init(player_model);
	npc.Init(npc_model);
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

	//	プレイヤーとＮＰＣは一定より近くにならない
	//	それぞれの更新処理が終わって座標が決まったので、ここで近づかない設定をします

	


		CalculatePhysics();
	//	プレイヤー座標とＮＰＣ座標を渡してカメラの更新処理
	camera.Update(player.m_pos, npc.m_pos);
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

	//	ＮＰＣの描画
	npc.Render();
	//	ＮＰＣの足元に円の描画
	DrawCircle3D_XZ(npc.m_pos, RADIUS, GetColor(255, 128, 0));

	//	プレイヤーモデルの描画
	player.Render();
	//	プレイヤー円の描画
	DrawCircle3D_XZ(player.m_pos, RADIUS, GetColor(0, 128, 255));

	DrawString(16, 16, "十字キー：プレイヤー回転・移動", GetColor(255, 255, 255));
	DrawString(16, 32, "プレイヤーとＮＰＣがいい感じに画面に入るようなカメラ", GetColor(255, 255, 255));
	DrawString(16, 48, "Ｆ１キー：現状のカメラ", GetColor(255, 255, 0));
	DrawString(16, 64, "Ｆ２キー：プレイヤーが手前・ＮＰＣが奥になるようなカメラ", GetColor(255, 255, 0));
	DrawString(16, 80, "Ｆ３キー：プレイヤーが左・ＮＰＣが右になるようなカメラ", GetColor(255, 255, 0));
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

	MV1DeleteModel(ground_model);
	MV1DeleteModel(player_model);
	MV1DeleteModel(npc_model);
}
