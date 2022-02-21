#ifndef WOODBOX_H_
#define WOODBOX_H_

#include "renderer.h"
#include "model.h"

class Map;

class WoodBox
{
private:
	D3DXVECTOR3		pos;	    // 位置
	D3DXVECTOR3		oldPos;	    // 位置
	D3DXVECTOR3		rot;		// 向き(回転)
	D3DXVECTOR3		scl;		// 大きさ(スケール)
	D3DXVECTOR3		spd = { 0.0f,0.0f,0.0f };
	int				frame = 0;
	int             maxFrame = 0;

	D3DXVECTOR3     size;		// 当たり判定用サイズ

	D3DXMATRIX		mtxWorld;	// ワールドマトリックス
	DX11_MODEL		g_Model;
public:
	WoodBox(D3DXVECTOR3 pos_);
	~WoodBox() 
	{
		//objモデルの解放
		UnloadModel(&g_Model);
	}

	void Update();
	void Draw();
	D3DXVECTOR3 GetPos()		  { return pos; }
	D3DXVECTOR3 GetOldPos()		  { return oldPos; }
	void SetPos(D3DXVECTOR3 pos_) { pos = pos_; }
	D3DXVECTOR3 GetSize() { return size; }

	void SetSpd(D3DXVECTOR3 spd_) { spd = spd_; }
	bool CheckIronBoxCollision();
};

#endif//IRONBOX_H_