#pragma once

#include "Base.h"

//---------------------------------------------------------------------------------
//	ＮＰＣクラス
//---------------------------------------------------------------------------------
class Npc : public Base
{
public:

	void Init( int image );		//	初期化処理
	void Update( Float2 &target_pos );	//	更新処理
	void Render();		//	描画処理
	void Exit();		//	終了処理
};
