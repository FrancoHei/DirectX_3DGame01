//=============================================================================
//
// �^�C�g����ʏ��� [title.h]
// Author : 
//
//=============================================================================
#pragma once

#include "main.h"
#include "renderer.h"
#include "Texture.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************

class Button;
class Image;

enum TITLESTATE
{
	TITLESTATE_UNLOCK,
	TITLESTATE_LOCK
};
//*****************************************************************************
// �v���g�^�C�v�錾
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


