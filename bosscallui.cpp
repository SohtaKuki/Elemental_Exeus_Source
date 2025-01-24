//=================================================
//
// �X�^�[�g�R�[��UI�\������ (startcallui.cpp)
// Author: Sohta Kuki
//
//=================================================

#include "bosscallui.h"

bool CBossCallUI::m_bUse[NUM_ICON] = {};
bool CBossCallUI::m_bStartComplete = false;
bool CBossCallUI::m_bStartCallFlag = false;
bool CBossCallUI::m_bAnimationEnd = false;
bool CBossCallUI::m_bBeginCallUI = false;

//============================
//�R���X�g���N�^
//============================
CBossCallUI::CBossCallUI(int nPriority) : CObject2D(nPriority)
{
    for (int nCntBG = 0; nCntBG < NUM_ICON; nCntBG++)
    {
        m_pTexBuff[nCntBG] = nullptr;
    }

    m_bUse[0] = false;
    m_bUse[1] = false;
    m_bUse[2] = false;
    m_pVtxBuff = nullptr;
    m_nAlphaCnt = 255;
    m_nMissonAnim = 0;
    m_bAlphaSwitch = false;
    m_bImageSwitch = false;
    m_bStartComplete = false;
    m_bStartCallFlag = false;
    m_bAnimationEnd = false;
}

//============================
//�f�X�g���N�^
//============================
CBossCallUI::~CBossCallUI()
{

}

