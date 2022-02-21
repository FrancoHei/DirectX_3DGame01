//=============================================================================
//
// �e���� [shadow.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "renderer.h"
#include "shadow.h"
#include "texture.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_MAX			(1)				// �e�N�X�`���̐�

#define	SHADOW_SIZE_X		(1.0f)			// ���_�T�C�Y
#define	SHADOW_SIZE_Z		(1.0f)			// ���_�T�C�Y

#define	MAX_SHADOW			(1024)			// �e�ő吔

//=============================================================================
// ����������
//=============================================================================
Shadow::Shadow(D3DXVECTOR3 pos_, D3DXVECTOR3 scl_)
{
	// ���_�o�b�t�@����
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	GetDevice()->CreateBuffer(&bd, NULL, &vertexBuffer);

	{//���_�o�b�t�@�̒��g�𖄂߂�
	D3D11_MAPPED_SUBRESOURCE msr;
		GetDeviceContext()->Map(vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

		VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

		// ���_���W�̐ݒ�
		vertex[0].Position = D3DXVECTOR3(-SHADOW_SIZE_X / 2, 0.0f, SHADOW_SIZE_Z / 2);
		vertex[1].Position = D3DXVECTOR3(SHADOW_SIZE_X / 2, 0.0f, SHADOW_SIZE_Z / 2);
		vertex[2].Position = D3DXVECTOR3(-SHADOW_SIZE_X / 2, 0.0f, -SHADOW_SIZE_Z / 2);
		vertex[3].Position = D3DXVECTOR3(SHADOW_SIZE_X / 2, 0.0f, -SHADOW_SIZE_Z / 2);

		// �@���̐ݒ�
		vertex[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vertex[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vertex[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vertex[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		// �g�U���̐ݒ�
		vertex[0].Diffuse = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f);
		vertex[1].Diffuse = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f);
		vertex[2].Diffuse = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f);
		vertex[3].Diffuse = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f);

		// �e�N�X�`�����W�̐ݒ�
		vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);
		vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f);
		vertex[2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);
		vertex[3].TexCoord = D3DXVECTOR2(1.0f, 1.0f);

		GetDeviceContext()->Unmap(vertexBuffer, 0);
	}

	// �e�N�X�`������
	texNo = LoadTexture("data/TEXTURE/shadow000.jpg");

	// �e���[�N������
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	pos = pos_;
	rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	scl = scl_;
}

//=============================================================================
// �X�V����
//=============================================================================
void Shadow::Update(void)
{
}

//=============================================================================
// �`�揈��
//=============================================================================
void Shadow::Draw(void)
{
	// ���Z����
	SetBlendState(BLEND_MODE_SUBTRACT);

	// Z��r�Ȃ�
	SetDepthEnable(false);

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

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

	// �}�e���A���̐ݒ�
	SetMaterial(material);

	// �|���S���̕`��
	GetDeviceContext()->Draw(4, 0);

	// �ʏ�u�����h
	SetBlendState(BLEND_MODE_ALPHABLEND);
	
	// Z��r����
	SetDepthEnable(true);
}

