#ifndef GAMESTART_BUTTON
#define GAMESTART_BUTTON

#include "button.h"
#include "Texture.h"

class GameStart_Button : public Button
{
private:


public:
	GameStart_Button(D3DXVECTOR2 pos) : Button(GAMESTARTBUTTON, LoadTexture("data/TEXTURE/gameStartButton.png"), LoadTexture("data/TEXTURE/gameStartButton_red.png"), pos){}

	void ButtonAction() override
	{
		SetStage(STAGE03);
		SceneTransition(SCENE_CHARACTERSELECTMENU);
	}
};

#endif//GAMESTART_BUTTON
