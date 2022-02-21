#ifndef MAP_2_H_
#define MAP_2_H_

#define MAP2_MAXCHECKPOINT 6

#include "map.h"
class Map_2 : public Map
{
private:

	const std::array<D3DXVECTOR3, MAP2_MAXCHECKPOINT> checkPointArray =       {	D3DXVECTOR3(0.0f,10.0f, 60.0f),
																				D3DXVECTOR3(0.0f,10.0f, 385.0f),
																				D3DXVECTOR3(0.0f,10.0f, 1000.0f),
																				D3DXVECTOR3(0.0f,10.0f, 1205.0f),
																				D3DXVECTOR3(0.0f,10.0f, 1555.0f),
																				D3DXVECTOR3(0.0f,10.0f, 2690.0f)};

	const std::array<D3DXVECTOR3, MAP2_MAXCHECKPOINT> checkPointOffsetArray = { D3DXVECTOR3(0.0f, 0.0f, 0.0f),
																				D3DXVECTOR3(0.0f, 0.0f, 0.0f),
																				D3DXVECTOR3(0.0f, 0.0f, 0.0f),
																				D3DXVECTOR3(0.0f, 0.0f, 0.0f),
																				D3DXVECTOR3(0.0f, 0.0f, 20.0f),
																				D3DXVECTOR3(0.0f, 0.0f, 190.0f)};

public:
	Map_2() :Map(MAP02)
	{
		for (int i = 0; i < MAXIRONBOX; i++)
		{
			ironBox[i] = nullptr;
		}
		SetUpArrow();
		SetUpMapBase();
		SetUpCheckPoint_1();
		SetUpCheckPoint_2();
		SetUpCheckPoint_3(0);
		SetUpCheckPoint_3(1);
		SetUpCheckPoint_4(0);
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
		return MAP2_MAXCHECKPOINT;
	}

	void SetUpArrow() override
	{
		for (int i = 0; i < MAP2_MAXCHECKPOINT; i++)
		{
			arrow[i] = new Arrow(checkPointArray[i]);
		}

		arrow[0]->SetShow(true);
	}

