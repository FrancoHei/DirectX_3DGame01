#ifndef TREASURE_H_
#define TREASURE_H_

#include "renderer.h"
#include "model.h"


class Treasure
{
private:
	D3DXVECTOR3		pos;	    // �ʒu
	float			maxHeight;
	D3DXVECTOR3		move;
	D3DXVECTOR3		rot;		// ����(��])
	D3DXVECTOR3		scl;		// �傫��(�X�P�[��)
	D3DXVECTOR3     size;		// �����蔻��p�T�C�Y

	D3DXMATRIX		mtxWorld;	// ���[���h�}�g���b�N�X
	DX11_MODEL		g_Model;
public:
	Treasure(D3DXVECTOR3 pos_);
	~Treasure()
	{
		//obj���f���̉��
		UnloadModel(&g_Model);
	}

	void Update();
	void Draw();
	D3DXVECTOR3 GetPos()  { return pos; }
	D3DXVECTOR3 GetSize() { return size; }
};

#endif//TREASURE_H_
