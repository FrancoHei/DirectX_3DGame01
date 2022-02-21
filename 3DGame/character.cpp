#include "character.h"
#include "main.h"
#include "input.h"
#include "camera.h"
#include "player.h"
#include "texture.h"
#include "model.h"
#include "light.h"
#include "shadow.h"
#include "map.h"
#include "collision.h"
#include "field.h"
#include "fade.h"
#include "rock.h"
#include "treasure.h"
#include "sound.h"

#define WALKSPD 0.5f
#define MAX_JUMP        (35.0f)
#define MAX_REBOUND		(20.0f)

Character::Character(CHARACTER character_, char* model, float acc_, float max_Vel_, float power_, float stamina_, float hp_):
					 acc(acc_), max_Vel(max_Vel_), power(power_),stamina(stamina_), hp(hp_), maxStamina(stamina_), maxHp(hp_)
{
	// 位置・回転・スケールの初期設定
	pos = D3DXVECTOR3(0.0f, 20.0f, 0.0f);
	rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	scl = D3DXVECTOR3(0.2f, 0.2f, 0.2f);
	//当たり判定用サイズの初期設定
	size = D3DXVECTOR3(8.0f, 8.0f, 8.0f);

	pos.z = 1000.0f;
//	pos.z = 1500.0f;

	//objモデルの読み込み
	//LoadModel((char*)"data/MODEL/ball.obj", &g_Model);
	LoadModel(model, &g_Model);
	//影の設定

	// 並行光源の設定（世界を照らす光）
	LIGHT* pLight = NULL;
	pLight = GetLightData(0);
	pLight->Direction = D3DXVECTOR4(1.0f, -1.0f, 1.0f, 0.0f);// 光の向き
	pLight->Diffuse = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);	// 光の色
	pLight->Type = LIGHT_TYPE_DIRECTIONAL;					// 並行光源
	pLight->Enable = true;									// このライトをON
	SetLightData(0, pLight);									// これで設定している

	// 点光源の設定
	pLight = GetLightData(1);
	pLight->Position = D3DXVECTOR4(0.0f, 500.0f, 0.0f, 0.0f);
	pLight->Direction = D3DXVECTOR4(1.0f, -1.0f, 1.0f, 0.0f);// 光の向き
	pLight->Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// 光の色
	pLight->Attenuation = 1000.0f;							// 減衰距離
	pLight->Type = LIGHT_TYPE_POINT;						// 並行光源
	pLight->Enable = true;									// このライトをON
	SetLightData(1, pLight);								// これで設定している
}

Character::~Character()
{
	delete shadow;
	//objモデルの解放
	UnloadModel(&g_Model);
}

void Character::Update(Map* map)
{
	oldPos = pos;
	CheckOverSpeed();
	CheckRockCollision(map);
	CheckTreasureCollision(map);
	CheckIronBoxCollision(map);
	CheckWoodBoxCollision(map);

	if(hp <= 0)
	{
		SceneTransition(SCENE_GAMEOVER);
	}

	if(isDemaged)
	{
		Rebound(map);
	}

	if(isFJump)
	{
		FJump(map);
	}else
	if(isSJump)
	{
		SJump(map);
	}

	
	CheckWallCollision(map);

	if(pos.z <= -40.0f)
	{
		pos.z = -40.0f;
	}

	if (!isFJump && !isSJump && !isDemaged)
	{
		CheckOnFloor(map);
		Fall();
		pos += spd;
	}
	
	//rot.y = D3DX_PI/-2.0f;
	//shadow->SetPos({ pos.x,0.0f,pos.z });

}

void Character::Draw()
{
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	// ワールドマトリックスの初期化（単位行列を作る関数）
	D3DXMatrixIdentity(&mtxWorld);

	// スケールを反映
	D3DXMatrixScaling(&mtxScl, scl.x, scl.y, scl.z);

	//第1引数 ＝          第2引数      ＊    第3引数
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScl);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

	// 移動を反映
	D3DXMatrixTranslation(&mtxTranslate, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);

	// ワールドマトリックスの設定
	SetWorldMatrix(&mtxWorld);

	//カリングなし
	SetCullingMode(CULL_MODE_NONE);

	//objモデルの描画
	DrawModel(&g_Model);

	//カリングを元に戻す
	SetCullingMode(CULL_MODE_BACK);
	//shadow->Draw();
}

