//=================================================
//
// �r���{�[�h�̃w�b�_�[�t�@�C�� (billboard.h)
// Author: Sohta Kuki
//
//=================================================
#ifndef _MESHFIELD_H_	
#define _MESHFIELD_H_	

#include "object3D.h"
#include  "objectX.h"

//�I�u�W�F�N�g2D�N���X
class CMeshField :public CObject3D
{
public:

	const int MESHFIELD_X_BLOCK = 2;
	const int MESHFIELD_Z_BLOCK = 2;

	const int  MESHFIELD_VERTEX_NUM = 14;
	const int  MESHFIELD_INDEX_NUM = 14;
	const int  MESHFIELD_PRIMITIVE_NUM = 12;

	// �萔�i�h�[���̕������j
	const int LATITUDE_DIVISIONS = 10; // �ܓx�̕�����
	const int LONGITUDE_DIVISIONS = 20; // �o�x�̕�����


	typedef struct
	{
		D3DXVECTOR3 pos;	// ���W
		D3DXVECTOR3 rot;	//����
	}Meshfield;

	CMeshField(int nPriority = 1);
	~CMeshField() override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	Meshfield GetMeshfield(void);
	static CMeshField* Create(D3DXVECTOR3 pos);
private:

	D3DXVECTOR3 m_nPos;
	D3DXVECTOR3 m_nSize;

	const int sphereDiv = 10;  // ���̕�����
	float m_fRadius;
	float m_fTexMoveSPD;
	static LPDIRECT3DTEXTURE9 m_pTextureMeshfield;
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffMeshfield;
	LPDIRECT3DINDEXBUFFER9  m_pldxBuffMeshField;
	D3DXMATRIX m_mtxWorldMeshfield;
	Meshfield m_Meshfield;

};

#endif