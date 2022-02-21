#ifndef HPBAR_H_
#define HPBAR_H_

#include "Texture.h"
#include "sprite.h"
#include "character.h"

class HpBar
{
private:
	D3DXVECTOR2						size;					    // 幅と高さ
	D3DXVECTOR2						oldSize;					// 幅と高さ
	D3DXVECTOR3						pos;						// ポリゴンの座標
	int								texNo;						// テクスチャ番号
	D3DXVECTOR2						textCoord;
	D3DXVECTOR2						textCoordSize;

public:
	HpBar(D3DXVECTOR3 pos_, D3DXVECTOR2 size_)
	{
		//テクスチャ生成
		texNo		  = LoadTexture("data/TEXTURE/hpBar.png");
		size		  = size_;
		oldSize		  = size_;
		pos			  = pos_;
		textCoord	  = { 0.0f,0.0f };
		textCoordSize = { 1.0f,1.0f };
	}

	~HpBar() {}

	void Update(Character* character) 
	{
		textCoordSize = { 1.0f * (FLOAT)character->GetHp() / (FLOAT)character->GetMaxHp(), 1.0f };
		size		  = { oldSize.x * (FLOAT)character->GetHp() / (FLOAT)character->GetMaxHp(), oldSize.y };
	}

	void Draw()
	{
		// テクスチャ設定
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(texNo));

		DrawSpriteLeftTop(texNo, pos.x, pos.y, size.x, size.y, textCoord.x, textCoord.y, textCoordSize.x, textCoordSize.y);

	}
};

#endif//HPBAR_H_