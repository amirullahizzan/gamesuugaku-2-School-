#include "Main.h"
#include "Game.h"
#include "Hit.h"

#include "Camera.h"
#include "Ground.h"
#include "Player.h"
#include "Npc.h"

//	各モデルデータ用の変数
//	地面モデル
int ground_model;
//	プレイヤーモデル
int player_model;
//	ＮＰＣモデル
int npc_model;

Float3* cameraPos;
Float3* cameraRot;

//	それぞれのクラスの宣言
//	カメラ
Camera	camera;
//	地面
Ground	ground;
//	プレイヤー
Player	player;
//	ＮＰＣ
Npc		npc;

//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
void GameInit()
{
	//	各モデルデータの読み込み
	ground_model = MV1LoadModel("data/ground.mqoz");
	player_model = MV1LoadModel("data/player.mqoz");
	npc_model = MV1LoadModel("data/npc.mqoz");

	//	クラスの初期化
	camera.Init();
	//	読み込んだモデルデータ番号を渡してクラスの初期化
	ground.Init(ground_model);
	player.Init(player_model);
	npc.Init(npc_model);

	cameraPos = &player.m_pos;
	cameraRot = &player.m_rot;
}
//---------------------------------------------------------------------------------
//	更新処理
//---------------------------------------------------------------------------------
void GameUpdate()
{
	ground.Update();
	//	左右キーで回転・上キーで向いている方向に移動
	player.Update();
	//	回転しながら移動
	npc.Update();

	//	プレイヤーの後ろからプレイヤーを見るカメラ
	//	座標と向きを渡します


	if (PushHitKey(KEY_INPUT_SPACE))
	{
		if (cameraPos != &npc.m_pos)
		{
			cameraPos = &npc.m_pos;
			cameraRot = &npc.m_rot;
		}
		else
		{
			cameraPos = &player.m_pos;
			cameraRot = &player.m_rot;
		}
	}


	camera.Update(*cameraPos, *cameraRot);
}
//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void GameRender()
{
	camera.Render();

	ground.Render();
	npc.Render();
	player.Render();

	DrawString(16, 16, "←→キー：プレイヤーの回転", GetColor(255, 255, 255));
	DrawString(16, 32, "↑　キー：向いている方向に移動", GetColor(255, 255, 255));

	DrawString(16, 48, "ＡＤキー：カメラ回転", GetColor(255, 255, 0));
	DrawString(16, 64, "Ｓ　キー：カメラをプレイヤーの後ろに", GetColor(255, 255, 0));
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
