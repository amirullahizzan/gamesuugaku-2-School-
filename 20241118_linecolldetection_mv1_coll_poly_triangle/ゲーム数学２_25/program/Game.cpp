#include "Main.h"
#include "Game.h"
#include "Hit.h"
#include "Random.h"
#include "Float3.h"

#include "Camera.h"
#include "Ground.h"
#include "Player.h"

#define LINE_LENGTH		30.0f

//	�f�[�^�p�̕ϐ�
int ground_model;
int player_model;
int npc_model;

//	�N���X�̐錾
Camera	camera;
Ground	ground;
Player	player;

Float3 line_start;
Float3 line_goal;
float line_rot;

bool player_right;

//---------------------------------------------------------------------------------
//	����������
//---------------------------------------------------------------------------------
void GameInit()
{
	//	�f�[�^�̓ǂݍ���
	ground_model = MV1LoadModel( "data/ground.mqoz" );
	player_model = MV1LoadModel( "data/player.mqoz" );
	npc_model = MV1LoadModel( "data/npc.mqoz" );

	//	�N���X�̏�����
	camera.Init();
	ground.Init( ground_model );
	player.Init( player_model );

	line_start.set( -5.0f, 0.0f, -10.0f );
	line_goal.set( 0.0f, 0.0f, 0.0f );
	line_rot = 0.0f;

	player_right = false;
}
//---------------------------------------------------------------------------------
//	�X�V����
//---------------------------------------------------------------------------------
void GameUpdate()
{
	ground.Update();
	//	�\���L�[�Ō����̕ύX�ƍ��W�ړ�
	player.Update();

	camera.Update();

	if( CheckHitKey( KEY_INPUT_D ) )	line_rot += 2.0f;
	if( CheckHitKey( KEY_INPUT_A ) )	line_rot -= 2.0f;

	Float3 base( 0.0f, 0.0f, LINE_LENGTH );
	MATRIX mat = MGetRotY( TO_RADIAN( line_rot ) );
	Float3 change = GetFloat3VTransform( base, mat );
	line_goal = line_start + change;

}
//---------------------------------------------------------------------------------
//	�`�揈��
//---------------------------------------------------------------------------------
void GameRender()
{
	camera.Render();

	ground.Render();
	player.Render();

	Float3 start = line_start + Float3( 0.0f, 0.1f, 0.0f );
	Float3 goal = line_goal + Float3( 0.0f, 0.1f, 0.0f );
	DrawLine3D( start.VGet(), goal.VGet(), GetColor( 255, 255, 0 ) );

	MV1SetPosition( npc_model, line_start.VGet() );
	MV1SetRotationXYZ( npc_model, VGet( 0.0f, TO_RADIAN( line_rot ), 0.0f ) );
	MV1DrawModel( npc_model );

	DrawSphere3D( goal.VGet(), 0.3f, 100, GetColor( 255, 255, 0 ), GetColor( 255, 255, 0 ), TRUE );

	if( player_right ){
		DrawString( 16, 48, "�v���C���[�͐��̉E�ɂ��܂�", GetColor( 255, 255, 0 ) );
	}else{
		DrawString( 16, 48, "�v���C���[�͐��̍��ɂ��܂�", GetColor( 0, 255, 255 ) );
	}

	DrawString( 16, 16, "�\���L�[�F�v���C���[�̉�]�E�ړ�", GetColor( 255, 255, 255 ) );
	DrawString( 16, 32, "�`�c�L�[�F���̉�]�p�x�ύX", GetColor( 255, 255, 255 ) );

}
//---------------------------------------------------------------------------------
//	�I������
//---------------------------------------------------------------------------------
void GameExit()
{
	camera.Exit();
	ground.Exit();
	player.Exit();

	MV1DeleteModel( ground_model );
	MV1DeleteModel( player_model );
	MV1DeleteModel( npc_model );
}
