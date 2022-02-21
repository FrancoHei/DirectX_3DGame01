#ifndef CHARACTER_1_H_
#define CHARACTER_1_H_

#include "character.h"
#include "sound.h"
#include "constant.h"


class Character_1 : public Character
{
private:

public:
	 Character_1():Character(CHARACTER01, (char*)"data/MODEL/slime.obj", CHARACTER01_ACC, CHARACTER01_MAXVEL, CHARACTER01_JUMPPOWER, CHARACTER01_STAMINIA, CHARACTER01_HP)
	 {
		 jumpSE = LoadSound("data/SE/jump.wav");
	 };

	~Character_1() 
	{
	
	};
};

#endif//CHARACTER_1_H_