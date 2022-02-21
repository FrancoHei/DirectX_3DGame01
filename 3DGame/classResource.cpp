#include "classResource.h"

#include "map.h"
#include "map_1.h"
#include "map_2.h"
#include "map_3.h"

#include "stage.h"
#include "stage_1.h"
#include "stage_2.h"
#include "stage_3.h"

#include "character.h"
#include "character_1.h"
#include "character_2.h"
#include "character_3.h"

Map* GetMap(MAP map_)
{
	switch(map_)
	{
	case MAP01:
		return new Map_1;
		break;
	case MAP02:
		return new Map_2;
		break;
	case MAP03:
		return new Map_3;
		break;
	default:
		return nullptr;
		break;
	}
}

Stage* GetStage(STAGE stage_, CHARACTER character)
{
	switch(stage_)
	{
	case STAGE01:
		return new Stage_1(CHARACTER01);
		break;
	case STAGE02:
		return new Stage_2(character);
		break;
	case STAGE03:
		return new Stage_3(character);
		break;
	default:
		return nullptr;
		break;
	}
}

Character* GetCharacter(CHARACTER character_)
{
	switch(character_)
	{
	case CHARACTER01:
		return new Character_1;
		break;
	case CHARACTER02:
		return new Character_2;
		break;
	case CHARACTER03:
		return new Character_3;
		break;
	default:
		return nullptr;
		break;
	}
}