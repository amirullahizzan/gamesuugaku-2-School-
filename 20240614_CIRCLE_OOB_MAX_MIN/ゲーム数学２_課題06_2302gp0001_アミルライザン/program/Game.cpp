#include "Main.h"
#include "Game.h"
#include "Hit.h"
#include "Random.h"

#include "Camera.h"
#include "Ground.h"
#include "Player.h"
#include "Npc.h"

//	モデルデータ用の変数
int ground_model;
int player_model;
int npc_model;

//	クラスの宣言
Camera	camera;
Ground	ground;
Player	player;
Npc		npc;

//	黄色いエリア円の半径
#define AREA_RADIUS			7.0f
//	エリアの中心座標
Float3 area;

//	プレイヤーのどれだけ前に円を置くかの長さ
#define FRONT_RADIUS		2.0f
//	プレイヤーの前の円の半径
#define FRONT_LENGTH		5.0f

//	プレイヤーの前の座標
Float3 front;

//	プレイヤーの前の円の描画時間
int draw_frame;

//	ＮＰＣが円の中に入っているか
bool npc_in;

//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
void GameInit()
{
	//	モデルデータの読み込み
	ground_model = MV1LoadModel( "data/ground.mqoz" );
	player_model = MV1LoadModel( "data/player.mqoz" );
	npc_model = MV1LoadModel( "data/npc.mqoz" );

	//	クラスの初期化
	camera.Init();
	ground.Init( ground_model );
	player.Init( player_model );
	npc.Init( npc_model );

	front.clear();
	area.set( 0.0f, 0.0f, 0.0f );
}
//---------------------------------------------------------------------------------
//	更新処理
//---------------------------------------------------------------------------------
void GameUpdate()
{
	ground.Update();
	//	十字キーで回転と移動
	player.Update();
	//	向きを変えながら移動
	npc.Update();

	//	プレイヤーがエリアから出ない処理
	float distance = GetFloat3Distance(area, player.m_pos);

	if (distance > AREA_RADIUS)
	{
		Float3 dir = area - player.m_pos;

		float length = distance - AREA_RADIUS;

		Float3 back = dir;

		back.SetLength(length);

		player.m_pos += back;
	}

	//	スペースキーを押したら
	if( PushHitKey( KEY_INPUT_SPACE ) )
	{
		//	１秒間だけ表示したいので
		draw_frame = 60;
	}
	//	表示時間を減らしていく
	//	０より小さくならない（ max：引数で渡されたうちの大きい方を返す）
	draw_frame--;
	draw_frame = max( 0, draw_frame );

	//	プレイヤーの前の座標を求める
	front.x = player.m_pos.x + FRONT_LENGTH * cosf(TO_RADIAN(player.m_rot.y - 90.0f));
	front.z = player.m_pos.z - FRONT_LENGTH * sinf(TO_RADIAN(player.m_rot.y - 90.0f));

	//	まずは入っていない状態にして
	npc_in = false;

	
	//	円が描画されている時だけ判定する
	if( draw_frame > 0 )
	{
		if (GetFloat3Distance(front, npc.m_pos) < FRONT_RADIUS)
		{
			npc_in = true;
		}
		//	円とＮＰＣの距離が円の半径よりも小さかったら
	}

	camera.Update();
}
//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void GameRender()
{
	//	カメラの設定
	camera.Render();
	//	モデルの描画
	ground.Render();
	npc.Render();
	player.Render();

	//	エリアの円の描画
	DrawCircle3D_XZ( area, AREA_RADIUS, GetColor( 255, 255, 0 ) );

	//	描画時間があるときだけ
	if( draw_frame > 0 )
	{
		//	プレイヤーの前の円の描画
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
	//	プレイヤーとＮＰＣの距離を表現するためのバーの外枠
	DrawLineBox( 20, 150, 220, 170, GetColor( 255, 255, 255 ) );

	//	ＮＰＣが円の中に入っていたら
	if( npc_in ){
		DrawString( 16, 80, "→　ＮＰＣがプレイヤー前方の円の中に入っています", GetColor( 0, 255, 0 ) );
	}

	DrawString( 16, 16, "十字キー：プレイヤーの回転・移動", GetColor( 255, 255, 255 ) );
	DrawString( 16, 32, "→　プレイヤーは黄色い円から出ない", GetColor( 255, 255, 0 ) );

	DrawString( 16, 64, "スペース：青い円をプレイヤーの前に一定時間表示", GetColor( 255, 255, 0 ) );

	DrawString( 16, 128, "プレイヤーとＮＰＣの距離をバーで表示（最大１０）→ 半分以下の時はバーの色を変える", GetColor( 255, 255, 0 ) );
}
//---------------------------------------------------------------------------------
//	終了処理
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
