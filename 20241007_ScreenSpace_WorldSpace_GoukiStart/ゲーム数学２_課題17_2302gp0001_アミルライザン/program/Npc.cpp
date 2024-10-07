#include "Main.h"
#include "Game.h"
#include "Random.h"
#include "Npc.h"

//	�m�o�b�̈ړ��X�s�[�h
#define NPC_MOV_SPEED	0.025f
//	�m�o�b�̉�]�X�s�[�h
#define NPC_ROT_SPEED	0.2f

//---------------------------------------------------------------------------------
//	����������
//---------------------------------------------------------------------------------
void Npc::Init( int model )
{
	m_model = model;

	m_pos.set( 0.0f, 0.0f, -10.0f );
	m_rot.y = -90.0f;

	speedMult = 1.0f;
}
//---------------------------------------------------------------------------------
//	�X�V����
//---------------------------------------------------------------------------------
void Npc::Update()
{
	if (speedMult > 1.0f)
	{
		speedMult -= 0.5f;
	}


	//	������ς���
	m_rot.y += NPC_ROT_SPEED;
	//	���W�ړ�
	Float3 base( 0.0f, 0.0f, NPC_MOV_SPEED);
	MATRIX mat = MGetRotY( TO_RADIAN( m_rot.y ) );
	Float3 mov = GetFloat3VTransform( base, mat );
	m_pos += mov * speedMult;
}
//---------------------------------------------------------------------------------
//	�`�揈��
//---------------------------------------------------------------------------------
void Npc::Render()
{
	//	�m�o�b�̃��f���̕`��
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
