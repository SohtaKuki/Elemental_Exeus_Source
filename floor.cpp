//=================================================
//
// ���̕`�揈�� (floor.cpp)
// Author: Sohta Kuki
//
//=================================================

#include "floor.h"

//======================
// �R���X�g���N�^
//======================
CFloor::CFloor(int nPriority) : CModel(nPriority)
{

}

//======================
// �f�X�g���N�^
//======================
CFloor::~CFloor()
{

}

HRESULT CFloor::Init()
{
	CRenderer* Renderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = Renderer->GetDevice();

	// ���_�o�b�t�@�̍쐬
	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * 4 * MAX_OBJECT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		nullptr)))
	{
		return E_FAIL;
	}

	VERTEX_3D* pVtx;

	// ���_�f�[�^�̐ݒ�
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	int row = static_cast<int>(sqrt(MAX_OBJECT)); // �l�p�`�|���S���̍s��
	int col = row; // ��
	float spacing = m_nSize.x * 1.0f / 10; // �|���S���Ԃ̋���

	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < col; ++j)
		{
			int index = (i * col + j) * 4;

			// �e�l�p�`�̒��S�ʒu���v�Z
			float centerX = j * spacing - (col / 2.0f) * spacing;
			float centerZ = i * spacing - (row / 2.0f) * spacing;

			// ���_���W
			pVtx[index + 0].pos = D3DXVECTOR3(centerX - (m_nSize.x / 10), 0.0f, centerZ + (m_nSize.z / 10));
			pVtx[index + 1].pos = D3DXVECTOR3(centerX + (m_nSize.x / 10), 0.0f, centerZ + (m_nSize.z / 10));
			pVtx[index + 2].pos = D3DXVECTOR3(centerX - (m_nSize.x / 10), 0.0f, centerZ - (m_nSize.z / 10));
			pVtx[index + 3].pos = D3DXVECTOR3(centerX + (m_nSize.x / 10), 0.0f, centerZ - (m_nSize.z / 10));

			// �@���x�N�g��
			for (int k = 0; k < 4; ++k)
			{
				pVtx[index + k].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
				pVtx[index + k].col = D3DCOLOR_RGBA(255, 255, 255, 255); // ��
			}

			// �e�N�X�`�����W
			pVtx[index + 0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[index + 1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[index + 2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[index + 3].tex = D3DXVECTOR2(1.0f, 1.0f);
		}
	}

	m_pVtxBuff->Unlock();

	return S_OK;
}




//======================
// �I������
//======================
void CFloor::Uninit()
{
	CObject3D::Uninit();
}

//======================
// �X�V����
//======================
void CFloor::Update()
{



	int nFadeState = CFade::GetFadeState();

	if (nFadeState == CFade::FADE_OUT)
	{
		CFloor::Uninit();
	}
}

void CFloor::Draw()
{
	CRenderer* Renderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = Renderer->GetDevice();

	// ���[���h�}�g���b�N�X�ݒ�
	D3DXMATRIX mtxRot, mtxTrans;
	D3DXMatrixIdentity(&m_mtxWorld);

	// ��]�ƈʒu�̓K�p
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	D3DXMatrixTranslation(&mtxTrans, m_nPos.x, m_nPos.y, m_nPos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	pDevice->SetFVF(FVF_VERTEX_3D);
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));
	pDevice->SetTexture(0, m_pTexBuff);

	// �|���S�����Ƃɕ`��
	for (int i = 0; i < MAX_OBJECT; ++i)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * 4, 2);
	}
}