	void SetUpMapBase() override
	{
		if(field[0] == nullptr)
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

		if(field[2] == nullptr)
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

	void SetUpCheckPoint_1() override
	{
		if (block[0] == nullptr)
		{
			block[0] = new Block({ -25.0f, -5.0f, 120.0f });
			block[0]->SetSpd({ 0.3f,0.0f,0.0f });
			block[0]->SetMaxFrame(210);
		}

		if (block[1] == nullptr)
		{
			block[1] = new Block({ -20.0f, -5.0f, 180.0f });
			block[1]->SetSpd({ 0.25f,0.0f,0.25f });
			block[1]->SetMaxFrame(70);
		}

		if (block[2] == nullptr)
		{
			block[2] = new Block({ 20.0f, -5.0f, 180.0f });
			block[2]->SetSpd({ -0.25f,0.0f,0.25f });
			block[2]->SetMaxFrame(70);
		}

		if (block[3] == nullptr)
		{
			block[3] = new Block({ -20.0f, -5.0f, 250.0f });
			block[3]->SetSpd({ 0.25f,0.0f,-0.25f });
			block[3]->SetMaxFrame(70);
		}

		if (block[4] == nullptr)
		{
			block[4] = new Block({ 20.0f, -5.0f, 250.0f });
			block[4]->SetSpd({ -0.25f,0.0f,-0.25f });
			block[4]->SetMaxFrame(70);
		}

		if (block[5] == nullptr)
		{
			block[5] = new Block({ 0.0f, 20.0f, 320.0f });
			block[5]->SetSpd({ 0.0f,-0.2f,0.0f });
			block[5]->SetMaxFrame(150);
		}

		if (block[6] == nullptr)
		{
			block[6] = new Block({ 0.0f, -15.0f, 350.0f });
			block[6]->SetSpd({ 0.0f,0.2f,0.0f });
			block[6]->SetMaxFrame(150);
		}
	}

	void DeleteCheckPoint_1() override
	{
		delete block[0];
		block[0] = nullptr;

		delete block[1];
		block[1] = nullptr;

		delete block[2];
		block[2] = nullptr;

		delete block[3];
		block[3] = nullptr;

		delete block[4];
		block[4] = nullptr;

		delete block[5];
		block[5] = nullptr;

		delete block[6];
		block[6] = nullptr;
	}

	void SetUpCheckPoint_2() override
	{
		semaphore[0] = new Semaphore({ 0.0f, 45.0f, 500.0f });
		block[7] = new Block({ 0.0f, 30.0f, 500.0f });
		
	}

	void DeleteCheckPoint_2() override
	{
		delete semaphore[0];
		semaphore[0] = nullptr;
		delete block[7];
		block[7]	 = nullptr;
	}

	void SetUpCheckPoint_3(int stage) override
	{
		if(stage == 0 )
		{
				if(ironBox[0] == nullptr)
				{
					ironBox[0] = new IronBox({ -40.0f, 5.0f, 1330.0f });
					ironBox[0]->SetScale(D3DXVECTOR3(1.0f,1.0f,5.0f));
					ironBox[0]->SetSize(D3DXVECTOR3(ironBox[0]->GetSize().x * ironBox[0]->GetScale().x,
											        ironBox[0]->GetSize().y * ironBox[0]->GetScale().y,
													ironBox[0]->GetSize().z * (ironBox[0]->GetScale().z - 2)));
				}

				if (ironBox[1] == nullptr)
				{
					ironBox[1] = new IronBox({ 40.0f, 5.0f, 1330.0f });
					ironBox[1]->SetScale(D3DXVECTOR3(1.0f, 1.0f, 5.0f));
					ironBox[1]->SetSize(D3DXVECTOR3(ironBox[1]->GetSize().x * ironBox[0]->GetScale().x,
					ironBox[1]->GetSize().y * ironBox[1]->GetScale().y,
					ironBox[1]->GetSize().z * (ironBox[1]->GetScale().z - 2)));
				}

				if (ironBox[2] == nullptr)
				{
					ironBox[2] = new IronBox({ 0.0f, 5.0f, 1360.0f });
					ironBox[2]->SetScale(D3DXVECTOR3(9.0f, 1.0f, 1.0f));
					ironBox[2]->SetSize(D3DXVECTOR3(ironBox[2]->GetSize().x * (ironBox[2]->GetScale().x - 2),
					ironBox[2]->GetSize().y * ironBox[2]->GetScale().y,
					ironBox[2]->GetSize().z * (ironBox[2]->GetScale().z)));
				}


				if (ironBox[3] == nullptr)
				{
					ironBox[3] = new IronBox({ -30.0f, 5.0f, 1300.0f });
					ironBox[3]->SetScale(D3DXVECTOR3(3.0f, 1.0f, 1.0f));
					ironBox[3]->SetSize(D3DXVECTOR3(ironBox[3]->GetSize().x * (ironBox[3]->GetScale().x - 0.6f),
					ironBox[3]->GetSize().y * ironBox[3]->GetScale().y,
					ironBox[3]->GetSize().z * (ironBox[3]->GetScale().z)));
				}

				if (ironBox[4] == nullptr)
				{
					ironBox[4] = new IronBox({ 30.0f, 5.0f, 1300.0f });
					ironBox[4]->SetScale(D3DXVECTOR3(3.0f, 1.0f, 1.0f));
					ironBox[4]->SetSize(D3DXVECTOR3(ironBox[4]->GetSize().x * (ironBox[4]->GetScale().x - 0.6f),
						ironBox[4]->GetSize().y * ironBox[4]->GetScale().y,
						ironBox[4]->GetSize().z * (ironBox[4]->GetScale().z)));
				}

				if (ironBox[28] == nullptr)
					ironBox[28] = new IronBox({ 5.0f, 5.0f, 1325.0f });
				if (ironBox[29] == nullptr)
					ironBox[29] = new IronBox({ -5.0f, 5.0f, 1325.0f });
				if (woodBox[0] == nullptr)
					woodBox[0] = new WoodBox({ -6.0f, 5.0f, 1336.0f });
				if (woodBox[1] == nullptr)
					woodBox[1] = new WoodBox({ 16.0f, 5.0f, 1325.0f });
				if (woodBox[2] == nullptr)
					woodBox[2] = new WoodBox({ -6.0f, 5.0f, 1314.0f });

				if (m_Switch[0] == nullptr)
					m_Switch[0] = new Yellow_Switch({ -23.0f, 0.1f, 1325.0f });
				if (m_Switch[2] == nullptr)
					m_Switch[2] = new Yellow_Switch({ 12.0f, 0.1f, 1345.0f });
				if (m_Switch[3] == nullptr)
					m_Switch[3] = new Yellow_Switch({ 23.0f, 0.1f, 1315.0f });

				if (m_Switch[1] == nullptr)
					m_Switch[1] = new Red_Switch({ 0.0f, 0.1f, 1275.0f });
		}else
		if(stage == 1)
		{

			if (ironBox[7] == nullptr)
			{
				ironBox[7] = new IronBox({ 0.0f, 5.0f, 1470.0f });
				ironBox[7]->SetScale(D3DXVECTOR3(9.0f, 1.0f, 1.0f));
				ironBox[7]->SetSize(D3DXVECTOR3(ironBox[7]->GetSize().x * (ironBox[7]->GetScale().x - 2),
				ironBox[7]->GetSize().y * ironBox[7]->GetScale().y,
				ironBox[7]->GetSize().z * (ironBox[7]->GetScale().z)));
			}


			if (ironBox[8] == nullptr)
			{
				ironBox[8] = new IronBox({ -30.0f, 5.0f, 1385.0f });
				ironBox[8]->SetScale(D3DXVECTOR3(3.0f, 1.0f, 1.0f));
				ironBox[8]->SetSize(D3DXVECTOR3(ironBox[8]->GetSize().x * (ironBox[8]->GetScale().x - 0.6f),
				ironBox[8]->GetSize().y * ironBox[8]->GetScale().y,
				ironBox[8]->GetSize().z * (ironBox[8]->GetScale().z)));
			}

			if (ironBox[9] == nullptr)
			{
				ironBox[9] = new IronBox({ 30.0f, 5.0f, 1385.0f });
				ironBox[9]->SetScale(D3DXVECTOR3(3.0f, 1.0f, 1.0f));
				ironBox[9]->SetSize(D3DXVECTOR3(ironBox[9]->GetSize().x * (ironBox[9]->GetScale().x - 0.6f),
				ironBox[9]->GetSize().y * ironBox[9]->GetScale().y,
				ironBox[9]->GetSize().z * (ironBox[9]->GetScale().z)));
			}
		
			if (m_Switch[4] == nullptr)
				m_Switch[4] = new Red_Switch({ 0.0f, 0.1f, 1375.0f });

			if (ironBox[39] == nullptr)
				ironBox[39] = new IronBox({ 5.0f, 5.0f, 1437.0f });
			if (ironBox[40] == nullptr)
				ironBox[40] = new IronBox({ 5.0f, 5.0f, 1405.0f });
			if (ironBox[41] == nullptr)
				ironBox[41] = new IronBox({ 15.0f, 5.0f, 1405.0f });
			if (ironBox[42] == nullptr)
				ironBox[42] = new IronBox({ -35.0f, 5.0f, 1413.0f });
			if (ironBox[43] == nullptr)
				ironBox[43] = new IronBox({ -35.0f, 5.0f, 1427.0f });
			if (ironBox[44] == nullptr)
				ironBox[44] = new IronBox({ 40.0f, 5.0f, 1457.0f });
			if (ironBox[45] == nullptr)
				ironBox[45] = new IronBox({ 40.0f, 5.0f, 1447.0f });

			if (woodBox[5] == nullptr)
				woodBox[5] = new WoodBox({ -25.0f, 5.0f, 1435.0f });
			if (woodBox[6] == nullptr)
				woodBox[6] = new WoodBox({ -25.0f, 5.0f, 1425.0f });
			if (woodBox[7] == nullptr)
				woodBox[7] = new WoodBox({ 25.0f, 5.0f, 1445.0f });
			if (woodBox[8] == nullptr)
				woodBox[8] = new WoodBox({ 25.0f, 5.0f, 1435.0f });

			if (m_Switch[5] == nullptr)
				m_Switch[5] = new Yellow_Switch({ -13.0f, 0.1f, 1425.0f });
			if (m_Switch[6] == nullptr)
				m_Switch[6] = new Yellow_Switch({ 12.0f, 0.1f, 1445.0f });
			if (m_Switch[7] == nullptr)
				m_Switch[7] = new Yellow_Switch({ -3.0f, 0.1f, 1425.0f });
			if (m_Switch[8] == nullptr)
				m_Switch[8] = new Yellow_Switch({ 2.0f, 0.1f, 1445.0f });
		}
	}

	void DeleteCheckPoint_3(int stage) override
	{

		if (stage == 0)
		{
			for(int i = 0; i < 5; i++)
			{
				delete ironBox[i];
				ironBox[i] = nullptr;
			}
			
			
			delete ironBox[28];
			ironBox[28] = nullptr;
			delete ironBox[29];
			ironBox[29] = nullptr;

			for(int i = 0; i < 3; i++)
			{
				delete woodBox[i];
				woodBox[i] = nullptr;
			}

				delete m_Switch[0];
				m_Switch[0] = nullptr;
				delete m_Switch[2];
				m_Switch[2] = nullptr;
				delete m_Switch[3];
				m_Switch[3] = nullptr;

				delete m_Switch[1];
				m_Switch[1] = nullptr;
		}else
		if (stage == 1)
		{
				for(int i = 5; i < 10; i++)
				{
					delete ironBox[i];
					ironBox[i] = nullptr;
				}

					delete m_Switch[4];
					m_Switch[4] = nullptr;

				for(int i = 39; i < 46; i++)
				{
					delete ironBox[i];
					ironBox[i] = nullptr;
				}
				
				for(int i = 5; i < 9; i++)
				{
					delete woodBox[i];
					woodBox[i] = nullptr;
				}

				for (int i = 5; i < 9; i++)
				{
					delete m_Switch[i];
					m_Switch[i] = nullptr;
				}

		}
	}

	void SetUpCheckPoint_4(int stage) override
	{
		if (stage == 0)
		{
			if (block[11] == nullptr)
			{
				block[11] = new Block({ -25.0f, -5.0f, 1800.0f });
				block[11]->SetSpd({ 0.0f,0.0f,0.0f });
				block[11]->SetMaxFrame(210);
			}

			if (block[12] == nullptr)
			{
				block[12] = new Block({ -25.0f, -5.0f, 1830.0f });
				block[12]->SetSpd({ 0.0f,0.0f,0.0f });
				block[12]->SetMaxFrame(70);
			}

			if (block[13] == nullptr)
			{
				block[13] = new Block({ -25.0f, -5.0f, 1860.0f });
				block[13]->SetSpd({ 0.0f,0.0f,0.0f });
				block[13]->SetMaxFrame(70);
			}
		}else
		if (stage == 1)
		{
			if(block[14] == nullptr)
			{
				block[14] = new Block({ 25.0f, -5.0f, 1890.0f });
				block[14]->SetSpd({ 0.0f,0.0f,0.0f });
				block[14]->SetMaxFrame(210);
			}
			

			if (block[15] == nullptr)
			{
				block[15] = new Block({ 25.0f, -5.0f, 1920.0f });
				block[15]->SetSpd({ 0.0f,0.0f,0.0f });
				block[15]->SetMaxFrame(70);
			}


			if (block[16] == nullptr)
			{
				block[16] = new Block({ 25.0f, -5.0f, 1950.0f });
				block[16]->SetSpd({ 0.0f,0.0f,0.0f });
				block[16]->SetMaxFrame(70);
			}
		}else
		if (stage == 2)
		{
			if(block[17] == nullptr)
			{
				block[17] = new Block({ 0.0f, -5.0f, 1980.0f });
				block[17]->SetSpd({ 0.0f,0.0f,0.0f });
				block[17]->SetMaxFrame(210);
			}
			
			if (block[18] == nullptr)
			{
				block[18] = new Block({ 0.0f, -5.0f, 2010.0f });
				block[18]->SetSpd({ 0.0f,0.0f,0.0f });
				block[18]->SetMaxFrame(70);
			}
		}else
		if (stage == 3)
		{
			if(block[19] == nullptr)
			{
				block[19] = new Block({ -25.0f, -5.0f, 2040.0f });
				block[19]->SetSpd({ 0.0f,0.0f,0.0f });
				block[19]->SetMaxFrame(210);
			}
			
			if (block[20] == nullptr)
			{
				block[20] = new Block({ -25.0f, -5.0f, 2070.0f });
				block[20]->SetSpd({ 0.0f,0.0f,0.0f });
				block[20]->SetMaxFrame(70);
			}
		}else
		if (stage == 4)
		{
			if(block[21] == nullptr)
			{
				block[21] = new Block({ 25.0f, -5.0f, 2100.0f });
				block[21]->SetSpd({ 0.0f,0.0f,0.0f });
				block[21]->SetMaxFrame(210);
			}
		}else
		if (stage == 5)
		{
			if(block[22] == nullptr)
			{
				block[22] = new Block({ -25.0f, -5.0f, 2130.0f });
				block[22]->SetSpd({ 0.0f,0.0f,0.0f });
				block[22]->SetMaxFrame(210);
			}
		}else
		if (stage == 6)
		{
			if(block[23] == nullptr)
			{
				block[23] = new Block({ -25.0f, -5.0f, 2190.0f });
				block[23]->SetSpd({ 0.0f,0.0f,0.0f });
				block[23]->SetMaxFrame(210);
			}
		}else
		if (stage == 7)
		{
			if(block[24] == nullptr)
			{
				block[24] = new Block({ -25.0f, -5.0f, 2290.0f });
				block[24]->SetSpd({ 0.0f,0.0f,0.0f });
				block[24]->SetMaxFrame(210);
			}
		}else
		if (stage == 8)
		{
			if(block[25] == nullptr)
			{
				block[25] = new Block({ 25.0f, -5.0f, 2390.0f });
				block[25]->SetSpd({ 0.0f,0.0f,0.0f });
				block[25]->SetMaxFrame(210);
			}
		}else
		if (stage == 9)
		{
			if(block[26] == nullptr)
			{
				block[26] = new Block({ -25.0f, -5.0f, 2500.0f });
				block[26]->SetSpd({ -0.7f,0.0f,0.0f });
				block[26]->SetMaxFrame(210);
			}

			if (block[27] == nullptr)
			{
				block[27] = new Block({ -25.0f, -5.0f, 2530.0f });
				block[27]->SetSpd({ -0.7f,0.0f,0.0f });
				block[27]->SetMaxFrame(210);
			}
		}else
		if (stage == 10)
		{
			if(block[28] == nullptr)
			{
				block[28] = new Block({ -25.0f, -5.0f, 2630.0f });
				block[28]->SetSpd({ -0.7f,0.0f,0.0f });
				block[28]->SetMaxFrame(210);
			}

			if (block[29] == nullptr)
			{
				block[29] = new Block({ -25.0f, -5.0f, 2660.0f });
				block[29]->SetSpd({ -0.5f,0.0f,0.0f });
				block[29]->SetMaxFrame(210);
			}
		}else
		if (stage == 11)
		{
			if(block[30] == nullptr)
			{
				block[30] = new Block({ -25.0f, -5.0f, 2730.0f });
				block[30]->SetSpd({ -0.5f,0.0f,0.0f });
				block[30]->SetMaxFrame(210);
			}
		}
	}

	void DeleteCheckPoint_4(int stage) override
	{
			delete block[stage];
			block[stage] = nullptr;
	}
};

#endif//MAP_2_H_
