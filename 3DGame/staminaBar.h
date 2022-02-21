#ifndef STAMINABAR_H_
#define STAMINABAR_H_

#include "Texture.h"
#include "sprite.h"
#include "character.h"

class StaminaBar
{
private:
	D3DXVECTOR2						size;					    // ���ƍ���
	D3DXVECTOR3						pos;						// �|���S���̍��W
	D3DXVECTOR2						oldSize;					// ���ƍ���
	int								texNo = LoadTexture("data/TEXTURE/staminaBar.png"); // �e�N�X�`���ԍ�
	D3DXVECTOR2						textCoord;
	D3DXVECTOR2						textCoordSize;

public:
	StaminaBar(D3DXVECTOR3 pos_, D3DXVECTOR2 size_) 
	{
		//�e�N�X�`������
		size		  = size_;
		oldSize		  = size_;
		pos			  = pos_;
		textCoord	  = {0.0f,0.0f};
		textCoordSize = {1.0f,1.0f};
	}

	~StaminaBar() {}

	void Update(Character* character) 
	{
		textCoordSize = { 1.0f * (FLOAT)character->GetStamina() / (FLOAT)character->GetMaxStamina(), 1.0f };
		size		  = { oldSize.x * (FLOAT)character->GetStamina() / (FLOAT)character->GetMaxStamina(), oldSize.y };
	}

	void Draw() 
	{
			// �e�N�X�`���ݒ�
			GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(texNo));

			DrawSpriteLeftTop(texNo, pos.x, pos.y, size.x, size.y, textCoord.x, textCoord.y, textCoordSize.x, textCoordSize.y);

	}
};

#endif//STAMINABAR_H_

