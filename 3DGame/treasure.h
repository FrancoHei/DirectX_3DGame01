#ifndef TREASURE_H_
#define TREASURE_H_

#include "renderer.h"
#include "model.h"


class Treasure
{
private:
	D3DXVECTOR3		pos;	    // 位置
	float			maxHeight;
	D3DXVECTOR3		move;
	D3DXVECTOR3		rot;		// 向き(回転)
	D3DXVECTOR3		scl;		// 大きさ(スケール)
	D3DXVECTOR3     size;		// 当たり判定用サイズ

	D3DXMATRIX		mtxWorld;	// ワールドマトリックス
	DX11_MODEL		g_Model;
public:
	Treasure(D3DXVECTOR3 pos_);
	~Treasure()
	{
		//objモデルの解放
		UnloadModel(&g_Model);
	}

	void Update();
	void Draw();
	D3DXVECTOR3 GetPos()  { return pos; }
	D3DXVECTOR3 GetSize() { return size; }
};

#endif//TREASURE_H_
