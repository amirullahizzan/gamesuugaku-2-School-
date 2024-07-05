#include <algorithm>

#include "Main.h"
#include "Game.h"
#include "Npc.h"
#include "Random.h"

//	基準の移動スピード
#define NPC_MOV_SPEED	3.0f

//	ＮＰＣの視野角（正面から±２０度）
#define VIEW_ANGLE	20.0f
//	視野距離
#define VIEW_LENGTH	250.0f
//	ＮＰＣの半径
#define NPC_RADIUS	25.0f

//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
void Npc::Init(int image)
{
	m_image = image;

	m_pos.x = 600.0f;
	m_pos.y = 200.0f;
	m_rot = 180.0f;
}
//---------------------------------------------------------------------------------
//	更新処理
//---------------------------------------------------------------------------------
void Npc::RandomizePos(EPos _pos)
{
	switch (_pos)
	{
	case Left:
		m_pos.x = -NPC_RADIUS;
		m_pos.y = GetRandomF(0, SCREEN_H);
		break;
	case Top:
		m_pos.x = GetRandomF(-NPC_RADIUS, SCREEN_W + NPC_RADIUS);
		m_pos.y = -NPC_RADIUS;
		break;
	case Right:
		m_pos.x = SCREEN_W + NPC_RADIUS;
		m_pos.y = GetRandomF(-NPC_RADIUS, SCREEN_H + NPC_RADIUS);
		break;
	case Bottom:
		m_pos.x = GetRandomF(-NPC_RADIUS, SCREEN_W + NPC_RADIUS);
		m_pos.y = SCREEN_H + NPC_RADIUS;
		break;
	}
}

void Npc::RandomizeRot(EPos _pos)
{
	float straightRot = 0.0f;
	switch (_pos)
	{
	case Left:
		straightRot = 0.0f;
		break;
	case Top:
		straightRot = 90.0f;
		break;
	case Right:
		straightRot = 180.0f;
		break;
	case Bottom:
		straightRot = 270.0f;
		break;
	}
	m_rot = GetRandomF(straightRot - 90.0f, straightRot + 90.0f);
}

void Npc::OOBHandler()
{
	bool isOOB = false;

	EPos currentOOBPos = Left;

	if (m_pos.x < -NPC_RADIUS)
	{
		isOOB = true;
		currentOOBPos = Left;
	}
	else if (m_pos.x > SCREEN_W + NPC_RADIUS)
	{
		isOOB = true;
		currentOOBPos = Right;
	}
	else if (m_pos.y < -NPC_RADIUS)
	{
		isOOB = true;
		currentOOBPos = Top;
	}
	else if (m_pos.y > SCREEN_H + NPC_RADIUS)
	{
		isOOB = true;
		currentOOBPos = Bottom;
	}

	if (isOOB)
	{
		EPos randomizeLocation = (EPos)GetRandomI(4);
		while (randomizeLocation == currentOOBPos)
		{
			randomizeLocation = (EPos)GetRandomI(4);
		}
		RandomizePos(randomizeLocation);
		RandomizeRot(randomizeLocation);

		isOOB = false;
	}
}

