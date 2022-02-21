#ifndef CHARACTER_3_H_
#define CHARACTER_3_H_

#include "character.h"
#include "sound.h"
#include "constant.h"

class Character_3 : public Character
{
private:

public:
	Character_3() :Character(CHARACTER03, (char*)"data/MODEL/yellow_slime.obj", CHARACTER03_ACC, CHARACTER03_MAXVEL, CHARACTER03_JUMPPOWER, CHARACTER03_STAMINIA, CHARACTER03_HP)
	{
		jumpSE = LoadSound("data/SE/jump.wav");
	};

	~Character_3()
	{

	};
};

#endif//CHARACTER_3_H_