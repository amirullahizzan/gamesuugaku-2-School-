#pragma once

#include "Base.h"

//---------------------------------------------------------------------------------
//	プレイヤークラス
//---------------------------------------------------------------------------------
class Player : public Base
{
public:

	void Init( int model );		//	初期化処理
	void Update();		//	更新処理
	void Render();		//	描画処理
	void Exit();		//	終了処理

private: 
	int m_frame;
	Float3 m_mov;
};
