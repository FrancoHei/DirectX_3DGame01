//=============================================================================
//
// �J�������� [camera.h]
// Author : 
//
//=============================================================================
#pragma once


//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include <d3dx9.h>
#include "renderer.h"

#define CAMERA1CAMERA2 60

class Character;

class Camera
{
private:
	D3DXVECTOR3			pos;			// �J�����̎��_(�ʒu)
	D3DXVECTOR3			at;				// �J�����̒����_
	D3DXVECTOR3			up;				// �J�����̏�����x�N�g��
	D3DXVECTOR3			rot;			// �J�����̉�]
	float				len;			// �J�����̎��_�ƒ����_�̋���

	D3DXMATRIX			mtxView;		// �r���[�}�g���b�N�X
	D3DXMATRIX			mtxInvView;		// �r���[�}�g���b�N�X
	D3DXMATRIX			mtxProjection;	// �v���W�F�N�V�����}�g���b�N�X

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

		// �J�����̎��_���J������Y����]�ɑΉ������Ă���
		pos.x = at.x - sinf(rot.y) * len;
		pos.z = at.z - cosf(rot.y) * len;
	}
	
	bool GetIsUpdateCamera2() { return isUpdateCamera_2; }

	void SetCamera_2(void);
	void SetCamera_1(void);


	D3DXVECTOR3 GetRot() { return rot; }
};
