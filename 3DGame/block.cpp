#include "block.h"
#include "main.h"
#include "texture.h"
#include "model.h"
#include "light.h"
#include "shadow.h"
#include "map.h"
#include "collision.h"

Block::Block(D3DXVECTOR3 pos_)
{
	// �ʒu�E��]�E�X�P�[���̏����ݒ�
	pos = pos_;
	rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	scl = D3DXVECTOR3(2.0f, 0.8f, 2.0f);

	//�����蔻��p�T�C�Y�̏����ݒ�
	size = D3DXVECTOR3(25.0f, 11.0f, 25.0f);

	//obj���f���̓ǂݍ���
	LoadModel((char*)"data/MODEL/block.obj", &g_Model);

	// ���s�����̐ݒ�i���E���Ƃ炷���j
	LIGHT* pLight = NULL;
	pLight = GetLightData(0);
	pLight->Direction = D3DXVECTOR4(1.0f, -1.0f, 1.0f, 0.0f);// ���̌���
	pLight->Diffuse = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);	// ���̐F
	pLight->Type = LIGHT_TYPE_DIRECTIONAL;					// ���s����
	pLight->Enable = true;									// ���̃��C�g��ON
	SetLightData(0, pLight);									// ����Őݒ肵�Ă���

	// �_�����̐ݒ�
	pLight = GetLightData(1);
	pLight->Position = D3DXVECTOR4(0.0f, 500.0f, 0.0f, 0.0f);
	pLight->Direction = D3DXVECTOR4(1.0f, -1.0f, 1.0f, 0.0f);// ���̌���
	pLight->Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// ���̐F
	pLight->Attenuation = 1000.0f;							// ��������
	pLight->Type = LIGHT_TYPE_POINT;						// ���s����
	pLight->Enable = true;									// ���̃��C�g��ON
	SetLightData(1, pLight);								// ����Őݒ肵�Ă���
}

void Block::Update(Map* map)
{
	frame ++;
	if ( frame >= maxFrame)
	{
		frame = 0;
		spd = -spd;
	}
	pos += spd;

	CheckBlockCollision(map);
	CheckWallCollision(map);
}

void Block::Draw()
{
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	// ���[���h�}�g���b�N�X�̏������i�P�ʍs������֐��j
	D3DXMatrixIdentity(&mtxWorld);

	// �X�P�[���𔽉f
	D3DXMatrixScaling(&mtxScl, scl.x, scl.y, scl.z);

	//��1���� ��          ��2����      ��    ��3����
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScl);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);

	// ���[���h�}�g���b�N�X�̐ݒ�
	SetWorldMatrix(&mtxWorld);

	//�J�����O�Ȃ�
	SetCullingMode(CULL_MODE_NONE);

	//obj���f���̕`��
	DrawModel(&g_Model);

	//�J�����O�����ɖ߂�
	SetCullingMode(CULL_MODE_BACK);
}

void Block::CheckBlockCollision(Map* map)
{
	bool collision = false;
	for (int i = 0; i < MAXBLOCK; i++)
	{
		if (map->GetBlock(i) && map->GetBlock(i) != this && CollisionBB(pos, { map->GetBlock(i)->GetPos().x , map->GetBlock(i)->GetPos().y - map->GetBlock(i)->GetSize().y/2.0f, map->GetBlock(i)->GetPos().z }, size, map->GetBlock(i)->GetSize()))
		{
			collision = true;
			frame = 0;
			spd = -spd;
			break;
		}
	}
}

void Block::CheckWallCollision(Map* map)
{
	bool collision = false;
	for (int i = 0; i < MAXWALL; i++)
	{
		if (map->GetWall(i) && CollisionBB(pos, map->GetWall(i)->GetPos(), size, map->GetWall(i)->GetSize()))
		{
			collision = true;
			frame = 0;
			spd = -spd;
			break;
		}
	}
}

