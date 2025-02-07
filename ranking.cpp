//================================
//
// �����L���O���� (ranking.cpp)
// Author: Sohta Kuki
//
//================================

#include "ranking.h"
#include "score.h"

//======================
// �R���X�g���N�^
//======================
CRanking::CRanking(int nPriority) : CObject2D(nPriority)
{

}

//======================
// �f�X�g���N�^
//======================
CRanking::~CRanking()
{
    Uninit();
}

//=====================
//�����L���O��ʂ̏���������
//=====================
HRESULT CRanking::Init(void)
{
    int nCountRank;
    CRenderer* Renderer = CManager::GetRenderer();
    LPDIRECT3DDEVICE9 pDevice = Renderer->GetDevice();

    //�e�N�X�`���̓ǂݍ���
    D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\ranking_bg.png", &m_pTextureRanking[0]);
    D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\ranking_rank.png", &m_pTextureRanking[1]);

    //���_�o�b�t�@�𐶐�
    pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_RANKINGBG, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuffRanking, NULL);

    VERTEX_2D* pVtx; //���_���ւ̃|�C���^

    //���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
    m_pVtxBuffRanking->Lock(0, 0, (void**)&pVtx, 0);

    for (nCountRank = 0; nCountRank < MAX_RANKINGBG; nCountRank++)
    {
        //���_���W�̐ݒ�
        pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
        pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);
        pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
        pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);

        if (nCountRank == 1)
        {
            pVtx[0].pos = D3DXVECTOR3(200.0f, 170.0f, 0.0f);
            pVtx[1].pos = D3DXVECTOR3(370.0f, 170.0f, 0.0f);
            pVtx[2].pos = D3DXVECTOR3(200.0f, 658.0f, 0.0f);
            pVtx[3].pos = D3DXVECTOR3(370.0f, 658.0f, 0.0f);
        }
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

        if (nCountRank == 1)
        {
            pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
            pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
            pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
            pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
        }

        //�e�N�X�`�����W�̐ݒ�
        pVtx[0].tex = D3DXVECTOR2(2.0f, 0.0f);
        pVtx[1].tex = D3DXVECTOR2(3.0f, 0.0f);
        pVtx[2].tex = D3DXVECTOR2(2.0f, 1.0f);
        pVtx[3].tex = D3DXVECTOR2(3.0f, 1.0f);

        pVtx += 4;//���_�f�[�^�̃|�C���^��4���i�߂�
    }

    //���_�o�b�t�@���A�����b�N����
    m_pVtxBuffRanking->Unlock();

    //�e�N�X�`���̓ǂݍ���
    D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\SCORE_NUMBER_type2.png", &m_pTextureRankingscore);

    //���_�o�b�t�@�𐶐�
    pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_SCORE, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuffRankingscore, NULL);

    //���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
    m_pVtxBuffRankingscore->Lock(0, 0, (void**)&pVtx, 0);

    for (nCountRank = 0; nCountRank < MAX_SCORE; nCountRank++)
    {
        //���_���W�̐ݒ�
        pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
        pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
        pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
        pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

        //rhw�̐ݒ�
        pVtx[0].rhw = 1.0f;
        pVtx[1].rhw = 1.0f;
        pVtx[2].rhw = 1.0f;
        pVtx[3].rhw = 1.0f;

        pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
        pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
        pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
        pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

        //�e�N�X�`�����W�̐ݒ�
        pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
        pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
        pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
        pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
        pVtx += 4;

    }
    //���_�o�b�t�@���A�����b�N����
    m_pVtxBuffRankingscore->Unlock();

    SetRankingPos(D3DXVECTOR3(550.0f, 230.0f, 0.0f), 1);
    SetRankingPos(D3DXVECTOR3(550.0f, 320.0f, 0.0f), 2);
    SetRankingPos(D3DXVECTOR3(550.0f, 410.0f, 0.0f), 3);
    SetRankingPos(D3DXVECTOR3(550.0f, 500.0f, 0.0f), 4);
    SetRankingPos(D3DXVECTOR3(550.0f, 590.0f, 0.0f), 5);

    return S_OK;
}

