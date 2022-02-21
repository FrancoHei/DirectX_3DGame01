#ifndef CHARACTER_2_H_
#define CHARACTER_2_H_

#include "character.h"
#include "sound.h"
#include "constant.h"

class Character_2 : public Character
{
private:

public:
	Character_2() :Character(CHARACTER02, (char*)"data/MODEL/green_slime.obj", CHARACTER02_ACC, CHARACTER02_MAXVEL, CHARACTER02_JUMPPOWER, CHARACTER02_STAMINIA, CHARACTER02_HP)
	{
		jumpSE = LoadSound("data/SE/jump.wav");
	};

	~Character_2()
	{

	};
};

#endif//CHARACTER_2_H_