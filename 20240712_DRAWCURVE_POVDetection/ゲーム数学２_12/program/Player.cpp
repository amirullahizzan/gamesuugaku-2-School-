#include "Main.h"
#include "Game.h"
#include "Player.h"

#define PLAYER_MOV_SPEED	5.0f
#define PLAYER_ROT_SPEED	3.0f

//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
void Player::Init( int image )
{
	m_image = image;

	m_pos.x		= 100.0f;
	m_pos.y		= 150.0f;
	m_rot		= 0.0f;
}
//---------------------------------------------------------------------------------
//	更新処理
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
//	描画処理
//---------------------------------------------------------------------------------
void Player::Render()
{
	DrawRotaGraphF( m_pos.x, m_pos.y, 1.0f, TO_RADIAN( m_rot ), m_image, TRUE );
}
//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void Player::Exit()
{
}
