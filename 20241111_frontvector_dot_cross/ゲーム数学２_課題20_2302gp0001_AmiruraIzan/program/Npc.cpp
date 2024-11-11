#include "Main.h"
#include "Game.h"
#include "Random.h"
#include "Hit.h"
#include "Npc.h"

//	プレイヤーとＮＰＣがこの距離以下だったら左右移動
#define MOVE_LENGTH	3.0f

//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
void Npc::Init( int model )
{
	m_model = model;
	//	座標や向きをランダムに設定
	m_pos.x = GetRandomF( -30.0f, 30.0f );
	m_pos.z = GetRandomF( -30.0f, 30.0f );
	m_rot.y = GetRandomF( 360.0f );
}
//---------------------------------------------------------------------------------
//	更新処理
//---------------------------------------------------------------------------------
void Npc::Update(Float3 &player_pos, Float3 &camera_rot)
{
	m_rot.y = camera_rot.y + 180.0f;

	float distance = GetFloat3Distance(m_pos,player_pos);

	if (distance < MOVE_LENGTH)
	{
		m_frame = 20;
	}

	m_frame--;

	m_frame = max(0, m_frame);

	if (m_frame > 0)
	{
		Float3 base(0.0f,0.0f,1.0f);

		MATRIX mat = MGetRotY(TO_RADIAN(m_rot.y));

		Float3 front = GetFloat3VTransform(base, mat);

		Float3 up(0.0f, 1.0f, 0.0f);
		
		Float3 right = GetFloat3Cross(up,front);

		float speed = 0.1f;

		VECTOR pos2d = ConvWorldPosToScreenPos(m_pos.VGet());

		if (pos2d.x > SCREEN_W / 2.0f)
		{
			speed - 0.1f;
		}

		Float3 mov = right;

		mov.SetLength(speed);

		m_pos += mov;
	}
}
//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void Npc::Render()
{
	MV1SetPosition( m_model, VGet( m_pos.x, m_pos.y, m_pos.z ) );
	MV1SetRotationXYZ( m_model, VGet( TO_RADIAN( m_rot.x ), TO_RADIAN( m_rot.y ), TO_RADIAN( m_rot.z ) ) );
	MV1DrawModel( m_model );
}
//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void Npc::Exit()
{
}
