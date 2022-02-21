//=============================================================================
//
// カメラ処理 [camera.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "input.h"
#include "camera.h"
#include "character.h"
#include "input.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	POS_X_CAM		(0.0f)			// カメラの初期位置(X座標)
#define	POS_Y_CAM		(45.0f)		// カメラの初期位置(Y座標)
#define	POS_Z_CAM		(90.0f)		// カメラの初期位置(Z座標)

#define	POS_X_CAM2		(0.0f)			// カメラの初期位置(X座標)
#define	POS_Y_CAM2		(120.0f)		// カメラの初期位置(Y座標)
#define	POS_Z_CAM2		(120.0f)		// カメラの初期位置(Z座標)

#define	VIEW_ANGLE		(D3DXToRadian(45.0f))							// ビュー平面の視野角
#define	VIEW_ASPECT		((float)SCREEN_WIDTH / (float)SCREEN_HEIGHT)	// ビュー平面のアスペクト比	
#define	VIEW_NEAR_Z		(10.0f)											// ビュー平面のNearZ値
#define	VIEW_FAR_Z		(5000.0f)										// ビュー平面のFarZ値

#define	VALUE_MOVE_CAMERA	(20.0f)										// カメラの移動量
#define	VALUE_ROTATE_CAMERA	(D3DX_PI * 0.01f)							// カメラの回転量

//*****************************************************************************
// グローバル変数
//*****************************************************************************

//=============================================================================
// 初期化処理
//=============================================================================
Camera::Camera(void)
{
	pos = D3DXVECTOR3(POS_X_CAM, POS_Y_CAM, POS_Z_CAM);
	at  = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	up  = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// 視点と注視点の距離を計算
	float vx, vz;
	vx  = pos.x - at.x;
	vz  = pos.z - at.z;
	len = sqrtf(vx * vx + vz * vz);
	
}


//=============================================================================
// カメラの更新処理
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
// カメラの更新
//=============================================================================
void Camera::SetCamera(void) 
{
	// ビューマトリックス設定
	D3DXMatrixLookAtLH(&mtxView, &pos, &at, &up);

	SetViewMatrix(&mtxView);


//	float det;
//	D3DXMatrixInverse(&g_Camera.mtxInvView, &det, &g_Camera.mtxView);


	// プロジェクションマトリックス設定
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


