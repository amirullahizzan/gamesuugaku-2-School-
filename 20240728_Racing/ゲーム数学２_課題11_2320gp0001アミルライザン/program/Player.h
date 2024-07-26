#pragma once

#include "Base.h"

//---------------------------------------------------------------------------------
//	プレイヤークラス
//---------------------------------------------------------------------------------
class Player : public Base
{
public:

	//	移動ベクトル（この方向に進む）
	Float3	m_mov;

	void Init( int model );		//	初期化処理
	void Update(float near_length);		//	更新処理
	void Render();		//	描画処理
	void Exit();		//	終了処理
};
