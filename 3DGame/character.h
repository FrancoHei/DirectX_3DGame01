#ifndef CHARACTER_H_
#define CHARACTER_H_

#include "renderer.h"
#include "model.h"

enum CHARACTER
{
	CHARACTER01,
	CHARACTER02,
	CHARACTER03,
	MAXCHARACTER
};

enum DIRECTION
{
	FRONT,
	FRONTRIGHT,
	FRONTLEFT,
	RIGHT,
	LEFT,
	BACK,
	BACKRIGHT,
	BACKLEFT,
	UP
};

enum JUMP
{
	FIRSTJUMP,
	SECONDJUMP,
};

class Shadow;
class Camera;
class Map;
class WoodBox;

class Character
{
private:
	CHARACTER		character;
	D3DXVECTOR3		pos ;	    // 位置
	D3DXVECTOR3		oldPos;	    // 位置
	D3DXVECTOR3		rot;		// 向き(回転)
	D3DXVECTOR3		scl;		// 大きさ(スケール)

	Shadow*         shadow;		// 影の識別子

	D3DXVECTOR3     size;		// 当たり判定用サイズ

	D3DXMATRIX		mtxWorld;	// ワールドマトリックス
	DX11_MODEL		g_Model;

	int				jumpTimer    = 0;
	int				reboundTimer = 0;
private:
	D3DXVECTOR3		spd		= {0.0f,0.0f,0.0f};			// 移動スピード
	float			acc;		
	float			max_Vel;
	float			power;
	float			maxStamina;
	float 		    stamina;
	float			maxHp;
	float		    hp;
private:
	bool		    isOnFloor = false;
	bool			isWalking = false;
	bool			isRushing = false;
	bool			isFJump   = false;
	bool			isSJump   = false;
	bool			isDemaged = false;
	bool            canJump   = true;
protected:
	int jumpSE;
public:
	 Character(CHARACTER character_, char* model, float acc_, float max_Vel_, float power_, float stamina_, float hp_);
	 ~Character();

	void Update(Map* map);
	void Draw();

	void Walk(DIRECTION direction);
	void Rush(DIRECTION direction);
	void Fall();
	void Jump(JUMP jumpType, DIRECTION direction);
	void CheckOverSpeed();
	bool CheckOnFloor(Map* map);
	bool CheckWallCollision(Map* map);
	bool CheckBlockCollision(Map* map);
	bool CheckRockCollision(Map* map);
	bool CheckTreasureCollision(Map* map);
	bool CheckIronBoxCollision(Map* map);
	bool CheckWoodBoxCollision(Map* map);
	bool CheckWoodBoxIronBoxCollision(WoodBox* woodBox, Map* map);
	void FJump(Map* map);
	void SJump(Map* map);
	void Rebound(Map* map);
	void SetSpd(D3DXVECTOR3 spd_)	  { spd = spd_; }
	D3DXVECTOR3 GetSpd()			  { return spd; }
	void CheckSpd(bool isLeftKey, bool isRightKey, bool isFrontKey, bool isBackKey, bool isRushKey, bool isJumpKey);
	void ResetState();
	D3DXVECTOR3 GetPos()			  { return pos; }
	D3DXVECTOR3 GetSize()			  { return size;}
	void SetPos(D3DXVECTOR3 pos_)	  { pos = pos_; }
	void SetIsRushing(bool isRushing_){ isRushing = isRushing_;}

	float  GetMaxHp()				  { return maxHp; }
	float  GetHp()					  { return hp; }
	float  GetMaxStamina()			  { return maxStamina; }
	float  GetStamina()				  { return stamina; }
	void SetStamina(float stamina_)	  { stamina = stamina_; }
	bool GetIsFJump()				  { return isFJump; }
	bool GetIsSJump()				  { return isSJump; }
	void SetCanJump(bool canJump_)	  { canJump = canJump_; }
	bool GetCanJump()				  { return canJump; }
	bool GetOnFloor()				  { return isOnFloor;}
};

#endif//CHARACTER_H_