//=====================
// �w�i����������
//======================
HRESULT CBossCallUI::Init()
{

    CRenderer* Renderer = CManager::GetRenderer();
    LPDIRECT3DDEVICE9 pDevice = Renderer->GetDevice();

    int nCntBG;

    //�e�N�X�`�����W�̊J�n�ʒu�iV�l�j�̏�����
    for (nCntBG = 0; nCntBG < NUM_ICON; nCntBG++)
    {
        m_aPosTexV[nCntBG] = 0.0f;
    }

    if (FAILED(pDevice->CreateVertexBuffer(
        sizeof(VERTEX_2D) * 4 * NUM_ICON,
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

    for (nCntBG = 0; nCntBG < NUM_ICON; nCntBG++)
    {

        //���_���W�̐ݒ�
        pVtx[0].pos = D3DXVECTOR3((m_nPos[nCntBG].x - m_nSize[nCntBG].x), m_nPos[nCntBG].y, 0.0f);
        pVtx[1].pos = D3DXVECTOR3((m_nPos[nCntBG].x + m_nSize[nCntBG].x), m_nPos[nCntBG].y, 0.0f);
        pVtx[2].pos = D3DXVECTOR3((m_nPos[nCntBG].x - m_nSize[nCntBG].x), m_nPos[nCntBG].y + m_nSize[nCntBG].y, 0.0f);
        pVtx[3].pos = D3DXVECTOR3((m_nPos[nCntBG].x + m_nSize[nCntBG].x), m_nPos[nCntBG].y + m_nSize[nCntBG].y, 0.0f);

        //rhw�̐ݒ�
        pVtx[0].rhw = 1.0f;
        pVtx[1].rhw = 1.0f;
        pVtx[2].rhw = 1.0f;
        pVtx[3].rhw = 1.0f;

        //���_�J���[
        pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
        pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
        pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
        pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

        //�e�N�X�`�����W�̐ݒ�
        pVtx[0].tex = D3DXVECTOR2(m_aPosTexXV[nCntBG], m_aPosTexV[nCntBG]);
        pVtx[1].tex = D3DXVECTOR2(m_aPosTexXV[nCntBG] + 1.0f, m_aPosTexV[nCntBG]);
        pVtx[2].tex = D3DXVECTOR2(m_aPosTexXV[nCntBG], m_aPosTexV[nCntBG] + 1.0f);
        pVtx[3].tex = D3DXVECTOR2(m_aPosTexXV[nCntBG] + 1.0f, m_aPosTexV[nCntBG] + 1.0f);

        pVtx += 4;


    }

    //���_�o�b�t�@�A�����b�N
    m_pVtxBuff->Unlock();


    return S_OK;
}

//=================================
// �w�i�I������
//=================================
void CBossCallUI::Uninit()
{
    //�e�N�X�`���̔j��
    for (int nCntBG = 0; nCntBG < NUM_ICON; nCntBG++)
    {
        if (m_pTexBuff[nCntBG] != nullptr)
        {
            m_pTexBuff[nCntBG]->Release();
            m_pTexBuff[nCntBG] = nullptr;
        }
    }

    //���_�o�b�t�@�̔j��
    if (m_pVtxBuff != nullptr)
    {
        m_pVtxBuff->Release();
        m_pVtxBuff = nullptr;
    }

    CObject::Release();
}


//=========================
// �w�i�X�V����
//=========================
void CBossCallUI::Update()
{
    //�Q�[�����i�s�\�̎��̂ݒʂ�
    if (CScene::GetUpdateStat() == true)
    {

        if (m_bStartCallFlag == true && m_bUse[0] == false && m_bImageSwitch == false)
        {

            m_bUse[0] = true;
        }

        if (m_bStartCallFlag == true && m_bUse[0] == true)
        {
            if (m_nPos[0].y < 160.0f)
            {
                m_nPos[0].y += 4.0f;
            }

            if (m_nPos[0].y >= 160.0f)
            {
                m_nPos[0].y = 160.0f;
                m_nMissonAnim++;
            }


            if (m_nMissonAnim == 30)
            {
                m_nMissonAnim = 0;
                m_bImageSwitch = true;

            }
        }

        //=================
        //�ʃe�N�X�`����\��������
        //================
        if (m_bImageSwitch == true)
        {
            if (m_bUse[1] == false && m_bUse[2] == false && m_bAnimationEnd == false)
            {
                CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_SE_ENTRY_WARNING);
                m_bUse[1] = true;
                m_bUse[2] = true;
                m_bBeginCallUI = true;
            }

            //�����Ō���
            if (m_nPos[1].x >= 600.0f && m_nPos[1].x < 800.0f)
            {
                m_nPos[1].x -= 1.5f;
                m_nPos[2].x += 1.5f;
                m_bStartComplete = true;
            }

            //������̉���
            if (m_nPos[1].x <= 600.0f)
            {
                m_nPos[1].x -= 30.0f;
                m_nPos[2].x += 30.0f;
            }

            //����
            if (m_nPos[1].x >= 800.0f)
            {
                m_nPos[1].x -= 15.0f;
                m_nPos[2].x += 15.0f;
            }

            if (m_nPos[1].x < -1500.0f && m_nPos[2].x > -1500.0f)
            {
                m_bUse[0] = false;
                m_bUse[1] = false;
                m_bUse[2] = false;
                m_bAnimationEnd = true;
                m_bBeginCallUI = false;
            }
        }


        if (m_bAlphaSwitch == false)
        {
            m_nAlphaCnt--;
        }

        if (m_bAlphaSwitch == true)
        {
            m_nAlphaCnt++;
        }

        if (m_nAlphaCnt == 205)
        {
            m_bAlphaSwitch = true;
        }

        if (m_nAlphaCnt == 255)
        {
            m_bAlphaSwitch = false;
        }

        SetAlpha(m_nAlphaCnt);

    }

    //�t�F�[�h�̏�Ԃ��擾
    int nFadeState = CFade::GetFadeState();

    //�t�F�[�h�A�E�g�ɂȂ����ꍇ�A�I�������Ɉڍs
    if (nFadeState == CFade::FADE_OUT)
    {
        CBossCallUI::Uninit();
    }
}

void CBossCallUI::SetAlpha(int nAlpha)
{
    int nCntBG;
    VERTEX_2D* pVtx; //���_���ւ̃|�C���^

    //���_�o�b�t�@���b�N
    m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

    for (nCntBG = 0; nCntBG < NUM_ICON; nCntBG++)
    {

        //if (nCntBG == 0)
        //{
        //    m_aPosTexV[nCntBG] -= 0.00f;
        //}
        //else if (nCntBG == 1)
        //{
        //    m_aPosTexV[nCntBG] -= 0.003f;
        //}
        //else if (nCntBG == 2)
        //{
        //    m_aPosTexV[nCntBG] -= 0.0020f;
        //}

        ////�e�N�X�`�����W�̐ݒ�
        //pVtx[0].tex = D3DXVECTOR2(m_aPosTexXV[nCntBG], m_aPosTexV[nCntBG]);
        //pVtx[1].tex = D3DXVECTOR2(m_aPosTexXV[nCntBG] + 1.0f, m_aPosTexV[nCntBG]);
        //pVtx[2].tex = D3DXVECTOR2(m_aPosTexXV[nCntBG], m_aPosTexV[nCntBG] + 1.0f);
        //pVtx[3].tex = D3DXVECTOR2(m_aPosTexXV[nCntBG] + 1.0f, m_aPosTexV[nCntBG] + 1.0f);

        pVtx[0].pos = D3DXVECTOR3((m_nPos[nCntBG].x - m_nSize[nCntBG].x), m_nPos[nCntBG].y, 0.0f);
        pVtx[1].pos = D3DXVECTOR3((m_nPos[nCntBG].x + m_nSize[nCntBG].x), m_nPos[nCntBG].y, 0.0f);
        pVtx[2].pos = D3DXVECTOR3((m_nPos[nCntBG].x - m_nSize[nCntBG].x), m_nPos[nCntBG].y + m_nSize[nCntBG].y, 0.0f);
        pVtx[3].pos = D3DXVECTOR3((m_nPos[nCntBG].x + m_nSize[nCntBG].x), m_nPos[nCntBG].y + m_nSize[nCntBG].y, 0.0f);

        pVtx[0].col = D3DCOLOR_RGBA(m_nAlphaCnt, m_nAlphaCnt, m_nAlphaCnt, m_nAlphaCnt);
        pVtx[1].col = D3DCOLOR_RGBA(m_nAlphaCnt, m_nAlphaCnt, m_nAlphaCnt, m_nAlphaCnt);
        pVtx[2].col = D3DCOLOR_RGBA(m_nAlphaCnt, m_nAlphaCnt, m_nAlphaCnt, m_nAlphaCnt);
        pVtx[3].col = D3DCOLOR_RGBA(m_nAlphaCnt, m_nAlphaCnt, m_nAlphaCnt, m_nAlphaCnt);



        pVtx += 4;
    }


    //���_�o�b�t�@���A�����b�N����
    m_pVtxBuff->Unlock();
}

//=========================
// �w�i�`�揈��
//=========================
void CBossCallUI::Draw()
{
    int nCntBG;

    CRenderer* Renderer = CManager::GetRenderer();
    LPDIRECT3DDEVICE9 pDevice = Renderer->GetDevice();

    //���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
    pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(CObject::VERTEX_2D));

    //���_�t�H�[�}�b�g�̐ݒ�
    pDevice->SetFVF(FVF_VERTEX_2D);

    for (nCntBG = 0; nCntBG < NUM_ICON; nCntBG++)
    {
        if (m_bUse[nCntBG] == true)
        {
            //�e�N�X�`���̐ݒ�
            pDevice->SetTexture(0, m_pTexBuff[nCntBG]);

            //�|���S���̕`��
            pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBG * 4, 2);
        }
    }
}

