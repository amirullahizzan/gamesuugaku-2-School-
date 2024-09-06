#include "Main.h"
#include "Game.h"

char KeyBuffer[256];
int KeyFrame[256];
int MouseLeftFrame;
int MouseRightFrame;

int NowMouseX;
int NowMouseY;
int BeforeMouseX;
int BeforeMouseY;

//---------------------------------------------------------------------------------
//	WinMain
//---------------------------------------------------------------------------------
int WINAPI WinMain( _In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow )
{
	int Time;

	SetOutApplicationLogValidFlag( FALSE );
	ChangeWindowMode( TRUE );
	SetMainWindowText( "ƒTƒ“ƒvƒ‹" );
	SetBackgroundColor( 100, 100, 100 );

	SetDoubleStartValidFlag( TRUE );
	SetAlwaysRunFlag( TRUE );

	SetGraphMode( SCREEN_W, SCREEN_H, 32 );

	if( DxLib_Init() == -1 )	return -1;

	SetDrawScreen( DX_SCREEN_BACK );
	SetTransColor( 255, 0, 255 );
	srand( GetNowCount() % RAND_MAX );

	for( int i = 0; i < 256; i++ ){
		KeyFrame[i] = 0;
	}
	MouseLeftFrame = 0;
	MouseRightFrame = 0;

	//	ƒJƒƒ‰‚Ì‰f‚·‹——£i 0.1f ` 3000.0f j
	SetCameraNearFar( 0.1f, 3000.0f );
	//	ƒJƒƒ‰‚Ì‰æŠpi‚S‚T“xj
	SetupCamera_Perspective( TO_RADIAN( 45.0f ) );

	SetUseZBuffer3D( TRUE );
	SetWriteZBuffer3D( TRUE );
	ChangeLightTypeDir( VGet( 0.8f, -1.2f, 1.0f ) );

	GameInit();

	while( TRUE )
	{
		Time = GetNowCount();
		ClearDrawScreen();

		GetHitKeyStateAll( KeyBuffer );

		for( int i = 0; i < 256; i++ ){
			if( KeyBuffer[i] )	KeyFrame[i]++;
			else				KeyFrame[i] = 0;
		}

		if( CheckMouseInput( MOUSE_INPUT_LEFT ) )	MouseLeftFrame++;
		else										MouseLeftFrame = 0;

		if( CheckMouseInput( MOUSE_INPUT_RIGHT ) )	MouseRightFrame++;
		else										MouseRightFrame = 0;

		NowMouseX = GetMouseX();
		NowMouseY = GetMouseY();

		GameUpdate();
		GameRender();

		BeforeMouseX = NowMouseX;
		BeforeMouseY = NowMouseY;

		ScreenFlip();
		while( GetNowCount() - Time < 17 ){}
		if( ProcessMessage() )	break;
		if( CheckHitKey( KEY_INPUT_ESCAPE ) )	break;
	}

	GameExit();

	DxLib_End();
	return 0;
}

