#pragma once

#include "Float3.h"

//---------------------------------------------------------------------------------
//	カメラクラス
//---------------------------------------------------------------------------------
class Camera
{
public:
	Float3		m_pos;
	Float3		m_look;

	void Init();		//	初期化処理
	void Update(Float3 &_playerPos, Float3 &_rot);		//	更新処理
	void Render();		//	描画処理
	void Exit();		//	終了処理
};
