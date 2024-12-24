//=================================================
//
// �^�C�g����ʔw�i�̏��� (titlebg.cpp)
// Author: Sohta Kuki
//
//=================================================

#include "titlebg.h"
#include "scene.h"
#include "sound.h"
#include "3dmeshfield.h"

//============================
//�R���X�g���N�^
//============================
CTitleBG::CTitleBG(int nPriority) : CObject2D(nPriority)
{
    m_bAnimSwitch = false;
}

//============================
//�f�X�g���N�^
//============================
CTitleBG::~CTitleBG()
{

}

//=====================
// �w�i����������
//======================
HRESULT CTitleBG::Init()
{

    CRenderer* Renderer = CManager::GetRenderer();
    LPDIRECT3DDEVICE9 pDevice = Renderer->GetDevice();

    int nCntBG;

    //�e�N�X�`���֘A�̏�����
    for (nCntBG = 0; nCntBG < NUM_BG; nCntBG++)
    {
        m_aPosTexV[nCntBG] = 0.0f;
        m_nColTex[nCntBG] = 255;
    }

    if (FAILED(pDevice->CreateVertexBuffer(
        sizeof(VERTEX_2D) * 4 * NUM_BG,
        D3DUSAGE_WRITEONLY,
        FVF_VERTEX_2D,
        D3DPOOL_MANAGED,
        &m_pVtxBuff,
        nullptr)))
    {
        return E_FAIL;
    }

    VERTEX_2D* pVtx; //���_���ւ̃|�C���^

    //���_�o�b�t�@���b�N
    m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

    for (nCntBG = 0; nCntBG < NUM_BG; nCntBG++)
    {
        //���_���W�̐ݒ�
        pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
        pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
        pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
        pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

        //rhw�̐ݒ�
        pVtx[0].rhw = 1.0f;
        pVtx[1].rhw = 1.0f;
        pVtx[2].rhw = 1.0f;
        pVtx[3].rhw = 1.0f;

        //���_�J���[
        pVtx[0].col = D3DCOLOR_RGBA(m_nColTex[nCntBG], m_nColTex[nCntBG], m_nColTex[nCntBG], 255);
        pVtx[1].col = D3DCOLOR_RGBA(m_nColTex[nCntBG], m_nColTex[nCntBG], m_nColTex[nCntBG], 255);
        pVtx[2].col = D3DCOLOR_RGBA(m_nColTex[nCntBG], m_nColTex[nCntBG], m_nColTex[nCntBG], 255);
        pVtx[3].col = D3DCOLOR_RGBA(m_nColTex[nCntBG], m_nColTex[nCntBG], m_nColTex[nCntBG], 255);

        //�e�N�X�`�����W�̐ݒ�
        pVtx[0].tex = D3DXVECTOR2(m_aPosTexXV[nCntBG], m_aPosTexV[nCntBG]);
        pVtx[1].tex = D3DXVECTOR2(m_aPosTexXV[nCntBG] + 1.0f, m_aPosTexV[nCntBG]);
        pVtx[2].tex = D3DXVECTOR2(m_aPosTexXV[nCntBG], m_aPosTexV[nCntBG] + 1.0f);
        pVtx[3].tex = D3DXVECTOR2(m_aPosTexXV[nCntBG] + 1.0f, m_aPosTexV[nCntBG] + 1.0f);

        pVtx += 4;
    }

    //���_�o�b�t�@�A�����b�N
    m_pVtxBuff->Unlock();
    CMeshField::Create(D3DXVECTOR3(50.0f, 3000.0f, 0.0f));

    CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_BGM);

    return S_OK;
}

//=================================
// �w�i�I������
//=================================
void CTitleBG::Uninit()
{
    //�e�N�X�`���̔j��
    for (int nCntBG = 0; nCntBG < NUM_BG; nCntBG++)
    {
        if (m_pTexBuff[nCntBG] != NULL)
        {
            m_pTexBuff[nCntBG]->Release();
            m_pTexBuff[nCntBG] = NULL;
        }
    }

    //���_�o�b�t�@�̔j��
    if (m_pVtxBuff != NULL)
    {
        m_pVtxBuff->Release();
        m_pVtxBuff = NULL;
    }

    CObject::Release();
}

