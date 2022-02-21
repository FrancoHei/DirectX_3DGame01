#ifndef ROCK_H_
#define ROCK_H_

#include "renderer.h"
#include "model.h"

class Map;

class Rock
{
private:
	D3DXVECTOR3		pos;	    // 位置
	float			maxHeight;
	D3DXVECTOR3		move;
	D3DXVECTOR3		rot;		// 向き(回転)
	D3DXVECTOR3		scl;		// 大きさ(スケール)
	int				timer = 0;
	int				attack = 10;
	D3DXVECTOR3     size;		// 当たり判定用サイズ

	D3DXMATRIX		mtxWorld;	// ワールドマトリックス
	DX11_MODEL		g_Model;
public:
	Rock(D3DXVECTOR3 pos_);
	~Rock() 
	{
		//objモデルの解放
		UnloadModel(&g_Model);
	}

	bool CheckOnFloor(Map* map);
	void Update(int i, Map* map);
	D3DXVECTOR3 GetPos()     { return pos; }
	D3DXVECTOR3 GetSize()    { return size; }
	int			GetAttack()	 { return attack; }
	void Draw();
};

#endif//ROCK_H_
