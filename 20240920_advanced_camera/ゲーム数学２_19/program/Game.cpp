#include "Main.h"
#include "Game.h"
#include "Random.h"
#include "Float3.h"

//	���f���f�[�^�̕ϐ�
int ground_model;
int player_model;
int npc_model;

//	�J�������W
Float3 camera_pos;
//	�J�����̌���
Float3 camera_rot;

//	�v���C���[���W
Float3	player_pos;
//	�v���C���[�̌���
Float3	player_rot;

int light_handle;

//---------------------------------------------------------------------------------
//	����������
//---------------------------------------------------------------------------------
void GameInit()
{
	//	�J�������W�ƌ����̏����ݒ�
	camera_pos.set( 0.0f, 3.0f, -10.0f );
	camera_rot.set( 10.0f, 0.0f, 0.0f );

	//	���f���f�[�^�̓ǂݍ���
	ground_model = MV1LoadModel( "data/ground.mqoz" );
	player_model = MV1LoadModel( "data/player.mqoz" );
	npc_model = MV1LoadModel( "data/npc.mqoz" );

	player_pos.set( 0.0f, 1.0f, -3.0f );

	SetLightDifColor( GetColorF( 0.2f, 0.2f, 0.2f, 1.0f ) );

	light_handle = CreateSpotLightHandle( player_pos.VGet(), VGet( 0.0f, 0.0f, 1.0f ), TO_RADIAN( 45.0f ), TO_RADIAN( 30.0f ), 100.0f, 1.0f, 0.0f, 0.01f );
}
//---------------------------------------------------------------------------------
//	�X�V����
//---------------------------------------------------------------------------------
void GameUpdate()
{

	//	�}�E�X�������Ă��鎞
	if( CheckMouseInput() ){
		//	�}�E�X�̈ړ��ʂ�
		float x = GetMouseMoveX();
		float y = GetMouseMoveY();

		//	�v���C���[�̌�����ύX���܂�
		player_rot.x += y * 0.2f;
		player_rot.y += x * 0.2f;
	}
}
//---------------------------------------------------------------------------------
//	�`�揈��
//---------------------------------------------------------------------------------
void GameRender()
{
	//	�J�������W�ƌ�����n���ăJ�����ݒ�
	SetCameraPositionAndAngle( camera_pos.VGet(), TO_RADIAN( camera_rot.x ), TO_RADIAN( camera_rot.y ), TO_RADIAN( camera_rot.z ) );

	//	�n�ʂ̕`��
	MV1DrawModel( ground_model );

	for( int i = 0; i < 5; i++ ){
		MV1SetPosition( npc_model, VGet( -7.0f + i * 3.5f, 0.0f, 5.0f ) );
		MV1DrawModel( npc_model );
	}

	MV1SetPosition( player_model, VGet( player_pos.x, player_pos.y, player_pos.z ) );
	MV1SetRotationXYZ( player_model, VGet( TO_RADIAN( player_rot.x ), TO_RADIAN( player_rot.y ), TO_RADIAN( player_rot.z ) ) );
	MV1DrawModel( player_model );

	DrawString( 16, 16, "�}�E�X�h���b�O�F�v���C���[�̌����ύX�i���̕����ɃX�|�b�g���C�g�j", GetColor( 255, 255, 255 ) );
	DrawString( 16, 32, "�}�E�X�z�C�[���F�X�|�b�g���C�g�̍L����ύX", GetColor( 255, 255, 255 ) );
}
//---------------------------------------------------------------------------------
//	�I������
//---------------------------------------------------------------------------------
void GameExit()
{
	MV1DeleteModel( ground_model );
	MV1DeleteModel( player_model );
	MV1DeleteModel( npc_model );
}
