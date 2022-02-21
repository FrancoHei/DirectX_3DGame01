#ifndef YELLOWSLIME_BUTTON
#define YELLOWSLIME_BUTTON

#include "button.h"
#include "Texture.h"

class YellowSlime_Button : public Button
{
private:


public:
	YellowSlime_Button(D3DXVECTOR2 pos) : Button(GAMESTARTBUTTON, LoadTexture("data/TEXTURE/yellow_slimeButton.png"), LoadTexture("data/TEXTURE/yellow_slimeButton_red.png"), pos) {}

	void ButtonAction() override
	{

	}
};

#endif//YELLOWSLIME_BUTTON