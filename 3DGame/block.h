#ifndef BLOCK_H_
#define BLOCK_H_

#include "renderer.h"
#include "model.h"

class Map;

class Block
{
private:
	D3DXVECTOR3		pos;	    // 位置
	D3DXVECTOR3		rot;		// 向き(回転)
	D3DXVECTOR3		scl;		// 大きさ(スケール)
	D3DXVECTOR3		spd      = {0.0f,0.0f,0.0f};
	int				frame    = 0;
	int             maxFrame = 0;

	D3DXVECTOR3     size;		// 当たり判定用サイズ

	D3DXMATRIX		mtxWorld;	// ワールドマトリックス
	DX11_MODEL		g_Model;
public:
	 Block(D3DXVECTOR3 pos_);
	 ~Block() 
	 {
		 //objモデルの解放
		 UnloadModel(&g_Model);
	 }
	 void Update(Map* map);
	 void Draw();
	 void CheckBlockCollision(Map* map);
	 void CheckWallCollision(Map* map);
	 D3DXVECTOR3 GetPos()				  { return pos; }
	 void SetPos(D3DXVECTOR3 pos_)		  { pos = pos_; }
	 D3DXVECTOR3 GetSize()				  { return size; }
	 void SetSpd(D3DXVECTOR3 spd_)        { spd = spd_; }
	 D3DXVECTOR3 GetSpd()				  { return spd;}
	 void SetMaxFrame(int maxFrame_)	  { maxFrame = maxFrame_; }
};

#endif//BLOCK_H_
