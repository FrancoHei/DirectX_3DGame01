#include "rock.h"
#include "shadow.h"
#include "light.h"
#include "map.h"
#include "collision.h"

Rock::Rock(D3DXVECTOR3 pos_)
{
	// �ʒu�E��]�E�X�P�[���̏����ݒ�
	pos  = pos_;
	maxHeight = pos.y;
	rot  = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	scl  = D3DXVECTOR3(0.4f, 0.4f, 0.4f);
	move = D3DXVECTOR3(0.0f, -0.7f, -1.0f);
	//�����蔻��p�T�C�Y�̏����ݒ�
	size = D3DXVECTOR3(5.0f, 5.0f, 5.0f);

	//obj���f���̓ǂݍ���
	LoadModel((char*)"data/MODEL/rock.obj", &g_Model);


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