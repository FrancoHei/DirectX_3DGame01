#ifndef WALL_H_
#define WALL_H_

#include "mapItem.h"
#include "renderer.h"

#define WALLSIZE 50

enum WALLDIRECTION
{
	WALL_RIGHT,
	WALL_LEFT
};

class Wall
{
private:
	WALLDIRECTION wallDirection;
	int		texNo              = LoadTexture("data/TEXTURE/bridgeField.jpg");	// テクスチャ番号
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXVECTOR3 scl;
	D3DXVECTOR3 move           = { 0.0f, 0.0f, 0.0f };
	int			frame          = 0;
	int			maxFrame       = 0;
	D3DXMATRIX  mtxWorld;
	ID3D11Buffer* vertexBuffer = NULL;
	ID3D11Buffer* indexBuffer  = NULL;
	D3DXVECTOR3     size;		// 当たり判定用サイズ
	int numVertex;
	int numIndex;
	bool isMove				   = false;
public:
	Wall(WALLDIRECTION wallDirection_, D3DXVECTOR3 pos_, int numFieldX, int numFieldY): wallDirection(wallDirection_)
	{ 
		CreateWall(pos_, D3DXVECTOR3(0.0f, 0.0f, 0.0f), numFieldX, numFieldY, WALLSIZE, WALLSIZE);
	}

	~Wall() 
	{
		if (vertexBuffer != NULL)
		{// 頂点バッファの解放
			vertexBuffer->Release();
			vertexBuffer = NULL;
		}

		if (indexBuffer != NULL)
		{// 頂点バッファの解放
			indexBuffer->Release();
			indexBuffer = NULL;
		}
	};

	void Update()
	{
		if (isMove)
		{
			frame++;
			pos += move;
			if (frame % maxFrame == 0)
			{
				move = -move;
			}

		}
	}

	void CreateWall(D3DXVECTOR3 pos_, D3DXVECTOR3 rot_, int numBlockX, int numBlockZ, float sizeX, float sizeZ)
	{
		// 位置・回転・スケールの初期設定
		pos = pos_;
		rot = rot_;
		scl = D3DXVECTOR3(0.1f, 1.0f, 1.0f);

		int yoko = numBlockX;
		int tate = numBlockZ;

		//必要な頂点数を計算する
		numVertex = (yoko + 1) * (tate + 1);
		numIndex = (yoko + 1) * 2 * tate + (tate - 1) * 2;

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

		{//頂点バッファの中身を埋める

			// 頂点バッファへのポインタを取得
			D3D11_MAPPED_SUBRESOURCE msr;
			GetDeviceContext()->Map(vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

			VERTEX_3D* pVtx = (VERTEX_3D*)msr.pData;

			//1縦には2回ループする
			for (int y = 0; y < (tate + 1); y++)
			{
				//横には必要枚数+1回ループする
				for (int x = 0; x < (yoko + 1); x++)
				{
					//配列のインデックスを計算する
					int i = y * (yoko + 1) + x;

					// 頂点座標の設定
					pVtx[i].Position = D3DXVECTOR3(pos.x, -(yoko / 2.0f) * sizeX + x * sizeX, (tate / 2.0f) * sizeZ - y * sizeZ);
					// UV値の設定
					pVtx[i].TexCoord = D3DXVECTOR2(x * 1.0f, y * 1.0f);

					// 法線の設定
					pVtx[i].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
					// 頂点カラーの設定
					pVtx[i].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				}
			}
			GetDeviceContext()->Unmap(vertexBuffer, 0);
		}

		{//インデックスバッファの中身を埋める

			// インデックスバッファのポインタを取得
			D3D11_MAPPED_SUBRESOURCE msr;
			GetDeviceContext()->Map(indexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

			unsigned short* pIdx = (unsigned short*)msr.pData;

			int idx = 0;

			if(wallDirection == WALL_RIGHT)
			{
				for (int y = 0; y < tate; y++)
				{
					//1行目のポリゴンのインデックス
					for (int x = 0; x < (yoko + 1); x++)
					{
						pIdx[idx] = (yoko + 1) + x + (yoko + 1) * y;
						idx++;
						pIdx[idx] = 0 + x + (yoko + 1) * y;
						idx++;
					}

					//縮退ポリゴン分のインデックス
					if (y < (tate - 1))
					{
						pIdx[idx] = yoko + (yoko + 1) * y;
						idx++;
						pIdx[idx] = (yoko + 1) * 2 + (yoko + 1) * y;
						idx++;
					}
				}
			}else
			if(wallDirection == WALL_LEFT)
			{
				for (int y = 0; y < tate; y++)
				{
					//1行目のポリゴンのインデックス
					for (int x = 0; x < (yoko + 1); x++)
					{
						pIdx[idx] = 0 + x + (yoko + 1) * y;
						idx++;
						pIdx[idx] = (yoko + 1) + x + (yoko + 1) * y;
						idx++;
					}

					//縮退ポリゴン分のインデックス
					if (y < (tate - 1))
					{
						pIdx[idx] = yoko + (yoko + 1) * y;
						idx++;
						pIdx[idx] = (yoko + 1) * 2 + (yoko + 1) * y;
						idx++;
					}
				}
			}

			GetDeviceContext()->Unmap(indexBuffer, 0);
		}
	}

	void SetMove(D3DXVECTOR3 move_) { move = move_; }

	D3DXVECTOR3 GetMove() { return move; }

	void SetIsMove(bool isMove_) { isMove = isMove_; }

	bool GetIsMove() { return isMove; }

	void SetMaxFrame(int maxFrame_) { maxFrame = maxFrame_; }

	WALLDIRECTION GetWallDirection() { return wallDirection; }

	void Draw()
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

	void SetSize(D3DXVECTOR3 size_)
	{
		size = size_;
	}

	D3DXVECTOR3 GetPos() { return pos; }
	D3DXVECTOR3 GetSize() { return size; }

};

#endif//WALL_H_