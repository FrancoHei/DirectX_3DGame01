#ifndef HPBAR_H_
#define HPBAR_H_

#include "Texture.h"
#include "sprite.h"
#include "character.h"

class HpBar
{
private:
	D3DXVECTOR2						size;					    // ���ƍ���
	D3DXVECTOR2						oldSize;					// ���ƍ���
	D3DXVECTOR3						pos;						// �|���S���̍��W
	int								texNo;						// �e�N�X�`���ԍ�
	D3DXVECTOR2						textCoord;
	D3DXVECTOR2						textCoordSize;

public:
	HpBar(D3DXVECTOR3 pos_, D3DXVECTOR2 size_)
	{
		//�e�N�X�`������
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
		// �e�N�X�`���ݒ�
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(texNo));

		DrawSpriteLeftTop(texNo, pos.x, pos.y, size.x, size.y, textCoord.x, textCoord.y, textCoordSize.x, textCoordSize.y);

	}
};

#endif//HPBAR_H_