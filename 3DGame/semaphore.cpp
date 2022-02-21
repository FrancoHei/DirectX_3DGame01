#include "semaphore.h"
#include "shadow.h"
#include "light.h"
#include "map.h"
#include "collision.h"
#include "character.h"

Semaphore::Semaphore(D3DXVECTOR3 pos_)
{
	// �ʒu�E��]�E�X�P�[���̏����ݒ�
	pos = pos_;
	rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	move = D3DXVECTOR3(0.0f, -0.7f, -1.0f);
	//�����蔻��p�T�C�Y�̏����ݒ�
	size = D3DXVECTOR3(5.0f, 5.0f, 5.0f);

	maxFrame = 80 + rand() % 200;
	//obj���f���̓ǂݍ���
	LoadModel((char*)"data/MODEL/red_ball.obj", &g_Model);
	LoadModel((char*)"data/MODEL/ball.obj", &g_Model_2);


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
	if (!canWalk)
	{
		DrawModel(&g_Model);
	}else
	{
		DrawModel(&g_Model_2);
	}

	//�J�����O�����ɖ߂�
	SetCullingMode(CULL_MODE_BACK);
}
