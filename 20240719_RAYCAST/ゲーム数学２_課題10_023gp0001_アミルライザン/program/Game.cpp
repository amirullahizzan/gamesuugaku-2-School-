#include "Main.h"
#include "Game.h"
#include "Hit.h"
#include "Random.h"

#include "Camera.h"
#include "Ground.h"
#include "Player.h"
#include "Npc.h"

int ground_model;
int player_model;
int npc_model;

Camera	camera;
Ground	ground;
Player	player;
Npc		npc;

//	���̊J�n���W
Float3 line_start;
//	���̃S�[�����W
Float3 line_goal;

//	�v���C���[�͂��̋����܂ł�������Ȃ�
#define LIMIT_LENGTH	3.0f
//	������̃v���C���[�Ɉ�ԋ߂����W
Float3 near_pos;

//	�m�o�b�̔��a�i���W�p�j
#define CHARA_RADIUS	1.0f

//---------------------------------------------------------------------------------
//	����������
//---------------------------------------------------------------------------------
void GameInit()
{
	//	���f���f�[�^�̓ǂݍ���
	ground_model = MV1LoadModel( "data/ground.mqoz" );
	player_model = MV1LoadModel( "data/player.mqoz" );
	npc_model = MV1LoadModel( "data/npc.mqoz" );
	//	�N���X�̏�����
	camera.Init();
	ground.Init( ground_model );
	player.Init( player_model );
	npc.Init( npc_model );
	//	���̊J�n���W�ƃS�[�����W�̐ݒ�
	line_start.set( -10.0f, 0.0f, -8.0f );
	line_goal.set( 10.0f, 0.0f, -5.0f );
}
//---------------------------------------------------------------------------------
//	�X�V����
//---------------------------------------------------------------------------------
void GameUpdate()
{
	ground.Update();
	//	�\���L�[�ŉ�]��ړ�
	player.Update();

	float distance = GetFloat3Distance(near_pos, player.m_pos);

	if (distance > LIMIT_LENGTH)
	{
		float length = distance - LIMIT_LENGTH;
		Float3 dir = near_pos - player.m_pos;
		dir.SetLength(length);
		player.m_pos += dir;
	}
	//	��]���Ă��邾��
	npc.Update();

	if (CheckLineBallHit(player.m_pos,player.m_front,npc.m_pos,CHARA_RADIUS))
	{
		npc.m_pos.x = GetRandomF(-20.0f,20.0f);
		npc.m_pos.z = GetRandomF(0.0f,10.0f);
	}

	camera.Update();
}
//---------------------------------------------------------------------------------
//	�`�揈��
//---------------------------------------------------------------------------------
void GameRender()
{
	camera.Render();

	ground.Render();
	npc.Render();
	player.Render();

	//	�����̕`��
	DrawLine3D( line_start.VGet(), line_goal.VGet(), GetColor( 255, 255, 255 ) );

	//	�v���C���[�ƈ�ԋ߂����W����ŕ`��
	DrawLine3D( player.m_pos.VGet(), near_pos.VGet(), GetColor( 0, 255, 0 ) );

	//	������̈�ԋ߂����W�ɋ��̕`��
	DrawSphere3D( near_pos.VGet(), 0.3f, 10, GetColor( 255, 255, 0 ), GetColor( 255, 255, 0 ), TRUE );

	DrawString( 16, 16, "�\���L�[�F�v���C���[��]�E�ړ�", GetColor( 255, 255, 255 ) );
	DrawString( 16, 32, "�v���C���[�����ԋ߂�������̍��W�����߂�i���̍��W�ɏ����ȋ��̕`��͂��Ă��܂��j", GetColor( 255, 255, 0 ) );
	DrawString( 16, 48, "�v���C���[�͂��̋�������ȏ㗣��Ȃ�", GetColor( 255, 255, 0 ) );
}
//---------------------------------------------------------------------------------
//	�I������
//---------------------------------------------------------------------------------
void GameExit()
{
	camera.Exit();
	ground.Exit();
	player.Exit();
	npc.Exit();

	MV1DeleteModel( ground_model );
	MV1DeleteModel( player_model );
	MV1DeleteModel( npc_model );
}
