#include "map.h"

Map::~Map()
{
	for (int i = 0; i < MAXFIELD; i++)
	{
		if (field[i])
			delete field[i];
	}

	for (int i = 0; i < MAXWALL; i++)
	{
		if (wall[i])
			delete wall[i];
	}

	for (int i = 0; i < MAXBLOCK; i++)
	{
		if (block[i])
			delete block[i];
	}

	for (int i = 0; i < MAXARROW; i++)
	{
		if (arrow[i])
			delete arrow[i];
	}

	for (int i = 0; i < MAXROCK; i++)
	{
		if (rock[i])
			delete rock[i];
	}

	for (int i = 0; i < MAXSEMAPHORE; i++)
	{
		if (semaphore[i])
			delete semaphore[i];
	}

	for (int i = 0; i < MAXIRONBOX; i++)
	{
		if(ironBox[i])
			delete ironBox[i];
	}

	for (int i = 0; i < MAXWOODBOX; i++)
	{
		if(woodBox[i])
			delete woodBox[i];
	}

	for (int i = 0; i < MAXSWITCH; i++)
	{
		if(m_Switch[i])
			delete m_Switch[i];
	}
}
