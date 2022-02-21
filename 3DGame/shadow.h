//=============================================================================
//
// 影処理 [shadow.h]
// Author : 
//
//=============================================================================
#pragma once

class Shadow
{
private:
	D3DXMATRIX		mtxWorld;				// ワールドマトリックス
	D3DXVECTOR3		pos;					// 位置
	D3DXVECTOR3		rot;					// 回転
	D3DXVECTOR3		scl;					// スケール
	MATERIAL		material;				// マテリアル
	ID3D11Buffer*	vertexBuffer;			// 頂点情報
	int				texNo;					// テクスチャ番号
public:
	Shadow(D3DXVECTOR3 pos_, D3DXVECTOR3 scl_);
	~Shadow(void)	 {}
	void Update(void);
	void Draw(void);
	void SetPos(D3DXVECTOR3 pos_) { pos = pos_; }
};
