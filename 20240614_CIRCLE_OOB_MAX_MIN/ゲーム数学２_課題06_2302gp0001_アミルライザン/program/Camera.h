#pragma once

#include "Float3.h"

//---------------------------------------------------------------------------------
//	カメラクラス
//---------------------------------------------------------------------------------
class Camera
{
public:
	//	カメラをどこに置くのかの座標
	Float3		m_pos;
	//	そのカメラがどこを見るのか
	Float3		m_look;

	void Init();		//	初期化処理
	void Update();		//	更新処理
	void Render();		//	描画処理
	void Exit();		//	終了処理
};
