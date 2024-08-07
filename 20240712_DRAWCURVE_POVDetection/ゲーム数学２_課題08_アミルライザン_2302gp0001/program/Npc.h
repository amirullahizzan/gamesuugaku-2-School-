#pragma once

#include "Base.h"

//---------------------------------------------------------------------------------
//	ＮＰＣクラス
//---------------------------------------------------------------------------------
class Npc : public Base
{
private:
	enum EPos
	{
		Left, Top, Right, Bottom
	};

public:

	void Init( int image );
	void RandomizePos(EPos _pos);
	void RandomizeRot(EPos _pos);
	void OOBHandler();
	//	初期化処理
	void Update( Float2 &target_pos );	//	更新処理
	void Render();		//	描画処理
	void Exit();		//	終了処理
};
