#ifndef GUIDE_H_
#define GUIDE_H_

#include "Texture.h"
#include "sprite.h"
#include "character.h"

class Guide
{
private:
	D3DXVECTOR2						size;					    // ���ƍ���
	D3DXVECTOR2						oldSize;					// ���ƍ���
	D3DXVECTOR3						pos;						// �|���S���̍��W
	int								texNo[100];						// �e�N�X�`���ԍ�
	D3DXVECTOR2						textCoord;
	D3DXVECTOR2						textCoordSize;

public:
	Guide()
	{
		//�e�N�X�`������
		texNo[0]         = LoadTexture("data/TEXTURE/guide001.png");
		texNo[1]         = LoadTexture("data/TEXTURE/guide002.png");
		texNo[2]		 = LoadTexture("data/TEXTURE/guide003.png");
		texNo[3]		 = LoadTexture("data/TEXTURE/guide004.png");
		texNo[4]		 = LoadTexture("data/TEXTURE/guide005.png");
		texNo[5]		 = LoadTexture("data/TEXTURE/guide006.png");

		size          = {1200.0f, 300.0f};
		pos           = {350.0f, 730.0f, 0.0f};
		textCoord     = { 0.0f,0.0f };
		textCoordSize = { 1.0f,1.0f };
	}

	~Guide() {}

	void Update()
	{
	}

	void Draw(int guide)
	{
		// �e�N�X�`���ݒ�
 		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(texNo[guide]));

		if(guide >= 0)
		DrawSpriteLeftTop(texNo[guide], pos.x, pos.y, size.x, size.y, textCoord.x, textCoord.y, textCoordSize.x, textCoordSize.y);

	}
};

#endif//GUIDE_H_