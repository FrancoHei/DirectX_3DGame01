#ifndef SWITCH_H_
#define SWITCH_H_

#include "renderer.h"
#include "model.h"

class Shadow;
class Map;

class Switch
{
private:
	D3DXVECTOR3		pos;	    // 位置
	D3DXVECTOR3		rot;		// 向き(回転)
	D3DXVECTOR3		scl;		// 大きさ(スケール)
	D3DXVECTOR3		spd = { 0.0f,0.0f,0.0f };
	int				frame = 0;
	int             maxFrame = 0;

	D3DXVECTOR3     size;		// 当たり判定用サイズ

	D3DXMATRIX		mtxWorld;	// ワールドマトリックス
	DX11_MODEL		g_Model;
public:
	Switch(char* model, D3DXVECTOR3 pos_);
	~Switch() 
	{
		//objモデルの解放
		UnloadModel(&g_Model);
	}

	void Update();
	void Draw();
	D3DXVECTOR3 GetPos() { return pos; }
	D3DXVECTOR3 GetSize() { return size; }
};

#endif//SWITCH_H_

