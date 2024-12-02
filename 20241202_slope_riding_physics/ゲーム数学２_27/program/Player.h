#pragma once

#include "Base.h"

//---------------------------------------------------------------------------------
//	プレイヤークラス
//---------------------------------------------------------------------------------
class Player : public Base
{
public:

	//	ジャンプ移動量
	Float3		m_jump_mov;

	void Init( int model );		//	初期化処理
	void Update( int ground_model );		//	更新処理
	void Render();		//	描画処理
	void Exit();		//	終了処理
};
