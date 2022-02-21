#ifndef SWITCH_H_
#define SWITCH_H_

#include "renderer.h"
#include "model.h"

class Shadow;
class Map;

class Switch
{
private:
	D3DXVECTOR3		pos;	    // �ʒu
	D3DXVECTOR3		rot;		// ����(��])
	D3DXVECTOR3		scl;		// �傫��(�X�P�[��)
	D3DXVECTOR3		spd = { 0.0f,0.0f,0.0f };
	int				frame = 0;
	int             maxFrame = 0;

	D3DXVECTOR3     size;		// �����蔻��p�T�C�Y

	D3DXMATRIX		mtxWorld;	// ���[���h�}�g���b�N�X
	DX11_MODEL		g_Model;
public:
	Switch(char* model, D3DXVECTOR3 pos_);
	~Switch() 
	{
		//obj���f���̉��
		UnloadModel(&g_Model);
	}

	void Update();
	void Draw();
	D3DXVECTOR3 GetPos() { return pos; }
	D3DXVECTOR3 GetSize() { return size; }
};

#endif//SWITCH_H_