//---------------------------------------------------------------------------------
//	ƒL[‚ª‰Ÿ‚³‚ê‚½uŠÔ‚ðŽæ“¾‚·‚é
//---------------------------------------------------------------------------------
bool PushHitKey( int key )
{
	if( KeyFrame[key] == 1 ){
		return true;
	}
	return false;
}
//---------------------------------------------------------------------------------
//	ƒ}ƒEƒX‚ª‰Ÿ‚³‚ê‚Ä‚¢‚é‚©‚ðŽæ“¾‚·‚é
//---------------------------------------------------------------------------------
bool CheckMouseInput( int button )
{
	if( GetMouseInput() & button ){
		return true;
	}
	return false;
}
//---------------------------------------------------------------------------------
//	ƒ}ƒEƒX‚ª‰Ÿ‚³‚ê‚½uŠÔ‚ðŽæ“¾‚·‚é
//---------------------------------------------------------------------------------
bool PushMouseInput( int button )
{
	if( button & MOUSE_INPUT_LEFT ){
		if( MouseLeftFrame == 1 ){
			return true;
		}
	}
	if( button & MOUSE_INPUT_RIGHT ){
		if( MouseRightFrame == 1 ){
			return true;
		}
	}
	return false;
}
//---------------------------------------------------------------------------------
//	ƒ}ƒEƒX‚ÌÀ•W‚ðŽæ“¾‚·‚é
//---------------------------------------------------------------------------------
int GetMouseX()
{
	int mouse_x;
	int mouse_y;
	GetMousePoint( &mouse_x, &mouse_y );
	return mouse_x;
}
int GetMouseY()
{
	int mouse_x;
	int mouse_y;
	GetMousePoint( &mouse_x, &mouse_y );
	return mouse_y;
}
//---------------------------------------------------------------------------------
//	ƒ}ƒEƒX‚ÌˆÚ“®—Ê‚ðŽæ“¾‚·‚é
//---------------------------------------------------------------------------------
int GetMouseMoveX()
{
	return NowMouseX - BeforeMouseX;
}
int GetMouseMoveY()
{
	return NowMouseY - BeforeMouseY;
}
//---------------------------------------------------------------------------------
//	“x‚ðƒ‰ƒWƒAƒ“‚É•ÏŠ·‚·‚éŠÖ”
//---------------------------------------------------------------------------------
float TO_RADIAN( float degree )
{
	return degree * 3.14159265f / 180.0f;
}
//---------------------------------------------------------------------------------
//	ƒ‰ƒWƒAƒ“‚ð“x‚É•ÏŠ·‚·‚éŠÖ”
//---------------------------------------------------------------------------------
float TO_DEGREE( float radian )
{
	return radian * 180.0f / 3.14159265f;
}
//---------------------------------------------------------------------------------
//	‚w‚y•ûŒü‚É‰~‚ð•`‰æ‚·‚é
//---------------------------------------------------------------------------------
void DrawCircle3D_XZ( Float3 center, float radius, int color, bool fill )
{
	VECTOR pos1;
	VECTOR pos2;
	for( int i = 0; i < 36; i++ ){
		pos1.x = center.x + radius * sinf( TO_RADIAN( i * 10.0f ) );
		pos1.y = center.y;
		pos1.z = center.z + radius * cosf( TO_RADIAN( i * 10.0f ) );

		pos2.x = center.x + radius * sinf( TO_RADIAN( ( i + 1 ) * 10.0f ) );
		pos2.y = center.y;
		pos2.z = center.z + radius * cosf( TO_RADIAN( ( i + 1 ) * 10.0f ) );

		if( fill ){
			DrawTriangle3D( center.VGet() ,pos1, pos2, color, TRUE );
		}else{
			DrawLine3D( pos1, pos2, color );
		}
	}
}
//---------------------------------------------------------------------------------
//	‚w‚y•ûŒü‚ÉŽlŠp‚ð•`‰æ‚·‚é
//---------------------------------------------------------------------------------
void DrawBox3D_XZ( Float3 center, float half_w, float half_h, int color, bool fill )
{
	VECTOR pos1, pos2, pos3, pos4;

	pos1.x = center.x + half_w;
	pos1.y = center.y;
	pos1.z = center.z + half_h;

	pos2.x = center.x + half_w;
	pos2.y = center.y;
	pos2.z = center.z - half_h;

	pos3.x = center.x - half_w;
	pos3.y = center.y;
	pos3.z = center.z - half_h;

	pos4.x = center.x - half_w;
	pos4.y = center.y;
	pos4.z = center.z + half_h;

	if( fill ){
		DrawTriangle3D( pos1, pos2, pos3, color, TRUE );
		DrawTriangle3D( pos1, pos3, pos4, color, TRUE );
	}else{
		DrawLine3D( pos1, pos2, color );
		DrawLine3D( pos2, pos3, color );
		DrawLine3D( pos3, pos4, color );
		DrawLine3D( pos4, pos1, color );
	}

}
