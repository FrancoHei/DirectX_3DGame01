#ifndef IRONBOX_H_
#define IRONBOX_H_

#include "renderer.h"
#include "model.h"

class Map;

class IronBox
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
	IronBox(D3DXVECTOR3 pos_);
	~IronBox()
	{	
		//objモデルの解放
		UnloadModel(&g_Model);
	}

	void Update();
	void Draw();
	D3DXVECTOR3 GetPos() { return pos; }
	D3DXVECTOR3 GetSize() { return size; }
	D3DXVECTOR3 GetScale() { return scl; }
	void SetScale(D3DXVECTOR3 scl_) { scl = scl_; }
	void SetSize(D3DXVECTOR3 size_) { size = size_; }
};

#endif//IRONBOX_H_