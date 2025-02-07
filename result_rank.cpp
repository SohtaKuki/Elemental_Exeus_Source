//=================================================
//
// �^�C�g����ʔw�i�̏��� (titlebg.cpp)
// Author: Sohta Kuki
//
//=================================================

#include "result_rank.h"
#include "score.h"

bool CResultRank::m_bUse[NUM_RANK] = {};

//============================
//�R���X�g���N�^
//============================
CResultRank::CResultRank(int nPriority) : CObject2D(nPriority)
{
    for (int nCntBG = 0; nCntBG < NUM_RANK; nCntBG++)
    {
        m_bUse[nCntBG] = false;
        m_pTexBuff[nCntBG] = nullptr;
    }

    m_pVtxBuff = nullptr;
    m_nAlphaCnt = 255;
    m_bAlphaSwitch = false;
}

//============================
//�f�X�g���N�^
//============================
CResultRank::~CResultRank()
{

}

//=====================
// �w�i����������
//======================
HRESULT CResultRank::Init()
{

    CRenderer* Renderer = CManager::GetRenderer();
    LPDIRECT3DDEVICE9 pDevice = Renderer->GetDevice();

    int nCntBG;

    //�e�N�X�`�����W�̊J�n�ʒu�iV�l�j�̏�����
    for (nCntBG = 0; nCntBG < NUM_RANK; nCntBG++)
    {
        m_aPosTexV[nCntBG] = 0.0f;
    }

    if (FAILED(pDevice->CreateVertexBuffer(
        sizeof(VERTEX_2D) * 4 * NUM_RANK,
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

    for (nCntBG = 0; nCntBG < NUM_RANK; nCntBG++)
    {

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


    }

    //���_�o�b�t�@�A�����b�N
    m_pVtxBuff->Unlock();

    return S_OK;
}

//=================================
// �w�i�I������
//=================================
void CResultRank::Uninit()
{
    //�e�N�X�`���̔j��
    for (int nCntBG = 0; nCntBG < NUM_RANK; nCntBG++)
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
void CResultRank::Update()
{


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

    if (CScore::GetScore() >= 0 && CScore::GetScore() <= 50000)
    {
        m_bUse[RANK_D] = true;
    }

    if (CScore::GetScore() >= 50000 && CScore::GetScore() <= 115000)
    {
        m_bUse[RANK_C] = true;
    }

    if (CScore::GetScore() >= 115000 && CScore::GetScore() <= 155000)
    {
        m_bUse[RANK_B] = true;
    }

    if (CScore::GetScore() >= 155000 && CScore::GetScore() <= 205000)
    {
        m_bUse[RANK_A] = true;
    }

    if (CScore::GetScore() >= 205000)
    {
        m_bUse[RANK_S] = true;
    }

    //�t�F�[�h�̏�Ԃ��擾
    int nFadeState = CFade::GetFadeState();

    //�t�F�[�h�A�E�g�ɂȂ����ꍇ�A�I�������Ɉڍs
    if (nFadeState == CFade::FADE_OUT)
    {
        CResultRank::Uninit();
    }

}

void CResultRank::SetAlpha(int nAlpha)
{
    int nCntBG;
    VERTEX_2D* pVtx; //���_���ւ̃|�C���^

    //���_�o�b�t�@���b�N
    m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

    for (nCntBG = 0; nCntBG < NUM_RANK; nCntBG++)
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
void CResultRank::Draw()
{
    int nCntBG;

    CRenderer* Renderer = CManager::GetRenderer();
    LPDIRECT3DDEVICE9 pDevice = Renderer->GetDevice();

    //���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
    pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(CObject::VERTEX_2D));

    //���_�t�H�[�}�b�g�̐ݒ�
    pDevice->SetFVF(FVF_VERTEX_2D);

    for (nCntBG = 0; nCntBG < NUM_RANK; nCntBG++)
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

void CResultRank::BindTexture(LPDIRECT3DTEXTURE9 pTex[NUM_RANK])
{
    for (int nCnt = 0; nCnt < NUM_RANK; nCnt++)
    {
        m_pTexBuff[nCnt] = pTex[nCnt];
    }
}

//============================
//�o�t�t�^UI�̐�������
//============================
CResultRank* CResultRank::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
    CResultRank* pResultRank;

    pResultRank = new CResultRank;

    for (int nCntBG = 0; nCntBG < NUM_RANK; nCntBG++)
    {
        pResultRank->m_nPos[nCntBG] = pos;
        pResultRank->m_nSize[nCntBG] = size;
    }

    if (FAILED(pResultRank->Init()))
    {
        delete pResultRank;
        return nullptr;
    }

    int nCntBG;

    LPDIRECT3DTEXTURE9 pTexture[NUM_RANK];

    //�e�N�X�`���ǂݍ���
    for (nCntBG = 0; nCntBG < NUM_RANK; nCntBG++)
    {
        switch (nCntBG)
        {
        case 0:
            D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(), "data\\TEXTURE\\Rank_Layout\\Rank_D.png", &pTexture[nCntBG]);
            break;                                                                         
        case 1:                                                                            
            D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(), "data\\TEXTURE\\Rank_Layout\\Rank_C.png", &pTexture[nCntBG]);
            break;                                                                         
        case 2:                                                                            
            D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(), "data\\TEXTURE\\Rank_Layout\\Rank_B.png", &pTexture[nCntBG]);
            break;                                                                         
        case 3:                                                                            
            D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(), "data\\TEXTURE\\Rank_Layout\\Rank_A.png", &pTexture[nCntBG]);
            break;                                                                         
        case 4:                                                                            
            D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(), "data\\TEXTURE\\Rank_Layout\\Rank_S.png", &pTexture[nCntBG]);
            break;
        }

        if (!pTexture[nCntBG])
        {
            pResultRank->Uninit();
            delete pResultRank;
            return nullptr;
        }
    }

    pResultRank->BindTexture(pTexture);

    return pResultRank;
}

//============================
//UI��\�������鏈��
//============================
bool CResultRank::DisplayResultRank(int nDisplayID, int DisplayOption)
{
    //�\������ꍇ
    if (DisplayOption == CResultRank::UIDISPLAY::UI_DISPLAY)
    {
        m_bUse[nDisplayID] = true;
    }

    //��\���ɂ���ꍇ
    if (DisplayOption == CResultRank::UIDISPLAY::UI_HIDDEN)
    {
        m_bUse[nDisplayID] = false;
    }

    return m_bUse[nDisplayID];
}
