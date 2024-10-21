#include "Main.h"
#include "Game.h"
#include "Random.h"
#include "Float2.h"
#include "Float3.h"
#include "Hit.h"

//	モデルデータ用の変数
int ground_model;
int npc_model;
int block_model;	//	ブロックモデル
int panel_model;	//	ブロックを置いていないところ用のパネルモデル

//	カメラ座標と向き
Float3 camera_pos;
Float3 camera_rot;

//	ＮＰＣ移動スピード
#define NPC_SPEED	0.03f

//	ブロックの大きさ
#define PANEL_SIZE	1.0f
//	ブロックの半分の大きさ（当たり判定でこの値を使います）
#define HALF_SIZE	(PANEL_SIZE*0.5f)

//	ＮＰＣ座標と向き
Float3 npc_pos;
Float3 npc_rot;
//	上の半分の大きさを入れる用の変数
Float3 half_size;

//	ＮＰＣとマウスが重なっているかどうか
bool mouse_hit;

//	マップのサイズ
#define MAP_W		20	//	横
#define	MAP_H		10	//	縦
//	マップデータ（クリックした地面に合わせてこの値を１にしたい）
int MapData[MAP_H][MAP_W];
//	今回はブロック座標ではなくてこの配列を見てブロックを置きます

int frame;
Float3 camera_offset;

