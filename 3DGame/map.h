#ifndef MAP_H_
#define MAP_H_

#include <iostream>
#include <array>

#include "mapItem.h"
#include "field.h"
#include "wall.h"
#include "block.h"
#include "arrow.h"
#include "rock.h"
#include "treasure.h"
#include "semaphore.h"
#include "character.h"
#include "ironBox.h"
#include "woodBox.h"
#include "switch.h"
#include "red_Switch.h"
#include "yellow_Switch.h"
#include "bridgeField.h"
#include "fireField.h"
#include "field.h"

#define MAXFIELD	 100
#define MAXWALL		 100
#define MAXBLOCK	 100
#define MAXARROW	 100
#define MAXROCK		 100
#define MAXSEMAPHORE 100
#define MAXIRONBOX   100
#define MAXWOODBOX	 100
#define MAXSWITCH    100

class Camera;

enum MAP
{
	MAP01,
	MAP02,
	MAP03
};

class Map
{
private:
	MAP map;

protected:
	Field*     field[MAXFIELD];
	Wall*      wall[MAXWALL];
	Block*     block[MAXBLOCK];
	Arrow*     arrow[MAXARROW];
	Rock*	   rock[MAXROCK];
	Semaphore* semaphore[MAXSEMAPHORE];
	IronBox*   ironBox[MAXIRONBOX];
	WoodBox*   woodBox[MAXWOODBOX];
	Switch*	   m_Switch[MAXSWITCH];

	Treasure* treasure;

public:
	Map() = delete;
	Map(MAP map_) : map(map_){}
	~Map();

	void Update(Character* character, Camera* cam)
	{
		for (int i = 0; i < MAXFIELD; i++)
		{
			if (field[i])
				field[i]->Update();
		}

		for (int i = 0; i < MAXWALL; i++)
		{
			if (wall[i])
				wall[i]->Update();
		}

		for (int i = 0; i < MAXBLOCK; i++)
		{
			if (block[i])
				block[i]->Update(this);
		}

		for (int i = 0; i < MAXARROW; i++)
		{
			if (arrow[i])
				arrow[i]->Update(cam);
		}

		for (int i = 0; i < MAXROCK; i++)
		{
			if (rock[i])
				rock[i]->Update(i, this);
		}

		for (int i = 0; i < MAXSEMAPHORE; i++)
		{
			if (semaphore[i])
				semaphore[i]->Update(character);
		}

		for (int i = 0; i < MAXIRONBOX; i++)
		{
			if (ironBox[i])
				ironBox[i]->Update();
		}

		for (int i = 0; i < MAXWOODBOX; i++)
		{
			if (woodBox[i])
				woodBox[i]->Update();
		}

		for (int i = 0; i < MAXSWITCH; i++)
		{
			if (m_Switch[i])
				m_Switch[i]->Update();
		}
		

		if (treasure)
			treasure->Update();
	}

	void Draw()
	{
		for(int i = 0; i < MAXFIELD; i++)
		{
			if(field[i])
				field[i]->Draw();
		}

		for (int i = 0; i < MAXWALL; i++)
		{
			if (wall[i])
				wall[i]->Draw();
		}

		for (int i = 0; i < MAXBLOCK; i++)
		{
			if (block[i])
				block[i]->Draw();
		}

		for (int i = 0; i < MAXARROW; i++)
		{
			if (arrow[i] && arrow[i]->GetShow())
				arrow[i]->Draw();
		}

		for (int i = 0; i < MAXROCK; i++)
		{
			if (rock[i])
				rock[i]->Draw();
		}

		for (int i = 0; i < MAXSEMAPHORE; i++)
		{
			if (semaphore[i])
				semaphore[i]->Draw();
		}

		for (int i = 0; i < MAXIRONBOX; i++)
		{
			if (ironBox[i])
				ironBox[i]->Draw();
		}

		for (int i = 0; i < MAXWOODBOX; i++)
		{
			if (woodBox[i])
				woodBox[i]->Draw();
		}
		

		for (int i = 0; i < MAXSWITCH; i++)
		{
			if (m_Switch[i])
				m_Switch[i]->Draw();
		}

		if (treasure)
			treasure->Draw();
	}

	Field* GetField(int i) const		 { return field[i]; }
	Wall*  GetWall(int i)  const		 { return wall[i];  }
	Block* GetBlock(int i) const		 { return block[i]; }
	Arrow* GetArrow(int i) const		 { return arrow[i]; }
	Rock*  GetRock(int i)  const		 { return rock[i];}
	Semaphore* GetSemaphore(int i) const { return semaphore[i]; }
	Treasure* GetTreasure() const		 { return treasure; }
	IronBox* GetIronBox(int i) const	 { return ironBox[i]; }
	WoodBox* GetWoodBox(int i) const	 { return woodBox[i]; }
	Switch*  GetSwitch(int i) const		 { return m_Switch[i];}

	MAP    GetMap() const				 { return map; }
	
	void DeleteIronBox(int i)
	{
		delete ironBox[i];
		ironBox[i] = nullptr;
	}

	virtual D3DXVECTOR3 GetCheckPoint(int i) const		 = 0;
	virtual D3DXVECTOR3 GetCheckPointOffset(int i) const = 0;
	virtual int         GetMaxCheckPoint() const		 = 0;


	void   CreateRock(D3DXVECTOR3 pos_)
	{
		for(int i = 0; i < MAXROCK; i++)
		{
			if(rock[i] == nullptr)
			{
				rock[i] = new Rock(pos_);
				break;
			}
		}
	}

	void DeleteRock(int i)
	{
		delete rock[i];
		rock[i] = nullptr;
	}

	virtual void SetUpMapBase(){}

	virtual void SetUpCheckPoint_1() {}
	virtual void DeleteCheckPoint_1() {}

	virtual void SetUpCheckPoint_2() {}
	virtual void DeleteCheckPoint_2() {}

	virtual void SetUpCheckPoint_3(){}
	virtual void SetUpCheckPoint_3(int stage) {}
	virtual void DeleteCheckPoint_3() {}
	virtual void DeleteCheckPoint_3(int stage) {}

	virtual void SetUpCheckPoint_4(int stage) {}
	virtual void DeleteCheckPoint_4(int stage) {}

	virtual void SetUpArrow() {}
};

#endif//MAP_H_
