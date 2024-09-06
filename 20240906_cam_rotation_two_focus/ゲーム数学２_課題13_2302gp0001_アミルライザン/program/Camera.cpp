#include "Main.h"
#include "Game.h"
#include "Camera.h"
#include "Random.h"

//	カメラはこれ以上近づかない距離
#define NEAR_DISTANCE	5.0f
//	これ以上離れない
#define FAR_DISTANCE	30.0f

//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
void Camera::Init()
{
	//	カメラ座標
	m_pos.set(0.0f, 5.0f, -10.0f);
	//	見る座標
	m_look.set(0.0f, 0.0f, 0.0f);
}
//---------------------------------------------------------------------------------
//	更新処理（プレイヤーとＮＰＣの座標をもらえるように引数を追加）
//---------------------------------------------------------------------------------
void Camera::Update(Float3& player_pos, Float3& npc_pos)
{
	//	Ｆ１～Ｆ３キーでカメラタイプの変更
	if (PushHitKey(KEY_INPUT_F1))	m_type = TYPE_NORMAL;	//	サンプルで実装したカメラ
	if (PushHitKey(KEY_INPUT_F2))	m_type = TYPE_FRONT;	//	プレイヤーが手前・ＮＰＣが奥になるようなカメラ
	if (PushHitKey(KEY_INPUT_F3))	m_type = TYPE_LEFT;		//	プレイヤーが左・ＮＰＣが右になるようなカメラ

	//	１：見る座標はプレイヤー座標とＮＰＣ座標の中間
	m_look = (player_pos + npc_pos) / 2.0f;

	//	２：プレイヤーとＮＰＣの距離
	float distance = GetFloat3Distance(player_pos, npc_pos);
	

	//	この距離のままだとプレイヤーとＮＰＣの位置関係によっては
	//	少し端に行き過ぎる可能性があるので
	//	少しだけ遠くにします（今回のプロジェクトでは）
	distance *= 1.5f;

	//	この距離に制限をかけます（ 5.0f ～ 30.0f ）
	distance = max(NEAR_DISTANCE, min(distance, FAR_DISTANCE));

	Float3 dir;

	if (m_type == TYPE_NORMAL)
	{
		//	３：基準のベクトル
		dir = Float3(0.0f, 0.5f, -1.0f);
		dir.SetLength(distance);
	}
	else if (m_type == TYPE_FRONT)
	{

		dir = player_pos - npc_pos;
		dir.y = dir.GetLength() / 2.0f;
	}
	else if (m_type == TYPE_LEFT)
	{
		dir = player_pos - npc_pos;
		dir.y = dir.GetLength() / 2.0f;

		auto mat  = MGetRotY(-90);
		dir = GetFloat3VTransform(dir, mat);
	}

		dir.SetLength(distance);
		m_pos = m_look + dir;
	//	４：この基準のベクトルを距離分の長さにします

	//	５：カメラ座標は、見る座標からこのベクトル分先のところ
}
//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void Camera::Render()
{
	//	カメラ座標と見る座標を渡してカメラ設定
	SetCameraPositionAndTarget_UpVecY(VGet(m_pos.x, m_pos.y, m_pos.z), VGet(m_look.x, m_look.y, m_look.z));
}
//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void Camera::Exit()
{
}
