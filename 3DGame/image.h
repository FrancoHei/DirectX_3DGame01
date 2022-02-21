#ifndef IMAGE_H_
#define IMAGE_H_

#include "renderer.h"
#include "main.h"
#include "Texture.h"
#include "sprite.h"

class Image
{
private:
	D3DXVECTOR2						size;					    // 幅と高さ
	D3DXVECTOR2						oldSize;					// 幅と高さ
	D3DXVECTOR3						pos;						// ポリゴンの座標
	int								texNo;						// テクスチャ番号
	D3DXVECTOR2						textCoord      = D3DXVECTOR2(0.0f,0.0f);
	D3DXVECTOR2						textCoordSize  = D3DXVECTOR2(1.0f, 1.0f);;

public:
	Image(D3DXVECTOR2 pos_, D3DXVECTOR2 size_, int texNo_)
		  :pos(pos_), size(size_), texNo(texNo_)
	{
	
	}

	~Image(){}

	void Draw()
	{
		// テクスチャ設定
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(texNo));

		DrawSpriteLeftTop(texNo, pos.x, pos.y, size.x, size.y, textCoord.x, textCoord.y, textCoordSize.x, textCoordSize.y);

	}
};

#endif IMAGE_H_