//=====================
//�����L���O��ʂ̏I������
//=====================
void CRanking::Uninit(void)
{
    int nCountRank;

    for (nCountRank = 0; nCountRank < MAX_RANKINGBG; nCountRank++)
    {
        if (m_pTextureRanking[nCountRank] != NULL)
        {
            m_pTextureRanking[nCountRank]->Release();
            m_pTextureRanking[nCountRank] = NULL;
        }
    }

    if (m_pTextureRankingscore != NULL)
    {
        m_pTextureRankingscore->Release();
        m_pTextureRankingscore = NULL;
    }

    if (m_pVtxBuffRanking != NULL)
    {
        m_pVtxBuffRanking->Release();
        m_pVtxBuffRanking = NULL;
    }

    if (m_pVtxBuffRankingscore != NULL)
    {
        m_pVtxBuffRankingscore->Release();
        m_pVtxBuffRankingscore = NULL;
    }

}

//=====================
//�����L���O��ʂ̍X�V����
//=====================
void CRanking::Update(void)
{

    int nCountRank, nCountRank3;

    VERTEX_2D* pVtx; //���_���ւ̃|�C���^

    //���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
    m_pVtxBuffRankingscore->Lock(0, 0, (void**)&pVtx, 0);

    for (nCountRank3 = 0; nCountRank3 < MAX_RANK; nCountRank3++)
    {
        for (nCountRank = 0; nCountRank < 6; nCountRank++)
        {
            //�e�N�X�`�����W�̐ݒ�	
            pVtx[0].tex = D3DXVECTOR2(0.0f + m_aPosTexU[nCountRank3][nCountRank] * 0.1f, 0.0f);
            pVtx[1].tex = D3DXVECTOR2((0.1f + m_aPosTexU[nCountRank3][nCountRank] * 0.1f), 0.0f);
            pVtx[2].tex = D3DXVECTOR2(0.0f + m_aPosTexU[nCountRank3][nCountRank] * 0.1f, 1.0f);
            pVtx[3].tex = D3DXVECTOR2((0.1f + m_aPosTexU[nCountRank3][nCountRank] * 0.1f), 1.0f);
            pVtx += 4;
        }
    }

    //���_�o�b�t�@���A�����b�N����
    m_pVtxBuffRankingscore->Unlock();

    if (m_nRankUpdate != -1)
    {
        m_pVtxBuffRankingscore->Unlock();
    }

    if (CManager::GetKeyboard()->GetTrigger(DIK_RETURN) || CManager::GetJoypad()->GetTrigger(CInputJoypad::JOYKEY_A))
    {
        WriteRankingData();
    }

    if (m_nRankingTimer >= 800)
    {
        WriteRankingData();
    }

}

//=====================
//�����L���O��ʂ̕`�揈��
//=====================
void CRanking::Draw(void)
{
    int nCountRank;

    CRenderer* Renderer = CManager::GetRenderer();
    LPDIRECT3DDEVICE9 pDevice = Renderer->GetDevice();

    pDevice->SetStreamSource(0, m_pVtxBuffRanking, 0, sizeof(VERTEX_2D));

    //���_�t�H�[�}�b�g�̐ݒ�
    pDevice->SetFVF(FVF_VERTEX_2D);

    for (nCountRank = 0; nCountRank < MAX_RANKINGBG; nCountRank++)
    {
        //�e�N�X�`���̐ݒ�
        pDevice->SetTexture(0, m_pTextureRanking[nCountRank]);

        //�|���S���̕`��
        pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCountRank * 4, 2);
    }

    pDevice->SetStreamSource(0, m_pVtxBuffRankingscore, 0, sizeof(VERTEX_2D));

    //���_�t�H�[�}�b�g�̐ݒ�
    pDevice->SetFVF(FVF_VERTEX_2D);

    //�e�N�X�`���̐ݒ�
    pDevice->SetTexture(0, m_pTextureRankingscore);

    for (nCountRank = 0; nCountRank < MAX_SCORE; nCountRank++)
    {
        //�|���S���̕`��
        pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCountRank * 4, 2);
    }
}

//=====================
//�����L���O�̃��Z�b�g����
//=====================
void CRanking::ResetRanking(void)
{
    int nCountRank;

    FILE* pFile;//�t�@�C���|�C���^��錾
    pFile = fopen("data\\ranking.bin", "rb");//�t�@�C�����J��
    if (pFile != NULL)
    {
        for (nCountRank = 0; nCountRank < MAX_RANK; nCountRank++)
        {
            fread(&m_aRankScore[nCountRank].nScore, sizeof(int), 1, pFile);//�t�@�C�����琔�l��ǂݍ���
        }
        fclose(pFile);//�t�@�C�������
    }
}

