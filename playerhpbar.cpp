//=================================================
//
// 2D�|���S���̕`�揈�� (object2D.cpp)
// Author: Sohta Kuki
//
//=================================================

#include "playerhpbar.h"
#include "manager.h"
#include "3dplayer.h"
#include "3dboss.h"
#include "3dtornado.h"
#include "bosscallui.h"
#include "3dgoalobj.h"
#include "tornado_reloadUI.h"

//======================
// �R���X�g���N�^
//======================
CPlayerHpBar::CPlayerHpBar(int nPriority) : CObject2D(nPriority)
{
    m_fCurrentLife = 1.0f;
    m_fTargetLife = 1.0f;
    m_fLifeLerpSpeed = 0.15f;
}

//======================
// �f�X�g���N�^
//======================
CPlayerHpBar::~CPlayerHpBar()
{

}

//======================
// ����������
//======================
HRESULT CPlayerHpBar::Init()
{
    CObject2D::Init();

    VERTEX_2D* pVtx;

    //���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
    CObject2D::GetBuff()->Lock(0, 0, (void**)&pVtx, 0);

    //���_���W�̐ݒ�
    pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    pVtx[1].pos = D3DXVECTOR3(m_nSize.x, 0.0f, 0.0f);
    pVtx[2].pos = D3DXVECTOR3(0.0f, m_nSize.y, 0.0f);
    pVtx[3].pos = D3DXVECTOR3(m_nSize.x, m_nSize.y, 0.0f);

    pVtx[0].rhw = 1.0f;
    pVtx[1].rhw = 1.0f;
    pVtx[2].rhw = 1.0f;
    pVtx[3].rhw = 1.0f;

    pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
    pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
    pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
    pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

    //�e�N�X�`�����W�̐ݒ�
    pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
    pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
    pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
    pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

    pVtx += 4;

    CObject2D::GetBuff()->Unlock();

    return S_OK;
}

//======================
// �I������
//======================
void CPlayerHpBar::Uninit()
{
    CObject2D::Uninit();
}

