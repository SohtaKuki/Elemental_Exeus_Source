//=================================================
//
// �X�^�[�g�R�[��UI�\������ (startcallui.cpp)
// Author: Sohta Kuki
//
//=================================================

#include "bossname_entry.h"
#include "3dboss.h"

bool CBossEntryUI::m_bUse[NUM_ICON] = {};
bool CBossEntryUI::m_bEndComplete = true;

//============================
//�R���X�g���N�^
//============================
CBossEntryUI::CBossEntryUI(int nPriority) : CObject2D(nPriority)
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
    m_bEndComplete = true;
}

//============================
//�f�X�g���N�^
//============================
CBossEntryUI::~CBossEntryUI()
{

}

//=====================
// �w�i����������
//======================
HRESULT CBossEntryUI::Init()
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
        switch (nCntBG)
        {
        case 0:
            //���_���W�̐ݒ�
            pVtx[0].pos = D3DXVECTOR3(m_nPos[nCntBG].x - m_nSize[nCntBG].x, m_nPos[nCntBG].y, 0.0f);
            pVtx[1].pos = D3DXVECTOR3(m_nPos[nCntBG].x + m_nSize[nCntBG].x, m_nPos[nCntBG].y, 0.0f);
            pVtx[2].pos = D3DXVECTOR3(m_nPos[nCntBG].x - m_nSize[nCntBG].x, m_nPos[nCntBG].y + m_nSize[nCntBG].y, 0.0f);
            pVtx[3].pos = D3DXVECTOR3(m_nPos[nCntBG].x + m_nSize[nCntBG].x, m_nPos[nCntBG].y + m_nSize[nCntBG].y, 0.0f);

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
            break;
        case 1:
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
            break;
        case 2:
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
            break;
        }



    }

    //���_�o�b�t�@�A�����b�N
    m_pVtxBuff->Unlock();


    return S_OK;
}

//=================================
// �w�i�I������
//=================================
void CBossEntryUI::Uninit()
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
void CBossEntryUI::Update()
{

    //�t�F�[�h�̏�Ԃ��擾
    int nFadeState = CFade::GetFadeState();

    //�t�F�[�h�A�E�g�ɂȂ����ꍇ�A�I�������Ɉڍs
    if (nFadeState == CFade::FADE_OUT)
    {
        CBossEntryUI::Uninit();
        return;
    }


    if (m_bUse[CBossEntryUI::ICON_BOSSNAME] == true)
    {

        if (m_nPos[CBossEntryUI::ICON_BOSSNAME].y > 420.0f)
        {
            m_nPos[CBossEntryUI::ICON_BOSSNAME].y -= 6.0f;
        }

        if (m_nPos[CBossEntryUI::ICON_BOSSNAME].y <= 420.0f)
        {
            m_nPos[CBossEntryUI::ICON_BOSSNAME].y = 420.0f;
        }


        if (C3dboss::GetBossEntry() == true)
        {
            m_bUse[CBossEntryUI::ICON_BOSSNAME] = false;
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

void CBossEntryUI::SetAlpha(int nAlpha)
{
    int nCntBG;
    VERTEX_2D* pVtx; //���_���ւ̃|�C���^

    //���_�o�b�t�@���b�N
    m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

    for (nCntBG = 0; nCntBG < NUM_ICON; nCntBG++)
    {


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
void CBossEntryUI::Draw()
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

void CBossEntryUI::BindTexture(LPDIRECT3DTEXTURE9 pTex[NUM_ICON])
{
    for (int nCnt = 0; nCnt < NUM_ICON; nCnt++)
    {
        m_pTexBuff[nCnt] = pTex[nCnt];
    }
}

//============================
//�o�t�t�^UI�̐�������
//============================
CBossEntryUI* CBossEntryUI::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
    CBossEntryUI* pBossEntryUI;

    pBossEntryUI = new CBossEntryUI;

    for (int nCntBG = 0; nCntBG < NUM_ICON; nCntBG++)
    {
        pBossEntryUI->m_nPos[nCntBG] = pos;
        pBossEntryUI->m_nSize[nCntBG] = size;
    }

    if (FAILED(pBossEntryUI->Init()))
    {
        delete pBossEntryUI;
        return nullptr;
    }

    int nCntBG;

    LPDIRECT3DTEXTURE9 pTexture[NUM_ICON];

    //�e�N�X�`���ǂݍ���
    for (nCntBG = 0; nCntBG < NUM_ICON; nCntBG++)
    {
        switch (nCntBG)
        {
        case 0: //�ʏ�S�[��
            D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(), "data\\TEXTURE\\boss_name.png", &pTexture[nCntBG]);
            break;
        case 1: //���s��
            D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(), "data\\TEXTURE\\billboard000.png", &pTexture[nCntBG]);
            break;
        case 2: //����S�[����
            D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(), "data\\TEXTURE\\spgoal_window.png", &pTexture[nCntBG]);
            break;
        }

        if (!pTexture[nCntBG])
        {
            pBossEntryUI->Uninit();
            delete pBossEntryUI;
            return nullptr;
        }
    }

    pBossEntryUI->BindTexture(pTexture);

    return pBossEntryUI;
}

//============================
//UI��\�������鏈��
//============================
bool CBossEntryUI::DisplayBossEntryUI(int nDisplayID, int DisplayOption)
{
    //�\������ꍇ
    if (DisplayOption == CBossEntryUI::UIDISPLAY::UI_DISPLAY)
    {
        m_bUse[nDisplayID] = true;
    }

    //��\���ɂ���ꍇ
    if (DisplayOption == CBossEntryUI::UIDISPLAY::UI_HIDDEN)
    {
        m_bUse[nDisplayID] = false;
    }

    //�N���A���̉���
    if (m_bUse[CBossEntryUI::ICON_BOSSNAME] == true)
    {
        CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_SE_BOSS_ENTRY_NAMEDISPLAY);
    }

    //SP�N���A���̉���
    else if (m_bUse[CBossEntryUI::ICON_SPSUCCESS] == true)
    {
        CManager::GetSound()->Stop();
        CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_SE_CLEAR);
    }

    //���s���̉���
    else if (m_bUse[CBossEntryUI::ICON_FAILED] == true)
    {
        CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_SE_FAILED);
    }

    return m_bUse[nDisplayID];
}
