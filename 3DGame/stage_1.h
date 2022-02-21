#ifndef STAGE01_H_
#define STAGE01_H_

#include "stage.h"
#include "ui.h"
#include "player.h"
#include "map_1.h"
#include "character.h"
#include "classResource.h"

class Stage_1 : public Stage
{
public:
	 Stage_1(CHARACTER character):Stage(STAGE01, MAP01, character)
	 {
		 min = 1;
		 sec = 0;
		 milliSec = 0;
	 }

	~Stage_1(){}

	void CheckGuide(Character* character, Map* map) override
	{
		for(int i = 0; i < map->GetMaxCheckPoint(); i++)
		{
			if (character->GetPos().z >= map->GetCheckPoint(i).z + 10)
			{
				switch(i)
				{
				case 0:
					guide = 1;
					break;
				case 1:
					guide = 2;
					break;
				case 2:
					guide = 2;
					break;
				case 3:
					guide = 3;
					break;
				case 4:
					guide = 4;
					break;
				case 5:
					guide = 5;
					break;
				default:
					break;
				}
				if(map->GetArrow(i))
					map->GetArrow(i)->SetShow(false);
				if (map->GetArrow(i+1))
				map->GetArrow(i+1)->SetShow(true);

			}
		}
	}

	void StageAction(Character* character, Map* map, Camera* cam) override
	{
		if (character->GetPos().z >= map->GetArrow(5)->GetPos().z + 10)
		{
			rockTimer++;
			if(rockTimer % 20 == 0)
			{
				int x = -40 + rand() % 80;
				map->CreateRock({ (float)x,40.0f, 1200.0f });
			}
		}
	}

private:
	int rockTimer = 0;
};

#endif//STAGE01_H_
