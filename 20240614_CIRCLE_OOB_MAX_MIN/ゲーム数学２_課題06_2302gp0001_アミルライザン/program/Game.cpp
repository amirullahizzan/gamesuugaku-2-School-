#include "Main.h"
#include "Game.h"
#include "Hit.h"
#include "Random.h"

#include "Camera.h"
#include "Ground.h"
#include "Player.h"
#include "Npc.h"

//	���f���f�[�^�p�̕ϐ�
int ground_model;
int player_model;
int npc_model;

//	�N���X�̐錾
Camera	camera;
Ground	ground;
Player	player;
Npc		npc;

//	���F���G���A�~�̔��a
#define AREA_RADIUS			7.0f
//	�G���A�̒��S���W
Float3 area;

//	�v���C���[�̂ǂꂾ���O�ɉ~��u�����̒���
#define FRONT_RADIUS		2.0f
//	�v���C���[�̑O�̉~�̔��a
#define FRONT_LENGTH		5.0f

//	�v���C���[�̑O�̍��W
Float3 front;

//	�v���C���[�̑O�̉~�̕`�掞��
int draw_frame;

//	�m�o�b���~�̒��ɓ����Ă��邩
bool npc_in;

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

	front.clear();
	area.set( 0.0f, 0.0f, 0.0f );
}
//---------------------------------------------------------------------------------
//	�X�V����
//---------------------------------------------------------------------------------
void GameUpdate()
{
	ground.Update();
	//	�\���L�[�ŉ�]�ƈړ�
	player.Update();
	//	������ς��Ȃ���ړ�
	npc.Update();

	//	�v���C���[���G���A����o�Ȃ�����
	float distance = GetFloat3Distance(area, player.m_pos);

	if (distance > AREA_RADIUS)
	{
		Float3 dir = area - player.m_pos;

		float length = distance - AREA_RADIUS;

		Float3 back = dir;

		back.SetLength(length);

		player.m_pos += back;
	}

	//	�X�y�[�X�L�[����������
	if( PushHitKey( KEY_INPUT_SPACE ) )
	{
		//	�P�b�Ԃ����\���������̂�
		draw_frame = 60;
	}
	//	�\�����Ԃ����炵�Ă���
	//	�O��菬�����Ȃ�Ȃ��i max�F�����œn���ꂽ�����̑傫������Ԃ��j
	draw_frame--;
	draw_frame = max( 0, draw_frame );

	//	�v���C���[�̑O�̍��W�����߂�
	front.x = player.m_pos.x + FRONT_LENGTH * cosf(TO_RADIAN(player.m_rot.y - 90.0f));
	front.z = player.m_pos.z - FRONT_LENGTH * sinf(TO_RADIAN(player.m_rot.y - 90.0f));

	//	�܂��͓����Ă��Ȃ���Ԃɂ���
	npc_in = false;

	
	//	�~���`�悳��Ă��鎞�������肷��
	if( draw_frame > 0 )
	{
		if (GetFloat3Distance(front, npc.m_pos) < FRONT_RADIUS)
		{
			npc_in = true;
		}
		//	�~�Ƃm�o�b�̋������~�̔��a����������������
	}

	camera.Update();
}
//---------------------------------------------------------------------------------
//	�`�揈��
//---------------------------------------------------------------------------------
void GameRender()
{
	//	�J�����̐ݒ�
	camera.Render();
	//	���f���̕`��
	ground.Render();
	npc.Render();
	player.Render();

	//	�G���A�̉~�̕`��
	DrawCircle3D_XZ( area, AREA_RADIUS, GetColor( 255, 255, 0 ) );

	//	�`�掞�Ԃ�����Ƃ�����
	if( draw_frame > 0 )
	{
		//	�v���C���[�̑O�̉~�̕`��
		SetDrawBlendMode(DX_BLENDMODE_ALPHA , draw_frame * (255 / 60));
		DrawCircle3D_XZ( front, FRONT_RADIUS, GetColor( 0, 255, 255 ) );
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND , 0);
	}

	float distance = GetFloat3Distance(player.m_pos, npc.m_pos);
	
	clsDx();

	distance = min(distance , 10.0f);

	float rate = distance / 10.0f;

	int r = 600 * (1.0f - rate);
	int g = 600 * rate;

	r = min(r,255);
	g = min(g,255);

	printfDx("%f" , distance);

	DrawFillBox(20, 150, 20 + (int)(distance * 20), 170, GetColor((int)r, (int)g, 0));
	//	�v���C���[�Ƃm�o�b�̋�����\�����邽�߂̃o�[�̊O�g
	DrawLineBox( 20, 150, 220, 170, GetColor( 255, 255, 255 ) );

	//	�m�o�b���~�̒��ɓ����Ă�����
	if( npc_in ){
		DrawString( 16, 80, "���@�m�o�b���v���C���[�O���̉~�̒��ɓ����Ă��܂�", GetColor( 0, 255, 0 ) );
	}

	DrawString( 16, 16, "�\���L�[�F�v���C���[�̉�]�E�ړ�", GetColor( 255, 255, 255 ) );
	DrawString( 16, 32, "���@�v���C���[�͉��F���~����o�Ȃ�", GetColor( 255, 255, 0 ) );

	DrawString( 16, 64, "�X�y�[�X�F���~���v���C���[�̑O�Ɉ�莞�ԕ\��", GetColor( 255, 255, 0 ) );

	DrawString( 16, 128, "�v���C���[�Ƃm�o�b�̋������o�[�ŕ\���i�ő�P�O�j�� �����ȉ��̎��̓o�[�̐F��ς���", GetColor( 255, 255, 0 ) );
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
