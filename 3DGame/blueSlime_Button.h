#ifndef BLUESLIME_BUTTON
#define BLUESLIME_BUTTON

#include "button.h"
#include "Texture.h"

class BlueSlime_Button : public Button
{
private:


public:
	BlueSlime_Button(D3DXVECTOR2 pos) : Button(GAMESTARTBUTTON, LoadTexture("data/TEXTURE/blue_slimeButton.png"), LoadTexture("data/TEXTURE/blue_slimeButton_red.png"), pos) {}

	void ButtonAction() override
	{
		
	}
};

#endif//BLUESLIME_BUTTON
