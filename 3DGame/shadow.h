//=============================================================================
//
// �e���� [shadow.h]
// Author : 
//
//=============================================================================
#pragma once

class Shadow
{
private:
	D3DXMATRIX		mtxWorld;				// ���[���h�}�g���b�N�X
	D3DXVECTOR3		pos;					// �ʒu
	D3DXVECTOR3		rot;					// ��]
	D3DXVECTOR3		scl;					// �X�P�[��
	MATERIAL		material;				// �}�e���A��
	ID3D11Buffer*	vertexBuffer;			// ���_���
	int				texNo;					// �e�N�X�`���ԍ�
public:
	Shadow(D3DXVECTOR3 pos_, D3DXVECTOR3 scl_);
	~Shadow(void)	 {}
	void Update(void);
	void Draw(void);
	void SetPos(D3DXVECTOR3 pos_) { pos = pos_; }
};
