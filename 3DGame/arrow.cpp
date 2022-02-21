#include "arrow.h"
#include "main.h"
#include "texture.h"
#include "model.h"
#include "light.h"
#include "shadow.h"
#include "camera.h"


Arrow::Arrow(D3DXVECTOR3 pos_)
{
	// �ʒu�E��]�E�X�P�[���̏����ݒ�
	oldpos = pos_;
	pos = pos_;
	rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);;
	scl = D3DXVECTOR3(1.0f, 1.0f, 0.1f);

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

	{
		// ���_�o�b�t�@�ւ̃|�C���^���擾
		D3D11_MAPPED_SUBRESOURCE msr;
		GetDeviceContext()->Map(vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

		VERTEX_3D* pVtx = (VERTEX_3D*)msr.pData;


		// ���_���W�̐ݒ�
		pVtx[0].Position = D3DXVECTOR3(pos.x - size.x, pos.y - size.y, pos.z);
		// UV�l�̐ݒ�
		pVtx[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);
		// �@���̐ݒ�
		pVtx[0].Normal = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		// ���_�J���[�̐ݒ�
		pVtx[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// ���_���W�̐ݒ�
		pVtx[1].Position = D3DXVECTOR3(pos.x + size.x, pos.y - size.y, pos.z);
		// UV�l�̐ݒ�
		pVtx[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f);
		// �@���̐ݒ�
		pVtx[1].Normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		// ���_�J���[�̐ݒ�
		pVtx[1].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// ���_���W�̐ݒ�
		pVtx[2].Position = D3DXVECTOR3(pos.x - size.x, pos.y + size.y, pos.z);
		// UV�l�̐ݒ�
		pVtx[2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);
		// �@���̐ݒ�
		pVtx[2].Normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		// ���_�J���[�̐ݒ�
		pVtx[2].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// ���_���W�̐ݒ�
		pVtx[3].Position = D3DXVECTOR3(pos.x + size.x, pos.y + size.y, pos.z);
		// UV�l�̐ݒ�
		pVtx[3].TexCoord = D3DXVECTOR2(1.0f, 1.0f);
		// �@���̐ݒ�
		pVtx[3].Normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		// ���_�J���[�̐ݒ�
		pVtx[3].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		GetDeviceContext()->Unmap(vertexBuffer, 0);
	}
	

	{//�C���f�b�N�X�o�b�t�@�̒��g�𖄂߂�

				// �C���f�b�N�X�o�b�t�@�̃|�C���^���擾
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