//=========================
// �w�i�X�V����
//=========================
void CTitleBG::Update()
{
    int nCntBG;
    VERTEX_2D* pVtx; //���_���ւ̃|�C���^

    //���_�o�b�t�@���b�N
    m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

    if (m_bAnimSwitch == false && CScene::GetScreenSwitch() == true)
    {
        m_nColTex[2] -= 4;
    }

    if (m_bAnimSwitch == true && CScene::GetScreenSwitch() == true)
    {
        m_nColTex[2] += 4;
    }

    if (m_nColTex[2] == 195)
    {
        m_bAnimSwitch = true;
    }

    if (m_nColTex[2] == 255)
    {
        m_bAnimSwitch = false;
    }

    //�e��e�N�X�`���̍X�V����
    for (nCntBG = 0; nCntBG < NUM_BG; nCntBG++)
    {
        if (nCntBG == 0)
        {
            m_aPosTexV[nCntBG] -= 0.00f;
        }



        //==========={�����܂�}==================

        //���_�J���[
        pVtx[0].col = D3DCOLOR_RGBA(m_nColTex[nCntBG], m_nColTex[nCntBG], m_nColTex[nCntBG], 255);
        pVtx[1].col = D3DCOLOR_RGBA(m_nColTex[nCntBG], m_nColTex[nCntBG], m_nColTex[nCntBG], 255);
        pVtx[2].col = D3DCOLOR_RGBA(m_nColTex[nCntBG], m_nColTex[nCntBG], m_nColTex[nCntBG], 255);
        pVtx[3].col = D3DCOLOR_RGBA(m_nColTex[nCntBG], m_nColTex[nCntBG], m_nColTex[nCntBG], 255);

        //�e�N�X�`�����W�̐ݒ�
        pVtx[0].tex = D3DXVECTOR2(m_aPosTexXV[nCntBG], m_aPosTexV[nCntBG]);
        pVtx[1].tex = D3DXVECTOR2(m_aPosTexXV[nCntBG] + 1.0f, m_aPosTexV[nCntBG]);
        pVtx[2].tex = D3DXVECTOR2(m_aPosTexXV[nCntBG], m_aPosTexV[nCntBG] + 1.0f);
        pVtx[3].tex = D3DXVECTOR2(m_aPosTexXV[nCntBG] + 1.0f, m_aPosTexV[nCntBG] + 1.0f);

        pVtx += 4;
    }


    //���_�o�b�t�@���A�����b�N����
    m_pVtxBuff->Unlock();

    int nFadeState = CFade::GetFadeState();

    if (nFadeState == CFade::FADE_OUT)
    {
        
        CTitleBG::Uninit();
        return;
    }

}

//==================================================================================================
// �w�i�`�揈��
//==================================================================================================
void CTitleBG::Draw()
{
    int nCntBG;

    CRenderer* Renderer = CManager::GetRenderer();
    LPDIRECT3DDEVICE9 pDevice = Renderer->GetDevice();

    //���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
    pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

    //���_�t�H�[�}�b�g�̐ݒ�
    pDevice->SetFVF(FVF_VERTEX_2D);

    for (nCntBG = 0; nCntBG < NUM_BG; nCntBG++)
    {
        //�e�N�X�`���̐ݒ�
        pDevice->SetTexture(0, m_pTexBuff[nCntBG]);

        //�|���S���̕`��
        pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBG * 4, 2);
    }
}

void CTitleBG::BindTexture(LPDIRECT3DTEXTURE9 pTex[NUM_BG])
{
    for (int nCnt = 0; nCnt < NUM_BG; nCnt++)
    {
        m_pTexBuff[nCnt] = pTex[nCnt];
    }
}

//============================
//�^�C�g���̐�������
//============================
CTitleBG* CTitleBG::Create()
{
    CTitleBG* pTitleBG;

    pTitleBG = new CTitleBG;

    if (FAILED(pTitleBG->Init()))
    {
        delete pTitleBG;
        return nullptr;
    }

    int nCntBG;

    LPDIRECT3DTEXTURE9 pTexture[NUM_BG];

    //�e�N�X�`���ǂݍ���
    for (nCntBG = 0; nCntBG < NUM_BG; nCntBG++)
    {
        switch (nCntBG)
        {
        case 0:
            D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(), "data\\TEXTURE\\EE_Title.png", &pTexture[nCntBG]);
            break;
        case 1:
            D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(), "data\\TEXTURE\\PRESS_START_BIGBUT.png", &pTexture[nCntBG]);
            break;
        case 2:
            D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(), "data\\TEXTURE\\PRESS_START_BIGBUT_BG.png", &pTexture[nCntBG]);
            break;
        case 3:
            D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(), "data\\TEXTURE\\title_exit_button.png", &pTexture[nCntBG]);
            break;

        }

        if (!pTexture[nCntBG])
        {
            pTitleBG->Uninit();
            delete pTitleBG;
            return nullptr;
        }
    }

    pTitleBG->BindTexture(pTexture);

    return pTitleBG;
}