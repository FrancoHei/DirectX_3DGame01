//=============================================================================
//
// ポリゴン表示処理 [player.cpp]
// Author : 
//
//=============================================================================
#include "player.h"
#include "character.h"
#include "input.h"
#include "camera.h"
#include "light.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	VALUE_ROTATE	(D3DX_PI * 0.02f)			// 回転量

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//=============================================================================
// 初期化処理
//=============================================================================
Player::Player(Character* character_): character(character_)
{
}

//=============================================================================
// 更新処理
//=============================================================================
void Player::Update(Map* map)
{
	bool isJumpKey  = GetKeyboardTrigger(DIK_X);
	bool isLeftKey  = GetKeyboardPress(DIK_LEFT);
	bool isRightKey = GetKeyboardPress(DIK_RIGHT);
	bool isFrontKey = GetKeyboardPress(DIK_UP);
	bool isBackKey  = GetKeyboardPress(DIK_DOWN);
	bool isRushKey  = GetKeyboardPress(DIK_Z);
	character->CheckSpd(isLeftKey, isRightKey, isFrontKey, isBackKey, isRushKey, isJumpKey);
	PlayerJumpController(isLeftKey, isRightKey, isFrontKey, isBackKey, isRushKey, isJumpKey);
	PlayerWalkController(isLeftKey, isRightKey, isFrontKey, isBackKey, isRushKey, isJumpKey);
	PlayerRushController(isLeftKey, isRightKey, isFrontKey, isBackKey, isRushKey, isJumpKey);

	character->Update(map);
}

void Player::PlayerWalkController(bool isLeftKey, bool isRightKey, bool isFrontKey, bool isBackKey, bool isRushKey, bool isJumpKey)
{
	if (isLeftKey && !isRushKey)
	{
		character->Walk(LEFT);
	}

	if (isRightKey && !isRushKey)
	{
		character->Walk(RIGHT);
	}

	if (isFrontKey && !isRushKey)
	{
		character->Walk(FRONT);
	}

	if (isBackKey && !isRushKey)
	{
		character->Walk(BACK);
	}

}

void Player::PlayerRushController(bool isLeftKey, bool isRightKey, bool isFrontKey, bool isBackKey, bool isRushKey, bool isJumpKey)
{

	if (isLeftKey && isRushKey && character->GetStamina() > 0)
	{
		character->SetStamina(character->GetStamina()-1);
		character->Rush(LEFT);
	}

	if (isRightKey && isRushKey && character->GetStamina() > 0)
	{
		character->SetStamina(character->GetStamina() - 1);
		character->Rush(RIGHT);
	}

	if (isFrontKey && isRushKey && character->GetStamina() > 0)
	{
		character->SetStamina(character->GetStamina() - 1);
		character->Rush(FRONT);
	}

	if (isBackKey && isRushKey && character->GetStamina() > 0)
	{
		character->SetStamina(character->GetStamina() - 1);
		character->Rush(BACK);
	}

	if (character->GetStamina() <= 0)
	{
		character->SetStamina(0);
	}

	if (!isRushKey)
	{
		character->SetStamina(character->GetStamina() + 1);
		if (character->GetStamina() >= character->GetMaxStamina())
		{
			character->SetStamina(character->GetMaxStamina());
		}
		character->SetIsRushing(false);
	}
}

void Player::PlayerJumpController(bool isLeftKey, bool isRightKey, bool isFrontKey, bool isBackKey, bool isRushKey, bool isJumpKey)
{
	if (isJumpKey && !character->GetIsFJump() && !character->GetIsSJump())
	{
		character->Jump(FIRSTJUMP, FRONT);
	}else
	if (isJumpKey && character->GetIsFJump() && !character->GetIsSJump())
	{
		if (isFrontKey && !isLeftKey && !isRightKey && !isBackKey)
		{
			character->Jump(SECONDJUMP, FRONT);
		}else
		if (isFrontKey && isLeftKey && !isRightKey && !isBackKey)
		{
			character->Jump(SECONDJUMP, FRONTLEFT);
		}else
		if (isFrontKey && !isLeftKey && isRightKey && !isBackKey)
		{
			character->Jump(SECONDJUMP, FRONTRIGHT);
		}else
		if (!isFrontKey && isLeftKey && !isRightKey && !isBackKey)
		{
			character->Jump(SECONDJUMP, LEFT);
		}else
		if (!isFrontKey && isLeftKey && !isRightKey && isBackKey)
		{
			character->Jump(SECONDJUMP, BACKLEFT);
		}else
		if (!isFrontKey && !isLeftKey && isRightKey && isBackKey)
		{
			character->Jump(SECONDJUMP, BACKRIGHT);
		}else
		if (!isFrontKey && !isLeftKey && isRightKey && !isBackKey)
		{
			character->Jump(SECONDJUMP, RIGHT);
		}else
		if (!isFrontKey && !isLeftKey && !isRightKey && isBackKey)
		{
			character->Jump(SECONDJUMP, BACK);
		}else
		if (!isFrontKey && !isLeftKey && !isRightKey && !isBackKey)
		{
			character->Jump(SECONDJUMP, UP);
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void Player::Draw(void)
{
	character->Draw();
}

Character* Player::GetCharacter()
{
	return character;
}