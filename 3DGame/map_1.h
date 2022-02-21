#ifndef MAP_1_H_
#define MAP_1_H_

#define MAP1_MAXCHECKPOINT 7

#include "map.h"

class Map_1 : public Map
{
private:

	const std::array<D3DXVECTOR3, MAP1_MAXCHECKPOINT> checkPointArray      =  { D3DXVECTOR3( 0.0f,10.0f, 200.0f ),
																				D3DXVECTOR3( 0.0f,10.0f, 250.0f ),
																				D3DXVECTOR3( 0.0f,10.0f, 315.0f ),
																				D3DXVECTOR3( 0.0f,10.0f, 445.0f ),
																				D3DXVECTOR3( 0.0f,10.0f, 555.0f ),
																				D3DXVECTOR3( 0.0f,10.0f, 685.0f ),
																				D3DXVECTOR3( 0.0f,10.0f, 1200.0f) };

	const std::array<D3DXVECTOR3, MAP1_MAXCHECKPOINT> checkPointOffsetArray = {	D3DXVECTOR3(0.0f, 0.0f, 0.0f),
																				D3DXVECTOR3(0.0f, 0.0f, 0.0f),
																				D3DXVECTOR3(0.0f, 0.0f, 0.0f),
																				D3DXVECTOR3(0.0f, 0.0f, 0.0f),
																				D3DXVECTOR3(0.0f, 0.0f, 0.0f),
																				D3DXVECTOR3(0.0f, 0.0f, 0.0f),
																				D3DXVECTOR3(0.0f, 0.0f, 0.0f) };

public:
	Map_1():Map(MAP01)
	{
		SetUpMapBase();

		SetUpCheckPoint_1();

		SetUpArrow();

		//ENDPOINT
		treasure = new Treasure({ 0.0f,0.0f, 1200.0f });
	}

	void SetUpMapBase() 
	{
		field[0] = new BridgeField({ 0.0f,0.0f, 0.0f }, 2, 10);
		field[0] ->SetSize({ 100.0f,0.0f,495.0f });

		field[1] = new FireField({ 0.0f,-20.0f, 300.0f }, 2, 50);
		field[1] ->SetSize({ 100.0f,0.0f,5000.0f });

		field[2] = new BridgeField({ 0.0f,0.0f, 550.0f }, 2, 3);
		field[2] ->SetSize({ 100.0f,0.0f,150.0f });

		field[3] = new BridgeField({ 0.0f,0.0f, 990.0f }, 2, 10);
		field[3] ->SetSize({ 100.0f,0.0f,495.0f });

		wall[0]  = new Wall(WALL_RIGHT, { 40.0f, 0.0f, 0.0f }, 5, 60);
		wall[0]  ->SetSize({ 0.0f,1000.0f,1000.0f });

		wall[1]  = new Wall(WALL_LEFT, { -40.0f, 0.0f, 0.0f }, 5, 60);
		wall[1]  ->SetSize({ 0.0f,1000.0f,1000.0f });
	}

	void SetUpCheckPoint_1() 
	{
		block[0] = new Block({ 0.0f, -5.0f, 280.0f });
		block[1] = new Block({ 0.0f, -5.0f, 350.0f });
		block[2] = new Block({ -30.0f, -5.0f, 420.0f });
	}

	void SetUpArrow() override
	{
		for (int i = 0; i < MAP1_MAXCHECKPOINT; i++)
		{
			arrow[i] = new Arrow(checkPointArray[i]);
		}

		arrow[0]->SetShow(true);
	}

	D3DXVECTOR3 GetCheckPoint(int i) const override
	{
		return checkPointArray[i];
	}

	D3DXVECTOR3 GetCheckPointOffset(int i) const override
	{
		return checkPointOffsetArray[i];
	}

	int  GetMaxCheckPoint() const override
	{
		return MAP1_MAXCHECKPOINT;
	}
};

#endif//MAP_1_H_
