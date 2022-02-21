//=============================================================================
//
// 地面処理 [player.h]
// Author : 
//
//=============================================================================
#pragma once

#include <d3dx9.h>
#include "renderer.h"
#include "model.h"
#include "character.h"

class Character;
class Camera;
class Map;
//*****************************************************************************
// マクロ定義
//*****************************************************************************

class Player
{
private: 
	Character* character;
public:
	 Player(Character* character_);
	~Player(void)
	 {
		delete character;
 	 }
	 void Update(Map* map);
	 void Draw(void);
	 void PlayerWalkController(bool isLeftKey, bool isRightKey, bool isFrontKey, bool isBackKey, bool isRushKey, bool isJumpKey);
	 void PlayerRushController(bool isLeftKey, bool isRightKey, bool isFrontKey, bool isBackKey, bool isRushKey, bool isJumpKey);
	 void PlayerJumpController(bool isLeftKey, bool isRightKey, bool isFrontKey, bool isBackKey, bool isRushKey, bool isJumpKey);
	 Character* GetCharacter();
};
