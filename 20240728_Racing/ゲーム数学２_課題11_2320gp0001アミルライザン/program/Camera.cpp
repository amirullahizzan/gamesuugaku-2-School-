#include "Main.h"
#include "Game.h"
#include "Random.h"
#include "Camera.h"

//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
void Camera::Init()
{
	m_pos.set( 0.0f, 35.0f, -35.0f );
	m_look.set( 0.0f, 0.0f, -5.0f );

	m_type = TYPE_STAGE;
}
//---------------------------------------------------------------------------------
//	更新処理
//---------------------------------------------------------------------------------
void Camera::Update( Float3 &player_pos, Float3 &player_rot, Float3 &player_mov )
{
	//	全体カメラ
	if( PushHitKey( KEY_INPUT_F1 ) )	m_type = TYPE_STAGE;
	//	プレイヤーを見るカメラ
	if( PushHitKey( KEY_INPUT_F2 ) )	m_type = TYPE_PLAYER;
	//	プレイヤーについていく感じのカメラ
	if( PushHitKey( KEY_INPUT_F3 ) )	m_type = TYPE_FOLLOW;

	switch( m_type ){
	case TYPE_STAGE:
		m_pos.set( 0.0f, 35.0f, -35.0f );
		m_look.set( 0.0f, 0.0f, -5.0f );
		break;

	case TYPE_PLAYER:
		//	見る座標はプレイヤー座標
		m_look = player_pos;
		//	カメラ座標はそこから一定方向離れたところ
		m_pos = m_look + Float3( 0.0f, 5.0f, -10.0f );
		break;

	case TYPE_FOLLOW:	//	プレイヤーについていく感じのカメラ
		{
			//	見る座標はプレイヤーの少し上
			m_look = player_pos + Float3( 0.0f, 1.0f, 0.0f );

			//	移動ベクトルの反対方向のベクトルを作成
			//	いったん移動ベクトルの値にして
			Float3 reverse_dir = player_mov;
			//	このベクトルを逆方向にします
			reverse_dir *= -1.0f;
			//	カメラを良い感じの所に置きたいので
			reverse_dir.SetLength( 5.0f );
			//	適当な高さにします
			reverse_dir.y = 1.0f;

//			m_pos = m_look + reverse_dir;

			//	プレイヤーの後ろ方向のベクトル
			Float3 base( 0.0f, 1.0f, -5.0f );
			MATRIX mat = MGetRotY( TO_RADIAN( player_rot.y ) );
			Float3 behind_dir = GetFloat3VTransform( base, mat );

//			m_pos = m_look + behind_dir;

			//	移動ベクトルが大きいほど reverse の方を
			//	小さかったら behind の方を使う割合を計算
			float reverse_rate = player_mov.GetLength() / 0.2f;	//	MOV_SPEED
			float behind_rate = 1.0f - reverse_rate;

			//	それぞれのベクトルをそれぞれの割合分足したものをカメラ座標に
			m_pos = m_look + reverse_dir * reverse_rate + behind_dir * behind_rate;
		}
		break;
	}
}
//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void Camera::Render()
{
	SetCameraPositionAndTarget_UpVecY( m_pos.VGet(), m_look.VGet() );
}
//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void Camera::Exit()
{
}
