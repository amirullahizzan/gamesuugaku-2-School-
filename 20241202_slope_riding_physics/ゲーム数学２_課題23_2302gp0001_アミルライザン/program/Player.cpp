#include "Main.h"
#include "Game.h"
#include "Hit.h"
#include "Player.h"

//	プレイヤーの移動スピード
#define MOV_SPEED	0.15f
//	プレイヤーの回転スピード
#define ROT_SPEED	3.0f
//	ジャンプスピード
#define JUMP_SPEED	0.5f

//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
void Player::Init( int model )
{
	m_model = model;

	m_pos.x		= -5.0f;
	m_pos.z		= -10.0f;
	m_stand = true;
}
//---------------------------------------------------------------------------------
//	更新処理
//---------------------------------------------------------------------------------
void Player::Update( int ground_model )
{
	//	左右キーでプレイヤーの向きの変更
	if( CheckHitKey( KEY_INPUT_RIGHT ) )	m_rot.y += ROT_SPEED;
	if( CheckHitKey( KEY_INPUT_LEFT ) )		m_rot.y -= ROT_SPEED;
	//	上キーで向いている方向に移動
	if( CheckHitKey( KEY_INPUT_UP ) ){
		Float3 base( 0.0f, 0.0f, MOV_SPEED );
		MATRIX mat = MGetRotY( TO_RADIAN( m_rot.y ) );
		//	ＸＺ方向の移動なので、変数名も xz_mov にしています
		Float3 xz_mov = GetFloat3VTransform( base, mat );
		m_pos += xz_mov;
	}

	//	線の開始座標（プレイヤー座標の少し上）
	Float3 start = m_pos + Float3( 0.0f, 10.0f, 0.0f );
	//	線のゴール座標（プレイヤー座標の少し下）
	Float3 goal = m_pos + Float3( 0.0f, -10.0f, 0.0f );

	//	上で決めた２点の線（ start goal ）と地面（ ground_model ）で
	//	当たり判定をした結果を情報として取得します
	MV1_COLL_RESULT_POLY hit_info = MV1CollCheck_Line( ground_model, -1, start.VGet(), goal.VGet() );

	//	着地すべき地面の高さ
	float ground_y = 0.0f;

	//	地面の傾き方向のベクトル
	//	（地面の情報が取れなかったときのためにＹを１にしときます）
	Float3 ground_normal( 0.0f, 1.0f, 0.0f );

	//	当たり情報が取得出来たら（地面と当たっていたら）
	if( hit_info.HitFlag ){
		//	プレイヤーのＸＺ座標から地面の高さを取得
		ground_y = hit_info.HitPosition.y;
		//	地面の法線も取得しておきます
		ground_normal.VSet( hit_info.Normal );
	}

	//	ジャンプ移動量だけ常に座標移動

	if (m_stand)
	{
		//	スペースキーを押したらジャンプ開始
		if (PushHitKey(KEY_INPUT_SPACE)) {
			//	面の傾いている方向（法線ベクトル方向）にジャンプします
			m_jump_mov = ground_normal;
			//	このベクトルの長さをジャンプスピードに合わせます
			m_jump_mov.SetLength(JUMP_SPEED);
			m_stand = false;
		}
	}
	
	m_pos += m_jump_mov;

	//	プレイヤーのＹ座標は地面よりも下にならない
	if( m_pos.y < ground_y ){
		m_pos.y = ground_y;
		//	着地したということで移動量も０にします
		m_jump_mov.clear();
		m_stand = true;
	}
	//	Ｙ移動量を少しずつ減らしていきます
	m_jump_mov.y -= 0.02f;


	if (m_stand)
	{
		Float3 up(0.0f,1.0f,0.0f);
		Float3 right = GetFloat3Cross(up, ground_normal);
		Float3 down = GetFloat3Cross(right,ground_normal);
		Float3 slide = down;
		slide.SetLength(0.05f);

		m_pos += slide;
	}


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
