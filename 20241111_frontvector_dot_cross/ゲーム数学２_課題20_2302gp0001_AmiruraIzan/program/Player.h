#pragma once

#include "Base.h"

//---------------------------------------------------------------------------------
//	プレイヤークラス
//---------------------------------------------------------------------------------
class Player : public Base
{
public:
	Float3 m_dash;
	void Init( int model );		//	初期化処理
	void Update();		//	更新処理
	void Render();		//	描画処理
	void Exit();		//	終了処理

private:
	float perspective = 45.0f;
};
