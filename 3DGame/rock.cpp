#include "rock.h"
#include "shadow.h"
#include "light.h"
#include "map.h"
#include "collision.h"

Rock::Rock(D3DXVECTOR3 pos_)
{
	// 位置・回転・スケールの初期設定
	pos  = pos_;
	maxHeight = pos.y;
	rot  = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	scl  = D3DXVECTOR3(0.4f, 0.4f, 0.4f);
	move = D3DXVECTOR3(0.0f, -0.7f, -1.0f);
	//当たり判定用サイズの初期設定
	size = D3DXVECTOR3(5.0f, 5.0f, 5.0f);

	//objモデルの読み込み
	LoadModel((char*)"data/MODEL/rock.obj", &g_Model);


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

void Rock::Update(int i, Map* map)
{
	timer++;
	CheckOnFloor(map);
	if(pos.y > maxHeight)
	{
		move.y *= -1;
	}
	pos += move;
	if(timer >= 400)
	{
		map->DeleteRock(i);
	}
}

void Rock::Draw()
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
	DrawModel(&g_Model);

	//カリングを元に戻す
	SetCullingMode(CULL_MODE_BACK);
}

bool Rock::CheckOnFloor(Map* map)
{
	bool collision = false;
	for (int i = 0; i < MAXFIELD; i++)
	{
		if ((map->GetField(i) && CollisionBB(pos, map->GetField(i)->GetPos(), size, map->GetField(i)->GetSize())))
		{
			collision = true;
			move.y = -move.y;
			break;
		}
	}

	return collision;
}