#include "Main.h"
#include "Game.h"
#include "Random.h"
#include "Npc.h"

#define NPC_MOV_SPEED	0.05f
#define NPC_ROT_SPEED	0.3f

//---------------------------------------------------------------------------------
//	èâä˙âªèàóù
//---------------------------------------------------------------------------------
void Npc::Init( int model )
{
	m_model = model;

	m_pos.x = -5.0f;
	m_pos.z = 10.0f;
	m_rot.y = 90.0f;
}
//---------------------------------------------------------------------------------
//	çXêVèàóù
//---------------------------------------------------------------------------------
void Npc::Update()
{
	m_rot.y += NPC_ROT_SPEED;

	m_pos.x += NPC_MOV_SPEED * sinf( TO_RADIAN( m_rot.y ) );
	m_pos.z += NPC_MOV_SPEED * cosf( TO_RADIAN( m_rot.y ) );
}
//---------------------------------------------------------------------------------
//	ï`âÊèàóù
//---------------------------------------------------------------------------------
void Npc::Render()
{
	MV1SetPosition( m_model, VGet( m_pos.x, m_pos.y, m_pos.z ) );
	MV1SetRotationXYZ( m_model, VGet( TO_RADIAN( m_rot.x ), TO_RADIAN( m_rot.y ), TO_RADIAN( m_rot.z ) ) );
	MV1DrawModel( m_model );
}
//---------------------------------------------------------------------------------
//	èIóπèàóù
//---------------------------------------------------------------------------------
void Npc::Exit()
{
}