void Character::Walk(DIRECTION direction)
{
	if(isOnFloor && !isSJump && !isFJump && !isDemaged)
	{
		isWalking = true;
		isRushing = false;
		switch (direction)
		{
		case FRONT:
			spd += { 0.0f, 0.0f, WALKSPD };
			break;
		case RIGHT:
			spd += { WALKSPD, 0.0f, 0.0f };
			break;
		case LEFT:
			spd += { -WALKSPD, 0.0f, 0.0f };
			break;
		case BACK:
			spd += { 0.0f, 0.0f, -WALKSPD };
			break;
		default:
			break;
		}
	}
}

void Character::Rush(DIRECTION direction)
{
	if (isOnFloor && !isSJump && !isFJump && !isDemaged)
	{
		isRushing = true;
		isWalking = false;
		switch (direction)
		{
		case FRONT:
			spd += { 0.0f, 0.0f, acc };
			break;
		case RIGHT:
			spd += { acc, 0.0f, 0.0f };
			break;
		case LEFT:
			spd += { -acc, 0.0f, 0.0f };
			break;
		case BACK:
			spd += { 0.0f, 0.0f, -acc };
			break;
		default:
			break;
		}
	}
	
	
}

void Character::Fall()
{
	if (!isOnFloor)
	{
		pos.y -= 1;
	}
}

void Character::Jump(JUMP jumpType, DIRECTION direction)
{
	if(canJump)
	{
		switch (jumpType)
		{
		case FIRSTJUMP:
			if (!isDemaged && isOnFloor)
			{
				SetVolume(jumpSE, 1.0f);
				PlaySound(jumpSE, 0);
				jumpTimer = 0;
				isFJump = true;
				spd.y += power;
			}
		break;
		case SECONDJUMP:
			if (!isDemaged)
			{
				jumpTimer = 0;
				isFJump = false;
				isSJump = true;
				spd = { 0.0f,0.0f,0.0f };
				if(direction == FRONT)
				{
					spd = { 0.0f, 0.0f, WALKSPD };
				}else
				if(direction == BACK)
				{
					spd = { 0.0f, 0.0f, -WALKSPD };
				}else
				if(direction == RIGHT)
				{
					spd = { WALKSPD, 0.0f, 0.0f };
				}else
				if(direction == LEFT)
				{
					spd = { -WALKSPD, 0.0f, 0.0f };
				}else
				if(direction == FRONTLEFT)
				{
					spd = { -WALKSPD, 0.0f, WALKSPD };
				}else
				if(direction == FRONTRIGHT)
				{
					spd = { WALKSPD, 0.0f, WALKSPD };
				}else
				if(direction == BACKLEFT)
				{
					spd = { -WALKSPD, 0.0f, -WALKSPD };
				}else
				if(direction == BACKRIGHT)
				{
					spd = { WALKSPD, 0.0f, -WALKSPD };
				}else
				if(direction == UP)
				{
					spd = { 0.0f, 0.0f, 0.0f };
				}
				spd.y += power * 0.7f;
			}
		break;
	default:
		break;
		}
	}
}


void Character::CheckOverSpeed()
{
	if(isRushing)
	{
		if (spd.x >= max_Vel)
		{
			spd.x = max_Vel;
		}else
		if (spd.x <= -max_Vel)
		{
			spd.x = -max_Vel;
		}

		if (spd.z >= max_Vel)
		{
			spd.z = max_Vel;
		}else
		if (spd.z <= -max_Vel)
		{
			spd.z = -max_Vel;
		}
	}else
	if(isWalking)
	{
		if (spd.x >= WALKSPD)
		{
			spd.x = WALKSPD;
		}else
		if (spd.x <= -WALKSPD)
		{
			spd.x = -WALKSPD;
		}

		if (spd.z >= WALKSPD)
		{
			spd.z = WALKSPD;
		}

		if (spd.z <= -WALKSPD)
		{
			spd.z = -WALKSPD;
		}
	}
}

bool Character::CheckOnFloor(Map* map)
{
	bool collision = false;
	for(int i = 0; i < MAXFIELD; i++)
	{
		if((map->GetField(i) && CollisionBB(pos,map->GetField(i)->GetPos(),size,map->GetField(i)->GetSize())) ||
			CheckBlockCollision(map))
		{
			if(map->GetField(i)->GetField() == FIELD_FIRE)
			{
				SceneTransition(SCENE_GAMEOVER);
			}else
			{
				collision = true;
				isOnFloor = true;
			}

			break;
		}
	}

	if(!collision)
	{
		isOnFloor = false;
	}

	return collision;
}