//======================
// �X�V����
//======================
void CPlayerHpBar::Update()
{
    // ���݂̎c�ʒl���ԍX�V����
    float playerLife = C3dplayer::GetPlayerLife();
    float BossLife = C3dboss::GetBossLife();
    float TornadoLife = C3dplayer::GetTorNum();

    m_fTargetLife = playerLife; // �v���C���[�̗̖͂ڕW�l���X�V
    m_fTargetBossLife = BossLife;// �{�X�̗̖͂ڕW�l���X�V
    m_fTargetTorLife = TornadoLife;// �����̎c�ʂ̖ڕW�l���X�V

    // ���`��ԂŌ��ݒl�����炩�ɕύX
    m_fCurrentLife += (m_fTargetLife - m_fCurrentLife) * m_fLifeLerpSpeed;
    m_fBossCurrentLife += (m_fTargetBossLife - m_fBossCurrentLife) * m_fLifeLerpSpeed;
    m_fTorCurrentLife += (m_fTargetTorLife - m_fTorCurrentLife) * m_fLifeLerpSpeed;

    VERTEX_2D* pVtx;

    //���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
    CObject2D::GetBuff()->Lock(0, 0, (void**)&pVtx, 0);

    //�Q�[�W�̔w��ɂ��锼�����Ԃ̂��
    if (m_nBarType == 0 || m_nBarType == 1)
    {
        pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.8f);
        pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.8f);
        pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.8f);
        pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.8f);
    }

    //�ʏ�̃Q�[�W
    if (m_nBarType == 2 || m_nBarType == 3 || m_nBarType == 4 || m_nBarType == 5)
    {
        pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
        pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
        pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
        pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
    }

    //�v���C���[�̗̑͒l
    if (m_nBarType == 0)
    {
        if (CBossCallUI::GetEndStat() == true && C3dboss::GetBossEntry() == true && C3dgoalobj::GetStageNum() == 2 ||
            CBossCallUI::GetEndStat() == false && C3dboss::GetBossEntry() == false && C3dgoalobj::GetStageNum() == 2
            || C3dgoalobj::GetStageNum() == 0 || C3dgoalobj::GetStageNum() == 1)
        {
            //���_���W�̍X�V
            float barWidth = 50 * 0.3585f * (m_fCurrentLife * 0.3585f);

            pVtx[0].pos.x = CObject2D::GetPos().x - 50 * 0.5f;
            pVtx[0].pos.y = CObject2D::GetPos().y - 50 * 0.5f;

            pVtx[1].pos.x = (m_nSize.x + 75) + CObject2D::GetPos().x + barWidth;
            pVtx[1].pos.y = CObject2D::GetPos().y - 50 * 0.5f;

            pVtx[2].pos.x = CObject2D::GetPos().x - 50 * 0.5f;
            pVtx[2].pos.y = (m_nSize.y + CObject2D::GetPos().y) + 50 * 0.5f;

            pVtx[3].pos.x = (m_nSize.x + 75) + CObject2D::GetPos().x + barWidth;
            pVtx[3].pos.y = (m_nSize.y + CObject2D::GetPos().y) + 50 * 0.5f;
        }
    }

    //�{�X�̗̑͒l
    if (m_nBarType == 1)
    {
        if (C3dboss::GetBossEntry() == true)
        {
            float barBossWidth = 49.7 * 0.16f * (m_fBossCurrentLife * 0.16f);

            //���_���W�̍X�V
            pVtx[0].pos.x = CObject2D::GetPos().x - 50 * 0.5f;
            pVtx[0].pos.y = CObject2D::GetPos().y - 50 * 0.5f;

            pVtx[1].pos.x = (m_nSize.x + CObject2D::GetPos().x) + barBossWidth;
            pVtx[1].pos.y = CObject2D::GetPos().y - 50 * 0.5f;

            pVtx[2].pos.x = CObject2D::GetPos().x - 50 * 0.5f;
            pVtx[2].pos.y = (m_nSize.y + CObject2D::GetPos().y) + 50 * 0.5f;

            pVtx[3].pos.x = (m_nSize.x + CObject2D::GetPos().x) + barBossWidth;
            pVtx[3].pos.y = (m_nSize.y + CObject2D::GetPos().y) + 50 * 0.5f;
        }

        if (C3dboss::GetBossEntry() == false)
        {
            //���_���W�̍X�V
            for (int nCnt = 0; nCnt < 4; nCnt++)
            {
                pVtx[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
            }
        }
    }

    //�����̎c�ʒl
    if (m_nBarType == 2)
    {
        if (CBossCallUI::GetEndStat() == true && C3dboss::GetBossEntry() == true && C3dgoalobj::GetStageNum() == 2 ||
            CBossCallUI::GetEndStat() == false && C3dboss::GetBossEntry() == false && C3dgoalobj::GetStageNum() == 2
            || C3dgoalobj::GetStageNum() == 0 || C3dgoalobj::GetStageNum() == 1)
        {
            float barTorWidth = 50 * 0.4f * (m_fTorCurrentLife * 5.5);

            //���_���W�̍X�V
            pVtx[0].pos.x = CObject2D::GetPos().x - 50 * 0.5f;
            pVtx[0].pos.y = CObject2D::GetPos().y - 50 * 0.5f;

            pVtx[1].pos.x = (m_nSize.x + CObject2D::GetPos().x) + barTorWidth;
            pVtx[1].pos.y = CObject2D::GetPos().y - 50 * 0.5f;

            pVtx[2].pos.x = CObject2D::GetPos().x - 50 * 0.5f;
            pVtx[2].pos.y = (m_nSize.y + CObject2D::GetPos().y) + 50 * 0.5f;

            pVtx[3].pos.x = (m_nSize.x + CObject2D::GetPos().x) + barTorWidth;
            pVtx[3].pos.y = (m_nSize.y + CObject2D::GetPos().y) + 50 * 0.5f;
        }


        //�����̔����\����2�������ꍇ
        if (C3dplayer::GetTorNum() >= 2)
        {
            CTornadoReloadUI::DisplayTornadoReloadUI(0, CTornadoReloadUI::UIDISPLAY::UI_HIDDEN);
        }

        //�����̔����\����2�ȉ��������ꍇ
        if (C3dplayer::GetTorNum() < 2)
        {
            CTornadoReloadUI::DisplayTornadoReloadUI(0, CTornadoReloadUI::UIDISPLAY::UI_DISPLAY);
        }

        if (CBossCallUI::GetEndStat() == true && C3dboss::GetBossEntry() == false && C3dgoalobj::GetStageNum() == 2)
        {
            //���_���W�̍X�V
            for (int nCnt = 0; nCnt < 4; nCnt++)
            {
                pVtx[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
            }
        }
    }

    if (m_nBarType == 3)
    {
        if (CBossCallUI::GetEndStat() == true && C3dboss::GetBossEntry() == true && C3dgoalobj::GetStageNum() == 2 ||
            CBossCallUI::GetEndStat() == false && C3dboss::GetBossEntry() == false && C3dgoalobj::GetStageNum() == 2
            || C3dgoalobj::GetStageNum() == 0 || C3dgoalobj::GetStageNum() == 1)
        {
            //���_���W�̍X�V
            pVtx[0].pos.x = CObject2D::GetPos().x - 50 * 0.5f;
            pVtx[0].pos.y = CObject2D::GetPos().y - 50 * 0.5f;

            pVtx[1].pos.x = ((m_nSize.x + 75) + CObject2D::GetPos().x) + 50 * 0.3585f * (C3dplayer::GetPlayerLife() * 0.3585f);
            pVtx[1].pos.y = CObject2D::GetPos().y - 50 * 0.5f;

            pVtx[2].pos.x = CObject2D::GetPos().x - 50 * 0.5f;
            pVtx[2].pos.y = (m_nSize.y + CObject2D::GetPos().y) + 50 * 0.5f;

            pVtx[3].pos.x = ((m_nSize.x + 75) + CObject2D::GetPos().x) + 50 * 0.3585f * (C3dplayer::GetPlayerLife() * 0.3585f);
            pVtx[3].pos.y = (m_nSize.y + CObject2D::GetPos().y) + 50 * 0.5f;
        }

        if (CBossCallUI::GetEndStat() == true && C3dboss::GetBossEntry() == false && C3dgoalobj::GetStageNum() == 2)
        {
            //���_���W�̍X�V
            for (int nCnt = 0; nCnt < 4; nCnt++)
            {
                pVtx[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
            }
        }
    }

    if (m_nBarType == 4)
    {
        if (C3dboss::GetBossEntry() == true)
        {
            //���_���W�̍X�V
            pVtx[0].pos.x = CObject2D::GetPos().x - 50 * 0.5f;
            pVtx[0].pos.y = CObject2D::GetPos().y - 50 * 0.5f;

            pVtx[1].pos.x = (m_nSize.x + CObject2D::GetPos().x) + 49.7 * 0.16f * (C3dboss::GetBossLife() * 0.16f);
            pVtx[1].pos.y = CObject2D::GetPos().y - 50 * 0.5f;

            pVtx[2].pos.x = CObject2D::GetPos().x - 50 * 0.5f;
            pVtx[2].pos.y = (m_nSize.y + CObject2D::GetPos().y) + 50 * 0.5f;

            pVtx[3].pos.x = (m_nSize.x + CObject2D::GetPos().x) + 49.7 * 0.16f * (C3dboss::GetBossLife() * 0.16f);
            pVtx[3].pos.y = (m_nSize.y + CObject2D::GetPos().y) + 50 * 0.5f;
        }

        if (C3dboss::GetBossEntry() == false)
        {
            //���_���W�̍X�V
            for (int nCnt = 0; nCnt < 4; nCnt++)
            {
                pVtx[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
            }
        }
    }

    if (m_nBarType == 5)
    {
        if (CBossCallUI::GetEndStat() == true && C3dboss::GetBossEntry() == true && C3dgoalobj::GetStageNum() == 2 ||
            CBossCallUI::GetEndStat() == false && C3dboss::GetBossEntry() == false && C3dgoalobj::GetStageNum() == 2
            || C3dgoalobj::GetStageNum() == 0 || C3dgoalobj::GetStageNum() == 1)
        {
            //���_���W�̍X�V
            pVtx[0].pos.x = CObject2D::GetPos().x - 50 * 0.5f;
            pVtx[0].pos.y = CObject2D::GetPos().y - 50 * 0.5f;

            pVtx[1].pos.x = (m_nSize.x + CObject2D::GetPos().x) + 50 * 0.4f * (C3dplayer::GetTorNum() * 5.5);
            pVtx[1].pos.y = CObject2D::GetPos().y - 50 * 0.5f;

            pVtx[2].pos.x = CObject2D::GetPos().x - 50 * 0.5f;
            pVtx[2].pos.y = (m_nSize.y + CObject2D::GetPos().y) + 50 * 0.5f;

            pVtx[3].pos.x = (m_nSize.x + CObject2D::GetPos().x) + 50 * 0.4f * (C3dplayer::GetTorNum() * 5.5);
            pVtx[3].pos.y = (m_nSize.y + CObject2D::GetPos().y) + 50 * 0.5f;
        }

        //�����̔����\����2�������ꍇ
        if (C3dplayer::GetTorNum() >= 2)
        {
            CTornadoReloadUI::DisplayTornadoReloadUI(0, CTornadoReloadUI::UIDISPLAY::UI_HIDDEN);
        }

        //�����̔����\����2�ȉ��������ꍇ
        if (C3dplayer::GetTorNum() < 2)
        {
            CTornadoReloadUI::DisplayTornadoReloadUI(0, CTornadoReloadUI::UIDISPLAY::UI_DISPLAY);
        }

        if (CBossCallUI::GetEndStat() == true && C3dboss::GetBossEntry() == false && C3dgoalobj::GetStageNum() == 2)
        {
            //���_���W�̍X�V
            for (int nCnt = 0; nCnt < 4; nCnt++)
            {
                pVtx[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
            }
        }
    }

    //���_�o�b�t�@���A�����b�N����
    CObject2D::GetBuff()->Unlock();

    int nFadeState = CFade::GetFadeState();

    if (nFadeState == CFade::FADE_OUT)
    {
        CPlayerHpBar::Uninit();
    }
}

//======================
// �`�揈��
//======================
void CPlayerHpBar::Draw()
{
    CObject2D::Draw();
}

//======================
// �I�u�W�F�N�g��������
//======================
CPlayerHpBar* CPlayerHpBar::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int nBarType)
{
    CPlayerHpBar* PlayerHpBar = new CPlayerHpBar;

    PlayerHpBar->CObject2D::SetPos(pos);

    PlayerHpBar->m_nSize = size;

    PlayerHpBar->m_nBarType = nBarType;

    PlayerHpBar->Init();

    //�̗̓Q�[�W�̃e�N�X�`���̓ǂݍ���
    if (nBarType == 3)
    {
        LPDIRECT3DTEXTURE9 pTexture;

        //�e�N�X�`���̓ǂݍ���
        D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(), "data\\TEXTURE\\hpbar.png", &pTexture);

        PlayerHpBar->BindTexture(pTexture);
    }

    //�{�X�̗̑̓Q�[�W�̃e�N�X�`���̓ǂݍ���
    if (nBarType == 4)
    {
        LPDIRECT3DTEXTURE9 pTexture;

        //�e�N�X�`���̓ǂݍ���
        D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(), "data\\TEXTURE\\boss_hpbar.png", &pTexture);

        PlayerHpBar->BindTexture(pTexture);
    }

    //�����̎c�ʃQ�[�W�̓ǂݍ���
    if (nBarType == 2)
    {
        LPDIRECT3DTEXTURE9 pTexture;

        //�e�N�X�`���̓ǂݍ���
        D3DXCreateTextureFromFile(CManager::GetRenderer()->GetDevice(), "data\\TEXTURE\\tornado_Gauge.png", &pTexture);

        PlayerHpBar->BindTexture(pTexture);
    }

    return PlayerHpBar;
}
