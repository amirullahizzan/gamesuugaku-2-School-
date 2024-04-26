#include "Main.h"
#include "Game.h"
#include "Camera.h"

//	プレイヤーからカメラまでの距離
#define CAMERA_LENGTH	10.0f
//	ＡＤキーを押したときの回転スピード
#define CAMERA_ROT_SPEED	1.0f

//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
void Camera::Init()
{
	//	カメラの初期座標
	m_pos.set(0.0f, 20.0f, -30.0f);
	//	カメラの見る初期座標
	m_look.set(0.0f, 0.0f, 0.0f);
	m_rot = 0.0f;
}
//---------------------------------------------------------------------------------
//	更新処理
//---------------------------------------------------------------------------------
void Camera::Update(Float3& pos, Float3& rot)
{

	//	ＡＤキーでカメラの持っている角度変数を更新
	if (CheckHitKey(KEY_INPUT_D))
	{
		//m_look.x += CAMERA_ROT_SPEED;
	//m_pos.x = m_look.x + CAMERA_LENGTH * sinf( TO_RADIAN( camera_rot ) );
		m_rot++;
	}
	if (CheckHitKey(KEY_INPUT_A))
	{
		m_rot--;
	}

	//	Ｓキーを押したらカメラをリセット（プレイヤーの後ろに）
	if (CheckHitKey(KEY_INPUT_S)) {
		m_rot = rot.y;
	}

	//	見る座標は常にプレイヤー座標（渡されてきた座標）
	m_look = pos;

	//	カメラ座標をプレイヤーの後ろにしたい
	//	カメラ座標は見る座標（プレイヤー座標）から
	//	プレイヤーの後ろの方向（プレイヤーの向き +180 度）に
	//	一定距離離れたところ
	float camera_rot = m_rot + 180.0f;

	//	プレイヤーの後ろ方向の向きを求める（プレイヤー向き + 180 ）

	//	その向きに見る座標から CAMERA_LENGTH 分移動させる
	m_pos.x = m_look.x + CAMERA_LENGTH * sinf(TO_RADIAN(camera_rot));
	m_pos.z = m_look.z + CAMERA_LENGTH * cosf(TO_RADIAN(camera_rot));

	//	このままだとカメラがめっちゃ高いところにあるので
	m_pos.y = m_look.y + 5.0f;
	//m_pos.x = m_look.x;
	//m_pos.z = m_look.z;
}
//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void Camera::Render()
{
	//	カメラ座標と見る座標を渡してカメラの設定
	SetCameraPositionAndTarget_UpVecY(VGet(m_pos.x, m_pos.y, m_pos.z), VGet(m_look.x, m_look.y, m_look.z));
}
//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void Camera::Exit()
{
}
