#pragma once

#include "Base.h"

//---------------------------------------------------------------------------------
//	‚m‚o‚bƒNƒ‰ƒX
//---------------------------------------------------------------------------------
class Npc : public Base
{
public:

	void Init( int image );		//	‰Šú‰»ˆ—
	void Update();	//	XVˆ—
	void Render();		//	•`‰æˆ—
	void Exit();		//	I—¹ˆ—
};