void Npc::Update(Float2& target_pos)
{
	//	見つけたかどうか
	bool find = false;

	//	１：２つのベクトルを用意
	//	ＮＰＣの前方向のベクトル（内積から角度を求めたいので長さを 1.0f に）
	Float2 front;
	front.x = 1.0f * cosf(TO_RADIAN(m_rot));
	front.y = 1.0f * sinf(TO_RADIAN(m_rot));

	//	ＮＰＣからプレイヤーへのベクトル
	Float2 target = target_pos - m_pos;
	//	２：ベクトルの正規化（ベクトルの長さを 1.0 にします）
	target.normalize();

	//	３：この２つのベクトルの内積を求める
	float front_dot = GetFloat2Dot(front, target);

	//	４：求めた内積の値から角度を求める
	//	この内積の値（ front_dot ）を acosf 関数に渡すことで角度を取得できます
	//	acosf：アークコサイン関数（ cos 関数の逆関数）← ラジアン角が返ってきます
	float target_radian = acosf(front_dot);
	//	ラジアン角を角度の度にします
	float target_degree = TO_DEGREE(target_radian);

	//	５：求めた角度と視野角で比較
	if (target_degree < VIEW_ANGLE && GetFloat2Distance(m_pos, target_pos) <= VIEW_LENGTH) 
	{
		//	視野角内に入っているので、見つけたフラグを true に
		find = true;
	}

	if (!find)
	{
	//	向いている方向に移動
		//clsDx();
	m_pos.x += NPC_MOV_SPEED * cosf(TO_RADIAN(m_rot));
	m_pos.y += NPC_MOV_SPEED * sinf(TO_RADIAN(m_rot));
	}
	else
	{
		//printfDx("Found!");
	}

	OOBHandler();
}
//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void Npc::Render()
{
	//	ＮＰＣの描画
	DrawRotaGraphF(m_pos.x, m_pos.y, 1.0f, TO_RADIAN(m_rot), m_image, TRUE);

	//	視野角内かどうかを分かりやすくするために線を２本描画
	Float2 line1;
	//	線の先の座標（ＮＰＣの向き +VIEW_ANGLE の方向に長さ VIEW_LENGTH だけ先の場所）
	line1.x = m_pos.x + VIEW_LENGTH * cosf(TO_RADIAN(m_rot + VIEW_ANGLE));
	line1.y = m_pos.y + VIEW_LENGTH * sinf(TO_RADIAN(m_rot + VIEW_ANGLE));
	//	ＮＰＣ座標とこの座標を線で結んで描画
	DrawLineAA(m_pos.x, m_pos.y, line1.x, line1.y, GetColor(255, 128, 128));

	Float2 line2;
	//	ＮＰＣの座標から、ＮＰＣの向き「ー１０度」の方向に長さ 1000.0f だけ先の座標
	line2.x = m_pos.x + VIEW_LENGTH * cosf(TO_RADIAN(m_rot - VIEW_ANGLE));
	line2.y = m_pos.y + VIEW_LENGTH * sinf(TO_RADIAN(m_rot - VIEW_ANGLE));
	//	ＮＰＣ座標とこの座標を線で結んで描画
	DrawLineAA(m_pos.x, m_pos.y, line2.x, line2.y, GetColor(255, 128, 128));

	//Float2 sinCurve;
	//sinCurve.x = sinf(VIEW_ANGLE);
	//const int LINE_NUM = 12;
	//for (int i = 0; i < LINE_NUM; i++)
	//{
	//	sinCurve.y = (float)sin(VIEW_ANGLE + (i + 1) * LINE_NUM);
	//	DrawLine(
	//		i * VIEW_LENGTH / LINE_NUM,
	//		sinCurve.x * VIEW_LENGTH + 240,
	//		(i + 1) * VIEW_LENGTH / LINE_NUM,
	//		sinCurve.y * VIEW_LENGTH + 240,
	//		GetColor(255, 255, 255)
	//	);
	//	sinCurve.x = sinCurve.y;
	//}
	// 
	

	//DrawCurve
	for (int angle = -VIEW_ANGLE ;angle < VIEW_ANGLE;angle++)
	{
		Float2 pos1;
		pos1.x = m_pos.x + VIEW_LENGTH * cosf(TO_RADIAN(m_rot + angle));
		pos1.y = m_pos.y + VIEW_LENGTH * sinf(TO_RADIAN(m_rot + angle));

		Float2 pos2;
		pos2.x = m_pos.x + VIEW_LENGTH * cosf(TO_RADIAN(m_rot + angle + 1.0f));
		pos2.y = m_pos.y + VIEW_LENGTH * sinf(TO_RADIAN(m_rot + angle + 1.0f));
		DrawLineAA(pos1.x, pos1.y, pos2.x, pos2.y, GetColor(200, 255, 0));
	}

	// 
	//DrawLineAA(line1.x, line1.y, line2.x, line2.y, GetColor(200, 128, 128));
}
//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void Npc::Exit()
{
}
