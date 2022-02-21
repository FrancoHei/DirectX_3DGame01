#ifndef GAMEDESCRIPTION_BUTTON
#define GAMEDESCRIPTION_BUTTON

#include "button.h"
#include "Texture.h"

class GameDescription_Button : public Button
{
private:


public:
	GameDescription_Button(D3DXVECTOR2 pos) 
		: Button(GAMEDESCRIPTIONBUTTON, LoadTexture("data/TEXTURE/gameDescriptButton.png"), LoadTexture("data/TEXTURE/gameDescriptButton_red.png"), pos) {}

	void ButtonAction() override
	{
		SetStage(STAGE01);
		SceneTransition(SCENE_GAME);
	}
};

#endif//GAMEDESCRIPTION_BUTTON