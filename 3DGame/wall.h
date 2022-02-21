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
	int		texNo              = LoadTexture("data/TEXTURE/bridgeField.jpg");	// �e�N�X�`���ԍ�
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DXVECTOR3 scl;
	D3DXVECTOR3 move           = { 0.0f, 0.0f, 0.0f };
	int			frame          = 0;
	int			maxFrame       = 0;
	D3DXMATRIX  mtxWorld;
	ID3D11Buffer* vertexBuffer = NULL;
	ID3D11Buffer* indexBuffer  = NULL;
	D3DXVECTOR3     size;		// �����蔻��p�T�C�Y
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
		{// ���_�o�b�t�@�̉��
			vertexBuffer->Release();
			vertexBuffer = NULL;
		}

		if (indexBuffer != NULL)
		{// ���_�o�b�t�@�̉��
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
		// �ʒu�E��]�E�X�P�[���̏����ݒ�
		pos = pos_;
		rot = rot_;
		scl = D3DXVECTOR3(0.1f, 1.0f, 1.0f);

		int yoko = numBlockX;
		int tate = numBlockZ;

		//�K�v�Ȓ��_�����v�Z����
		numVertex = (yoko + 1) * (tate + 1);
		numIndex = (yoko + 1) * 2 * tate + (tate - 1) * 2;

		// ���_�o�b�t�@����
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DYNAMIC;
		bd.ByteWidth = sizeof(VERTEX_3D) * numVertex;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		GetDevice()->CreateBuffer(&bd, NULL, &vertexBuffer);


		// �C���f�b�N�X�o�b�t�@����
		ZeroMemory(&bd, sizeof(bd));
		bd.Usage = D3D11_USAGE_DYNAMIC;
		bd.ByteWidth = sizeof(unsigned short) * numIndex;
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		GetDevice()->CreateBuffer(&bd, NULL, &indexBuffer);

		{//���_�o�b�t�@�̒��g�𖄂߂�

			// ���_�o�b�t�@�ւ̃|�C���^���擾
			D3D11_MAPPED_SUBRESOURCE msr;
			GetDeviceContext()->Map(vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

			VERTEX_3D* pVtx = (VERTEX_3D*)msr.pData;

			//1�c�ɂ�2�񃋁[�v����
			for (int y = 0; y < (tate + 1); y++)
			{
				//���ɂ͕K�v����+1�񃋁[�v����
				for (int x = 0; x < (yoko + 1); x++)
				{
					//�z��̃C���f�b�N�X���v�Z����
					int i = y * (yoko + 1) + x;

					// ���_���W�̐ݒ�
					pVtx[i].Position = D3DXVECTOR3(pos.x, -(yoko / 2.0f) * sizeX + x * sizeX, (tate / 2.0f) * sizeZ - y * sizeZ);
					// UV�l�̐ݒ�
					pVtx[i].TexCoord = D3DXVECTOR2(x * 1.0f, y * 1.0f);

					// �@���̐ݒ�
					pVtx[i].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
					// ���_�J���[�̐ݒ�
					pVtx[i].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
				}
			}
			GetDeviceContext()->Unmap(vertexBuffer, 0);
		}

		{//�C���f�b�N�X�o�b�t�@�̒��g�𖄂߂�

			// �C���f�b�N�X�o�b�t�@�̃|�C���^���擾
			D3D11_MAPPED_SUBRESOURCE msr;
			GetDeviceContext()->Map(indexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

			unsigned short* pIdx = (unsigned short*)msr.pData;

			int idx = 0;

			if(wallDirection == WALL_RIGHT)
			{
				for (int y = 0; y < tate; y++)
				{
					//1�s�ڂ̃|���S���̃C���f�b�N�X
					for (int x = 0; x < (yoko + 1); x++)
					{
						pIdx[idx] = (yoko + 1) + x + (yoko + 1) * y;
						idx++;
						pIdx[idx] = 0 + x + (yoko + 1) * y;
						idx++;
					}

					//�k�ރ|���S�����̃C���f�b�N�X
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
					//1�s�ڂ̃|���S���̃C���f�b�N�X
					for (int x = 0; x < (yoko + 1); x++)
					{
						pIdx[idx] = 0 + x + (yoko + 1) * y;
						idx++;
						pIdx[idx] = (yoko + 1) + x + (yoko + 1) * y;
						idx++;
					}

					//�k�ރ|���S�����̃C���f�b�N�X
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

		// ���_�o�b�t�@�ݒ�
		UINT stride = sizeof(VERTEX_3D);
		UINT offset = 0;
		GetDeviceContext()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);

		// �C���f�b�N�X�o�b�t�@�ݒ�
		GetDeviceContext()->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R16_UINT, 0);

		// �v���~�e�B�u�g�|���W�ݒ�
		GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

		// �}�e���A���ݒ�
		MATERIAL material;
		ZeroMemory(&material, sizeof(material));
		material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		SetMaterial(material);

		// �e�N�X�`���ݒ�
		GetDeviceContext()->PSSetShaderResources(0, 1, GetTexture(texNo));


		D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&mtxWorld);

		// �X�P�[���𔽉f
		D3DXMatrixScaling(&mtxScl, scl.x, scl.y, scl.z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScl);

		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

		// �ړ��𔽉f
		D3DXMatrixTranslation(&mtxTranslate, pos.x, pos.y, pos.z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);

		// ���[���h�}�g���b�N�X�̐ݒ�
		SetWorldMatrix(&mtxWorld);

		// �|���S���̕`��
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