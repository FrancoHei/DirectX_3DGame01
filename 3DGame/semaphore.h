#ifndef SEMAPHORE_H_
#define SEMAPHORE_H_

#include "renderer.h"
#include "model.h"

class Character;

class Semaphore
{
private:
	D3DXVECTOR3		pos;	    // �ʒu
	float			maxHeight;
	D3DXVECTOR3		move;
	D3DXVECTOR3		rot;		// ����(��])
	D3DXVECTOR3		scl;		// �傫��(�X�P�[��)
	int				timer = 0;
	D3DXVECTOR3     size;		// �����蔻��p�T�C�Y

	D3DXMATRIX		mtxWorld;	// ���[���h�}�g���b�N�X
	DX11_MODEL		g_Model;
	DX11_MODEL		g_Model_2;

	bool            startSemaphore = false;
	bool			canWalk		   = false;
	int				frame		   = 0;
	int				maxFrame;
public:
	 Semaphore(D3DXVECTOR3 pos_);
	~Semaphore()
	{
		//obj���f���̉��
		UnloadModel(&g_Model);
		UnloadModel(&g_Model_2);
	}

	void Update(Character* character);
	void Draw();

	void SetStartSemaphore(bool startSemaphore_) { startSemaphore = startSemaphore_;}
	bool GetStartSemaphore()					 { return startSemaphore; }
	bool GetCanWalk()							 { return canWalk; }

	D3DXVECTOR3 GetPos()	{ return pos;}
};

#endif//SEMAPHORE_H_
