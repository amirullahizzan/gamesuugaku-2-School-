#include "Main.h"
#include "Game.h"
#include "Random.h"

//---------------------------------------------------------------------------------
//	０〜 i_max までのランダムな値を返す関数（ int 型）
//---------------------------------------------------------------------------------
int GetRandomI( int i_max )
{
	return rand() % ( i_max + 1 );
}
//---------------------------------------------------------------------------------
//	i_from 〜 i_to までのランダムな値を返す関数（ int 型）
//---------------------------------------------------------------------------------
int GetRandomI( int i_from, int i_to )
{
	int value = i_to - i_from;
	int random = GetRandomI( value );
	return i_from + random;
}
//---------------------------------------------------------------------------------
//	0.0 〜 1.0 までのランダムな値を返す関数（ float 型）
//---------------------------------------------------------------------------------
float GetRandomF()
{
	float random = (float)rand();
	return random / RAND_MAX;
}
//---------------------------------------------------------------------------------
//	0.0 〜 f_max までのランダムな値を返す関数（ float 型）
//---------------------------------------------------------------------------------
float GetRandomF( float f_max )
{
	float random = GetRandomF();
	return random * f_max;
}
//---------------------------------------------------------------------------------
//	f_from 〜 f_to までのランダムな値を返す関数（ float 型）
//---------------------------------------------------------------------------------
float GetRandomF( float f_from, float f_to )
{
	float value = f_to - f_from;
	float random = GetRandomF( value );
	return f_from + random;
}
