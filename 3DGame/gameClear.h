#ifndef GAMECLEAR_H_
#define GAMECLEAR_H_

#include "Texture.h"
#include "sprite.h"
#include "input.h"
#include "fade.h"
#include "scene.h"
#include "sound.h"
#include "title.h"

class GameClear
{
private:
	int		textureNo   = LoadTexture("data/TEXTURE/bg.jpg");
	int		textureNo_2 = LoadTexture("data/TEXTURE/stageClear.png");
	int		winSE		= LoadSound("data/SE/win.wav");
	int		timer       = 0;
public:
	 GameClear()
	 {
		 SetVolume(winSE, 1.0f);
		 PlaySound(winSE, 0);
	 }

	~GameClear(){}

	void Update()
	{
		if (GetFadeState() == FADE_NONE)
		{
			timer++;
		}

		if (timer >= 180)
		{
			SceneTransition(SCENE_TITLE);
		}
		else
		if (GetKeyboardTrigger(DIK_RETURN) && GetFadeState() == FADE_NONE)
		{
			if (GetStage() == STAGE01)
			{
				GetTitle()->SetTitleState(1, TITLESTATE_UNLOCK);
			}
			SceneTransition(SCENE_TITLE);
		}
	}

	void Draw()
	{
		DrawSpriteLeftTop(textureNo, 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f, 1.0f);
		DrawSprite(textureNo_2, SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, 400.0f, 100.0f, 0.0f, 0.0f, 1.0f, 1.0f);
	}
};

#endif // !GAMECLEAR_H_