//======================
// �I�u�W�F�N�g��������
//======================
CFloor* CFloor::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size,int nType)
{
	CFloor* Floor = nullptr;

	Floor = new CFloor;

	Floor->m_nPos = pos;

	Floor->m_nSize = size;

	//�������ɐ��������ꍇ
	if (SUCCEEDED(Floor->Init()))
	{
		//�e�N�X�`���ǂݍ��ݑI��
		if (nType == 0)
		{
			Floor->SetType(TYPE::FLOOR);
			Floor->Load("data\\TEXTURE\\dark_tile.png");
		}

		else if (nType == 1)
		{
			Floor->SetType(TYPE::FLOOR);
			Floor->Load("data\\TEXTURE\\stone_road.jpg");
		}


		//�e�N�X�`���̐ݒ�
		Floor->BindTexture(Floor->m_pTexBuff);
	}

	return Floor;
}

//======================
// �e�N�X�`�����[�h����
//======================
HRESULT CFloor::Load(LPCSTR textureFileName)
{
	LPDIRECT3DDEVICE9 pDevice = nullptr;
	pDevice = CManager::GetRenderer()->GetDevice();

	if (FAILED(D3DXCreateTextureFromFile(pDevice, textureFileName, &m_pTexBuff)))
	{
		return E_FAIL;
	}

	return S_OK;
}

//======================
// �e�N�X�`���A�����[�h(�I��)����
//======================
void CFloor::Unload()
{
	//if (m_pTexBuff != nullptr)
	//{
	//	m_pTexBuff->Release();
	//	m_pTexBuff = nullptr;
	//}
}

//===========================
// ���̓����蔻��
//===========================
bool CFloor::Collision3DFloor(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3* pMove, float fWidth, float fHeight)
{
	bool bLanding = false; // �d�͂�K�������ꍇ�̂ݎg�p

	D3DXVECTOR3 Pos = CObject3D::GetPos();

	// �E�������蔻��
	if (pPos->x - fWidth <= Pos.x + m_nSize.x && pPosOld->x - fWidth >= Pos.x + m_nSize.x && pPos->z - fHeight < Pos.z + m_nSize.z && pPos->z > Pos.z - m_nSize.z && pPos->y < Pos.y+ m_nSize.y && pPos->y > Pos.y- m_nSize.y)
	{
		pPos->x = Pos.x + m_nSize.x + fWidth;
	}
	// ���������蔻��
	else if (pPos->x + fWidth >= Pos.x - m_nSize.x && pPosOld->x + fWidth <= Pos.x - m_nSize.x && pPos->z - fHeight < Pos.z + m_nSize.z && pPos->z > Pos.z - m_nSize.z && pPos->y < Pos.y+ m_nSize.y && pPos->y > Pos.y- m_nSize.y)
	{
		pPos->x = Pos.x - m_nSize.x - fWidth;
	}
	// �O�������蔻��
	if (pPos->x - fWidth < Pos.x + m_nSize.x && pPos->x + fWidth > Pos.x - m_nSize.x && pPos->z - fHeight <= Pos.z + m_nSize.z && pPosOld->z - fHeight >= Pos.z + m_nSize.z && pPos->y < Pos.y+ m_nSize.y && pPos->y > Pos.y- m_nSize.y)
	{
		pPos->z = Pos.z + m_nSize.z + fHeight;
	}
	// �㑤�����蔻��
	else if (pPos->x - fWidth < Pos.x + m_nSize.x && pPos->x + fWidth > Pos.x - m_nSize.x && pPos->z >= Pos.z - m_nSize.z && pPosOld->z <= Pos.z - m_nSize.z && pPos->y < Pos.y+ m_nSize.y && pPos->y > Pos.y- m_nSize.y)
	{
		pPos->z = Pos.z - m_nSize.z - fHeight;

	}

	// y���W�㑤�����蔻��
	if (pPos->x - fWidth < Pos.x + m_nSize.x && pPos->x + fWidth > Pos.x - m_nSize.x && pPos->y - fHeight <= Pos.y+ m_nSize.y && pPosOld->y - fHeight >= Pos.y+ m_nSize.y && pPos->z < Pos.z + m_nSize.z && pPos->z > Pos.z - m_nSize.z)
	{
		pPos->y = Pos.y+ m_nSize.y + fHeight;
		bLanding = true;
	}

	return bLanding;
}
