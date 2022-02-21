#ifndef MAP_3_H_
#define MAP_3_H_

#include "map.h"

class Map_3 :public Map
{
private:
	const int maxCheckPoint = 7;
	const D3DXVECTOR3 checkPoint[7] = { { 0.0f,10.0f, 200.0f },
										   { 0.0f,10.0f, 250.0f },
										   { 0.0f,10.0f, 315.0f },
										   { 0.0f,10.0f, 445.0f },
										   { 0.0f,10.0f, 555.0f },
										   { 0.0f,10.0f, 685.0f },
										   { 0.0f,10.0f, 1200.0f } };

	const D3DXVECTOR3 checkPointOffset[6] = { { 0.0f,0.0f,0.0f },
												{ 0.0f,0.0f,0.0f },
												{ 0.0f,0.0f,0.0f },
												{ 0.0f,0.0f,0.0f },
												{ 0.0f,0.0f,0.0f },
												{ 0.0f,0.0f,0.0f } };

public:
	Map_3() :Map(MAP03)
	{
		SetUpMapBase();
	}

	D3DXVECTOR3 GetCheckPoint(int i) const override
	{
		return checkPoint[i];
	}

	D3DXVECTOR3 GetCheckPointOffset(int i) const override
	{
		return checkPointOffset[i];
	}

	int  GetMaxCheckPoint() const override
	{
		return maxCheckPoint;
	}

	void SetUpMapBase() override
	{
		if (field[0] == nullptr)
		{
			field[0] = new BridgeField({ 0.0f,0.0f, 0.0f }, 2, 3);
			field[0]->SetSize({ 100.0f,0.0f,150.0f });
		}


		if (wall[0] == nullptr)
		{
			wall[0] = new Wall(WALL_RIGHT, { 40.0f, 0.0f, 0.0f }, 5, 120);
			wall[0]->SetSize({ 0.0f,1000.0f,1000000.0f });
		}

		if (wall[1] == nullptr)
		{
			wall[1] = new Wall(WALL_LEFT, { -40.0f, 0.0f, 0.0f }, 5, 120);
			wall[1]->SetSize({ 0.0f,1000.0f,1000000.0f });
		}

		if (field[1] == nullptr)
		{
			field[1] = new FireField({ 0.0f,-20.0f, 300.0f }, 2, 120);
			field[1]->SetSize({ 100.0f,0.0f,50000.0f });
		}

		if (field[2] == nullptr)
		{
			field[2] = new BridgeField({ 0.0f,0.0f, 750.0f }, 2, 15);
			field[2]->SetSize({ 100.0f,0.0f,755.0f });
		}


		if (field[3] == nullptr)
		{
			field[3] = new BridgeField({ 0.0f,0.0f, 1500.0f }, 2, 10);
			field[3]->SetSize({ 100.0f,0.0f,495.0f });
		}

		if (field[4] == nullptr)
		{
			field[4] = new BridgeField({ 0.0f,0.0f, 2900.0f }, 2, 3);
			field[4]->SetSize({ 100.0f,0.0f,150.0f });
		}

		if (treasure == nullptr)
		{
			treasure = new Treasure({ 0.0f,0.0f, 2900.0f });
		}
	}
};

#endif//MAP_3_H_
