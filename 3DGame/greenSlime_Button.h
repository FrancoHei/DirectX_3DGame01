#ifndef GREENSLIME_BUTTON
#define GREENSLIME_BUTTON

#include "button.h"
#include "Texture.h"

class GreenSlime_Button : public Button
{
private:


public:
	GreenSlime_Button(D3DXVECTOR2 pos) : Button(GAMESTARTBUTTON, LoadTexture("data/TEXTURE/green_slimeButton.png"), LoadTexture("data/TEXTURE/green_slimeButton_red.png"), pos) {}

	void ButtonAction() override
	{

	}
};

#endif//GREENSLIME_BUTTON