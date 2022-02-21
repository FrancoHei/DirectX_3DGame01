#ifndef CLASSRESOURCE_H_
#define CLASSRESOURCE_H_

#include "map.h"
#include "stage.h"
#include "character.h"

Map* GetMap(MAP map_);
Stage* GetStage(STAGE stage_, CHARACTER character);
Character* GetCharacter(CHARACTER character_);

#endif//CLASSRESOURCE_H_
