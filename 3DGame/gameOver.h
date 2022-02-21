#ifndef GAMEOVER_H_
#define GAMEOVER_H_

#include "Texture.h"
#include "sprite.h"
#include "input.h"
#include "fade.h"
#include "scene.h"

class GameOver
{
private:
	int		textureNo   = LoadTexture("data/TEXTURE/bg.jpg");
	int		textureNo_2 = LoadTexture("data/TEXTURE/gameOver.png");
	int		loseSE		= LoadSound("data/SE/lose.wav");
	int		timer       = 0;
public:
	GameOver() 
	{
		SetVolume(loseSE, 1.0f);
		PlaySound(loseSE, 0);
	}

	~GameOver() {}

	void Update()
	{
		if(GetFadeState() == FADE_NONE)
		{
			timer++;
		}

		if(timer >= 180)
		{
			SceneTransition(SCENE_TITLE);
		}else
		if (GetKeyboardTrigger(DIK_RETURN) && GetFadeState() == FADE_NONE)
		{
			SceneTransition(SCENE_TITLE);
		}
	}

	void Draw()
	{
		DrawSpriteLeftTop(textureNo, 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f, 1.0f);
		DrawSprite(textureNo_2, SCREEN_WIDTH/2.0f, SCREEN_HEIGHT/2.0f, 400.0f, 100.0f, 0.0f, 0.0f, 1.0f, 1.0f);
	}
};

#endif // !GAMEOVER_H_