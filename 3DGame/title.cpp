//=============================================================================
//
// タイトル画面処理 [title.cpp]
// Author : 
//
//=============================================================================
#include "title.h"
#include "input.h"
#include "texture.h"
#include "sprite.h"
#include "fade.h"
#include "sound.h"
#include "button.h"
#include "gameStart_Button.h"
#include "gameDescription_Button.h"
#include "image.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define GAMESTARTBUTTONPOSX				SCREEN_WIDTH / 2.0f
#define GAMESTARTBUTTONPOSY				800.0f
#define GAMEDESCRIPTIONBUTTONPOSX		SCREEN_WIDTH / 2.0f
#define GAMEDESCRIPTIONBUTTONPOSY		700.0f
#define BLUESLIMEIMAGEPOSX				SCREEN_WIDTH / 2.0f - 150.0f
#define BLUESLIMEIMAGEPOSY				200.0f
#define YELLOWSLIMEIMAGEPOSX			SCREEN_WIDTH / 2.0f - 450.0f
#define YELLOWSLIMEIMAGEPOSY			200.0f
#define GREENSLIMEIMAGEPOSX				SCREEN_WIDTH / 2.0f + 150.0f
#define GREENSLIMEIMAGEPOSY				200.0f
#define SLIMEIMAGESIZEX					300.0f
#define SLIMEIMAGESIZEY					300.0f
#define GAMEDESCRIPTIONBUTTONLOCKPOSX	SCREEN_WIDTH / 2.0f - 350.0f
#define GAMEDESCRIPTIONBUTTONLOCKPOSY	750.0f
#define GAMEDESCRIPTIONBUTTONLOCKSIZEX	100.0f
#define GAMEDESCRIPTIONBUTTONLOCKSIZEY	100.0f
//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************


//=============================================================================
// 初期化処理
//=============================================================================
Title::Title()
{
	gameDescriptionButton = new GameDescription_Button({ GAMEDESCRIPTIONBUTTONPOSX, GAMEDESCRIPTIONBUTTONPOSY });
	gameStartButton       = new GameStart_Button      ({ GAMESTARTBUTTONPOSX, GAMESTARTBUTTONPOSY });
	blue_SlimeImage		  = new Image({ BLUESLIMEIMAGEPOSX, BLUESLIMEIMAGEPOSY }, { SLIMEIMAGESIZEX, SLIMEIMAGESIZEY }, LoadTexture("data/TEXTURE/blue_slime.png"));
	green_SlimeImage	  = new Image({ GREENSLIMEIMAGEPOSX, GREENSLIMEIMAGEPOSY }, { SLIMEIMAGESIZEX, SLIMEIMAGESIZEY }, LoadTexture("data/TEXTURE/green_slime.png"));
	yellow_SlimeImage	  = new Image({ YELLOWSLIMEIMAGEPOSX, YELLOWSLIMEIMAGEPOSY }, { SLIMEIMAGESIZEX, SLIMEIMAGESIZEY }, LoadTexture("data/TEXTURE/yellow_slime.png"));
	gameDescriptionLock	  = new Image({ GAMEDESCRIPTIONBUTTONLOCKPOSX, GAMEDESCRIPTIONBUTTONLOCKPOSY }, { GAMEDESCRIPTIONBUTTONLOCKSIZEX, GAMEDESCRIPTIONBUTTONLOCKSIZEY }, LoadTexture("data/TEXTURE/lock.png"));

	titleState[0]		  = TITLESTATE_UNLOCK;
	titleState[1]		  = TITLESTATE_UNLOCK;
}

void Title::Update()
{
	if(choice == 1 && titleState[0] == TITLESTATE_UNLOCK)
	{
		gameDescriptionButton->Update(true);
		gameStartButton->Update(false);
	}else
	if(choice == 2 && titleState[1] == TITLESTATE_UNLOCK)
	{
		gameDescriptionButton->Update(false);
		gameStartButton->Update(true);
	}

	if (GetKeyboardTrigger(DIK_DOWN) && GetFadeState() == FADE_NONE && titleState[0] == TITLESTATE_UNLOCK)
	{
		if(choice == 1)
		{
			choice = 2;
		}

	}else
	if (GetKeyboardTrigger(DIK_UP) && GetFadeState() == FADE_NONE && titleState[1] == TITLESTATE_UNLOCK)
	{
		if (choice == 2)
		{
			choice = 1;
		}
	}

	if (GetKeyboardTrigger(DIK_RETURN) && GetFadeState() == FADE_NONE)
	{
		if (choice == 1 && titleState[0] == TITLESTATE_UNLOCK)
		{
			gameDescriptionButton->ButtonAction();
		}else
		if (choice == 2 && titleState[1] == TITLESTATE_UNLOCK)
		{
			gameStartButton->ButtonAction();
		}
	}
}

void Title::Draw()
{
	// １枚のポリゴンの頂点とテクスチャ座標を設定
	DrawSpriteLeftTop(textureNo, 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f, 1.0f);
	if(gameDescriptionButton)
		gameDescriptionButton->Draw();
	if (gameStartButton)
		gameStartButton->Draw();
	if (blue_SlimeImage)
		blue_SlimeImage->Draw();
	if (yellow_SlimeImage)
		yellow_SlimeImage->Draw();
	if (green_SlimeImage)
		green_SlimeImage->Draw();
	if (gameDescriptionLock && titleState[1] == TITLESTATE_LOCK)
		gameDescriptionLock->Draw();
}
