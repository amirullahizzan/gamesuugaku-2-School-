#pragma once

#include "Base.h"

//---------------------------------------------------------------------------------
//	‚m‚o‚bƒNƒ‰ƒX
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
	//	‰Šú‰»ˆ—
	void Update( Float2 &target_pos );	//	XVˆ—
	void Render();		//	•`‰æˆ—
	void Exit();		//	I—¹ˆ—
};
