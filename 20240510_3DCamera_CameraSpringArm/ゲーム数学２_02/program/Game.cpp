#include "Main.h"
#include "Game.h"
#include "Hit.h"

#include "Player.h"

#define BALL_LENGTH 100.0f

int player_image;

//	プレイヤークラス
Player	player;

Float2	ball_pos;

//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
void GameInit()
{
	//	プレイヤー画像を読み込む
	player_image = LoadGraph("data/player.bmp");
	//	画像を渡して初期化
	player.Init(player_image);

	ball_pos.set(500.0f, 200.0f);
}
//---------------------------------------------------------------------------------
//	更新処理
//---------------------------------------------------------------------------------
Float2 dir;
void GameUpdate()
{
	player.Update();

	//円の座標を設定押したい
	//
	dir = ball_pos - player.m_pos; //Range?
	
	//dir.SetLength(BALL_LENGTH);
	////////////////////////////////////
	//Normalize
	float magnitude = dir.GetLength();
	{
		if (magnitude > 0.0f)
		{
			dir /= magnitude;
		}
	}
	////////////////////////////////////
	dir *= BALL_LENGTH;
	ball_pos = player.m_pos + dir;
}
//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void GameRender()
{
	clsDx();
	printfDx("length %.3f : %.3f", dir.x, dir.y);
	DrawLineAA(player.m_pos.x, player.m_pos.y, ball_pos.x, ball_pos.y, GetColor(255, 255, 255));
	DrawCircleAA(ball_pos.x, ball_pos.y, 10.0f, 50, GetColor(255, 255, 0));
	//	プレイヤーの描画
	player.Render();

	DrawString(16, 16, "←→キー：回転", GetColor(255, 255, 255));
	DrawString(16, 32, "↑　キー：移動", GetColor(255, 255, 255));
}
//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void GameExit()
{
	player.Exit();

	DeleteGraph(player_image);
}
