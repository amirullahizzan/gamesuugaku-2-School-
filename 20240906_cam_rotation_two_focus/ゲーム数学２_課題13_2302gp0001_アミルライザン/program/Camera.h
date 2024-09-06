#pragma once

#include "Float3.h"

enum {
	TYPE_NORMAL,	//	サンプルで実装したカメラ
	TYPE_FRONT,		//	プレイヤーが手前・ＮＰＣが奥になるようなカメラ
	TYPE_LEFT,		//	プレイヤーが左・ＮＰＣが右になるようなカメラ
};

//---------------------------------------------------------------------------------
//	カメラクラス
//---------------------------------------------------------------------------------
class Camera
{
public:
	//	カメラ座標
	Float3		m_pos;
	//	見る座標
	Float3		m_look;

	//	カメラタイプ
	int			m_type;

	void Init();		//	初期化処理

	//	プレイヤーとＮＰＣの座標をもらえるように引数を追加
	void Update( Float3 &player_pos, Float3 &npc_pos );		//	更新処理

	void Render();		//	描画処理
	void Exit();		//	終了処理
};
