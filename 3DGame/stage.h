#ifndef STAGE_H_
#define STAGE_H_

#include "map.h"
#include "character.h"
#include "player.h"
#include "camera.h"

#define MAXCHECKPOINT 5

enum STAGE
{
	STAGE01,
	STAGE02,
	STAGE03
};

class Guide;

class Stage
{
private:
	STAGE	stage;
	Map*	map;
	Player* player;
	Guide*  guideTexture;
protected: 
	int guide    = 0;
	int min      = 0;
	int sec      = 0;
	int milliSec = 0;
public:
	Stage(STAGE stage_, MAP map_, CHARACTER character);
	~Stage();

	void Update(Camera* cam);
	void Draw();
	Player* GetPlayer() { return player; }
	int GetSec()		{ return sec;}
	int GetMilliSec()	{ return milliSec;}
	int GetMin()		{ return min; }

	virtual void CheckGuide(Character* character, Map* map) = 0;
	virtual void StageAction(Character* character, Map* map, Camera* cam) = 0;

};

#endif STAGE_H_
