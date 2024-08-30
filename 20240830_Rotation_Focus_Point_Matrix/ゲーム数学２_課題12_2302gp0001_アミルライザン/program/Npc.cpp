#include "Main.h"
#include "Game.h"
#include "Random.h"
#include "Npc.h"

//	�ړ��X�s�[�h
#define NPC_MOV_SPEED	0.05f
//	��]�X�s�[�h
#define NPC_ROT_SPEED	0.3f

//---------------------------------------------------------------------------------
//	����������
//---------------------------------------------------------------------------------
void Npc::Init( int model )
{
	m_model = model;

	m_pos.x = -5.0f;
	m_pos.z = 10.0f;
	m_rot.y = 90.0f;
}
//---------------------------------------------------------------------------------
//	�X�V����
//---------------------------------------------------------------------------------
void Npc::Update()
{
	m_rot.y += NPC_ROT_SPEED;

	//	���x�N�g�����쐬
	Float3 base( 0.0f, 0.0f, NPC_MOV_SPEED );
	//	�x����]�s����쐬
	MATRIX mat = MGetRotY( TO_RADIAN( m_rot.y ) );
	//	���x�N�g�������̍s��ŕϊ����Ĉړ��x�N�g���쐬
	Float3 mov = VTransform( base.VGet(), mat );
	//	���̈ړ��x�N�g���ō��W�ړ�
	m_pos += mov;
}
//---------------------------------------------------------------------------------
//	�`�揈��
//---------------------------------------------------------------------------------
void Npc::Render()
{
	MV1SetPosition( m_model, VGet( m_pos.x, m_pos.y, m_pos.z ) );
	MV1SetRotationXYZ( m_model, VGet( TO_RADIAN( m_rot.x ), TO_RADIAN( m_rot.y ), TO_RADIAN( m_rot.z ) ) );
	MV1DrawModel( m_model );
}
//---------------------------------------------------------------------------------
//	�I������
//---------------------------------------------------------------------------------
void Npc::Exit()
{
}
