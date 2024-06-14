#include "Main.h"
#include "Player.h"

#define PLAYER_MOV_SPEED	0.1f
#define PLAYER_ROT_SPEED	3.0f

//---------------------------------------------------------------------------------
//	èâä˙âªèàóù
//---------------------------------------------------------------------------------
void Player::Init( int model )
{
	m_model = model;
	m_pos.set( -3.0f, 0.0f, 0.0f );
	m_rot.set( 0.0f, 0.0f, 0.0f );
}
//---------------------------------------------------------------------------------
//	çXêVèàóù
//---------------------------------------------------------------------------------
void Player::Update()
{
	if( CheckHitKey( KEY_INPUT_RIGHT ) )	m_rot.y += PLAYER_ROT_SPEED;
	if( CheckHitKey( KEY_INPUT_LEFT ) )		m_rot.y -= PLAYER_ROT_SPEED;

	if( CheckHitKey( KEY_INPUT_UP ) ){
		m_pos.x += PLAYER_MOV_SPEED * sinf( TO_RADIAN( m_rot.y ) );
		m_pos.z += PLAYER_MOV_SPEED * cosf( TO_RADIAN( m_rot.y ) );
	}
}
//---------------------------------------------------------------------------------
//	ï`âÊèàóù
//---------------------------------------------------------------------------------
void Player::Render()
{
	MV1SetPosition( m_model, VGet( m_pos.x, m_pos.y, m_pos.z ) );
	MV1SetRotationXYZ( m_model, VGet( TO_RADIAN( m_rot.x ), TO_RADIAN( m_rot.y ), TO_RADIAN( m_rot.z ) ) );
	MV1DrawModel( m_model );
}
//---------------------------------------------------------------------------------
//	èIóπèàóù
//---------------------------------------------------------------------------------
void Player::Exit()
{
}
