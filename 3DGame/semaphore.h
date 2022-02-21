#ifndef SEMAPHORE_H_
#define SEMAPHORE_H_

#include "renderer.h"
#include "model.h"

class Character;

class Semaphore
{
private:
	D3DXVECTOR3		pos;	    // 位置
	float			maxHeight;
	D3DXVECTOR3		move;
	D3DXVECTOR3		rot;		// 向き(回転)
	D3DXVECTOR3		scl;		// 大きさ(スケール)
	int				timer = 0;
	D3DXVECTOR3     size;		// 当たり判定用サイズ

	D3DXMATRIX		mtxWorld;	// ワールドマトリックス
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
		//objモデルの解放
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
