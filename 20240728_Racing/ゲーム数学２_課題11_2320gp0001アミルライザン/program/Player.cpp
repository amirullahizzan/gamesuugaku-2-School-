#include "Main.h"
#include "Game.h"
#include "Player.h"

//	移動スピード（ここまでスピードを上げる）
#define MOV_SPEED	0.2f
//	回転スピード（度）
#define ROT_SPEED	2.0f

//	加速スピード
#define ACCEL_SPEED	0.005f
//	減速スピード
#define BRAKE_SPEED	0.003f

//	一番近い線からこの距離より離れたらスピードを落とす
#define LIMIT_LENGTH	5.0f

//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
void Player::Init( int model )
{
	m_model = model;

	m_pos.set( -25.0f, 0.0f, 0.0f );
	m_rot.y = 0.0f;

	m_mov.set( 0.0f, 0.0f, 0.0f );
}
//---------------------------------------------------------------------------------
//	更新処理
//---------------------------------------------------------------------------------
void Player::Update(float near_length)
{
	//	左右キーで向きの変更
	if( CheckHitKey( KEY_INPUT_RIGHT ) )	m_rot.y += ROT_SPEED;
	if( CheckHitKey( KEY_INPUT_LEFT ) )		m_rot.y -= ROT_SPEED;

	//	上キーを押している時
	if( CheckHitKey( KEY_INPUT_UP ) ){
		//	プレイヤーが向いている方向に加速ベクトルを作成
		Float3 base( 0.0f, 0.0f, ACCEL_SPEED );
		//	このベクトルをプレイヤーの向きに合わせたいので回転行列
		MATRIX mat = MGetRotY( TO_RADIAN( m_rot.y ) );
		//	行列変換して加速ベクトルにします
		Float3 accel = GetFloat3VTransform( base, mat );

		//	移動ベクトルに加速ベクトルを足します
		m_mov += accel;
		//	移動ベクトルの大きさは移動スピードより大きくしない
		if( m_mov.GetLength() > MOV_SPEED ){
			m_mov.SetLength( MOV_SPEED );
		}

		if (near_length > LIMIT_LENGTH)
		{
			float speed = m_mov.GetLength();

			speed -= BRAKE_SPEED * 3.0f;
			speed = max(MOV_SPEED * 0.2f, speed);

			m_mov.SetLength(speed);
		}
	}else{
		//	キーを押していないとき
		//	徐々にスピードを落としていくような処理
		//	移動ベクトルを小さくしていく
		float speed = m_mov.GetLength();
		//	このスピードを減らす
		speed -= BRAKE_SPEED;
		//	0.0f よりは小さくしたくない
		speed = max( 0.0f, speed );
		//	移動ベクトルをこの大きさにする
		m_mov.SetLength( speed );
	}

	//	移動ベクトル分座標移動
	m_pos += m_mov;
}
//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void Player::Render()
{
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
