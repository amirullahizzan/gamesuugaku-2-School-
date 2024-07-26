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
	if( PushHitKey( KEY_INPUT_F1 ) )	m_type = TYPE_STAGE;
	if( PushHitKey( KEY_INPUT_F2 ) )	m_type = TYPE_PLAYER;
	if( PushHitKey( KEY_INPUT_F3 ) )	m_type = TYPE_FOLLOW;

	switch( m_type ){
	case TYPE_STAGE:
		m_pos.set( 0.0f, 35.0f, -35.0f );
		m_look.set( 0.0f, 0.0f, -5.0f );
		break;

	case TYPE_PLAYER:
		m_look = player_pos;
		m_pos = m_look + Float3( 0.0f, 5.0f, -10.0f );
		break;

	case TYPE_FOLLOW:
		{
			m_look = player_pos + Float3( 0.0f, 1.0f, 0.0f );

			Float3 reverse_dir = player_mov;

			reverse_dir *= -1.0f;
			reverse_dir.SetLength(5.0f);
			reverse_dir.y = 1.0f;

			//	プレイヤーの後ろ方向のベクトル
			Float3 base( 0.0f, 1.0f, -5.0f );
			MATRIX mat = MGetRotY( TO_RADIAN( player_rot.y ) );
			Float3 behind_dir = GetFloat3VTransform( base, mat );

			//m_pos = m_look + behind_dir;

			float reverse_rate = player_mov.GetLength() / 0.2f;
			float behind_rate = 1.0f - reverse_rate;

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
