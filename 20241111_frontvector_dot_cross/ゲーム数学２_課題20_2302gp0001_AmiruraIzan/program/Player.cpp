#include "Main.h"
#include "Game.h"
#include "Random.h"
#include "Hit.h"
#include "Player.h"

//	移動スピード
#define PLAYER_MOV_SPEED	0.05f
//	ダッシュ開始時のスピード
#define PLAYER_DASH_SPEED	0.5f

//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
void Player::Init(int model)
{
	m_model = model;

	m_pos.x = 0.0f;
	m_pos.z = 0.0f;
}
//---------------------------------------------------------------------------------
//	更新処理
//---------------------------------------------------------------------------------
void Player::Update()
{
	//	マウスの左ボタンを押しているとき
	if (CheckMouseInput(MOUSE_INPUT_LEFT)) {
		//	マウスの移動量の取得
		float x = (float)GetMouseMoveX();
		//	プレイヤーの回転（Ｙ軸）：ゆっくり目な回転
		m_rot.y += x * 0.2f;
	}

	//	１：外積を求めるために２つのベクトルを用意
	//	１個目のベクトルはプレイヤーの前方向のベクトル

	//	プレイヤーが回転していないときの前方向ベクトル
	Float3 base(0.0f, 0.0f, 1.0f);
	//	このベクトルをプレイヤーの向いている角度分回転させたい
	//	回転させるための行列を取得
	MATRIX mat = MGetRotY(TO_RADIAN(m_rot.y));
	//	この行列を使って基準のベクトルを変換（１個目のベクトル）
	Float3 front = GetFloat3VTransform(base, mat);

	//	２個目のベクトル：上方向のベクトル
	Float3 up(0.0f, 1.0f, 0.0f);

	//	２：この２つのベクトル（ up front ）の外積を取得
	Float3 right = GetFloat3Cross(up, front);

	//	ＡＤキーで左右移動（向きを変えずに）
	if (CheckHitKey(KEY_INPUT_D)) {
		//	右方向ベクトルを移動ベクトルにします
		Float3 mov = right;
		mov.SetLength(PLAYER_MOV_SPEED);
		m_pos += mov;
	}
	if (CheckHitKey(KEY_INPUT_A)) {
		//	左方向移動なんですが右方向移動の逆になります
		Float3 mov = right * -1.0f;
		mov.SetLength(PLAYER_MOV_SPEED);
		m_pos += mov;
	}

	//	Ｗキーで前方向に移動
	if (CheckHitKey(KEY_INPUT_W)) 
	{
		//	前方向のベクトルを移動ベクトルとします
		Float3 mov = front;
		//	そのままだと移動が速いので PLAYER_MOV_SPEED の長さにします
		mov.SetLength(PLAYER_MOV_SPEED);
		//	移動ベクトル分座標移動
		m_pos += mov;
	}

	//	ＱＥキーで左右ダッシュ
	if (PushHitKey(KEY_INPUT_E))
	{
		m_dash = right;
		m_dash.SetLength(PLAYER_DASH_SPEED);
	}
	if (PushHitKey(KEY_INPUT_Q)) 
	{
		m_dash = right * -1;
		m_dash.SetLength(PLAYER_DASH_SPEED);
	}

	SetupCamera_Perspective(TO_RADIAN(perspective));

	m_pos += m_dash;
	m_dash *= 0.9f;
	
	float length = m_dash.GetLength();
	if (length > 0.1f)
	{
		if (perspective < 90.0f)
		{
			perspective += 1.0f;
		}
	}
	else
	{
		if (perspective > 45.0f)
		{
			perspective -= 0.1f;
		}
	}
}
//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void Player::Render()
{
	MV1SetPosition(m_model, VGet(m_pos.x, m_pos.y, m_pos.z));
	MV1SetRotationXYZ(m_model, VGet(TO_RADIAN(m_rot.x), TO_RADIAN(m_rot.y), TO_RADIAN(m_rot.z)));
	MV1DrawModel(m_model);
}
//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void Player::Exit()
{
}
