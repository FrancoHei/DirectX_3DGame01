//=============================================================================
//
// タイトル画面処理 [title.h]
// Author : 
//
//=============================================================================
#pragma once

#include "main.h"
#include "renderer.h"
#include "Texture.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************

class Button;
class Image;

enum TITLESTATE
{
	TITLESTATE_UNLOCK,
	TITLESTATE_LOCK
};
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
class Title
{
private:
	Button* gameDescriptionButton = nullptr;
	Button* gameStartButton       = nullptr;
	Image*  blue_SlimeImage       = nullptr;
	Image*  yellow_SlimeImage     = nullptr;
	Image*  green_SlimeImage      = nullptr;
	Image*  gameDescriptionLock   = nullptr; 
	int		textureNo			  = LoadTexture("data/TEXTURE/bg.jpg");
	int     choice				  = 1;
	TITLESTATE titleState[2];
	
public:
	  Title();
	 ~Title() {};
	 void Update();
	 void Draw();
	 void SetTitleState(int num, TITLESTATE state)
	 {
		 titleState[num] = state;
	 }
};