void CBossCallUI::BindTexture(LPDIRECT3DTEXTURE9 pTex[NUM_ICON])
{
    for (int nCnt = 0; nCnt < NUM_ICON; nCnt++)
    {
        m_pTexBuff[nCnt] = pTex[nCnt];
    }
}

//============================
//�o�t�t�^UI�̐�������
//============================
CBossCallUI* CBossCallUI::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
    CBossCallUI* pBossCallUI;

    pBossCallUI = new CBossCallUI;

    for (int nCntBG = 0; nCntBG < NUM_ICON; nCntBG++)
    {
        pBossCallUI->m_nPos[nCntBG] = pos;
        pBossCallUI->m_nSize[nCntBG] = size;
    }

    pBossCallUI->m_nPos[1].y = 520.0f;
    pBossCallUI->m_nPos[1].x = 2200.0f;
    pBossCallUI->m_nSize[1].x = 1000.0f;
    pBossCallUI->m_nSize[1].y = 300.0f;

    pBossCallUI->m_nPos[2].y = -100.0f;
    pBossCallUI->m_nPos[2].x = -1200.0f;
    pBossCallUI->m_nSize[2].x = 1000.0f;
    pBossCallUI->m_nSize[2].y = 300.0f;

    if (FAILED(pBossCallUI->Init()))
    {
        delete pBossCallUI;
        return nullptr;
    }

    int nCntBG;

    LPDIRECT3DTEXTURE9 pTexture[NUM_ICON];

    //�e�N�X�`���ǂݍ���
    for (nCntBG = 0; nCntBG < NUM_ICON; nCntBG++)
    {
        switch (nCntBG)
        {
        case 0:
            D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(), "data\\TEXTURE\\bosscallui_text.png", &pTexture[nCntBG]);
            break;
        case 1:
            D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(), "data\\TEXTURE\\boss_warning.png", &pTexture[nCntBG]);
            break;
        case 2:
            D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(), "data\\TEXTURE\\boss_warning.png", &pTexture[nCntBG]);
            break;
        }

        if (!pTexture[nCntBG])
        {
            pBossCallUI->Uninit();
            delete pBossCallUI;
            return nullptr;
        }
    }

    pBossCallUI->BindTexture(pTexture);

    return pBossCallUI;
}

void CBossCallUI::StartCallUIBossFlag()
{
    m_bStartCallFlag = true;
}

//============================
//UI��\�������鏈��
//============================
bool CBossCallUI::DisplayBossCallUI(int nDisplayID, int DisplayOption)
{
    //�\������ꍇ
    if (DisplayOption == CBossCallUI::UIDISPLAY::UI_DISPLAY)
    {
        m_bUse[nDisplayID] = true;
    }

    //��\���ɂ���ꍇ
    if (DisplayOption == CBossCallUI::UIDISPLAY::UI_HIDDEN)
    {
        m_bUse[nDisplayID] = false;
    }

    return m_bUse[nDisplayID];
}


