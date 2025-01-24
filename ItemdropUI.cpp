//=================================================
//
// �`���[�W�V���b�g�[�U����UI�\������ (3dchargeshotui.cpp)
// Author: Sohta Kuki
//
//=================================================

#include "ItemdropUI.h"
#include "manager.h"

bool CItemDropUI::m_bUse = false;

//======================
// �R���X�g���N�^
//======================
CItemDropUI::CItemDropUI(int nPriority) : CObject2D(nPriority)
{
	m_bUse = false;
	m_nDisplaytime = 0;
	m_nAlpha = 0;
}

//======================
// �f�X�g���N�^
//======================
CItemDropUI::~CItemDropUI()
{

}

//======================
// ����������
//======================
HRESULT CItemDropUI::Init()
{
	m_nAlpha = 0;

	CRenderer* Renderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = Renderer->GetDevice();

	if (FAILED(pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4 * MAX_OBJECT,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		nullptr)))
	{
		return E_FAIL;
	}

	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_nPos.x - m_nSize.x, m_nPos.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_nPos.x + m_nSize.x, m_nPos.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_nPos.x - m_nSize.x, m_nPos.y + m_nSize.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_nPos.x + m_nSize.x, m_nPos.y + m_nSize.y, 0.0f);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 0);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 0);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 0);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 0);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	pVtx += 4;

	m_pVtxBuff->Unlock();

	return S_OK;
}

//======================
// �I������
//======================
void CItemDropUI::Uninit()
{
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	if (m_pTexBuff != nullptr)
	{
		m_pTexBuff->Release();
		m_pTexBuff = nullptr;
	}


	CObject::Release();
}

//======================
// �X�V����
//======================
void CItemDropUI::Update()
{
	//�e�N�X�`���\���ς݂�������
	if (m_bUse == true)
	{
		m_nDisplaytime++;
		m_nAlpha += 5;

		if (m_nPos.y <= -5.0f && m_nDisplaytime <= 120)
		{
			m_nPos.y += 15.0f;
		}

		if (m_nPos.y >= -5.0f && m_nDisplaytime <= 120)
		{
			m_nPos.y = -5.0f;
		}

		//����̎��ԂɂȂ������\�������Z�b�g
		if (m_nDisplaytime >= 120)
		{
			m_nPos.y -= 8.0f;

			if (m_nPos.y <= -55.0f)
			{
				m_nDisplaytime = 0;
				m_bUse = false;
			}
		}
	}

	VERTEX_2D* pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_nPos.x - m_nSize.x, m_nPos.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_nPos.x + m_nSize.x, m_nPos.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_nPos.x - m_nSize.x, m_nPos.y + m_nSize.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_nPos.x + m_nSize.x, m_nPos.y + m_nSize.y, 0.0f);

	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, m_nAlpha);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, m_nAlpha);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, m_nAlpha);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, m_nAlpha);

	pVtx += 4;

	m_pVtxBuff->Unlock();

	//�t�F�[�h�̏�Ԃ��擾
	int nFadeState = CFade::GetFadeState();

	//�t�F�[�h�A�E�g�����狭���폜
	if (nFadeState == CFade::FADE_OUT)
	{
		CItemDropUI::Uninit();
	}
}

//======================
// �`�揈��
//======================
void CItemDropUI::Draw()
{
	CRenderer* Renderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = Renderer->GetDevice();

	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	pDevice->SetFVF(FVF_VERTEX_2D);


	if (m_bUse == true)
	{
		pDevice->SetTexture(0, m_pTexBuff);

		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
}

//======================
// �I�u�W�F�N�g��������
//======================
CItemDropUI* CItemDropUI::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CItemDropUI* ItemDropUI = new CItemDropUI;

	ItemDropUI->m_nPos = pos;

	ItemDropUI->m_nSize = size;

	ItemDropUI->Init();

	LPDIRECT3DTEXTURE9 pTexture;

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(), "data\\TEXTURE\\addlife_itemdrop000.png", &pTexture);

	ItemDropUI->BindTexture(pTexture);

	return ItemDropUI;
}

//=======================
//�e�N�X�`���̐ݒ�
//=======================
void CItemDropUI::BindTexture(LPDIRECT3DTEXTURE9 pTex)
{
	m_pTexBuff = pTex;
}


//======================
//�e�N�X�`����\��������
//======================
bool CItemDropUI::DisplayAddLifeUI()
{
	m_bUse = true;

	return m_bUse;
}