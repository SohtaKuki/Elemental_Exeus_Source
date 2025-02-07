//=================================================
//
// �^�C�}�[���� (timer.cpp)
// Author: Sohta Kuki
//
//=================================================

#include "timer.h"
#include "manager.h"
#include "object2D.h"
#include "player.h"
#include "explosion.h"
#include "enemy.h"
#include "block.h"
#include "scene.h"
#include "endcallui.h"
#include "3dgoalobj.h"

int CTimer::m_nTime = {};
int CTimer::m_nDisplayTime = {};
int CTimer::m_nTimerCnt = {};

//============================
//�R���X�g���N�^
//============================
CTimer::CTimer(int nPriority) : CObject2D(nPriority)
{

	bUpdateTime = false;
	for (int nCntTime = 0; nCntTime < 3; nCntTime++)
	{
		bUse[nCntTime] = true;
	}
}

//============================
//�f�X�g���N�^
//============================
CTimer::~CTimer()
{

}


//============================
//�^�C�}�[�̏���������
//============================
HRESULT CTimer::Init()
{
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

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	for (int nCntTime = 0; nCntTime < NUM_TIME; nCntTime++)
	{
		float offset = (nCntTime == 0) ? -10.0f : 0.0f; // 3���ڂ�������10�s�N�Z�����炷

		// ���_���W��ݒ�
		pVtx[0].pos = D3DXVECTOR3(m_nPos.x + (nCntTime * TEX_TIME_INTERVAL) + offset, m_nPos.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(m_nPos.x + m_nSize.x + (nCntTime * TEX_TIME_INTERVAL) + offset, m_nPos.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(m_nPos.x + (nCntTime * TEX_TIME_INTERVAL) + offset, m_nPos.y + m_nSize.y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(m_nPos.x + m_nSize.x + (nCntTime * TEX_TIME_INTERVAL) + offset, m_nPos.y + m_nSize.y, 0.0f);

		// rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		// ���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4;
	}


	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}

//============================
//�^�C�}�[�̏���������
//============================
void CTimer::Uninit()
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

//============================
//�^�C�}�[�̍X�V����
//============================
void CTimer::Update()
{
	if (CScene::GetUpdateStat() == true)
	{
		VERTEX_2D* pVtx;

		int aPosTexU[NUM_TIME];

		if (bUpdateTime == false)
		{
			m_nTimerCnt++;

			if (m_nTimerCnt == MAX_TIMESPEED)
			{
				m_nTime++; // ���Ԃ�1�b���Z
				m_nTimerCnt = 0; // �t���[���J�E���g���Z�b�g

				// ���P�ʕ\���̏������C��
				int minutes = m_nTime / 60; // �����v�Z
				int seconds = m_nTime % 60; // �b���v�Z
				m_nDisplayTime = minutes * 100 + seconds; // ���ƕb��g�ݍ��킹���\���`���ɕύX
			}
		}

		if (CManager::GetKeyboard()->GetTrigger(DIK_F1))
		{
			if (bUpdateTime == false)
			{
				bUpdateTime = true;
			}
		}

		if (CManager::GetKeyboard()->GetTrigger(DIK_F2))
		{
			if (bUpdateTime == true)
			{
				bUpdateTime = false;
			}
		}

		// ���Ԃ̒l���R�s�[
		int CopyTime = m_nDisplayTime;

		// �e���̒l���v�Z
		for (int nCntTime = NUM_TIME - 1; nCntTime >= 0; nCntTime--)
		{
			aPosTexU[nCntTime] = CopyTime % 10;
			CopyTime /= 10;
		}

		// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// �e�N�X�`�����W�̍X�V
		for (int nCntTime = 0; nCntTime < NUM_TIME; nCntTime++)
		{
			pVtx[0].tex = D3DXVECTOR2(aPosTexU[nCntTime] / 10.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2((aPosTexU[nCntTime] + 1) / 10.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(aPosTexU[nCntTime] / 10.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2((aPosTexU[nCntTime] + 1) / 10.0f, 1.0f);

			pVtx += 4;
		}

		// ���_�o�b�t�@���A�����b�N����
		m_pVtxBuff->Unlock();

		// �t�F�[�h��Ԏ擾
		int nFadeState = CFade::GetFadeState();

		// �t�F�[�h�A�E�g���ɏI������������
		if (nFadeState == CFade::FADE_OUT)
		{
			Uninit();
		}
	}
}



//============================
//�^�C�}�[�̕`�揈��
//============================
void CTimer::Draw()
{
	CRenderer* Renderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = Renderer->GetDevice();

	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	pDevice->SetFVF(FVF_VERTEX_2D);

	pDevice->SetTexture(0, m_pTexBuff);

	for (int nCntTime = 0; nCntTime < 3; nCntTime++)
	{
		if (bUse[nCntTime] == true)
		{
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntTime * 4, 2);
		}
	}
}

//============================
//�^�C�}�[�̐�������
//============================
CTimer* CTimer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CTimer* pTimer;

	pTimer = new CTimer;

	pTimer->SetType(TYPE::TIMER);
	pTimer->m_nPos = pos;
	pTimer->m_nSize = size;

	//�^�C�}�[�̏�����
	pTimer->Init();


	if (C3dgoalobj::GetStageNum() == 0 || C3dgoalobj::GetStageNum() == 1)
	{
		m_nTimerCnt = 0;
		m_nTime = 0;
		m_nDisplayTime = 0;
	}

	LPDIRECT3DTEXTURE9 pTexture;

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(), "data\\TEXTURE\\SCORE_NUMBER.png", &pTexture);

	pTimer->BindTexture(pTexture);

	return pTimer;
}

void CTimer::AddTimer(int nTime)
{
	m_nTime += nTime;
}

//=======================
//�e�N�X�`���̐ݒ�
//=======================
void CTimer::BindTexture(LPDIRECT3DTEXTURE9 pTex)
{
	m_pTexBuff = pTex;
}

