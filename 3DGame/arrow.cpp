#include "arrow.h"
#include "main.h"
#include "texture.h"
#include "model.h"
#include "light.h"
#include "shadow.h"
#include "camera.h"


Arrow::Arrow(D3DXVECTOR3 pos_)
{
	// 位置・回転・スケールの初期設定
	oldpos = pos_;
	pos = pos_;
	rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);;
	scl = D3DXVECTOR3(1.0f, 1.0f, 0.1f);

	// 頂点バッファ生成
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * numVertex;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	GetDevice()->CreateBuffer(&bd, NULL, &vertexBuffer);

	// インデックスバッファ生成
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(unsigned short) * numIndex;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	GetDevice()->CreateBuffer(&bd, NULL, &indexBuffer);

	{
		// 頂点バッファへのポインタを取得
		D3D11_MAPPED_SUBRESOURCE msr;
		GetDeviceContext()->Map(vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

		VERTEX_3D* pVtx = (VERTEX_3D*)msr.pData;


		// 頂点座標の設定
		pVtx[0].Position = D3DXVECTOR3(pos.x - size.x, pos.y - size.y, pos.z);
		// UV値の設定
		pVtx[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);
		// 法線の設定
		pVtx[0].Normal = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		// 頂点カラーの設定
		pVtx[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// 頂点座標の設定
		pVtx[1].Position = D3DXVECTOR3(pos.x + size.x, pos.y - size.y, pos.z);
		// UV値の設定
		pVtx[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f);
		// 法線の設定
		pVtx[1].Normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		// 頂点カラーの設定
		pVtx[1].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// 頂点座標の設定
		pVtx[2].Position = D3DXVECTOR3(pos.x - size.x, pos.y + size.y, pos.z);
		// UV値の設定
		pVtx[2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);
		// 法線の設定
		pVtx[2].Normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		// 頂点カラーの設定
		pVtx[2].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// 頂点座標の設定
		pVtx[3].Position = D3DXVECTOR3(pos.x + size.x, pos.y + size.y, pos.z);
		// UV値の設定
		pVtx[3].TexCoord = D3DXVECTOR2(1.0f, 1.0f);
		// 法線の設定
		pVtx[3].Normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		// 頂点カラーの設定
		pVtx[3].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		GetDeviceContext()->Unmap(vertexBuffer, 0);
	}
	

	{//インデックスバッファの中身を埋める

				// インデックスバッファのポインタを取得
		D3D11_MAPPED_SUBRESOURCE msr;
		GetDeviceContext()->Map(indexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

		unsigned short* pIdx = (unsigned short*)msr.pData;
		pIdx[0] = 0;
		pIdx[1] = 2;
		pIdx[2] = 1;
		pIdx[3] = 3;
		pIdx[4] = 1;
		pIdx[5] = 2;

		GetDeviceContext()->Unmap(indexBuffer, 0);
	}
}

void Arrow::Update(Camera* cam)
{
	scl.x += sclSpd;
	if(scl.x <= 0 || scl.x >= 1.0f)
	{
		sclSpd = -sclSpd;
	}
}

void Arrow::Draw()
{
	SetCullingMode(CULL_MODE_BACK);

	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);

	// インデックスバッファ設定
	GetDeviceContext()->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R16_UINT, 0);

	// プリミティブトポロジ設定
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// マテリアル設定
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	SetMaterial(material);

	// テクスチャ設定
	GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(texNo));


	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&mtxWorld);

	// スケールを反映
	D3DXMatrixScaling(&mtxScl, scl.x, scl.y, scl.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScl);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

	// 移動を反映
	D3DXMatrixTranslation(&mtxTranslate, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);

	// ワールドマトリックスの設定
	SetWorldMatrix(&mtxWorld);

	// ポリゴンの描画
	GetDeviceContext()->DrawIndexed(numIndex, 0, 0);
}