//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
void GameInit()
{
	//	カメラ座標の初期設定
	camera_pos.set(10.0f, 15.0f, -5.5f);
	//	カメラの向き
	camera_rot.set(50.0f, 0.0f, 0.0f);

	//	モデルデータの読み込み
	ground_model = MV1LoadModel("data/ground.mqoz");
	npc_model = MV1LoadModel("data/npc.mqoz");
	block_model = MV1LoadModel("data/block.mqoz");
	panel_model = MV1LoadModel("data/panel.mqoz");

	//	マウスの先の線と地面モデルで当たり判定をしたい　→　なので地面モデルの当たり情報を作成します
	MV1SetupCollInfo(ground_model);
	//	マウスの先の線とＮＰＣモデルで当たり判定をしたい　→　なのでＮＰＣモデルの当たり情報を作成します
	MV1SetupCollInfo(npc_model);

	npc_pos.set(10.0f, 0.0f, 15.0f);
	npc_rot.set(0.0f, 180.0f, 0.0f);
	//	当たり判定用に大きさ用の変数を設定
	half_size.set(HALF_SIZE, HALF_SIZE, HALF_SIZE);
	//	重なっていない状態から開始
	mouse_hit = false;

	//	マップデータの初期化（全部０で埋めた状態で開始）
	for (int h = 0; h < MAP_H; h++) {
		for (int w = 0; w < MAP_W; w++) {
			MapData[h][w] = 0;
		}
	}
}
//---------------------------------------------------------------------------------
//	更新処理
//---------------------------------------------------------------------------------
void GameUpdate()
{
	//	モデルと線で当たり判定をするために当たり情報の更新もします
	MV1RefreshCollInfo(ground_model);
	MV1RefreshCollInfo(npc_model);

	//	現状はサンプルのまま画面手前に移動しています（課題２：ＮＰＣの向きに合わせて移動）
	//npc_pos.z -= NPC_SPEED;
	Float3 base(0.0f, 0.0f, NPC_SPEED);
	MATRIX mat = MGetRotY(TO_RADIAN(npc_rot.y));
	Float3 mov = GetFloat3VTransform(base, mat);
	npc_pos += mov;

	//	マウス座標の取得
	Float2 mouse;
	mouse.x = (float)GetMouseX();
	mouse.y = (float)GetMouseY();

	//	マウス座標（画面座標）を３Ｄ空間座標に変換
	//	カメラで映されている中の一番手前の３Ｄ空間座標
	VECTOR wpos_start = ConvScreenPosToWorldPos(VGet(mouse.x, mouse.y, 0.0f));
	//	一番奥の座標
	VECTOR wpos_goal = ConvScreenPosToWorldPos(VGet(mouse.x, mouse.y, 1.0f));

	//	上で求めた２点を線としてＮＰＣモデルと当たり判定
	MV1_COLL_RESULT_POLY hit_info = MV1CollCheck_Line(npc_model, -1, wpos_start, wpos_goal);
	//	当たっていたら
	if (hit_info.HitFlag) {
		//	重なっているフラグを立てます（これを見て文字列描画します）
		mouse_hit = true;
	}
	else {
		//	じゃなかったらフラグを落とす
		mouse_hit = false;
	}

	//	マウスをクリックしたら、その先の地面にブロックを置きたい
	if (PushMouseInput()) {
		if (mouse_hit) {
			//	とりあえずＮＰＣ座標をランダムにする実装はしています
			npc_pos.x = GetRandomF(0.0f, 20.0f);
			npc_pos.z = 15.0f;

			//	課題２：ＮＰＣの向きの設定
			Float3 goal;
			goal.x = GetRandomF(0.0f, 20.0f);
			goal.y = 0.0f;
			goal.z = GetRandomF(0.0f, 10.0f);

			float x = goal.x - npc_pos.x;
			float z = goal.z - npc_pos.z;

			npc_rot.y = TO_DEGREE(atan2f(x, z));
		}
		else {
			//	マウス線と地面モデルで当たり判定をして当たり情報を取得
			hit_info = MV1CollCheck_Line(ground_model, -1, wpos_start, wpos_goal);
			//	当たっていたら
			if (hit_info.HitFlag) {
				//	当たっている座標を求める
				Float3 pos(hit_info.HitPosition);

				//	今回のブロックは黄色い四角の範囲の中にしか置けない
				//	Ｘ座標は 0.0f ～ 20.0f の間
				if (pos.x >= 0.0f && pos.x <= 20.0f) {
					//	Ｚ座標は 0.0f ～ 10.0f の間
					if (pos.z >= 0.0f && pos.z <= 10.0f)
					{
						int w = (int)(pos.x / PANEL_SIZE);
						int h = (int)(pos.z / PANEL_SIZE);
						//	課題１：マウスクリックでブロック配置（地面のマス目に合わせて：MapData[][] を使って）
						MapData[h][w] = 1;
					}
				}
			}
		}
	}

	//	マップ上のブロックとＮＰＣで当たり判定（課題３：ＮＰＣと当たったブロックは消える：MapData[][] を使って）
	for (int h = 0; h < MAP_H; h++) {

		for (int w = 0; w < MAP_W; w++) {
			if (MapData[h][w] == 1)
			{
				Float3 pos;
				pos.x = w * PANEL_SIZE + HALF_SIZE;
				pos.y = 0.0f;
				pos.z = h * PANEL_SIZE + HALF_SIZE;
				if (CheckBoxHit3D(npc_pos, half_size, pos, half_size))
				{
					MapData[h][w] == 0;

					frame = 10;
				}
			}
		}
	}
	if (frame > 0)
	{
		frame--;
		camera_offset.set(GetRandomF(-0.1f,0.1f), GetRandomF(-0.1f, 0.1f), GetRandomF(-0.1f, 0.1f));
	}
	else
	{
		camera_offset.clear();
	}
}
//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void GameRender()
{
	Float3 pos = camera_pos + camera_offset;

	//	座標と向きを渡してカメラの設定
	SetCameraPositionAndAngle(pos.VGet(), TO_RADIAN(camera_rot.x), TO_RADIAN(camera_rot.y), TO_RADIAN(camera_rot.z));

	//	地面モデルの描画
	MV1DrawModel(ground_model);

	//	マップの描画
	for (int h = 0; h < MAP_H; h++) {
		for (int w = 0; w < MAP_W; w++) {
			//	描画するための座標を設定（MapData[][] を使って BLOCK_SIZE ずらして並べます）
			Float3 pos;
			pos.x = w * PANEL_SIZE + HALF_SIZE;
			pos.y = 0.0f;
			pos.z = h * PANEL_SIZE + HALF_SIZE;
			//	下のパネル部分はすべて描画しています
			MV1SetPosition(panel_model, pos.VGet());
			MV1DrawModel(panel_model);


			//	課題１：マウスクリックでブロック配置（地面のマス目に合わせて：MapData[][] を使って）
			if (MapData[h][w] == 1)
			{
				MV1SetPosition(block_model, pos.VGet());
				MV1DrawModel(block_model);
			}
		}
	}

	//	ＮＰＣのモデルの描画
	MV1SetPosition(npc_model, VGet(npc_pos.x, npc_pos.y, npc_pos.z));
	MV1SetRotationXYZ(npc_model, VGet(TO_RADIAN(npc_rot.x), TO_RADIAN(npc_rot.y), TO_RADIAN(npc_rot.z)));
	MV1DrawModel(npc_model);

	//	Ｘ座標 0.0f ～ 20.0f　Ｚ座標 0.0f ～ 10.0f の四角です
	DrawBox3D_XZ(Float3(10.0f, 0.0f, 5.0f), 10.0f, 5.0f, GetColor(255, 255, 0), FALSE);

	if (mouse_hit) {
		//	マウスとＮＰＣが重なっている時文字列の描画
		DrawString(16, 128, "マウスとＮＰＣが重なっています", GetColor(255, 255, 0));
	}

	DrawString(16, 16, "マウスクリック：マウスの先の地面にブロックのセット", GetColor(255, 255, 255));
	DrawString(16, 32, "（ＮＰＣとマウスが重なっていないとき・黄色い枠の中）", GetColor(255, 255, 255));
	DrawString(16, 48, "→　地面のマス目に合わせてブロックのセット", GetColor(255, 255, 0));
	DrawString(16, 64, "ＮＰＣクリック：ＮＰＣ座標ランダムに再設定", GetColor(255, 255, 255));
	DrawString(16, 80, "→　黄色い枠内のランダムな座標の方向に移動する（なので向きも変える）", GetColor(255, 255, 0));
	DrawString(16, 96, "→　ＮＰＣと当たったブロックは消える", GetColor(255, 255, 0));
}
//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void GameExit()
{
	MV1DeleteModel(ground_model);
	MV1DeleteModel(npc_model);
	MV1DeleteModel(block_model);
	MV1DeleteModel(panel_model);
}