bool Character::CheckWallCollision(Map* map)
{
	bool collision = false;
	for (int i = 0; i < MAXWALL; i++)
	{
		if (map->GetWall(i) && CollisionBB(pos, map->GetWall(i)->GetPos(), size, map->GetWall(i)->GetSize()))
		{
			pos = oldPos;
			collision = true;
			if(map->GetWall(i)->GetWallDirection() == WALL_LEFT)
			{
				if (isFJump || isSJump)
				{
					if (spd.x < 0.0f)
					{
						spd.x = 0.0f;
						spd.z = 0.0f;
						spd.y = 0.0f;
						Fall();
					}
				}else
				{
					if (spd.x < 0.0f)
					{
						spd.x = 0.0f;
					}
				}
			}else
			if(map->GetWall(i)->GetWallDirection() == WALL_RIGHT)
			{
				if (isFJump || isSJump)
				{
					if (spd.x > 0.0f)
					{
						spd.x = 0.0f;
						spd.z = 0.0f;
						spd.y = 0.0f;
						Fall();
					}
				}else
				{
					if (spd.x > 0.0f)
					{
						spd.x = 0.0f;
					}
				}
			}
			break;
		}
	}

	return collision;
}

bool Character::CheckBlockCollision(Map* map)
{
	bool collision = false;
	for (int i = 0; i < MAXBLOCK; i++)
	{
		if (map->GetBlock(i) && CollisionBBCharacterDownBlockUp(pos, map->GetBlock(i)->GetPos(),
																size, map->GetBlock(i)->GetSize()))
		{
			collision = true;
			if(!isFJump && !isSJump)
				pos.y = map->GetBlock(i)->GetPos().y + map->GetBlock(i)->GetSize().y/2.0f + size.y/2.0f;
			pos += map->GetBlock(i)->GetSpd();
			isOnFloor = true;
			break;
		}
	}

	if (!collision)
	{
		isOnFloor = false;
	}

	return collision;
}

bool Character::CheckRockCollision(Map* map)
{
	bool collision = false;
	for (int i = 0; i < MAXROCK; i++)
	{
		if ((map->GetRock(i) && CollisionBB(pos, map->GetRock(i)->GetPos(), size, map->GetRock(i)->GetSize()) && !isDemaged))
		{
			collision = true;
			isDemaged = true;
			hp -= map->GetRock(i)->GetAttack();
			spd = D3DXVECTOR3(0.0f, 0.1f, -0.1f);
			break;
		}
	}

	return collision;
}

bool Character::CheckTreasureCollision(Map* map)
{
	bool collision = false;

	if ((map->GetTreasure() && CollisionBB(pos, map->GetTreasure()->GetPos(), size, map->GetTreasure()->GetSize()) && !isDemaged))
	{
		SceneTransition(SCENE_GAMECLEAR);
	}

	return collision;
}

bool Character::CheckIronBoxCollision(Map* map)
{
	bool collision = false;
	for (int i = 0; i < MAXIRONBOX; i++)
	{
		if ((map->GetIronBox(i) && CollisionBB(pos, map->GetIronBox(i)->GetPos(), size, map->GetIronBox(i)->GetSize())))
		{
			collision = true;
			if(pos.x > map->GetIronBox(i)->GetPos().x + map->GetIronBox(i)->GetSize().x * 0.5f &&	
			   pos.z - size.z * 0.4f <= map->GetIronBox(i)->GetPos().z + map->GetIronBox(i)->GetSize().z * 0.5f &&
			   pos.z + size.z * 0.4f >= map->GetIronBox(i)->GetPos().z - map->GetIronBox(i)->GetSize().z * 0.5f)
			{
				if(spd.x < 0)
				{
					pos = oldPos;
					spd.x = 0.0f;
				}
			}

			if(pos.x < map->GetIronBox(i)->GetPos().x - map->GetIronBox(i)->GetSize().x * 0.5f &&
			   pos.z - size.z * 0.4f <= map->GetIronBox(i)->GetPos().z + map->GetIronBox(i)->GetSize().z * 0.5f &&
			   pos.z + size.z * 0.4f >= map->GetIronBox(i)->GetPos().z - map->GetIronBox(i)->GetSize().z * 0.5f)
			{
				if(spd.x > 0)
				{
					pos = oldPos;
					spd.x = 0.0f;
				}
			}

			if(pos.z < map->GetIronBox(i)->GetPos().z - map->GetIronBox(i)->GetSize().z * 0.5f &&
			   pos.x + size.x * 0.4f >= map->GetIronBox(i)->GetPos().x - map->GetIronBox(i)->GetSize().x * 0.5f &&
			   pos.x - size.x * 0.4f <= map->GetIronBox(i)->GetPos().x + map->GetIronBox(i)->GetSize().x * 0.5f)
			{
				if(spd.z > 0)
				{
					pos = oldPos;
					spd.z = 0.0f;
				}
			}

			if(pos.z > map->GetIronBox(i)->GetPos().z + map->GetIronBox(i)->GetSize().z * 0.5f &&
				pos.x + size.x * 0.4f >= map->GetIronBox(i)->GetPos().x - map->GetIronBox(i)->GetSize().x * 0.5f &&
				pos.x - size.x * 0.4f <= map->GetIronBox(i)->GetPos().x + map->GetIronBox(i)->GetSize().x * 0.5f)
			{
				if(spd.z < 0)
				{
					pos = oldPos;
					spd.z = 0.0f;
				}
			}
		}
	}

	return collision;
}

