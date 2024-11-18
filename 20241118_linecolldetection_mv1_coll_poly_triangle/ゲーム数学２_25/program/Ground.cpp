#include "Main.h"
#include "Game.h"
#include "Ground.h"

//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
void Ground::Init( int model )
{
	m_model = model;

	m_pos.clear();
	m_rot.clear();
}
//---------------------------------------------------------------------------------
//	更新処理
//---------------------------------------------------------------------------------
void Ground::Update()
{
}
//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void Ground::Render()
{
	MV1SetPosition( m_model, VGet( m_pos.x, m_pos.y, m_pos.z ) );
	MV1SetRotationXYZ( m_model, VGet( TO_RADIAN( m_rot.x ), TO_RADIAN( m_rot.y ), TO_RADIAN( m_rot.z ) ) );
	MV1DrawModel( m_model );

	DrawLine3D( VGet( -50.0f, 0.0f,   0.0f ), VGet( 50.0f, 0.0f,  0.0f ), GetColor( 255, 0,   0 ) );
	DrawLine3D( VGet(   0.0f, 0.0f, -50.0f ), VGet(  0.0f, 0.0f, 50.0f ), GetColor(   0, 0, 255 ) );
}
//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void Ground::Exit()
{
}
