#include "Main.h"
#include "Game.h"
#include "Hit.h"
#include "Random.h"
#include "Float3.h"

#include "Camera.h"
#include "Ground.h"
#include "Player.h"

//	線の長さ
#define LINE_LENGTH		30.0f

//	データ用の変数
int ground_model;
int player_model;
int npc_model;
int wall_model;

//	クラスの宣言
Camera	camera;
Ground	ground;
Player	player;

//	線の開始座標
Float3 line_start;
//	線のゴール座標
Float3 line_goal;
//	線の向く角度（度）：Ｙ軸の回転角度として使います
float line_rot;

//	プレイヤーが線の右にいるかどうか
bool player_right;

//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
void GameInit()
{
	//	データの読み込み
	ground_model = MV1LoadModel("data/ground.mqoz");
	player_model = MV1LoadModel("data/player.mqoz");
	//	今回のＮＰＣモデルはクラスではなく線の開始座標の目安として描画します
	npc_model = MV1LoadModel("data/npc.mqoz");
	wall_model = MV1LoadModel("data/wall.mqoz");

	MV1SetupCollInfo(wall_model);



	//	クラスの初期化
	camera.Init();
	ground.Init(ground_model);
	player.Init(player_model);

	//	線の開始座標の設定
	line_start.set(-5.0f, 0.0f, -10.0f);
	//	更新処理ですぐに座標が変わりますけど、とりあえず
	line_goal.set(0.0f, 0.0f, 0.0f);
	//	０度から開始
	line_rot = 0.0f;

	player_right = false;
}

int draw_frame;
//---------------------------------------------------------------------------------
//	更新処理
//---------------------------------------------------------------------------------
void GameUpdate()
{
	Float3 before_line_dir = line_goal - line_start;
	Float3 before_player_dir = player.m_pos - line_start;
	Float3 before_cross = GetFloat3Cross(before_line_dir, before_player_dir);

	ground.Update();
	player.Update();
	camera.Update();
	//	線の角度を更新（今回の線は自動で回転をしています）
	line_rot += 2.0f;

	//	線の角度の方向に LINE_LENGTH 分先のところにゴール座標を設定
	Float3 base(0.0f, 0.0f, LINE_LENGTH);
	MATRIX mat = MGetRotY(TO_RADIAN(line_rot));
	Float3 change = GetFloat3VTransform(base, mat);
	line_goal = line_start + change;

	Float3 line_dir = line_goal - line_start;
	line_dir.y = 0.0f;
	Float3 player_dir = player.m_pos - line_start;
	player_dir.y = 0.0f;
	Float3 cross = GetFloat3Cross(line_dir, player_dir);

	MV1RefreshCollInfo(wall_model);

	MV1_COLL_RESULT_POLY hit_info = MV1CollCheck_Line(wall_model, -1, line_start.VGet(), line_goal.VGet());

	if (hit_info.HitFlag)
	{
		line_goal.VSet(hit_info.HitPosition);
	}

	Float3 dir_start = line_start - player.m_pos;
	Float3 dir_goal = line_goal - player.m_pos;

	if (GetFloat3Dot(dir_start, dir_goal) < 0.0f)
	{
		if (before_cross.y * cross.y <= 0.0f)
		{
			draw_frame = 60;
		}
	}

	draw_frame--;
}
//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void GameRender()
{
	camera.Render();

	ground.Render();
	player.Render();
	//	線の描画（そのままの座標だと線の描画が地面に埋まってしまう場合があるので少し上にあげています）
	Float3 start = line_start + Float3(0.0f, 0.1f, 0.0f);
	Float3 goal = line_goal + Float3(0.0f, 0.1f, 0.0f);
	//	開始座標とゴール座標を結んで線の描画
	DrawLine3D(start.VGet(), goal.VGet(), GetColor(255, 255, 0));

	//	線の開始座標の目安としてその場所に（向きも）ＮＰＣモデルの描画だけしています
	MV1SetPosition(npc_model, line_start.VGet());
	MV1SetRotationXYZ(npc_model, VGet(0.0f, TO_RADIAN(line_rot), 0.0f));
	MV1DrawModel(npc_model);
	MV1DrawModel(wall_model);

	//	ゴール座標に黄色い球の描画
	DrawSphere3D(goal.VGet(), 0.3f, 100, GetColor(255, 255, 0), GetColor(255, 255, 0), TRUE);

	Float3 pos1;
	Float3 pos2;
	Float3 pos3;

	Float3 dir1to2 = pos2 - pos1;
	Float3 dir1toPlayer = player.m_pos - pos1;

	Float3 dir2to3 = pos3 - pos2;
	Float3 dir2toPlayer = player.m_pos - pos2;

	Float3 dir3to1 = pos1 - pos3;
	Float3 dir3toPlayer = player.m_pos - pos3;

	bool triangle_in = false;
	Float3 cross1 = GetFloat3Cross(dir1to2, dir1toPlayer);
	Float3 cross2 = GetFloat3Cross(dir2to3, dir2toPlayer);
	Float3 cross3 = GetFloat3Cross(dir3to1, dir3toPlayer);

	if (cross1.y > 0.0f && cross2.y > 0.0f && cross3.y > 0.0f)
	{
		triangle_in = true;
	}
	if (cross1.y < 0.0f && cross2.y < 0.0f && cross3.y < 0.0f)
	{
		triangle_in = true;
	}

	DrawLine3D(pos1.VGet(), pos2.VGet(), GetColor(0, 255, 0));
	DrawLine3D(pos2.VGet(), pos3.VGet(), GetColor(0, 255, 0));
	DrawLine3D(pos3.VGet(), pos1.VGet(), GetColor(0, 255, 0));

	if (triangle_in)
	{
		DrawString(450, 270, "三角の中にプレイヤーがいます", GetColor(0, 255, 0));

	}

	if (draw_frame > 0)
	{
		DrawString(336, 350, "線が通過しました", GetColor(255, 255, 0));
	}

	DrawString(16, 16, "十字キー：プレイヤーの回転・移動", GetColor(255, 255, 255));
	DrawString(16, 32, "線が通過した時に一定時間文字列の描画", GetColor(255, 255, 0));
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
	MV1DeleteModel(npc_model);
}
