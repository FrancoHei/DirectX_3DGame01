#ifndef BUTTON_H_
#define BUTTON_H_

#include "scene.h"
#include "fade.h"

enum BUTTON
{
	GAMEDESCRIPTIONBUTTON,
	GAMESTARTBUTTON
};

class Button
{
private:
	BUTTON      button;
	int			textureNo;
	int         textureNo_Choice;
	int         textureNo_unChoice;
	D3DXVECTOR2 pos;
	D3DXVECTOR2 size = {400.0f,100.0f};
public:
	 Button(BUTTON button_, int textureNo_unChoice_, int textureNo_Choice_, D3DXVECTOR2 pos_)
		 : button(button_), textureNo(textureNo_unChoice_), textureNo_unChoice(textureNo_unChoice_), textureNo_Choice(textureNo_Choice_),pos(pos_) {}
	~Button() {} 
	
	void Update(bool choice)
	{
		if(choice)
		{
			textureNo = textureNo_Choice;
		}else
		{
			textureNo = textureNo_unChoice;
		}
	}

	void SetSize(D3DXVECTOR2 size_)
	{
		size = size_;
	}

	virtual void ButtonAction() = 0;

	void Draw()
	{
		DrawSprite(textureNo, pos.x, pos.y, size.x, size.y, 0.0f, 0.0f, 1.0f, 1.0f);
	}
};

#endif//BUTTON_H_
