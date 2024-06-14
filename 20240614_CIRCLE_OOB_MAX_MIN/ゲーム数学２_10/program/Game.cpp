#include "Main.h"
#include "Game.h"
#include "Hit.h"
#include "Random.h"

#include "Player.h"
#include "Npc.h"

//	画像変数
int player_image;
int npc_image;

//	クラスの宣言
Player	player;
Npc		npc;

#define AREA_RADIUS		200.0f

Float2 area;

#define FRONT_LENGTH	100.0f
#define FRONT_RADIUS	 50.0f

Float2 front;

//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
void GameInit()
{
	//	画像の読み込み
	player_image = LoadGraph("data/player.bmp");
	npc_image = LoadGraph("data/npc.bmp");
	//	クラスの初期化
	player.Init(player_image);
	npc.Init(npc_image);

	area.set(400.0f, 225.0f);
}

int draw_frame;
bool npc_in;

//---------------------------------------------------------------------------------
//	更新処理
//---------------------------------------------------------------------------------
void GameUpdate()
{
	//	十字キーで回転と移動
	player.Update();
	//	向きを変えながら移動
	npc.Update();

	float distance = GetFloat2Distance(area, player.m_pos);

	if (distance > AREA_RADIUS)
	{
		Float2 dir = area - player.m_pos;

		float length = distance - AREA_RADIUS;

		Float2 back = dir;

		back.SetLength(length);

		player.m_pos += back;
	}

	if (PushHitKey(KEY_INPUT_SPACE))
	{
		draw_frame = 60;
	}
	npc_in = false;
	if (draw_frame > 0)
	{
		if (GetFloat2Distance(front, npc.m_pos) < FRONT_RADIUS)
		{
			npc_in = true;
		}
	}

	draw_frame--;
	draw_frame = max(0, draw_frame);

	front.x = player.m_pos.x + FRONT_LENGTH * cosf(TO_RADIAN(player.m_rot));
	front.y = player.m_pos.y + FRONT_LENGTH * sinf(TO_RADIAN(player.m_rot));
}
//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void GameRender()
{
	DrawCircleAA(area.x, area.y, AREA_RADIUS, 100, GetColor(255, 255, 0), FALSE);

	//	ＮＰＣの描画
	npc.Render();
	//	プレイヤーの描画
	player.Render();


	if (draw_frame > 0)
	{
		DrawCircleAA(front.x, front.y, FRONT_RADIUS, 100, GetColor(0, 255, 255), FALSE);
	}

	float distance = GetFloat2Distance(player.m_pos, npc.m_pos);

	distance = min(distance, 200.0f);

	DrawFillBox(20, 150, 20 + (int)distance, 170, GetColor(0, 255, 0));

	DrawLineBox(20, 150, 220, 170, GetColor(255, 255, 255));

	DrawString(16, 16, "十字キー：プレイヤーの回転・移動", GetColor(255, 255, 255));
	DrawString(16, 32, "→　プレイヤーは黄色い円から出ない", GetColor(255, 255, 255));

	DrawString(16, 64, "スペース：青い円をプレイヤーの前に一定時間表示", GetColor(255, 255, 255));

	DrawString(16, 128, "プレイヤーとＮＰＣの距離をバーで表示（最大２００）", GetColor(255, 255, 255));
}
//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void GameExit()
{
	player.Exit();
	npc.Exit();

	DeleteGraph(player_image);
	DeleteGraph(npc_image);
}
