#ifndef GAME_H_
#define GAME_H_

#include "stage.h"

class Camera;
class UI;
class Game
{
private:
	UI*     ui;
	Stage*  stage;
	Camera* camera;
	int     bgmNo;
public:
		 Game  (STAGE stage_, CHARACTER character);
		 ~Game(void);
	void Update(void);
	void Draw  (void);
};

#endif//GAME_H_