bool Character::CheckWoodBoxCollision(Map* map)
{
	bool collision = false;
	for (int i = 0; i < MAXWOODBOX; i++)
	{
		if ((map->GetWoodBox(i) && CollisionBB(pos, map->GetWoodBox(i)->GetPos(), size, map->GetWoodBox(i)->GetSize())))
		{
			collision = true;
			if (pos.x > map->GetWoodBox(i)->GetPos().x + map->GetWoodBox(i)->GetSize().x * 0.5f &&
				pos.z - size.z * 0.2f < map->GetWoodBox(i)->GetPos().z + map->GetWoodBox(i)->GetSize().z * 0.5f &&
				pos.z + size.z * 0.2f > map->GetWoodBox(i)->GetPos().z - map->GetWoodBox(i)->GetSize().z * 0.5f)
			{
				if (spd.x < 0)
				{
					map->GetWoodBox(i)->SetPos(map->GetWoodBox(i)->GetPos() + D3DXVECTOR3(spd.x, 0.0f, 0.0f));
					if (CheckWoodBoxIronBoxCollision(map->GetWoodBox(i), map))
					{
						map->GetWoodBox(i)->SetPos(map->GetWoodBox(i)->GetPos() - D3DXVECTOR3(spd.x, 0.0f, 0.0f));
						pos = oldPos;
						spd.x = 0.0f;
					}
				}
			}

			if (pos.x  < map->GetWoodBox(i)->GetPos().x - map->GetWoodBox(i)->GetSize().x * 0.5f &&
				pos.z - size.z * 0.2f < map->GetWoodBox(i)->GetPos().z + map->GetWoodBox(i)->GetSize().z * 0.5f &&
				pos.z + size.z * 0.2f > map->GetWoodBox(i)->GetPos().z - map->GetWoodBox(i)->GetSize().z * 0.5f)
			{
				if (spd.x > 0)
				{
					map->GetWoodBox(i)->SetPos(map->GetWoodBox(i)->GetPos() + D3DXVECTOR3(spd.x, 0.0f, 0.0f));
					if (CheckWoodBoxIronBoxCollision(map->GetWoodBox(i), map))
					{
						map->GetWoodBox(i)->SetPos(map->GetWoodBox(i)->GetPos() - D3DXVECTOR3(spd.x, 0.0f, 0.0f));
						pos = oldPos;
						spd.x = 0.0f;
					}
				}
			}

			if (pos.z  < map->GetWoodBox(i)->GetPos().z - map->GetWoodBox(i)->GetSize().z * 0.5f &&
				pos.x + size.x * 0.2f > map->GetWoodBox(i)->GetPos().x - map->GetWoodBox(i)->GetSize().x * 0.5f &&
				pos.x - size.x * 0.2f < map->GetWoodBox(i)->GetPos().x + map->GetWoodBox(i)->GetSize().x * 0.5f)
			{
				if (spd.z > 0)
				{
					map->GetWoodBox(i)->SetPos(map->GetWoodBox(i)->GetPos() + D3DXVECTOR3(0.0f, 0.0f, spd.z));
					if (CheckWoodBoxIronBoxCollision(map->GetWoodBox(i), map))
					{
						map->GetWoodBox(i)->SetPos(map->GetWoodBox(i)->GetPos() - D3DXVECTOR3(0.0f, 0.0f, spd.z));
						pos = oldPos;
						spd.z = 0.0f;
					}
				}
			}

			if (pos.z > map->GetWoodBox(i)->GetPos().z + map->GetWoodBox(i)->GetSize().z * 0.5f &&
				pos.x + size.x * 0.2f > map->GetWoodBox(i)->GetPos().x - map->GetWoodBox(i)->GetSize().x * 0.5f &&
				pos.x - size.x * 0.2f < map->GetWoodBox(i)->GetPos().x + map->GetWoodBox(i)->GetSize().x * 0.5f)
			{
				if (spd.z < 0)
				{
					map->GetWoodBox(i)->SetPos(map->GetWoodBox(i)->GetPos() + D3DXVECTOR3(0.0f, 0.0f, spd.z));
					if (CheckWoodBoxIronBoxCollision(map->GetWoodBox(i), map))
					{
						map->GetWoodBox(i)->SetPos(map->GetWoodBox(i)->GetPos() - D3DXVECTOR3(0.0f, 0.0f, spd.z));
						pos = oldPos;
						spd.z = 0.0f;
					}
				}
			}

		}
	}
	return collision;
}

