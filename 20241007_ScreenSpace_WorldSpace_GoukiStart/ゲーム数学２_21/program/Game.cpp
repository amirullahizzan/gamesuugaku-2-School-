#include "Main.h"
#include "Game.h"
#include "Hit.h"
#include "Random.h"
#include "Float3.h"
#include "Float2.h"

#include "Camera.h"
#include "Ground.h"
#include "Npc.h"

//	ボールの移動スピード
#define BALL_SPEED		1.0f
//	ボールの半径
#define BALL_RADIUS		0.1f
//	ＮＰＣの半径
#define NPC_RADIUS		0.75f

//	モデルデータ用の変数
int ground_model;
int npc_model;

//	クラスの宣言
Camera camera;
Ground ground;
Npc	npc;

//	カーソル円の座標
Float2 cursor;

//	ボールの座標
Float3 ball_pos;
//	ボールの移動ベクトル
Float3 ball_mov;

//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
void GameInit()
{
	//	モデルデータの読み込み
	ground_model = MV1LoadModel("data/ground.mqoz");
	npc_model = MV1LoadModel("data/npc.mqoz");

	//	クラスの初期化
	camera.Init();
	ground.Init(ground_model);
	npc.Init(npc_model);

	ball_pos.clear();
	ball_mov.clear();
}
//---------------------------------------------------------------------------------
//	更新処理
//---------------------------------------------------------------------------------
void GameUpdate()
{
	ground.Update();
	//	ＮＰＣの回転
	npc.Update();
	//	カメラの設定
	camera.Update();

	//	マウス座標の取得
	cursor.x = GetMouseX();
	cursor.y = GetMouseY();

	//	マウスをクリックしたとき
	if (PushMouseInput())
	{
		//ball_pos = camera.m_pos;
		//Float3 forward_vector = Float3(0.0f, 0.0f, 1.0f);
		//MATRIX mat_x = MGetRotX(TO_RADIAN(camera.m_rot.x));
		//MATRIX mat_y = MGetRotY(TO_RADIAN(camera.m_rot.y));
		//MATRIX mat = MMult(mat_x, mat_y);
		//ball_mov = GetFloat3VTransform(forward_vector, mat);
		//

	VECTOR worldPos = ConvScreenPosToWorldPos(VECTOR{ cursor.x, cursor.y, 0.0f });

	ball_pos.VSet(worldPos);

	ball_mov = ball_pos - camera.m_pos;
	

	ball_mov.SetLength(BALL_SPEED);
	}


	ball_pos += ball_mov;

	//	ボールとＮＰＣの当たり判定
	if (CheckBallHit(ball_pos, BALL_RADIUS, npc.m_pos, NPC_RADIUS)) {
		//	ＮＰＣの座標を再設定
		npc.SetRandom();
	}
}
//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void GameRender()
{
	//	カメラの設定
	camera.Render();

	ground.Render();
	npc.Render();

	DrawSphere3D(ball_pos.VGet(), BALL_RADIUS, 100, GetColor(255, 255, 0), GetColor(255, 255, 0), TRUE);

	//	カーソル円の描画
	DrawCircleAA(cursor.x, cursor.y, 30.0f, 100, GetColor(255, 255, 0), FALSE);

	DrawString(16, 16, "マウス座標にカーソル", GetColor(255, 255, 255));
	DrawString(16, 32, "ＷＡＳＤ：カメラ回転", GetColor(255, 255, 255));
	DrawString(16, 48, "クリック：ボール発射（マウスの所から３Ｄ空間の奥に）", GetColor(255, 255, 255));
	DrawString(16, 64, "→　ボールがＮＰＣに当たったら座標を再設定", GetColor(255, 255, 255));
}
//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void GameExit()
{
	camera.Exit();
	ground.Exit();
	npc.Exit();

	MV1DeleteModel(ground_model);
	MV1DeleteModel(npc_model);
}
