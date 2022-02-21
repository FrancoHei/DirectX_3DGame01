#ifndef CHARACTERSELECTMENU_H_
#define CHARACTERSELECTMENU_H_

#include "Texture.h"

class Image;
class Button;

class CharacterSelectMenu
{
private:
	Image* blue_Slime	= nullptr;
	Image* yellow_Slime	= nullptr;
	Image* green_Slime	= nullptr;

	Button* blueSlimeButton   = nullptr;
	Button* yellowSlimeButton = nullptr;
	Button* greenSlimeButton  = nullptr;
	int		textureNo		  = LoadTexture("data/TEXTURE/bg.jpg");
	int		stateBaseTextNo   = LoadTexture("data/TEXTURE/stateBase.png");
	int		statusTextNo	  = LoadTexture("data/TEXTURE/status.png");
	int		status_3TextNo	  = LoadTexture("data/TEXTURE/status_2.png");
	int		status_2TextNo	  = LoadTexture("data/TEXTURE/status_3.png");

	Image*  status[5][5];
	int		choice			  = 0;
public:
	CharacterSelectMenu();
	~CharacterSelectMenu();

	void Update();
	void Draw();
};

#endif//CHARACTERSELECTMENU_H_