bool Character::CheckWoodBoxIronBoxCollision(WoodBox* woodBox, Map* map)
{
	bool collision = false;
	for (int i = 0; i < MAXIRONBOX; i++)
	{
		if ((map->GetIronBox(i) && CollisionBB(woodBox->GetPos(), map->GetIronBox(i)->GetPos(), woodBox->GetSize() - D3DXVECTOR3(5.0f,5.0f,5.0f), map->GetIronBox(i)->GetSize() - D3DXVECTOR3(5.0f, 5.0f, 5.0f))))
		{
			return true;
		}
	}

	for (int i = 0; i < MAXWOODBOX; i++)
	{
		if ((map->GetWoodBox(i) && map->GetWoodBox(i) != woodBox && CollisionBB(woodBox->GetPos(), map->GetWoodBox(i)->GetPos(), woodBox->GetSize() - D3DXVECTOR3(5.0f, 5.0f, 5.0f), map->GetWoodBox(i)->GetSize() - D3DXVECTOR3(5.0f, 5.0f, 5.0f))))
		{
			return true;
		}
	}

	return false;
}

void Character::FJump(Map* map)
{
	jumpTimer++;
	if (jumpTimer <= MAX_JUMP)
	{
		pos += spd;
	}

	if(jumpTimer > MAX_JUMP)
	{
		pos.x += spd.x;
		pos.z += spd.z;
		Fall();
		spd.y = 0.0f;

	}

	if (CheckOnFloor(map) || CheckBlockCollision(map) || CheckRockCollision(map))
	{
		jumpTimer = 0;
		isFJump   = false;
	}
}

void Character::SJump(Map* map)
{
	jumpTimer++;
	if (jumpTimer <= MAX_JUMP)
	{
		pos += spd;
	}

	if (jumpTimer > MAX_JUMP)
	{
		pos.x += spd.x;
		pos.z += spd.z;
		Fall();
		spd.y = 0.0f;
	}

	if (CheckOnFloor(map) || CheckBlockCollision(map) || CheckRockCollision(map))
	{
		pos = oldPos;
		jumpTimer = 0;
		isSJump = false;
	}
}

void Character::Rebound(Map* map)
{
	reboundTimer++;
	if (reboundTimer <= MAX_REBOUND)
	{
		pos += spd;
	}

	if (reboundTimer > MAX_REBOUND)
	{
		pos.x += spd.x;
		pos.z += spd.z;
		Fall();
		spd.y = 0.0f;

	}

	if (CheckOnFloor(map) || CheckBlockCollision(map) || CheckWallCollision(map))
	{
		reboundTimer = 0;
		isDemaged = false;
	}
}

void Character::CheckSpd(bool isLeftKey, bool isRightKey, bool isFrontKey, bool isBackKey, bool isRushKey, bool isJumpKey)
{
	if (isLeftKey && !isRightKey && !isFrontKey && !isBackKey && !isFJump && !isSJump && !isDemaged)
	{
		spd = { spd.x,0.0f,0.0f };
	}

	if (!isLeftKey && isRightKey && !isFrontKey && !isBackKey && !isFJump && !isSJump && !isDemaged)
	{
		spd = { spd.x,0.0f,0.0f };
	}

	if (!isLeftKey && !isRightKey && isFrontKey && !isBackKey && !isFJump && !isSJump && !isDemaged)
	{
		spd = { 0.0f,0.0f, spd.z };
	}

	if (!isLeftKey && !isRightKey && !isFrontKey && isBackKey && !isFJump && !isSJump && !isDemaged)
	{
		spd = { 0.0f,0.0f, spd.z };
	}


	if (!isLeftKey && !isRightKey && !isFrontKey && !isBackKey && !isFJump && !isSJump && !isDemaged)
	{
		spd = { 0.0f,0.0f,0.0f };
		ResetState();
	}
}

void Character::ResetState()
{
	isWalking = false;
	isRushing = false;
}
