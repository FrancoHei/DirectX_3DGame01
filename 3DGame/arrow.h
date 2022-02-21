#ifndef ARROW_H_
#define ARROW_H_

#include "renderer.h"
#include "model.h"
#include "Texture.h"

#define ARROW_SIZEX (8)
#define ARROW_SIZEY (8)

class Shadow;
class Camera;

class Arrow
{
private:
	int						texNo = LoadTexture("data/TEXTURE/arrow.png");	// テクスチャ番号
	D3DXVECTOR3				pos;
	D3DXVECTOR3				oldpos;
	D3DXVECTOR2				size = { ARROW_SIZEX, ARROW_SIZEY };
	D3DXVECTOR3				rot;
	D3DXVECTOR3				scl;
	D3DXMATRIX				mtxWorld;
	ID3D11Buffer*			vertexBuffer = NULL;
	ID3D11Buffer*			indexBuffer  = NULL;
	int						numVertex    = 4;
	int						numIndex     = 6;
	float                   sclSpd = -0.02f;
	bool					show         = false;
public:
	Arrow(D3DXVECTOR3 pos_);
	~Arrow() {}
	void Update(Camera* cam);
	void Draw();
	void SetShow(bool show_)	{ show = show_;}
	bool GetShow()				{ return show; }
	D3DXVECTOR3 GetPos()		{ return pos; }
};

#endif//ARROW_H_