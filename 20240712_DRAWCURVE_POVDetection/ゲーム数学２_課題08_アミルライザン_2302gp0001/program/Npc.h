#pragma once

#include "Base.h"

//---------------------------------------------------------------------------------
//	�m�o�b�N���X
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
	//	����������
	void Update( Float2 &target_pos );	//	�X�V����
	void Render();		//	�`�揈��
	void Exit();		//	�I������
};
