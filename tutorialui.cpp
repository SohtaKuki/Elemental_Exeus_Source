//===================================
//
// �|�[�Y���� [pause.cpp]
// Author: Sohta Kuki
//
//===================================

#include "tutorialui.h"
#include "input.h"

int CTutorialUI::m_nPauseSelect = 0;

//==========================
//�R���X�g���N�^
//==========================
CTutorialUI::CTutorialUI(int nPriority) : CObject2D(nPriority)
{
	m_nPauseSelect = 0;
}

//==========================
//�f�X�g���N�^
//==========================
CTutorialUI::~CTutorialUI()
{

}

//=============================
//�|�[�Y��ʂ̏���������
//=============================

HRESULT CTutorialUI::Init()
{
	CRenderer* Renderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = Renderer->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\tutorial000.png", &m_pTexturePauseSelect[TUTORIAL_UI_1]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\tutorial001.png", &m_pTexturePauseSelect[TUTORIAL_UI_2]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\tutorial002.png", &m_pTexturePauseSelect[TUTORIAL_UI_3]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\tutorial003.png", &m_pTexturePauseSelect[TUTORIAL_UI_4]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\tutorial004.png", &m_pTexturePauseSelect[TUTORIAL_UI_5]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuffPauseSelect,
		NULL);
	VERTEX_2D* pVtx;	//���_���̃|�C���^

	//���_�o�b�t�@�����b�N���āA���_���ւ̃|�C���^���擾
	m_pVtxBuffPauseSelect->Lock(0, 0, (void**)&pVtx, 0);
	pVtx[0].pos = D3DXVECTOR3(0, 0, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);


	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);



	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuffPauseSelect->Unlock();


	return S_OK;
}

//=============================
//�|�[�Y��ʂ̏I������
//=============================

void CTutorialUI::Uninit(void)
{
	for (int nCnt = 0; nCnt < TUTORIAL_UI_MAX; nCnt++)
	{
		//�e�N�X�`���̔j��
		if (m_pTexturePauseSelect[nCnt] != NULL)
		{
			m_pTexturePauseSelect[nCnt]->Release();
			m_pTexturePauseSelect[nCnt] = NULL;
		}
	}
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuffPauseSelect != NULL)
	{
		m_pVtxBuffPauseSelect->Release();
		m_pVtxBuffPauseSelect = NULL;
	}
}

//=============================
//�|�[�Y��ʂ̍X�V����
//=============================

void CTutorialUI::Update(void)
{
	int nFadeState = CFade::GetFadeState();

	if (nFadeState == CFade::FADE_OUT)
	{
		CTutorialUI::Uninit();
		return;
	}

	VERTEX_2D* pVtx;	//���_���̃|�C���^

	//���_�o�b�t�@�����b�N���āA���_���ւ̃|�C���^���擾
	m_pVtxBuffPauseSelect->Lock(0, 0, (void**)&pVtx, 0);

	D3DXVECTOR2 RightStickPos = CManager::GetJoypad()->GetStickPosition(CInputJoypad::STICKTYPE_RIGHT);


	if (CManager::GetKeyboard()->GetTrigger(DIK_LEFT) || CManager::GetJoypad()->GetStickTrigger(CInputJoypad::STICKTYPE_RIGHT, CInputJoypad::STICKANGLE_LEFT) == true)
	{
		CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_SE_SELECT);

		if (m_nPauseSelect > 0)
		{
			m_nPauseSelect--;
		}
		else if (m_nPauseSelect <= 0)
		{
			m_nPauseSelect = TUTORIAL_UI_5;
		}
	}


	if (CManager::GetKeyboard()->GetTrigger(DIK_RIGHT) || CManager::GetJoypad()->GetStickTrigger(CInputJoypad::STICKTYPE_RIGHT, CInputJoypad::STICKANGLE_RIGHT) == true)
	{
		CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_SE_SELECT);

		if (m_nPauseSelect < 4)
		{
			m_nPauseSelect++;
		}
		else if (m_nPauseSelect >= 2)
		{
			m_nPauseSelect = TUTORIAL_UI_1;
		}
	}
	//���_�o�b�t�@�̃A�����b�N
	m_pVtxBuffPauseSelect->Unlock();


}
//=============================
//�|�[�Y��ʂ̕`�揈��
//=============================
void CTutorialUI::Draw(void)
{
	CRenderer* Renderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = Renderer->GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuffPauseSelect, 0, sizeof(VERTEX_2D));
	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	//�e�N�X�`���̐ݒ�

	pDevice->SetTexture(0, m_pTexturePauseSelect[m_nPauseSelect]);
	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 4);
}

//=============================
//�|�[�Y��ʂ̎擾����
//=============================
int CTutorialUI::GetTutorialUI(void)
{
	return m_nPauseSelect;
}

//============================
//�^�C�g���̐�������
//============================
CTutorialUI* CTutorialUI::Create()
{
	CTutorialUI* pTutorialUI;

	pTutorialUI = new CTutorialUI;

	if (FAILED(pTutorialUI->Init()))
	{
		delete pTutorialUI;
		return nullptr;
	}

	return pTutorialUI;
}