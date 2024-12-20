#include "Main.h"
#include "Game.h"
#include "Camera.h"
#include "Random.h"

//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
void Camera::Init()
{
	//	カメラ座標
	m_pos.set( 0.0f, 20.0f, -35.0f );
	//	カメラの向いている角度
	m_rot.set( 35.0f, 0.0f, 0.0f );
}
//---------------------------------------------------------------------------------
//	更新処理
//---------------------------------------------------------------------------------
void Camera::Update()
{
}
//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void Camera::Render()
{
	//	カメラ座標と角度を渡してカメラ設定
	SetCameraPositionAndAngle( m_pos.VGet(), TO_RADIAN( m_rot.x ), TO_RADIAN( m_rot.y ), TO_RADIAN( m_rot.z ) );
}
//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void Camera::Exit()
{
}
