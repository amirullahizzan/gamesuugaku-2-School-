#include "Main.h"
#include "Npc.h"
#include "Random.h"

//	ＮＰＣの移動スピード
#define NPC_MOV_SPEED	2.0f
//	ＮＰＣの回転スピード
#define NPC_ROT_SPEED	1.0f

#define VIEW_ANGLE	10.0f

//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
void Npc::Init(int image)
{
	m_image = image;

	m_pos.x = 700.0f;
	m_pos.y = 250.0f;
	m_rot = 90.0f;
}
//---------------------------------------------------------------------------------
//	更新処理
//---------------------------------------------------------------------------------
void Npc::Update(Float2& target_pos)
{
	bool find = false;

	Float2 front;

	front.x = 1.0f * cosf(TO_RADIAN(m_rot));
	front.y = 1.0f * sinf(TO_RADIAN(m_rot));

	Float2 target = target_pos - m_pos;
	target.normalize();

	float front_dot = GetFloat2Dot(front, target);

	float target_radian = acosf(front_dot);
	float target_degree = TO_DEGREE(target_radian);


	if (target_degree < VIEW_ANGLE)
	{
		find = true;
	}


	if (find == false)
	{
		//	向きを変える
		m_rot += NPC_ROT_SPEED;
		//	向いている方向に移動
		m_pos.x += NPC_MOV_SPEED * cosf(TO_RADIAN(m_rot));
		m_pos.y += NPC_MOV_SPEED * sinf(TO_RADIAN(m_rot));
	}
}
//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void Npc::Render()
{
	DrawRotaGraphF(m_pos.x, m_pos.y, 1.0f, TO_RADIAN(m_rot), m_image, TRUE);

	//RED
	Float2 line0;
	line0.x = m_pos.x + 1000.0f * cosf(TO_RADIAN(m_rot));
	line0.y = m_pos.y + 1000.0f * sinf(TO_RADIAN(m_rot));
	DrawLineAA(m_pos.x, m_pos.y, line0.x, line0.y, GetColor(255, 128, 128));

	Float2 line1;
	line1.x = m_pos.x + 1000.0f * cosf(TO_RADIAN(m_rot + VIEW_ANGLE));
	line1.y = m_pos.y + 1000.0f * sinf(TO_RADIAN(m_rot + VIEW_ANGLE));
	DrawLineAA(m_pos.x, m_pos.y, line1.x, line1.y, GetColor(255, 255, 0));

	Float2 line2;
	line2.x = m_pos.x + 1000.0f * cosf(TO_RADIAN(m_rot - VIEW_ANGLE));
	line2.y = m_pos.y + 1000.0f * sinf(TO_RADIAN(m_rot - VIEW_ANGLE));
	DrawLineAA(m_pos.x, m_pos.y, line2.x, line2.y, GetColor(255, 255, 0));
}
//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void Npc::Exit()
{
}