//=====================
//�����L���O�̐ݒ菈��
//=====================
void CRanking::SetRanking(int nScore)
{
    ResetRanking();

    int nCountRank, nCountRank2, swap, swap2;

    swap2 = nScore;

    for (nCountRank = 0; nCountRank < MAX_RANK; nCountRank++)
    {
        if (nScore > m_aRankScore[nCountRank].nScore)
        {
            swap = m_aRankScore[nCountRank].nScore;
            m_aRankScore[nCountRank].nScore = swap2;
            swap2 = swap;
            m_nRankUpdate++;
        }
    }

    for (nCountRank = 0; nCountRank < MAX_RANK; nCountRank++)
    {
        m_aPosTexU[nCountRank][0] = m_aRankScore[nCountRank].nScore % 1000000 / 100000;
        m_aPosTexU[nCountRank][1] = m_aRankScore[nCountRank].nScore % 100000 / 10000;
        m_aPosTexU[nCountRank][2] = m_aRankScore[nCountRank].nScore % 10000 / 1000;
        m_aPosTexU[nCountRank][3] = m_aRankScore[nCountRank].nScore % 1000 / 100;
        m_aPosTexU[nCountRank][4] = m_aRankScore[nCountRank].nScore % 100 / 10;
        m_aPosTexU[nCountRank][5] = m_aRankScore[nCountRank].nScore % 10 / 1;
    }
}

//=====================
//�����L���O�̏����o������
//=====================
void CRanking::WriteRankingData(void)
{
    int nCountRank;

    FILE* pFile;//�t�@�C���|�C���^��錾
    pFile = fopen("data\\ranking.bin", "wb");//�t�@�C�����J��
    if (pFile != NULL)
    {
        for (nCountRank = 0; nCountRank < MAX_RANK; nCountRank++)
        {
            fwrite(&m_aRankScore[nCountRank].nScore, sizeof(int), 1, pFile);//�t�@�C�����琔�l��ǂݍ���
        }
        fclose(pFile);//�t�@�C�������
    }
}

//=====================
//�X�R�A�̕\������
//=====================
void CRanking::SetRankingPos(D3DXVECTOR3 pos, int rank)
{
    int nCount;
    m_aRankScore[rank - 1].pos = pos;

    VERTEX_2D* pVtx; //���_���ւ̃|�C���^

    //���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
    m_pVtxBuffRankingscore->Lock(0, 0, (void**)&pVtx, 0);

    pVtx += 24 * (rank - 1);
    for (nCount = 0; nCount < 6; nCount++)
    {
        //���_���W�̐ݒ�
        pVtx[0].pos = D3DXVECTOR3(m_aRankScore[rank - 1].pos.x + (nCount * SCORE_NUM_SPACE) - SCORE_NUM_SCALEX, m_aRankScore[rank - 1].pos.y - SCORE_NUM_SCALEY, 0.0f);
        pVtx[1].pos = D3DXVECTOR3(m_aRankScore[rank - 1].pos.x + (nCount * SCORE_NUM_SPACE) + SCORE_NUM_SCALEX, m_aRankScore[rank - 1].pos.y - SCORE_NUM_SCALEY, 0.0f);
        pVtx[2].pos = D3DXVECTOR3(m_aRankScore[rank - 1].pos.x + (nCount * SCORE_NUM_SPACE) - SCORE_NUM_SCALEX, m_aRankScore[rank - 1].pos.y + SCORE_NUM_SCALEY, 0.0f);
        pVtx[3].pos = D3DXVECTOR3(m_aRankScore[rank - 1].pos.x + (nCount * SCORE_NUM_SPACE) + SCORE_NUM_SCALEX, m_aRankScore[rank - 1].pos.y + SCORE_NUM_SCALEY, 0.0f);

        pVtx += 4;
    }

    //���_�o�b�t�@���A�����b�N����
   m_pVtxBuffRankingscore->Unlock();

}

CRanking* CRanking::Create()
{
	CRanking* ranking = nullptr;

	ranking = new CRanking;

	ranking->SetType(TYPE::RANKING);

	ranking->Init();

	ranking->SetRanking(CScore::GetScore());

	return ranking;
}