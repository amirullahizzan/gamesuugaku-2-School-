#pragma once

#include "Base.h"

//---------------------------------------------------------------------------------
//	ＮＰＣクラス
//---------------------------------------------------------------------------------
class Npc : public Base
{
public:

	void Init( int model );		//	初期化処理
	void Update(Float3& player_pos, Float3& camera_rot);
	void Render();		//	描画処理
	void Exit();		//	終了処理

private:
	int m_frame = 0;
};
