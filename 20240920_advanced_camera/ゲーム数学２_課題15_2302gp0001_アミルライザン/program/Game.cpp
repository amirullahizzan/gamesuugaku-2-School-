#include "Main.h"
#include "Game.h"
#include "Random.h"
#include "Float3.h"

//	�n�ʃ��f��
int ground_model;

//	�J�������W
Float3 camera_pos;
//	�J�����̌���
Float3 camera_rot;

#define BALL_SPEED  1.0f

Float3 ball_pos;
Float3 ball_mov;

//---------------------------------------------------------------------------------
//	����������
//---------------------------------------------------------------------------------
void GameInit()
{
	//	�J�������W�ƌ����̏����ݒ�
	camera_pos.set(0.0f, 5.0f, -20.0f);
	camera_rot.set(10.0f, 0.0f, 0.0f);

	//	�n�ʃ��f���̓ǂݍ���
	ground_model = MV1LoadModel("data/ground.mqoz");

	//	����������쐬
	MV1SetupCollInfo(ground_model);
}
//---------------------------------------------------------------------------------
//	�X�V����
//---------------------------------------------------------------------------------
void GameUpdate()
{
	//	��������̍X�V
	MV1RefreshCollInfo(ground_model);
	Float3 base;
	//	�}�E�X�������Ă��鎞
	if (CheckMouseInput())
	{
		//	�}�E�X�̈ړ��ʂ�
		float x = GetMouseMoveX();
		float y = GetMouseMoveY();

		if (CheckHitKey(KEY_INPUT_SPACE))
		{
			base.x = x * 0.1f;
			base.y = -y * 0.1f;
		}
		else
		{
			//	�J�����̌�����ύX���܂�
			camera_rot.x += y * 0.2f;
			camera_rot.y += x * 0.2f;
		}
	}

	//	�}�E�X�z�C�[���̉�]�ʂ��擾
	float speed = GetMouseWheelRotVolF();

	base.z = speed;

	MATRIX mat_x = MGetRotX(TO_RADIAN(camera_rot.x));
	MATRIX mat_y = MGetRotX(TO_RADIAN(camera_rot.y));

	MATRIX mat = MMult(mat_x, mat_y);
	Float3 change = GetFloat3VTransform(base, mat);

	camera_pos += change;

	Float3 start = camera_pos + Float3(0.0f, 100.0f, 0.0f);
	Float3 goal = camera_pos + Float3(0.0f, -100.0f, 0.0f);

	MV1_COLL_RESULT_POLY hit_info;
	hit_info = MV1CollCheck_Line(ground_model, -1, start.VGet(), goal.VGet());

	float ground_y = 1.0f;

	if (hit_info.HitFlag)
	{
		ground_y = hit_info.HitPosition.y + 1.0f;
	}

	if (camera_pos.y < ground_y)
	{
		camera_pos.y = ground_y;
	}

	if (PushHitKey(KEY_INPUT_B))
	{
		ball_pos = camera_pos;

		base.set(0.0f, 0.0f, BALL_SPEED);

		change = GetFloat3VTransform(base,mat);

		ball_mov = change;
	}


	ball_pos += ball_mov;
}
//---------------------------------------------------------------------------------
//	�`�揈��
//---------------------------------------------------------------------------------
void GameRender()
{
	//	�J�������W�ƌ�����n���ăJ�����ݒ�
	SetCameraPositionAndAngle(camera_pos.VGet(), TO_RADIAN(camera_rot.x), TO_RADIAN(camera_rot.y), TO_RADIAN(camera_rot.z));

	//	�n�ʂ̕`��
	MV1DrawModel(ground_model);

	DrawSphere3D(ball_mov.VGet(), 0.1f,100,GetColor(0,255,255), GetColor(255, 255, 255), true);

	DrawString(16, 16, "�}�E�X�h���b�O�F�J�����̌����ύX", GetColor(255, 255, 255));
	DrawString(16, 32, "�}�E�X�z�C�[���F�J�����̌����Ă�������Ɉړ�", GetColor(255, 255, 0));
	DrawString(16, 48, "�X�y�[�X�L�[�����Ȃ���}�E�X�h���b�O�F�J�����̌����Ă�������ɑ΂��ď㉺���E�ړ�", GetColor(255, 255, 0));
	DrawString(16, 64, "�J�����͒n�ʂɖ��܂�Ȃ��i�n�ʂ̍��� + 1.0 ��艺�ɂȂ�Ȃ��悤�ɂ��Ă��܂��j", GetColor(255, 255, 0));
}
//---------------------------------------------------------------------------------
//	�I������
//---------------------------------------------------------------------------------
void GameExit()
{
	MV1DeleteModel(ground_model);
}
