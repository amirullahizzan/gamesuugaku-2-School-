#include "Main.h"
#include "Game.h"
#include "Player.h"

#define PLAYER_MOV_SPEED	5.0f
#define PLAYER_ROT_SPEED	3.0f

//---------------------------------------------------------------------------------
//	èâä˙âªèàóù
//---------------------------------------------------------------------------------
void Player::Init( int image )
{
	m_image = image;

	m_pos.x		= 100.0f;
	m_pos.y		= 150.0f;
	m_rot		= 0.0f;
}
//---------------------------------------------------------------------------------
//	çXêVèàóù
//---------------------------------------------------------------------------------
void Player::Update()
{
	if( CheckHitKey( KEY_INPUT_RIGHT ) )	m_rot += PLAYER_ROT_SPEED;
	if( CheckHitKey( KEY_INPUT_LEFT ) )		m_rot -= PLAYER_ROT_SPEED;

	if( CheckHitKey( KEY_INPUT_UP ) ){
		m_pos.x += PLAYER_MOV_SPEED * cosf( TO_RADIAN( m_rot ) );
		m_pos.y += PLAYER_MOV_SPEED * sinf( TO_RADIAN( m_rot ) );
	}
}
//---------------------------------------------------------------------------------
//	ï`âÊèàóù
//---------------------------------------------------------------------------------
void Player::Render()
{
	DrawRotaGraphF( m_pos.x, m_pos.y, 1.0f, TO_RADIAN( m_rot ), m_image, TRUE );
}
//---------------------------------------------------------------------------------
//	èIóπèàóù
//---------------------------------------------------------------------------------
void Player::Exit()
{
}
