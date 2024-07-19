#include "Main.h"
#include "Game.h"
#include "Player.h"

//	移動スピード
#define PLAYER_MOV_SPEED	0.2f
//	回転スピード（度）
#define PLAYER_ROT_SPEED	3.0f

//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
void Player::Init( int model )
{
	m_model = model;

	m_pos.x		= -5.0f;
	m_pos.z		= -5.0f;
}
//---------------------------------------------------------------------------------
//	更新処理
//---------------------------------------------------------------------------------
void Player::Update()
{
	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		m_length += 3.0f;
	}
	else
	{
		m_length -= 3.0f;

		if (CheckHitKey(KEY_INPUT_RIGHT))	m_rot.y += PLAYER_ROT_SPEED;
		if (CheckHitKey(KEY_INPUT_LEFT))		m_rot.y -= PLAYER_ROT_SPEED;

		//	上キーで向いている方向に移動
		if (CheckHitKey(KEY_INPUT_UP)) {
			//	元ベクトルを作成
			Float3 base(0.0f, 0.0f, PLAYER_MOV_SPEED);
			//	Ｙ軸回転行列を作成
			MATRIX mat = MGetRotY(TO_RADIAN(m_rot.y));
			//	元ベクトルをその行列で変換して移動ベクトル作成
			Float3 mov  = VTransform(base.VGet(), mat);
			//	その移動ベクトルで座標移動
			m_pos += mov;
		}
	}

	m_length = max(0.0f,min(m_length, 20.0f));

	Float3 base(0.0f,0.0f,m_length);

	MATRIX mat = MGetRotY(TO_RADIAN(m_rot.y));
	//	左右キーで向きの変更
	Float3 dir = VTransform(base.VGet(), mat);
	//	その移動ベクトルで座標移動
	m_front = m_pos + dir;
}
//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void Player::Render()
{
	DrawLine3D(m_pos.VGet(), m_front.VGet(), GetColor(0,255,255));

	MV1SetPosition( m_model, VGet( m_pos.x, m_pos.y, m_pos.z ) );
	MV1SetRotationXYZ( m_model, VGet( TO_RADIAN( m_rot.x ), TO_RADIAN( m_rot.y ), TO_RADIAN( m_rot.z ) ) );
	MV1DrawModel( m_model );
}
//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void Player::Exit()
{
}
