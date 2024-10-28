#include "Main.h"
#include "Game.h"
#include "Hit.h"
#include "Random.h"
#include "Float2.h"
#include "Float3.h"

//	ボールの半径
#define BALL_RADIUS		0.2f
//	ボールが出てくる黒い円の半径
#define START_RADIUS	1.0f
//	ボールの移動スピード
#define BALL_SPEED		0.5f

//	登場エリア円の半径
#define AREA_RADIUS		6.0f

//登場エリアの数
#define AREA_MAX	6
//	各エリアの中心座標
Float3 area_pos[AREA_MAX] = {
	{   8.0f, 0.1f,   7.0f },
	{  -8.0f, 0.1f,   7.0f },
	{   8.0f, 0.1f, -13.0f },
	{  -8.0f, 0.1f, -13.0f },
	{  20.0f, 0.1f,  -3.0f },
	{ -20.0f, 0.1f,  -3.0f },
};

//	画面にぶつかったときに描画するペイント画像
int paint_image;
//	モデル
int ground_model;

//	カメラ座標と向き
Float3 camera_pos;
Float3 camera_rot;

//	ボール発射座標（ワールド座標）
Float3 start_pos;

//	ボールの座標（ワールド座標）
Float3 ball_pos;
//	ボールの移動ベクトル
Float3 ball_mov;
//	ボールが飛んでいるのかどうか
bool ball_active;

//	ペイント画像の表示座標（２Ｄの描画座標：Ｘ・Ｙを使って描画します）
Float2 paint_pos;

//	一定時間を数える用の変数
int frame_count;

int area_num;
int shake_frame;

float start_radius;
int paint_alpha;


//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
void GameInit()
{
	//	カメラ座標の初期設定
	camera_pos.set( 0.0f, 25.0f, -35.0f );
	//	カメラの向き
	camera_rot.set( 37.0f, 0.0f, 0.0f );

	//	ペイント画像の読み込み
	paint_image = LoadGraph( "data/paint.bmp" );

	ground_model = MV1LoadModel( "data/ground.mqoz" );

	start_pos.set( 0.0f, 0.1f, 0.0f );
	frame_count = 0;

	//	ボールの初期設定
	ball_pos.clear();
	ball_mov.clear();
	//	ボールは飛んでいない状態から開始
	ball_active = false;

	//	ペイント画像の表示座標
	paint_pos.set( 0.0f, 0.0f );
}
//---------------------------------------------------------------------------------
//	更新処理
//---------------------------------------------------------------------------------
void GameUpdate()
{
	frame_count++;

	if (frame_count >= 0 && frame_count <= 20) start_radius += 0.05f;
	if (frame_count >= 250 && frame_count <= 270) start_radius += 0.05f;
	start_radius = max(0.0f, min(start_radius, START_RADIUS));

	if (frame_count >= 300) {
		frame_count = 0;

		//		start_pos.z = GetRandomF(-20.0f, 20.0f);
		//		start_pos.x = GetRandomF(-20.0f, 20.0f);

				//area_num += GetRandomI(1,AREA_MAX-1);
				//area_num %= AREA_MAX;

		float length = GetRandomF(AREA_RADIUS - START_RADIUS);

		float rot = GetRandomF(360.0f);

		start_pos.x = area_pos[area_num].x + length * sinf(TO_RADIAN(rot));
		start_pos.z = area_pos[area_num].x + length * sinf(TO_RADIAN(rot));
	}

	if (frame_count == 120)
	{
		ball_pos = start_pos;
		ball_mov = camera_pos - ball_pos;
		ball_mov.SetLength(BALL_SPEED);
		ball_active = true;

		area_num += GetRandomI(1, AREA_MAX - 1);
		area_num %= AREA_MAX;
	}

	if (ball_active)
	{
		ball_pos += ball_mov;
		float distance = GetFloat3Distance(ball_pos, camera_pos);
		if (distance < 2.0f)
		{
			VECTOR pos2d = ConvWorldPosToScreenPos(ball_pos.VGet());
			paint_pos.x = pos2d.x;
			paint_pos.y = pos2d.y;
			paint_alpha = 255;
			ball_active = false;
			shake_frame = 15;
		}

	}

	//ball_pos += ball_mov;
	paint_pos.y += 0.35f;
	paint_alpha -= 5;
	paint_alpha = max(0, paint_alpha);

	shake_frame--;
	shake_frame = max(0, shake_frame);

	if (PushMouseInput())
	{
		float x = GetMouseX();
		float y = GetMouseY();

		VECTOR start = ConvScreenPosToWorldPos(VGet(x, y, 0.0f));
		VECTOR goal = ConvScreenPosToWorldPos(VGet(x, y, 1.0f));

		Float3 line_start(start);
		Float3 line_goal(goal);
		if (CheckLineBallHit(line_start, line_goal, ball_pos, BALL_RADIUS))
		{
			ball_active = false;
		}

	}
}
//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void GameRender()
{
	//	座標と向きを渡してカメラの設定
		//	座標と向きを渡してカメラの設定
	SetCameraPositionAndAngle(camera_pos.VGet(), TO_RADIAN(camera_rot.x), TO_RADIAN(camera_rot.y), TO_RADIAN(camera_rot.z));

	//	地面モデルの描画
	MV1DrawModel(ground_model);

	for (int i = 0; i < AREA_MAX; i++)
	{
		//	ボールの発射座標に円の描画
		if (i == area_num)
		{
			DrawCircle3D_XZ(area_pos[i], AREA_RADIUS, GetColor(0, 255, 255), true);

		}
		else
		{
			DrawCircle3D_XZ(area_pos[i], AREA_RADIUS, GetColor(255, 128, 128), true);
		}
	}

	if (ball_active)
	{
		//	黄色いボールの描画
		DrawSphere3D(ball_pos.VGet(), BALL_RADIUS, 32, GetColor(255, 255, 0), GetColor(255, 255, 0), TRUE);
	}

	//	ペイント画像の描画
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	DrawRotaGraphF(paint_pos.x, paint_pos.y, 1.0f, TO_RADIAN(0.0f), paint_image, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	int x = 0;
	int y = 0;
	if (shake_frame > 0)
	{
		x = GetRandomI(-3, 3);
		y = GetRandomI(-3, 3);
	}

	DrawString(16 + x, 16 + y, "一定タイミングで地面の円からカメラにボール発射", GetColor( 255, 255, 255 ) );
	DrawString(16 + x, 32 + y, "ボールがカメラの近くになったら２Ｄ画面座標に画像を描画", GetColor( 255, 255, 255 ) );
	DrawString(16 + x, 48 + y, "ボールが出てくる黒い円を、出てくるときと消えるときに半径を変更する", GetColor( 255, 255, 0 ) );
	DrawString(16 + x, 64 + y, "黒い円の登場場所を赤い円の中のどこかランダムに（２回連続同じ円にはならない）", GetColor( 255, 255, 0 ) );
	DrawString(16 + x, 80 + y, "画面に当たったペイント画像は下に移動しながら透明になって消えていく", GetColor( 255, 255, 0 ) );
}
//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void GameExit()
{
	MV1DeleteModel( ground_model );
}
