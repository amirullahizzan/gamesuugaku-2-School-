#pragma once

#include "Base.h"

//---------------------------------------------------------------------------------
//	‚m‚o‚bƒNƒ‰ƒX
//---------------------------------------------------------------------------------
class Npc : public Base
{
public:

	void Init( int model );		//	‰Šú‰»ˆ—
	void Update(Float3& player_pos, Float3& camera_rot);
	void Render();		//	•`‰æˆ—
	void Exit();		//	I—¹ˆ—

private:
	int m_frame = 0;
};
