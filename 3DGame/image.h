#ifndef IMAGE_H_
#define IMAGE_H_

#include "renderer.h"
#include "main.h"
#include "Texture.h"
#include "sprite.h"

class Image
{
private:
	D3DXVECTOR2						size;					    // ���ƍ���
	D3DXVECTOR2						oldSize;					// ���ƍ���
	D3DXVECTOR3						pos;						// �|���S���̍��W
	int								texNo;						// �e�N�X�`���ԍ�
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
		// �e�N�X�`���ݒ�
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(texNo));

		DrawSpriteLeftTop(texNo, pos.x, pos.y, size.x, size.y, textCoord.x, textCoord.y, textCoordSize.x, textCoordSize.y);

	}
};

#endif IMAGE_H_
