#ifndef FIREFIELD_H_
#define FIREFIELD_H_

#include "mapItem.h"
#include "renderer.h"
#include "field.h"

class FireField : public Field
{
private:

public:
	FireField(D3DXVECTOR3 pos_, int numFieldX, int numFieldY) : Field(FIELD_FIRE, pos_,numFieldX, numFieldY)
	{
		texNo = LoadTexture("data/TEXTURE/fireField.jpg");	// テクスチャ番号	
	}

	~FireField() {}

};

#endif//FIREFIELD_H_
