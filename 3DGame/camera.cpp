//=============================================================================
//
// �J�������� [camera.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "camera.h"
#include "character.h"
#include "input.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	POS_X_CAM		(0.0f)			// �J�����̏����ʒu(X���W)
#define	POS_Y_CAM		(45.0f)		// �J�����̏����ʒu(Y���W)
#define	POS_Z_CAM		(90.0f)		// �J�����̏����ʒu(Z���W)

#define	POS_X_CAM2		(0.0f)			// �J�����̏����ʒu(X���W)
#define	POS_Y_CAM2		(120.0f)		// �J�����̏����ʒu(Y���W)
#define	POS_Z_CAM2		(120.0f)		// �J�����̏����ʒu(Z���W)

#define	VIEW_ANGLE		(D3DXToRadian(45.0f))							// �r���[���ʂ̎���p
#define	VIEW_ASPECT		((float)SCREEN_WIDTH / (float)SCREEN_HEIGHT)	// �r���[���ʂ̃A�X�y�N�g��	
#define	VIEW_NEAR_Z		(10.0f)											// �r���[���ʂ�NearZ�l
#define	VIEW_FAR_Z		(5000.0f)										// �r���[���ʂ�FarZ�l

#define	VALUE_MOVE_CAMERA	(20.0f)										// �J�����̈ړ���
#define	VALUE_ROTATE_CAMERA	(D3DX_PI * 0.01f)							// �J�����̉�]��

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

//=============================================================================
// ����������
//=============================================================================
Camera::Camera(void)
{
	pos = D3DXVECTOR3(POS_X_CAM, POS_Y_CAM, POS_Z_CAM);
	at  = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	up  = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// ���_�ƒ����_�̋������v�Z
	float vx, vz;
	vx  = pos.x - at.x;
	vz  = pos.z - at.z;
	len = sqrtf(vx * vx + vz * vz);
	
}


//=============================================================================
// �J�����̍X�V����
//=============================================================================
void Camera::Update(Character* character)
{
	if (isUpdateCamera_2)
	{
		if(pos.y - character->GetPos().y < POS_Y_CAM2)
		{
			pos.y++;
		}

		if (character->GetPos().z - pos.z  < POS_Z_CAM2)
		{
			pos.z++;
		}

		if(pos.y - character->GetPos().y >= POS_Y_CAM2 && character->GetPos().z - pos.z  >= POS_Z_CAM2)
		{
			isUpdateCamera_2 = false;
		}
	}
	if (isUpdateCamera_1)
	{
		if (pos.y - character->GetPos().y > POS_Y_CAM)
		{
			pos.y--;
		}

		if (character->GetPos().z - pos.z > POS_Z_CAM)
		{
			pos.z--;
		}

		if (pos.y - character->GetPos().y <= POS_Y_CAM && character->GetPos().z - pos.z <= POS_Z_CAM)
		{
			isUpdateCamera_1 = false;
		}
	}


	if(GetMouseX() > 0)
	{
		rot.x++;
	}
}


//=============================================================================
// �J�����̍X�V
//=============================================================================
void Camera::SetCamera(void) 
{
	// �r���[�}�g���b�N�X�ݒ�
	D3DXMatrixLookAtLH(&mtxView, &pos, &at, &up);

	SetViewMatrix(&mtxView);


//	float det;
//	D3DXMatrixInverse(&g_Camera.mtxInvView, &det, &g_Camera.mtxView);


	// �v���W�F�N�V�����}�g���b�N�X�ݒ�
	D3DXMatrixPerspectiveFovLH(&mtxProjection, 1.0f, (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, VIEW_NEAR_Z, VIEW_FAR_Z);

	SetProjectionMatrix(&mtxProjection);
}

void Camera::SetCamera_2(void)
{
	isUpdateCamera_1 = false;
	isUpdateCamera_2 = true;
	camera_1_camera_2 = CAMERA1CAMERA2;
}

void Camera::SetCamera_1(void)
{
	isUpdateCamera_2 = false;
	isUpdateCamera_1 = true;
	camera_1_camera_2 = CAMERA1CAMERA2;

}


