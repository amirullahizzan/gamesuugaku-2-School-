#pragma once

#include "Float3.h"

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

	void Init();		//	初期化処理
	void Update( Float3 &player_pos, Float3 &npc_pos );		//	更新処理
	void Render();		//	描画処理
	void Exit();		//	終了処理
};
