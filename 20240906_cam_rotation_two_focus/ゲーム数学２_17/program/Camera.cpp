#include "Main.h"
#include "Game.h"
#include "Camera.h"
#include "Random.h"

#define NEAR_DISTANCE	5.0f
#define FAR_DISTANCE	30.0f

//---------------------------------------------------------------------------------
//	����������
//---------------------------------------------------------------------------------
void Camera::Init()
{
	m_pos.set(0.0f, 5.0f, -10.0f);
	m_look.set(0.0f, 0.0f, 0.0f);
}
//---------------------------------------------------------------------------------
//	�X�V����
//---------------------------------------------------------------------------------
void Camera::Update(Float3& player_pos, Float3& npc_pos)
{
	m_look = (player_pos + npc_pos) / 2.0f; //Nilai tengah

	float distance = GetFloat3Distance(player_pos, npc_pos);
	distance *= 1.5f; // increase by approx camera half twice pov
	distance = max(NEAR_DISTANCE, min(distance, FAR_DISTANCE));

	Float3 dir(0.0f, 0.5f, -1.0f);

	dir.SetLength(distance);

	m_pos = m_look + dir;
}
//---------------------------------------------------------------------------------
//	�`�揈��
//---------------------------------------------------------------------------------
void Camera::Render()
{
	//	�J�������W�ƌ�����W��n���ăJ�����ݒ�
	SetCameraPositionAndTarget_UpVecY(VGet(m_pos.x, m_pos.y, m_pos.z), VGet(m_look.x, m_look.y, m_look.z));
}
//---------------------------------------------------------------------------------
//	�I������
//---------------------------------------------------------------------------------
void Camera::Exit()
{
}
