#include "semaphore.h"
#include "shadow.h"
#include "light.h"
#include "map.h"
#include "collision.h"
#include "character.h"

Semaphore::Semaphore(D3DXVECTOR3 pos_)
{
	// 位置・回転・スケールの初期設定
	pos = pos_;
	rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	move = D3DXVECTOR3(0.0f, -0.7f, -1.0f);
	//当たり判定用サイズの初期設定
	size = D3DXVECTOR3(5.0f, 5.0f, 5.0f);

	maxFrame = 80 + rand() % 200;
	//objモデルの読み込み
	LoadModel((char*)"data/MODEL/red_ball.obj", &g_Model);
	LoadModel((char*)"data/MODEL/ball.obj", &g_Model_2);


	// 並行光源の設定（世界を照らす光）
	LIGHT* pLight = NULL;
	pLight = GetLightData(0);
	pLight->Direction = D3DXVECTOR4(1.0f, -1.0f, 1.0f, 0.0f);// 光の向き
	pLight->Diffuse = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);	// 光の色
	pLight->Type = LIGHT_TYPE_DIRECTIONAL;					// 並行光源
	pLight->Enable = true;									// このライトをON
	SetLightData(0, pLight);									// これで設定している

	// 点光源の設定
	pLight = GetLightData(1);
	pLight->Position = D3DXVECTOR4(0.0f, 500.0f, 0.0f, 0.0f);
	pLight->Direction = D3DXVECTOR4(1.0f, -1.0f, 1.0f, 0.0f);// 光の向き
	pLight->Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// 光の色
	pLight->Attenuation = 1000.0f;							// 減衰距離
	pLight->Type = LIGHT_TYPE_POINT;						// 並行光源
	pLight->Enable = true;									// このライトをON
	SetLightData(1, pLight);								// これで設定している
}

void Semaphore::Update(Character* character)
{
	if(startSemaphore)
	{
		pos.z = character->GetPos().z + 150.0f;
		frame++;
		if(frame >= maxFrame)
		{
			frame    = 0;
			maxFrame = 80 + rand() % 200;
			canWalk = !canWalk;
		}
	}
}

void Semaphore::Draw()
{
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	// ワールドマトリックスの初期化（単位行列を作る関数）
	D3DXMatrixIdentity(&mtxWorld);

	// スケールを反映
	D3DXMatrixScaling(&mtxScl, scl.x, scl.y, scl.z);

	//第1引数 ＝          第2引数      ＊    第3引数
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScl);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

	// 移動を反映
	D3DXMatrixTranslation(&mtxTranslate, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);

	// ワールドマトリックスの設定
	SetWorldMatrix(&mtxWorld);

	//カリングなし
	SetCullingMode(CULL_MODE_NONE);

	//objモデルの描画
	if (!canWalk)
	{
		DrawModel(&g_Model);
	}else
	{
		DrawModel(&g_Model_2);
	}

	//カリングを元に戻す
	SetCullingMode(CULL_MODE_BACK);
}
