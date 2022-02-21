#ifndef STAGE02_H_
#define STAGE02_H_

#include "stage.h"
#include "ui.h"
#include "player.h"
#include "map_2.h"
#include "character.h"
#include "classResource.h"
#include "collision.h"
#include "sound.h"

class Stage_2 : public Stage
{
private:
	bool start_CheckPoint_4_Timer = false;
	int  checkPoint_4_timer = 0;
	int box = 11;
	int failSE;

public:
	Stage_2(CHARACTER character) :Stage(STAGE02, MAP02, character)
	{
		min = 5;
		sec = 0;
		milliSec = 0;
		failSE = LoadSound("data/SE/fail.wav");
	}

	~Stage_2() {}

	void CheckGuide(Character* character, Map* map) override
	{
		guide = -1;
		for (int i = 0; i < map->GetMaxCheckPoint(); i++)
		{
			if (character->GetPos().z >= map->GetCheckPoint(i).z + map->GetCheckPointOffset(i).z)
			{
				if (map->GetArrow(i))
					map->GetArrow(i)->SetShow(false);
				if (map->GetArrow(i + 1))
					map->GetArrow(i + 1)->SetShow(true);
			}
		}
	}

	void StageAction(Character* character, Map* map, Camera* cam) override
	{
		if (character->GetPos().z >= map->GetCheckPoint(1).z && character->GetPos().z < map->GetCheckPoint(2).z && character->GetOnFloor())
		{
			if (map->GetSemaphore(0))
			{
				map->GetSemaphore(0)->SetStartSemaphore(true);
			}
		}else
		if (character->GetPos().z <= map->GetCheckPoint(1).z)
		{
			if (map->GetSemaphore(0))
				map->GetSemaphore(0)->SetStartSemaphore(false);
		}else
		if (character->GetPos().z >= map->GetCheckPoint(2).z)
		{
			if (map->GetSemaphore(0))
				map->GetSemaphore(0)->SetStartSemaphore(false);
		}

		
		if(map->GetSemaphore(0) && map->GetSemaphore(0)->GetStartSemaphore())
		{
			map->GetBlock(7)->SetPos(map->GetSemaphore(0)->GetPos() - D3DXVECTOR3{ 0.0f, 15.0f, 0.0f });
			if(map->GetSemaphore(0) && !map->GetSemaphore(0)->GetCanWalk())
			{
				if(character->GetSpd() != D3DXVECTOR3{0.0f,0.0f,0.0f})
				{
					SetVolume(failSE, 1.0f);
					PlaySound(failSE, 0);
					character->SetPos(map->GetCheckPoint(1));
				}
			}
		}

		
		if (character->GetPos().z >= map->GetCheckPoint(3).z && character->GetPos().z < map->GetCheckPoint(4).z)
		{
			if(character->GetOnFloor())
			{
				character->SetCanJump(false);
				cam->SetCamera_2();
			}
		}

		if (character->GetPos().z >= map->GetCheckPoint(4).z && character->GetPos().z < map->GetCheckPoint(5).z ||
			character->GetPos().z <= map->GetCheckPoint(3).z)
		{
			if (character->GetOnFloor())
			{
				character->SetCanJump(true);
				cam->SetCamera_1();
			}
		}

		if (character->GetPos().z >= map->GetCheckPoint(4).z)
		{
			map->DeleteCheckPoint_1();
			map->DeleteCheckPoint_2();
		}

		if(map->GetSwitch(1) &&
			CollisionBB(character->GetPos(), map->GetSwitch(1)->GetPos(), character->GetSize(), map->GetSwitch(1)->GetSize()))
		{
			map->GetWoodBox(0)->SetPos(map->GetWoodBox(0)->GetOldPos());
			map->GetWoodBox(1)->SetPos(map->GetWoodBox(1)->GetOldPos());
			map->GetWoodBox(2)->SetPos(map->GetWoodBox(2)->GetOldPos());
		}

		if (map->GetSwitch(4) &&
			CollisionBB(character->GetPos(), map->GetSwitch(4)->GetPos(), character->GetSize(), map->GetSwitch(4)->GetSize()))
		{
			map->GetWoodBox(5)->SetPos(map->GetWoodBox(5)->GetOldPos());
			map->GetWoodBox(6)->SetPos(map->GetWoodBox(6)->GetOldPos());
			map->GetWoodBox(7)->SetPos(map->GetWoodBox(7)->GetOldPos());
			map->GetWoodBox(8)->SetPos(map->GetWoodBox(8)->GetOldPos());
		}

		if (map->GetWoodBox(0) && map->GetWoodBox(1) && 
			map->GetWoodBox(2) && map->GetSwitch(0)&& 
			map->GetSwitch(2) && map->GetSwitch(3) &&
			CollisionBB(map->GetWoodBox(0)->GetPos(), map->GetSwitch(0)->GetPos(), map->GetWoodBox(0)->GetSize(), map->GetSwitch(0)->GetSize())&&
			CollisionBB(map->GetWoodBox(1)->GetPos(), map->GetSwitch(2)->GetPos(), map->GetWoodBox(1)->GetSize(), map->GetSwitch(2)->GetSize())&&
			CollisionBB(map->GetWoodBox(2)->GetPos(), map->GetSwitch(3)->GetPos(), map->GetWoodBox(2)->GetSize(), map->GetSwitch(3)->GetSize()))
		{
			map->DeleteCheckPoint_3(0);
		}

		if (map->GetWoodBox(5) && map->GetWoodBox(6) &&
			map->GetWoodBox(7) && map->GetWoodBox(8) && map->GetSwitch(5) &&
			map->GetSwitch(6) && map->GetSwitch(7) && map->GetSwitch(8) &&
			((CollisionBB(map->GetWoodBox(7)->GetPos(), map->GetSwitch(5)->GetPos(), map->GetWoodBox(7)->GetSize(), map->GetSwitch(5)->GetSize()) || 
			  CollisionBB(map->GetWoodBox(7)->GetPos(), map->GetSwitch(7)->GetPos(), map->GetWoodBox(7)->GetSize(), map->GetSwitch(7)->GetSize())))
										&&
			(CollisionBB(map->GetWoodBox(8)->GetPos(), map->GetSwitch(5)->GetPos(), map->GetWoodBox(8)->GetSize(), map->GetSwitch(5)->GetSize()) ||
			 CollisionBB(map->GetWoodBox(8)->GetPos(), map->GetSwitch(7)->GetPos(), map->GetWoodBox(8)->GetSize(), map->GetSwitch(7)->GetSize())) 
										&&
			(CollisionBB(map->GetWoodBox(5)->GetPos(), map->GetSwitch(6)->GetPos(), map->GetWoodBox(5)->GetSize(), map->GetSwitch(6)->GetSize()) ||
			 CollisionBB(map->GetWoodBox(5)->GetPos(), map->GetSwitch(8)->GetPos(), map->GetWoodBox(5)->GetSize(), map->GetSwitch(8)->GetSize())) 
										&&			
			(CollisionBB(map->GetWoodBox(6)->GetPos(), map->GetSwitch(6)->GetPos(), map->GetWoodBox(6)->GetSize(), map->GetSwitch(6)->GetSize()) ||
			 CollisionBB(map->GetWoodBox(6)->GetPos(), map->GetSwitch(8)->GetPos(), map->GetWoodBox(6)->GetSize(), map->GetSwitch(8)->GetSize())))
		{
			map->DeleteCheckPoint_3(1);
		}



		if (map->GetBlock(13) && CollisionBBCharacterDownBlockUp(character->GetPos(), map->GetBlock(13)->GetPos(), character->GetSize(), map->GetBlock(13)->GetSize()))
		{
			map->SetUpCheckPoint_4(1);
		}

		if (map->GetBlock(16) && CollisionBBCharacterDownBlockUp(character->GetPos(), map->GetBlock(16)->GetPos(), character->GetSize(), map->GetBlock(16)->GetSize()))
		{
			map->SetUpCheckPoint_4(2);
		}

		if (map->GetBlock(18) && CollisionBBCharacterDownBlockUp(character->GetPos(), map->GetBlock(18)->GetPos(), character->GetSize(), map->GetBlock(18)->GetSize()))
		{
			map->SetUpCheckPoint_4(3);
		}

		if (map->GetBlock(20) && CollisionBBCharacterDownBlockUp(character->GetPos(), map->GetBlock(20)->GetPos(), character->GetSize(), map->GetBlock(20)->GetSize()))
		{
			map->SetUpCheckPoint_4(4);
		}

		if (map->GetBlock(21) && CollisionBBCharacterDownBlockUp(character->GetPos(), map->GetBlock(21)->GetPos(), character->GetSize(), map->GetBlock(21)->GetSize()))
		{
			map->SetUpCheckPoint_4(6);
		}

		if (map->GetBlock(22) && CollisionBBCharacterDownBlockUp(character->GetPos(), map->GetBlock(22)->GetPos(), character->GetSize(), map->GetBlock(22)->GetSize()))
		{
			map->SetUpCheckPoint_4(6);
		}

		if (map->GetBlock(23) && CollisionBBCharacterDownBlockUp(character->GetPos(), map->GetBlock(23)->GetPos(), character->GetSize(), map->GetBlock(23)->GetSize()))
		{
			map->SetUpCheckPoint_4(7);
		}

		if (map->GetBlock(24) && CollisionBBCharacterDownBlockUp(character->GetPos(), map->GetBlock(24)->GetPos(), character->GetSize(), map->GetBlock(24)->GetSize()))
		{
			map->SetUpCheckPoint_4(8);
		}

		if (map->GetBlock(25) && CollisionBBCharacterDownBlockUp(character->GetPos(), map->GetBlock(25)->GetPos(), character->GetSize(), map->GetBlock(25)->GetSize()))
		{
			map->SetUpCheckPoint_4(9);
		}

		if (map->GetBlock(27) && CollisionBBCharacterDownBlockUp(character->GetPos(), map->GetBlock(27)->GetPos(), character->GetSize(), map->GetBlock(27)->GetSize()))
		{
			map->SetUpCheckPoint_4(10);
		}

		if (map->GetBlock(29) && CollisionBBCharacterDownBlockUp(character->GetPos(), map->GetBlock(29)->GetPos(), character->GetSize(), map->GetBlock(29)->GetSize()))
		{
			map->SetUpCheckPoint_4(11);
		}

		if (map->GetBlock(14) && CollisionBBCharacterDownBlockUp(character->GetPos(), map->GetBlock(14)->GetPos(), character->GetSize(), map->GetBlock(14)->GetSize()))
		{
;			start_CheckPoint_4_Timer = true;
		}

		if(start_CheckPoint_4_Timer)
		{
			checkPoint_4_timer++;
			if(checkPoint_4_timer % 90 == 0)
			{
				map->DeleteCheckPoint_4(box);
				box++;
			}
		}
	}
};

#endif//STAGE02_H_