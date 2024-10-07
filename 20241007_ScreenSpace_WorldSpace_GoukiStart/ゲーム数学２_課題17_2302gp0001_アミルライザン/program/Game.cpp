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

//	カーソル円の座標（２Ｄ画面座標：２Ｄなので Float2 です）
Float2 cursor;

//	ボールの座標（３Ｄ空間座標：ワールド座標）
Float3 ball_pos;
//	ボールの移動ベクトル（３Ｄ空間を移動するベクトル）
Float3 ball_mov;

float alpha_blend = 0.0f;

float displayTimer = 0.0f;

Float2 textPos;
float textPosOffsetY;

int mode = 0;

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
	//	とりあえず０初期化
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

	//	マウス座標の取得（２Ｄ画面座標）
	cursor.x = GetMouseX();
	cursor.y = GetMouseY();

	//	マウスをクリックしたとき
	if (PushMouseInput()) {
		//	マウス座標を３Ｄ座標に変換してそこからボールをカメラからマウスの先方向に移動させたい
		//	カーソル座標を変換して３Ｄ空間の座標に持っていくために
		VECTOR pos2d = VGet(cursor.x, cursor.y, 0.0f);
		//	この座標を変換します（２Ｄ画面座標を３Ｄ空間座標（ワールド座標）に変換）
		VECTOR wpos = ConvScreenPosToWorldPos(pos2d);

		//	上で求めた座標をボールの座標にします
		ball_pos.VSet(wpos);
		//	ボールの移動ベクトルは画面の奥に行くようにしたい（カメラ座標から今求めた座標の方向）
		ball_mov = ball_pos - camera.m_pos;
		//	ボールの移動スピードの設定
		ball_mov.SetLength(BALL_SPEED);
	}

	//	ボールの座標移動
	ball_pos += ball_mov;

	//	ボールとＮＰＣの当たり判定
	if (CheckBallHit(ball_pos, BALL_RADIUS, npc.m_pos, NPC_RADIUS))
	{
		//	当たったらＮＰＣ側に「HIT!!!」表示を開始
	
		displayTimer = 20.0f;
		npc.speedMult = 10.0f;
		textPosOffsetY = 0.0f;
		mode = 0;
	}

	VECTOR worldPos = npc.m_pos.VGet();
	VECTOR screenPos = ConvWorldPosToScreenPos(worldPos);
	textPos = { screenPos.x - 5.0f,screenPos.y + 2.0f };

	switch (mode)
	{
	case 0 :
		if (displayTimer > 0.0f)
		{
			displayTimer--;
			textPosOffsetY -= 1.2f;

			if (alpha_blend < 255.0f)
			{
				alpha_blend += 20.0f;
			}
		}
		else
		{
			displayTimer = 20.0f;
			mode++;
		}
		break;
	case 1:
		if (displayTimer > 0.0f)
		{
			displayTimer--;
		}
		else
		{
			mode++;
		}
		break;
	case 2:
		if (alpha_blend > 0.0f)
		{
			textPosOffsetY -= 1.2f;
			alpha_blend -= 20.0f;
			displayTimer--;
		}
		else
		{
			mode++;
		}
		break;
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

	//	ボールの描画
	DrawSphere3D(ball_pos.VGet(), BALL_RADIUS, 100, GetColor(255, 255, 0), GetColor(255, 255, 0), TRUE);

	if (alpha_blend > 0.0f)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha_blend);
		DrawString(textPos.x - 25.0f, textPos.y + textPosOffsetY, "HIT!!!", GetColor(255, 255, 255));
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

	//	カーソル円の描画
	DrawCircleAA(cursor.x, cursor.y, 30.0f, 100, GetColor(255, 255, 0), FALSE);

	DrawString(16, 16, "マウス座標にカーソル", GetColor(255, 255, 255));
	DrawString(16, 32, "ＷＡＳＤ：カメラ回転", GetColor(255, 255, 255));
	DrawString(16, 48, "クリック：ボール発射（マウスの所から３Ｄ空間の奥に）", GetColor(255, 255, 255));
	DrawString(16, 64, "→　ボールがＮＰＣに当たったら「HIT!!!」表示", GetColor(255, 255, 0));
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
