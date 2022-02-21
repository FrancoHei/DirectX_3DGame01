#include "stage.h"
#include "classResource.h"
#include "map.h"
#include "character.h"
#include "player.h"
#include "guide.h"

Stage::Stage(STAGE stage_, MAP map_, CHARACTER character) : stage(stage_)
{
	player		 = new Player(GetCharacter(character));
	map			 = GetMap(map_);
	guideTexture = new Guide();
}

Stage::~Stage()
{
	delete map;
	delete player;
	delete guideTexture;
}

void Stage::Update(Camera* cam)
{
	map	  ->Update(player->GetCharacter(), cam);
	player->Update(map);
	CheckGuide(player->GetCharacter(), map);
	StageAction(player->GetCharacter(), map, cam);
	if (guideTexture)
		guideTexture->Update();
}

void Stage::Draw()
{
	if (map)
		map	  ->Draw();
	if (player)
		player->Draw();
	if (guideTexture)
		guideTexture->Draw(guide);
}
