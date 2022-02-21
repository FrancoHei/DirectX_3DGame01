//=============================================================================
//
// カメラ処理 [camera.h]
// Author : 
//
//=============================================================================
#pragma once


//*****************************************************************************
// インクルードファイル
//*****************************************************************************
#include <d3dx9.h>
#include "renderer.h"

#define CAMERA1CAMERA2 60

class Character;

class Camera
{
private:
	D3DXVECTOR3			pos;			// カメラの視点(位置)
	D3DXVECTOR3			at;				// カメラの注視点
	D3DXVECTOR3			up;				// カメラの上方向ベクトル
	D3DXVECTOR3			rot;			// カメラの回転
	float				len;			// カメラの視点と注視点の距離

	D3DXMATRIX			mtxView;		// ビューマトリックス
	D3DXMATRIX			mtxInvView;		// ビューマトリックス
	D3DXMATRIX			mtxProjection;	// プロジェクションマトリックス

	bool isUpdateCamera_2 = false;
	bool isUpdateCamera_1 = false;

	int camera_1_camera_2 = CAMERA1CAMERA2;
public:
	 Camera(void);
	~Camera(void){}
	void Update(Character* character);
	void SetCamera(void);
	void SetCameraAT(D3DXVECTOR3 pos_)
	{
		at = pos_ ;

		// カメラの視点をカメラのY軸回転に対応させている
		pos.x = at.x - sinf(rot.y) * len;
		pos.z = at.z - cosf(rot.y) * len;
	}
	
	bool GetIsUpdateCamera2() { return isUpdateCamera_2; }

	void SetCamera_2(void);
	void SetCamera_1(void);


	D3DXVECTOR3 GetRot() { return rot; }
};
