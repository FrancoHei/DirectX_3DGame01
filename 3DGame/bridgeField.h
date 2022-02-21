#ifndef BRIDGEFIELD_H_
#define BRIDGEFIELD_H_

#include "mapItem.h"
#include "renderer.h"
#include "field.h"

class BridgeField : public Field
{
private:

public:
	BridgeField(D3DXVECTOR3 pos_, int numFieldX, int numFieldY) : Field(FIELD_BRIDGE, pos_, numFieldX, numFieldY)
	{
		texNo = LoadTexture("data/TEXTURE/bridgeField.jpg");	// テクスチャ番号	
	}

	~BridgeField() 
	{
	
	}


};

#endif//BRIDGEFIELD_H_