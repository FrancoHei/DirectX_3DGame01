#ifndef BLOCK_H_
#define BLOCK_H_

#include "renderer.h"
#include "model.h"

class Map;

class Block
{
private:
	D3DXVECTOR3		pos;	    // �ʒu
	D3DXVECTOR3		rot;		// ����(��])
	D3DXVECTOR3		scl;		// �傫��(�X�P�[��)
	D3DXVECTOR3		spd      = {0.0f,0.0f,0.0f};
	int				frame    = 0;
	int             maxFrame = 0;

	D3DXVECTOR3     size;		// �����蔻��p�T�C�Y

	D3DXMATRIX		mtxWorld;	// ���[���h�}�g���b�N�X
	DX11_MODEL		g_Model;
public:
	 Block(D3DXVECTOR3 pos_);
	 ~Block() 
	 {
		 //obj���f���̉��
		 UnloadModel(&g_Model);
	 }
	 void Update(Map* map);
	 void Draw();
	 void CheckBlockCollision(Map* map);
	 void CheckWallCollision(Map* map);
	 D3DXVECTOR3 GetPos()				  { return pos; }
	 void SetPos(D3DXVECTOR3 pos_)		  { pos = pos_; }
	 D3DXVECTOR3 GetSize()				  { return size; }
	 void SetSpd(D3DXVECTOR3 spd_)        { spd = spd_; }
	 D3DXVECTOR3 GetSpd()				  { return spd;}
	 void SetMaxFrame(int maxFrame_)	  { maxFrame = maxFrame_; }
};

#endif//BLOCK_H_
