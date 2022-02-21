#ifndef STAGE03_H_
#define STAGE03_H_

#include "stage.h"
#include "ui.h"
#include "player.h"
#include "map_1.h"
#include "character.h"
#include "classResource.h"

class Stage_3 : public Stage
{
public:
	Stage_3(CHARACTER character) :Stage(STAGE03, MAP03, character)
	{
		min = 1;
		sec = 0;
		milliSec = 0;
	}

	~Stage_3() {}

	void CheckGuide(Character* character, Map* map) override
	{
		guide = -1;

	}

	void StageAction(Character* character, Map* map, Camera* cam) override
	{
		
	}

};

#endif//STAGE03_H_