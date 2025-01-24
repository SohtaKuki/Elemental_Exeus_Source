//=================================================
//
// 3D���f���̃v���C���[�̕\������ (3dboss.cpp)
// Author: Sohta Kuki
//
//=================================================

#include "3dblock.h"
#include "3dmoveblock.h"
#include "player.h"
#include "block.h"
#include "startobj.h"
#include "3ditem.h"
#include "3dbullet.h"
#include "3dchargebullet.h"
#include "3denemy.h"
#include "3dgoalobj.h"
#include "timer.h"
#include "floor.h"
#include "score.h"
#include "3dbuffui.h"
#include "scene.h"
#include "endcallui.h"
#include "3dexplosion.h"
#include "3dslashwind.h"
#include "3dbosstornado.h"
#include "3dboss.h"
#include "3dgoalobj.h"
#include "score.h"
#include "bosscallui.h"
#include "camera.h"
#include "bossname_entry.h"
#include "3dbossatk_ui.h"
#include "3dplayer.h"
#include "3dslashwind_boss.h"
#include "3dbossatk_ui_diag.h"
#include "3dexplosion_sub.h"

LPDIRECT3DTEXTURE9 C3dboss::m_pTexBuff = nullptr;
int C3dboss::m_nLife = 0;
bool C3dboss::m_bEntry = false;
D3DXVECTOR3 C3dboss::m_nPos = {};
D3DVERTEXELEMENT9 C3dboss::m_aElements[MAX_FVF_DECL_SIZE] = {};
D3DXVECTOR3 C3dboss::m_rot = {};

//======================
// �R���X�g���N�^
//======================
C3dboss::C3dboss(int nPriority) : CModel(nPriority)
{
    m_nLife = BOSS_LIFE;
    m_nJumpCnt = 0;
    m_nWalkSoundCnt = 0;
    m_bIsCollision = false;
    m_bJumping = false;
    m_bFlying = false;
    m_nFlyTimer = 0;
    m_bDashAtk = false;
    m_bWiredAtk = false;
    m_bFlyAtk = false;
    m_nLRPos = 0;
    m_bBossUPzone = false;
    m_fRotSpeed = 0.0f;
    m_nACTIONTimer = 0;
    random_number = 0;
    m_bBossSPATK = false;
    m_bBossPowerUP = false;
    bUse = false;
    m_bEntry = false;
    m_nBossDmgColorTimer = 0;
    m_bBossDMGState = false;
}

//======================
// �f�X�g���N�^
//======================
C3dboss::~C3dboss()
{

}

//======================
// ����������
//======================
HRESULT C3dboss::Init()
{
    //������
    if (FAILED(CModel::Init()))
    {
        return E_FAIL;
    }

    //���[�V�����̏�����
    for (int nCount = 0; nCount < MAX_MOTION; nCount++)
    {
        MotionSet[nCount].Loop = false;
        MotionSet[nCount].NumKey = 0;
        for (int nKeySetCount = 0; nKeySetCount < MAX_KEYSET; nKeySetCount++)
        {
            MotionSet[nCount].KeySet[nKeySetCount].Frame = 0;

            for (int nKeyCount = 0; nKeyCount < BOSS_MODEL; nKeyCount++)
            {
                MotionSet[nCount].KeySet[nKeySetCount].aKey[nKeyCount].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
                MotionSet[nCount].KeySet[nKeySetCount].aKey[nKeyCount].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
            }
        }
    }

    for (int nCnt = 0; nCnt < BOSS_MODEL; nCnt++)
    {
        m_pBuffMat[nCnt] = 0;
    }

    return S_OK;
}

//======================
// �I������
//======================
void C3dboss::Uninit()
{
    if (m_pTexBuff != nullptr)
    {
        m_pTexBuff->Release();
        m_pTexBuff = nullptr;
    }

    for (int i = 0; i < BOSS_MODEL; i++)
    {
        if (m_pMesh[i] != nullptr)
        {
            m_pMesh[i]->Release();
            m_pMesh[i] = nullptr;
        }
        if (m_pBuffMat[i] != nullptr)
        {
            m_pBuffMat[i]->Release();
            m_pBuffMat[i] = nullptr;
        }
    }

    CModel::Uninit();
}



//======================
// �X�V����
//======================
void C3dboss::Update()
{
    //�Q�[�����i�s�\�̎��̂ݒʂ�
    if (CScene::GetUpdateStat() == true)
    {
        C3dboss::ModelMotion();

        D3DXVECTOR3 Pos = CObject3D::GetPos();

        if (CBossCallUI::GetEndStat() == true)
        {
            if (Pos.y > 40.0f && m_bEntry == false)
            {
                m_n3DBossMove.y -= 0.15f;
                bUse = true;
            }

            if (Pos.y <= 40.0f && m_bEntry == false)
            {
                SetPlayerMotion(MOTION_ENTRY);
                MotionUse = true;

            }
        }

        //�o�����o�̃��[�V����
        if (Motion == MOTION_ENTRY)
        {
            if (m_nMotionCnt == 0 && m_nFrameCnt == 0)
            {
                CManager::GetSound()->Stop(CSound::SOUND_LABEL_SE_BOSS_ENTRY_MOVE);
                CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_SE_BOSS_TORNADO_STARTUP);
            }

            if (m_nMotionCnt == 0 && m_nFrameCnt == 20)
            {
                CBossEntryUI::DisplayBossEntryUI(CBossEntryUI::ICONDISPLAY::ICON_BOSSNAME, CBossCallUI::UIDISPLAY::UI_DISPLAY);
            }

            if (m_nMotionCnt == 2 && m_nFrameCnt == 0)
            {
                /*CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_SE_BOSS_ENTRY_NAMEDISPLAY);*/
                CManager::GetSound()->Stop(CSound::SOUND_LABEL_SE_BOSS_TORNADO_STARTUP);
                CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_SE_BOSS_ENTRY_MOTION);
                CCamera::SetShake(40, 10.0f);
            }

            if (m_nMotionCnt == 4 && m_nFrameCnt == 15)
            {
                CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_BGM_STAGE_BOSS);
                m_bEntry = true;
            }
        }


        //SetPlayerPos();

        int nCnt = 0;
        bool bMove = false;

        //�v���C���[�̍ő�̗͒l�𒴂��Ȃ��悤�ɂ���
        if (m_nLife >= BOSS_LIFE)
        {
            m_nLife = BOSS_LIFE;
        }


        ////�d�͂̓K�p
        //m_n3DBossMove.y -= 1.5f;


        //�v���C���[��HP��0�ȏ�̏ꍇ�̂ݒʂ�
        if (m_nLife > 0 && m_bEntry == true)
        {

            if (MotionUse == false)
            {
                if (m_nLife > 260)
                {
                    m_bBossPowerUP = false;
                }

                if (m_nLife < 260)
                {
                    m_bBossPowerUP = true;
                }

                m_nACTIONTimer++;
            }

            srand(time(0));


            CObject* pObjPos = CObject::GetObj(3, 1);

            if (pObjPos != nullptr)
            {
                CObject::TYPE type = pObjPos->GetType();

                C3dplayer* p3dplayer = (C3dplayer*)pObjPos;

                D3DXVECTOR3 playerPos = p3dplayer->GetPos();

                // �v���C���[�ƃ{�X��Y���W�̋������v�Z
                float yDistance = fabs(Pos.y - playerPos.y);

                // �v���C���[�ƃ{�X�̋������v�Z
                float distance = sqrt(pow(Pos.x - playerPos.x, 2) + pow(Pos.y - playerPos.y, 2) + pow(Pos.z - playerPos.z, 2));

                //�{�X���E�������Ă���ꍇ
                if (m_rot.y <= -1.57f)
                {
                    m_nLRPos = C3dboss::BOSS_LRPOSTION::POSTION_LEFT;
                }

                //�{�X�����������Ă���ꍇ
                if (m_rot.y >= 1.57f)
                {
                    m_nLRPos = C3dboss::BOSS_LRPOSTION::POSTION_RIGHT;
                }

                // ������250.0f�ȓ��̏ꍇ�̏���
                if (distance <= 340.0f && yDistance <= 50.0f || distance <= 210.0f && yDistance <= 210.0f)
                {
                    //�s���p�^�[�����I
                    if (m_nACTIONTimer >= 120)

                    {
                        int randoms[] = { BOSSACTION::ACTION_MELEE, BOSSACTION::ACTION_SHORTMELEE };

                        // �C�ӂ̗����𐶐�
                        random_number = randoms[rand() % 2];

                        m_nACTIONTimer = 0;
                    }
                }

                // �{�X�̏㉺�ړ�
                if (yDistance <= 240.0f && yDistance >= 211.0f || yDistance <= 440.0f && yDistance >= 400.0f)
                {
                    //�s���p�^�[�����I
                    if (m_nACTIONTimer >= 120)
                    {
                        //�v���C���[����A�{�X�����ɂ���ꍇ
                        if (m_bFlying == false)
                        {
                            // 0����6�܂ł̗����𐶐�
                            random_number = BOSSACTION::ACTION_UP;
                            m_nACTIONTimer = 0;
                        }

                        //�v���C���[�����A�{�X����ɂ��Ă��������߂��ꍇ
                        if (m_bFlying == true && distance <= 360.0f && yDistance <= 240.0f && yDistance >= 200.0f)
                        {
                            // 0����6�܂ł̗����𐶐�
                            random_number = BOSSACTION::ACTION_DOWN;
                            m_nACTIONTimer = 0;
                        }


                        //�v���C���[�����A�{�X����ɂ��Ă�����������Ă���ꍇ
                        if (m_bFlying == true && distance <= 730.0f && distance >= 360.0f && yDistance <= 240.0f && yDistance >= 200.0f)
                        {
                            int randoms[] = { BOSSACTION::ACTION_UPPERATK, BOSSACTION::ACTION_TORATK, BOSSACTION::ACTION_DOWN};

                            // 0����6�܂ł̗����𐶐�
                            random_number = randoms[rand() % 3];

                            m_nACTIONTimer = 0;
                        }


                    }
                }

                //�v���C���[���{�X�Ƌ߂������̎����A�ŏ�i�ɗ����Ă����ꍇ
                if (distance <= 390.0f && distance >= 250.1f && yDistance <= 205.0f && yDistance >= 200.0f)
                { 
                    if (m_nACTIONTimer >= 120)
                    {
                        int randoms[] = { BOSSACTION::ACTION_MELEE, BOSSACTION::ACTION_SHORTMELEE};

                        // �C�ӂ̗����𐶐�
                        random_number = randoms[rand() % 2];

                        m_nACTIONTimer = 0;
                    }
                }

                //�{�X�ƃv���C���[�Ƃ̋��������������ꍇ
                if (distance <= 760.0f && distance >= 355.0f && yDistance <= 10.0f && yDistance >= 1.0f || distance <= 760.0f && distance >= 390.0f && yDistance <= 205.0f && yDistance >= 202.0f)
                {
                    if (m_nACTIONTimer >= 120)
                    {
                        int randoms[] = { BOSSACTION::ACTION_DASHATK, BOSSACTION::ACTION_WIREDATK,BOSSACTION::ACTION_TORATK };

                        // 0����6�܂ł̗����𐶐�
                        random_number = randoms[rand() % 3];

                        //�ُ�ȕ������������ۂ̑΍�
                        if (random_number == BOSSACTION::ACTION_DASHATK && m_rot.y >= 1.56f && m_rot.y <= -1.56f)
                        {
                            random_number = BOSSACTION::ACTION_WIREDATK;

                            m_rot.y = 0.00f;
                        }

                        if (random_number == BOSSACTION::ACTION_SPATK && m_bBossPowerUP == false)
                        {
                            random_number = BOSSACTION::ACTION_DASHATK;
                        }

                        if (random_number == BOSSACTION::ACTION_UPPERATK && m_bFlying == false)
                        {
                            random_number = BOSSACTION::ACTION_DASHATK;
                        }

                        m_nACTIONTimer = 0;
                    }
                }
            }

            D3DXVECTOR3 moveDirection = { 0.0f, 0.0f, 0.0f };

            //�{�X�̈ʒu�ɍ��킹�Č������������鏈��
            if (Pos.x < 310.0f && MotionUse == false)
            {
                moveDirection.x -= BOSS_MOVE_SPD;
            }

            if (Pos.x > 250.0f && MotionUse == false)
            {
                moveDirection.x += BOSS_MOVE_SPD;
            }


            //�ːi�U���̏ꍇ
            if (random_number == BOSSACTION::ACTION_DASHATK)
            {
                SetPlayerMotion(MOTION_ACTION);
                MotionUse = true;

                random_number = 0;
            }

            //�{�X���㏸������
            if (random_number == BOSSACTION::ACTION_UP)
            {
                m_bFlying = true;

                random_number = 0;
            }

            //�{�X�����~������
            if (random_number == BOSSACTION::ACTION_DOWN)
            {
                if (m_bFlying == true)
                {
                    m_bBossDownzone = true;

                    random_number = 0;
                }
            }

            if (random_number == BOSSACTION::ACTION_SPATK)
            {
                SetPlayerMotion(MOTION_SP_AIRATK);
                MotionUse = true;
                m_bBossSPATK = true;

                random_number = 0;
            }

            //�󒆍U��
            if (random_number == BOSSACTION::ACTION_UPPERATK)
            {
                //CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_SE_BOSS_TORNADO_STARTUP);

                m_bFlyAtk = true;

                random_number = 0;
            }

            //���[�ɗ������o���U��
            if (random_number == BOSSACTION::ACTION_WIREDATK)
            {
                SetPlayerMotion(MOTION_ACTION_WIRED);
                MotionUse = true;
                m_bWiredAtk = true;

                random_number = 0;
            }

            //�ߐڍU���̏ꍇ
            if (random_number == BOSSACTION::ACTION_MELEE)
            {
                SetPlayerMotion(MOTION_MELEEATK);
                MotionUse = true;

                random_number = 0;
            }

            //�����痳�����o���U���̏ꍇ
            if (random_number == BOSSACTION::ACTION_TORATK)
            {
                SetPlayerMotion(MOTION_TORUPATK);
                MotionUse = true;

                random_number = 0;
            }

            if (random_number == BOSSACTION::ACTION_SHORTMELEE)
            {
                SetPlayerMotion(MOTION_SHORTMELEEATK);
                MotionUse = true;

                random_number = 0;
            }

            //�U�����I���������]�̒l��0�ɂ���
            if (m_bWiredAtk == false)
            {
                m_fRotSpeed = 0.0f;
            }

            //���[�ɗ������o���U���̃��[�V����
            if (Motion == MOTION_ACTION_WIRED)
            {

                if (m_bWiredAtk == true)
                {
                    m_fRotSpeed += 0.008f;

                    m_rot.y += m_fRotSpeed;
                }

                if (m_nMotionCnt == 1)
                {

                    if (m_nFrameCnt == 0)
                    {
                        CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_SE_BOSS_TORNADO_WIDE_ADVENT);
                        C3dbosstornado::Create(D3DXVECTOR3(Pos.x - 200.0f, Pos.y, Pos.z), (1));


                        C3dBossATKUI::DisplayBossATKUI(C3dBossATKUI::ATKUI_DISPLAY::BSUI_WIREDATK, C3dBossATKUI::UIDISPLAY::UI_DISPLAY);
                    }

                    if (m_nFrameCnt == 75)
                    {
                        CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_SE_BOSS_TORNADO_WIDE_ADVENT);
                        C3dbosstornado::Create(D3DXVECTOR3(Pos.x + 200.0f, Pos.y, Pos.z), (2));

                    }
                }

                if (m_nMotionCnt == 2)
                {
                    if (m_nFrameCnt == 0)
                    {
                        CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_SE_BOSS_TORNADO_WIDE_SHOT);

                        if (m_nLRPos == C3dboss::BOSS_LRPOSTION::POSTION_RIGHT)
                        {
                            m_rot.y = 1.57f;
                        }

                        if (m_nLRPos == C3dboss::BOSS_LRPOSTION::POSTION_LEFT)
                        {
                            m_rot.y = -1.57f;
                        }

                        C3dBossATKUI::DisplayBossATKUI(C3dBossATKUI::ATKUI_DISPLAY::BSUI_WIREDATK, C3dBossATKUI::UIDISPLAY::UI_HIDDEN);


                        m_bWiredAtk = false;

                    }

                }
            }

            //���ȉ��̃{�X�̗͂̎��̂ݔ���
            if (Motion == C3dboss::MOTION_SP_AIRATK && m_bBossSPATK == true)
            {

                if (m_nLRPos == C3dboss::BOSS_LRPOSTION::POSTION_RIGHT)
                {
                    if (m_nMotionCnt == 0 && m_nFrameCnt == 10)
                    {
                        CCamera::SetShake(40, 10.0f);
                    }

                    if ((m_nMotionCnt == 1 || m_nMotionCnt == 5) && m_nFrameCnt == 0)
                    {
                        C3dbosstornado::Create(D3DXVECTOR3(Pos.x - 310.0f, Pos.y, Pos.z), (1));
                        C3dbosstornado::Create(D3DXVECTOR3(Pos.x - 190.0f, Pos.y, Pos.z), (1));
                        C3dbosstornado::Create(D3DXVECTOR3(Pos.x - 70.0f, Pos.y, Pos.z), (1));

                        for (int nCntObj = 0; nCntObj < 90; nCntObj++)
                        {
                            CObject* pObj = CObject::GetObj(3, nCntObj);

                            if (pObj != nullptr)
                            {
                                CObject::TYPE type = pObj->GetType();

                                C3dbosstornado* p3dbosstornado = (C3dbosstornado*)pObj;
                                p3dbosstornado->BosstornadoAtk(2);
                            }
                        }
                    }

                    if ((m_nMotionCnt == 3 || m_nMotionCnt == 7) && m_nFrameCnt == 0)
                    {
                        C3dbosstornado::Create(D3DXVECTOR3(Pos.x - 250.0f, Pos.y, Pos.z), (1));
                        C3dbosstornado::Create(D3DXVECTOR3(Pos.x - 130.0f, Pos.y, Pos.z), (1));
                        for (int nCntObj = 0; nCntObj < 90; nCntObj++)
                        {
                            CObject* pObj = CObject::GetObj(3, nCntObj);

                            if (pObj != nullptr)
                            {
                                CObject::TYPE type = pObj->GetType();

                                C3dbosstornado* p3dbosstornado = (C3dbosstornado*)pObj;
                                p3dbosstornado->BosstornadoAtk(2);
                            }
                        }

                    }
                }

                if (m_nLRPos == C3dboss::BOSS_LRPOSTION::POSTION_LEFT)
                {
                    if ((m_nMotionCnt == 1 || m_nMotionCnt == 5) && m_nFrameCnt == 0)
                    {
                        C3dbosstornado::Create(D3DXVECTOR3(Pos.x + 310.0f, Pos.y, Pos.z), (1));
                        C3dbosstornado::Create(D3DXVECTOR3(Pos.x + 190.0f, Pos.y, Pos.z), (1));
                        C3dbosstornado::Create(D3DXVECTOR3(Pos.x + 70.0f, Pos.y, Pos.z), (1));

                        for (int nCntObj = 0; nCntObj < 90; nCntObj++)
                        {
                            CObject* pObj = CObject::GetObj(3, nCntObj);

                            if (pObj != nullptr)
                            {
                                CObject::TYPE type = pObj->GetType();

                                C3dbosstornado* p3dbosstornado = (C3dbosstornado*)pObj;
                                p3dbosstornado->BosstornadoAtk(3);
                            }
                        }
                    }


                    if ((m_nMotionCnt == 3 || m_nMotionCnt == 7) && m_nFrameCnt == 0)
                    {
                        C3dbosstornado::Create(D3DXVECTOR3(Pos.x + 250.0f, Pos.y, Pos.z), (1));
                        C3dbosstornado::Create(D3DXVECTOR3(Pos.x + 130.0f, Pos.y, Pos.z), (1));
                        for (int nCntObj = 0; nCntObj < 90; nCntObj++)
                        {
                            CObject* pObj = CObject::GetObj(3, nCntObj);

                            if (pObj != nullptr)
                            {
                                CObject::TYPE type = pObj->GetType();

                                C3dbosstornado* p3dbosstornado = (C3dbosstornado*)pObj;
                                p3dbosstornado->BosstornadoAtk(3);
                            }
                        }
                    }
                }

                if (m_nMotionCnt == 11 && m_nFrameCnt == 0)
                {
                    m_bBossSPATK = false;
                }
            }



            //�ːi�U�����[�V����
            if (Motion == C3dboss::MOTION_ACTION)
            {
                if (m_nMotionCnt == 0 && m_nFrameCnt == 0)
                {
                    if (m_nLRPos == C3dboss::BOSS_LRPOSTION::POSTION_RIGHT)
                    {
                        if (m_bFlying == false)
                        {
                            C3dBossATKUI::DisplayBossATKUI(C3dBossATKUI::ATKUI_DISPLAY::BSUI_R_LOWERDASHATK, C3dBossATKUI::UIDISPLAY::UI_DISPLAY);
                        }

                        if (m_bFlying == true)
                        {
                            C3dBossATKUI::DisplayBossATKUI(C3dBossATKUI::ATKUI_DISPLAY::BSUI_R_UPPERDASHATK, C3dBossATKUI::UIDISPLAY::UI_DISPLAY);
                        }
                    }

                    if (m_nLRPos == C3dboss::BOSS_LRPOSTION::POSTION_LEFT)
                    {
                        if (m_bFlying == false)
                        {
                            C3dBossATKUI::DisplayBossATKUI(C3dBossATKUI::ATKUI_DISPLAY::BSUI_L_LOWERDASHATK, C3dBossATKUI::UIDISPLAY::UI_DISPLAY);
                        }

                        if (m_bFlying == true)
                        {
                            C3dBossATKUI::DisplayBossATKUI(C3dBossATKUI::ATKUI_DISPLAY::BSUI_L_UPPERDASHATK, C3dBossATKUI::UIDISPLAY::UI_DISPLAY);
                        }
                    }
                }

                if (m_nMotionCnt == 2 && m_nFrameCnt == 0)
                {
                    if (m_nLRPos == C3dboss::BOSS_LRPOSTION::POSTION_RIGHT)
                    {
                        if (m_bFlying == false)
                        {
                            C3dBossATKUI::DisplayBossATKUI(C3dBossATKUI::ATKUI_DISPLAY::BSUI_R_LOWERDASHATK, C3dBossATKUI::UIDISPLAY::UI_HIDDEN);
                        }

                        if (m_bFlying == true)
                        {
                            C3dBossATKUI::DisplayBossATKUI(C3dBossATKUI::ATKUI_DISPLAY::BSUI_R_UPPERDASHATK, C3dBossATKUI::UIDISPLAY::UI_HIDDEN);
                        }

                        CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_SE_BOSS_DASH_ATK);
                        m_n3DBossMove.x -= 35.0f;

                    }

                    if (m_nLRPos == C3dboss::BOSS_LRPOSTION::POSTION_LEFT)
                    {
                        if (m_bFlying == false)
                        {
                            C3dBossATKUI::DisplayBossATKUI(C3dBossATKUI::ATKUI_DISPLAY::BSUI_L_LOWERDASHATK, C3dBossATKUI::UIDISPLAY::UI_HIDDEN);
                        }

                        if (m_bFlying == true)
                        {
                            C3dBossATKUI::DisplayBossATKUI(C3dBossATKUI::ATKUI_DISPLAY::BSUI_L_UPPERDASHATK, C3dBossATKUI::UIDISPLAY::UI_HIDDEN);
                        }

                        CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_SE_BOSS_DASH_ATK);
                        m_n3DBossMove.x += 35.0f;
                    }
                }
            }

            // ��s��ԂɂȂ�����
            if (m_bFlying == true && m_bBossUPzone == false && m_bBossDownzone == false)
            {
                if (m_nFlyTimer <= 60)
                {
                    m_n3DBossMove.y += BOSS_MOVE_SPD;
                    moveDirection.y -= BOSS_MOVE_SPD;
                    m_nFlyTimer++;
                }

                if (m_nFlyTimer == 1)
                {
                    CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_SE_BOSS_MOVE);
                }

                if (m_nFlyTimer == 60)
                {
                    m_bBossUPzone = true;
                    m_bBossDownzone = false;
                    m_nFlyTimer = 0;
                    CManager::GetSound()->Stop(CSound::SOUND_LABEL_SE_BOSS_MOVE);
                }
            }

            #if _DEBUG
                if (CManager::GetKeyboard()->GetPress(DIK_Y))
                {
                    m_nLife--;
                }
            #endif

            // ��s��Ԃ����������ꍇ
            if (m_bFlying == true && m_bBossUPzone == true && m_bBossDownzone == true)
            {
                if (m_nFlyTimer <= 60)
                {
                    m_n3DBossMove.y -= BOSS_MOVE_SPD;
                    moveDirection.y += BOSS_MOVE_SPD;
                    m_nFlyTimer++;
                }

                if (m_nFlyTimer == 1)
                {
                    CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_SE_BOSS_MOVE);
                }

                if (m_nFlyTimer == 60)
                {
                    m_bFlying = false;
                    m_bBossUPzone = false;
                    m_bBossDownzone = false;
                    m_nFlyTimer = 0;
                    CManager::GetSound()->Stop(CSound::SOUND_LABEL_SE_BOSS_MOVE);

                }
            }

            if (m_bFlyAtk == true && m_bBossUPzone == true && m_bBossDownzone == false)
            {
                if (m_bFlying == true)
                {
                    SetPlayerMotion(MOTION_ACTION2);
                    MotionUse = true;
                    m_bFlyAtk = false;
                }
            }

            if (Motion == C3dboss::MOTION_ACTION_WIRED)
            {
                if (m_nMotionCnt == 0 && m_nFrameCnt == 0)
                {
                    CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_SE_BOSS_TORNADO_WIDESTARTUP);
                }

                if (m_nMotionCnt == 3 && m_nFrameCnt == 0)
                {
                    CManager::GetSound()->Stop(CSound::SOUND_LABEL_SE_BOSS_TORNADO_WIDESTARTUP);
                }
            }

            //�󒆍U���̏ꍇ
            if (Motion == C3dboss::MOTION_ACTION2)
            {
                if (m_nMotionCnt == 1 && m_nFrameCnt == 0)
                {

                    C3dbosstornado::Create(D3DXVECTOR3(Pos.x, Pos.y + 180.0f, Pos.z), (0));

                    if (m_nLRPos == C3dboss::BOSS_LRPOSTION::POSTION_RIGHT)
                    {
                        C3dBossATKUIDiag::DisplayBossATKUI(C3dBossATKUIDiag::ATKUI_DISPLAY::BSUI_L_DIAGATK, C3dBossATKUIDiag::UIDISPLAY::UI_DISPLAY);
                    }

                    if (m_nLRPos == C3dboss::BOSS_LRPOSTION::POSTION_LEFT)
                    {
                        C3dBossATKUIDiag::DisplayBossATKUI(C3dBossATKUIDiag::ATKUI_DISPLAY::BSUI_R_DIAGATK, C3dBossATKUIDiag::UIDISPLAY::UI_DISPLAY);
                    }
                }

                if (m_nMotionCnt == 2 && m_nFrameCnt == 0 && m_nLRPos == C3dboss::BOSS_LRPOSTION::POSTION_RIGHT)
                {
                    CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_SE_BOSS_TORNADO_ATK);
                    for (int nCntObj = 0; nCntObj < 70; nCntObj++)
                    {
                        CObject* pObj = CObject::GetObj(3, nCntObj);

                        if (pObj != nullptr)
                        {
                            CObject::TYPE type = pObj->GetType();

                            //CManager::GetSound()->Stop(CSound::SOUND_LABEL_SE_BOSS_TORNADO_STARTUP);
                            
                            C3dbosstornado* p3dbosstornado = (C3dbosstornado*)pObj;
                            p3dbosstornado->BosstornadoAtk(2);

                            C3dBossATKUIDiag::DisplayBossATKUI(C3dBossATKUIDiag::ATKUI_DISPLAY::BSUI_L_DIAGATK, C3dBossATKUIDiag::UIDISPLAY::UI_HIDDEN);
                            //CBossATKUI::DisplayBossATKUI(CBossATKUI::ATKUI_DISPLAY::BSUI_R_AIRATK, CBossATKUI::UIDISPLAY::UI_HIDDEN);
                        }
                    }
                }

                if (m_nMotionCnt == 2 && m_nFrameCnt == 0 && m_nLRPos == C3dboss::BOSS_LRPOSTION::POSTION_LEFT)
                {
                    CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_SE_BOSS_TORNADO_ATK);
                    for (int nCntObj = 0; nCntObj < 70; nCntObj++)
                    {
                        CObject* pObj = CObject::GetObj(3, nCntObj);

                        if (pObj != nullptr)
                        {
                            CObject::TYPE type = pObj->GetType();

                            //CManager::GetSound()->Stop(CSound::SOUND_LABEL_SE_BOSS_TORNADO_STARTUP);
                            
                            C3dbosstornado* p3dbosstornado = (C3dbosstornado*)pObj;
                            p3dbosstornado->BosstornadoAtk(3);

                            C3dBossATKUIDiag::DisplayBossATKUI(C3dBossATKUIDiag::ATKUI_DISPLAY::BSUI_R_DIAGATK, C3dBossATKUIDiag::UIDISPLAY::UI_HIDDEN);
                            //CBossATKUI::DisplayBossATKUI(CBossATKUI::ATKUI_DISPLAY::BSUI_L_AIRATK, CBossATKUI::UIDISPLAY::UI_HIDDEN);
                        }
                    }
                }
            }

            //�ːi�U���̓����蔻��
            if (Motion == C3dboss::MOTION_ACTION)
            {
                for (int nCntObj = 0; nCntObj < C3denemy::MAX_ENEMY; nCntObj++)
                {
                    CObject* pObj = CObject::GetObj(3, nCntObj);

                    if (pObj != nullptr)
                    {
                        CObject::TYPE type = pObj->GetType();

                        C3dplayer* p3dplayer = (C3dplayer*)pObj;

                        D3DXVECTOR3 PlayerPos = p3dplayer->GetPos();

                        //�G�̏ꍇ
                        if (type == CObject::TYPE::PLAYER && m_bDashATKDamage == false)
                        {
                            if (Pos.x >= PlayerPos.x - 25
                                && Pos.x <= PlayerPos.x + 25
                                && Pos.y >= PlayerPos.y - 10
                                && Pos.y <= PlayerPos.y + 10
                                && Pos.z >= PlayerPos.z - 10
                                && Pos.z <= PlayerPos.z + 10)
                            {
                                p3dplayer->PlayerDamage(8);
                                m_bDashATKDamage = true;
                                return;
                            }
                        }
                    }
                }
            }

            //�ߐړS���U���̓����蔻��
            if (Motion == C3dboss::MOTION_SHORTMELEEATK && m_bATKCollisonState == true)
            {
                for (int nCntObj = 0; nCntObj < C3denemy::MAX_ENEMY; nCntObj++)
                {
                    CObject* pObj = CObject::GetObj(3, nCntObj);

                    if (pObj != nullptr)
                    {
                        CObject::TYPE type = pObj->GetType();

                        C3dplayer* p3dplayer = (C3dplayer*)pObj;

                        D3DXVECTOR3 PlayerPos = p3dplayer->GetPos();

                        //�G�̏ꍇ
                        if (type == CObject::TYPE::PLAYER && m_bDashATKDamage == false)
                        {
                            if (Pos.x >= PlayerPos.x - 300
                                && Pos.x <= PlayerPos.x + 300
                                && Pos.y >= PlayerPos.y - 170
                                && Pos.y <= PlayerPos.y + 170
                                && Pos.z >= PlayerPos.z - 20
                                && Pos.z <= PlayerPos.z + 20)
                            {
                                p3dplayer->PlayerBlown(2); //�v���C���[���m�b�N�o�b�N������
                                p3dplayer->PlayerDamage(10); //�_���[�W��^����
                                m_bDashATKDamage = true;
                                return;
                            }
                        }
                    }
                }
            }

            //��������ɔ�΂��U��
            if (Motion == C3dboss::MOTION_TORUPATK)
            {
                if (m_nMotionCnt == 0 && m_nFrameCnt == 0)
                {
                    if (m_nLRPos == C3dboss::BOSS_LRPOSTION::POSTION_LEFT)
                    {
                        C3dBossATKUI::DisplayBossATKUI(C3dBossATKUI::ATKUI_DISPLAY::BSUI_L_UPPERDOUBLEATK, C3dBossATKUI::UIDISPLAY::UI_DISPLAY);
                    }

                    if (m_nLRPos == C3dboss::BOSS_LRPOSTION::POSTION_RIGHT)
                    {
                        C3dBossATKUI::DisplayBossATKUI(C3dBossATKUI::ATKUI_DISPLAY::BSUI_R_UPPERDOUBLEATK, C3dBossATKUI::UIDISPLAY::UI_DISPLAY);
                    }
                }

                if (m_nMotionCnt == 2 && m_nFrameCnt == 0)
                {
                    CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_SE_BOSS_TORNADO_WIDE_SHOT);
                    //�����ŗ������o��
                    if (m_nLRPos == C3dboss::BOSS_LRPOSTION::POSTION_LEFT)
                    {
                        C3dBossATKUI::DisplayBossATKUI(C3dBossATKUI::ATKUI_DISPLAY::BSUI_L_UPPERDOUBLEATK, C3dBossATKUI::UIDISPLAY::UI_HIDDEN);
                        C3dbosstornado::Create(D3DXVECTOR3(Pos.x + 610.0f, Pos.y - 400.0f, Pos.z), (4));
                        C3dbosstornado::Create(D3DXVECTOR3(Pos.x + 410.0f, Pos.y - 650.0f, Pos.z), (4));
                    }

                    if (m_nLRPos == C3dboss::BOSS_LRPOSTION::POSTION_RIGHT)
                    {
                        C3dBossATKUI::DisplayBossATKUI(C3dBossATKUI::ATKUI_DISPLAY::BSUI_R_UPPERDOUBLEATK, C3dBossATKUI::UIDISPLAY::UI_HIDDEN);
                        C3dbosstornado::Create(D3DXVECTOR3(Pos.x - 610.0f, Pos.y - 400.0f, Pos.z), (4));
                        C3dbosstornado::Create(D3DXVECTOR3(Pos.x - 410.0f, Pos.y - 650.0f, Pos.z), (4));
                    }

                    CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_SE_BOSS_TORUPATK_SHOT);
                }

            }

            //�ߋ��������U���̏ꍇ
            if (Motion == C3dboss::MOTION_MELEEATK)
            {
                if (m_nMotionCnt == 0 && m_nFrameCnt == 0)
                {
                    if (m_nLRPos == C3dboss::BOSS_LRPOSTION::POSTION_LEFT)
                    {
                        C3dBossATKUI::DisplayBossATKUI(C3dBossATKUI::ATKUI_DISPLAY::BSUI_L_MELEEATK, C3dBossATKUI::UIDISPLAY::UI_DISPLAY);
                    }

                    if (m_nLRPos == C3dboss::BOSS_LRPOSTION::POSTION_RIGHT)
                    {
                        C3dBossATKUI::DisplayBossATKUI(C3dBossATKUI::ATKUI_DISPLAY::BSUI_R_MELEEATK, C3dBossATKUI::UIDISPLAY::UI_DISPLAY);
                    }
                }

                //�U���ƃv���C���[�̓����蔻��
                if (m_nMotionCnt == 1 && m_nFrameCnt == 0)
                {
                    if (m_nLRPos == C3dboss::BOSS_LRPOSTION::POSTION_LEFT)
                    {
                        C3dslashwindBoss::Create(D3DXVECTOR3(Pos.x + 150.0f, Pos.y, Pos.z));
                        C3dslashwindBoss::Create(D3DXVECTOR3(Pos.x + 300.0f, Pos.y, Pos.z));
                        C3dBossATKUI::DisplayBossATKUI(C3dBossATKUI::ATKUI_DISPLAY::BSUI_L_MELEEATK, C3dBossATKUI::UIDISPLAY::UI_HIDDEN);
                        CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_SE_BOSS_MELEE_ATK);
                    }

                    if (m_nLRPos == C3dboss::BOSS_LRPOSTION::POSTION_RIGHT)
                    {
                        C3dslashwindBoss::Create(D3DXVECTOR3(Pos.x - 150.0f, Pos.y, Pos.z));
                        C3dslashwindBoss::Create(D3DXVECTOR3(Pos.x - 300.0f, Pos.y, Pos.z));
                        C3dBossATKUI::DisplayBossATKUI(C3dBossATKUI::ATKUI_DISPLAY::BSUI_R_MELEEATK, C3dBossATKUI::UIDISPLAY::UI_HIDDEN);
                        CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_SE_BOSS_MELEE_ATK);
                    }
                }
            }

            //�ߋ����S���U���̏ꍇ
            if (Motion == C3dboss::MOTION_SHORTMELEEATK)
            {
                if (m_nMotionCnt == 0 && m_nFrameCnt == 0)
                {

                    if (m_nLRPos == C3dboss::BOSS_LRPOSTION::POSTION_LEFT)
                    {
                        C3dBossATKUI::DisplayBossATKUI(C3dBossATKUI::ATKUI_DISPLAY::BSUI_L_MELEEATK, C3dBossATKUI::UIDISPLAY::UI_DISPLAY);
                    }

                    if (m_nLRPos == C3dboss::BOSS_LRPOSTION::POSTION_RIGHT)
                    {
                        C3dBossATKUI::DisplayBossATKUI(C3dBossATKUI::ATKUI_DISPLAY::BSUI_R_MELEEATK, C3dBossATKUI::UIDISPLAY::UI_DISPLAY);
                    }
                }

                //�U���ƃv���C���[�̓����蔻��
                if (m_nMotionCnt == 2 && m_nFrameCnt == 0)
                {
                    if (m_nLRPos == C3dboss::BOSS_LRPOSTION::POSTION_LEFT)
                    {
                        C3dBossATKUI::DisplayBossATKUI(C3dBossATKUI::ATKUI_DISPLAY::BSUI_L_MELEEATK, C3dBossATKUI::UIDISPLAY::UI_HIDDEN);
                        CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_SE_BOSS_MELEE_ATK);
                    }

                    if (m_nLRPos == C3dboss::BOSS_LRPOSTION::POSTION_RIGHT)
                    {
                        C3dBossATKUI::DisplayBossATKUI(C3dBossATKUI::ATKUI_DISPLAY::BSUI_R_MELEEATK, C3dBossATKUI::UIDISPLAY::UI_HIDDEN);
                        CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_SE_BOSS_MELEE_ATK);
                    }
                    m_bATKCollisonState = true;
                }

                if (m_nMotionCnt == 2 && m_nFrameCnt == 15)
                {
                    m_bATKCollisonState = false;
                }
            }

            CObject* pObj = CObject::GetObj(3, 1);

            if (pObj != nullptr)
            {
                CObject::TYPE type = pObj->GetType();

                C3dplayer* p3dplayer = (C3dplayer*)pObj;

                D3DXVECTOR3 PlayerPos = p3dplayer->GetPos();

                //�G�̏ꍇ
                if (type == CObject::TYPE::PLAYER)
                {
                    D3DXVECTOR3 DirectionToPlayer = PlayerPos - Pos; // �{�X����v���C���[�ւ̃x�N�g��

                    // �x�N�g���𐳋K�����ĕ������v�Z
                    D3DXVec3Normalize(&DirectionToPlayer, &DirectionToPlayer);

                    // �{�X�̌������v�Z
                    if (m_bWiredAtk == false && MotionUse == false) // ����̍U�����͌��������𖳌���
                    {
                        float targetAngle = atan2(-DirectionToPlayer.x, DirectionToPlayer.z); // �ڕW�p�x���v�Z
                        float deltaAngle = targetAngle - m_rot.y; // ���݂̌����Ƃ̍������v�Z

                        // �p�x�� -�� �` �� �͈̔͂ɒ���
                        while (deltaAngle > D3DX_PI) deltaAngle -= 2 * D3DX_PI;
                        while (deltaAngle < -D3DX_PI) deltaAngle += 2 * D3DX_PI;

                        // �X���[�Y�Ɍ����𒲐�
                        const float rotationSpeed = 0.25f; // ��]���x�𒲐�
                        if (fabs(deltaAngle) > rotationSpeed)
                        {
                            m_rot.y += (deltaAngle > 0 ? rotationSpeed : -rotationSpeed);
                        }
                        else
                        {
                            m_rot.y = targetAngle; // ���ږڕW�p�x�ɃZ�b�g
                        }
                    }
                }
            }
          

            //���ʂȃ��[�V�������ł͂Ȃ��ꍇ
            if (MotionUse == false)
            {
                //�����Ă���Ȃ�
                if (bMove)
                {
                    SetPlayerMotion(MOTION_WALK);
                }
                else //�~�܂�����
                {
                    SetPlayerMotion(MOTION_NORMAL);
                    m_bDashATKDamage = false;
                }
            }
        }

            //�ߋ����W��ۑ�
            m_nOld3DBossPos = Pos;

            Pos.x += m_n3DBossMove.x;
            Pos.y += m_n3DBossMove.y;
            Pos.z += m_n3DBossMove.z;

            //�u���b�N�Ƃ̓����蔻��̕␳
            for (int nCntPriority = 0; nCntPriority < MAX_PRIORITY; nCntPriority++)
            {
                for (int nCntObj = 0; nCntObj < C3dblock::GetMaxBlock() + 10; nCntObj++)
                {
                    CObject* pObj = CObject::GetObj(nCntPriority, nCntObj);

                    if (pObj != nullptr)
                    {
                        CObject::TYPE type = pObj->GetType();

                        if (type == CObject::TYPE::BLOCK)
                        {
                            C3dblock* p3dblock = (C3dblock*)pObj;

                            bool bIsCollision = p3dblock->Collision3DBlock(&Pos, &m_nOld3DBossPos, &m_n3DBossMove, 50.0f, 10.0f);

                            if (bIsCollision == true)
                            {
                                m_bJumping = false;
                                m_nJumpCnt = 0;
                                m_n3DBossMove.y = 0.0f;
                            }
                        }

                    }
                }
            }

            //�u���b�N�Ƃ̓����蔻��̕␳
            for (int nCntPriority = 0; nCntPriority < MAX_PRIORITY; nCntPriority++)
            {
                for (int nCntObj = 0; nCntObj < 100; nCntObj++)
                {
                    CObject* pObj = CObject::GetObj(nCntPriority, nCntObj);

                    if (pObj != nullptr)
                    {
                        CObject::TYPE type = pObj->GetType();

                        if (type == CObject::TYPE::MOVEBLOCK_X)
                        {
                            C3dmoveblock* p3dmoveblock = (C3dmoveblock*)pObj;

                            m_bIsCollision = p3dmoveblock->Collision3DMoveblock(&Pos, &m_nOld3DBossPos, &m_n3DBossMove, 10.0f, 50.0f);

                            if (m_bIsCollision == true)
                            {

                                m_n3DBossMove.y = 0.0f;
                                m_nJumpCnt = 0;
                                Pos.x += (p3dmoveblock->GetMoveBlock().x * 1.1);

                            }
                        }

                        if (type == CObject::TYPE::MOVEBLOCK_Z)
                        {
                            C3dmoveblock* p3dmoveblock = (C3dmoveblock*)pObj;

                            bool bIsCollision = p3dmoveblock->Collision3DMoveblock(&Pos, &m_nOld3DBossPos, &m_n3DBossMove, 50.0f, 50.0f);

                            if (bIsCollision == true)
                            {
                                m_n3DBossMove.y = 0.0f;
                                m_nJumpCnt = 0;
                                Pos.z += (p3dmoveblock->GetMoveBlock().z);
                            }
                        }

                    }
                }

                C3dboss::m_nPos = Pos;

                //���W��ݒ�
                SetPos(Pos);
            }



            //X���W�̈ړ��ʂ��X�V
            m_n3DBossMove.x += (Length_value2 - m_n3DBossMove.x) * Attenuation_value;

            //Y���W�̈ړ��ʂ��X�V
            m_n3DBossMove.y += (Length_value2 - m_n3DBossMove.y) * Attenuation_value;

            //Z���W�̈ړ��ʂ��X�V
            m_n3DBossMove.z += (Length_value2 - m_n3DBossMove.z) * Attenuation_value;

            //�W�����v���ĂȂ����͕��sSE�𗬂��Ȃ�
            if (m_n3DBossMove.y < 0.0f)
            {
                //CManager::GetSound()->Stop(CSound::SOUND_LABEL_SE_BOSS_WALK);
            }

    }

    //�v���C���[�̗̑͂�0�ȉ��ɂȂ����ꍇ���U���g��ʂ֑J��
    if (m_nLife <= 0)
    {
        //if (MotionUse == false)
        //{
        //    Uninit();
        //}


        MotionUse = false;

        SetPlayerMotion(MOTION_DEAD);
        MotionUse = true;

        if (Motion == C3dboss::MOTION_DEAD)
        {
            if (m_nMotionCnt == 1 && m_nFrameCnt == 0)
            {
                CScore::AddScore(20000);
            }

            if (m_nMotionCnt == 2 && m_nFrameCnt == 25)
            {
                m_bDeathSwitch = true;
                C3dexplosionsub::Create(D3DXVECTOR3(m_nPos.x, m_nPos.y - 50.0f, m_nPos.z), D3DXVECTOR3(300.0f, 420.0f, 0.0f), m_rot, 0);
                CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_SE_BOSS_EXPLOSION);
            }

            if (m_nMotionCnt == 3 && m_nFrameCnt == 0)
            {
                bUse = false;
                
            }

        }

        if (m_bDeathSwitch == true)
        {
            m_nEndTimer++;
        }

        if (m_nEndTimer == 120)
        {
            CEndCallUI::DisplayEndCallUI(CEndCallUI::ICONDISPLAY::ICON_SPSUCCESS, CEndCallUI::UIDISPLAY::UI_DISPLAY);
        }
    }

    //�_���[�W���󂯂���
    if (m_bBossDMGState == true)
    {
        m_nBossDmgColorTimer++;

        if (m_nBossDmgColorTimer >= 5)
        {
            m_bBossDMGState = false; //�}�e���A���̐F��߂�
            m_nBossDmgColorTimer = 0;
        }
    }


    int nFadeState = CFade::GetFadeState();

    if (nFadeState == CFade::FADE_OUT && m_nLife >= 0)
    {
        C3dboss::Uninit();
    }

}



//======================
// �`�揈��
//======================
void C3dboss::Draw()
{
    LPDIRECT3DDEVICE9 pDevice = nullptr;
    pDevice = CManager::GetRenderer()->GetDevice();

    D3DXMATRIX mtxRot, mtxTrans; //�v�Z�p�}�g���b�N�X
    D3DMATERIAL9 matDef; //���݂̃}�e���A���ۑ��p
    D3DXMATERIAL* pMat; //�}�e���A���f�[�^�ւ̃|�C���^
    D3DXVECTOR3 Pos = CObject3D::GetPos();

    //���[���h�}�g���b�N�X�̏�����
    D3DXMatrixIdentity(&m_mtxworld);

    //�����𔽉f
    D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
    D3DXMatrixMultiply(&m_mtxworld, &m_mtxworld, &mtxRot);

    //�ʒu�𔽉f
    D3DXMatrixTranslation(&mtxTrans, Pos.x, Pos.y, Pos.z);
    D3DXMatrixMultiply(&m_mtxworld, &m_mtxworld, &mtxTrans);

    ////���f���̉e�̐ݒ�
    //D3DXMATRIX mtxshadow , mtxshadowTrans;
    //D3DXPLANE plane;
    //D3DXVECTOR4 vecLight;
    //D3DXVECTOR3 pos, nor;

    //D3DXMatrixIdentity(&mtxshadow);

    ////���C�g�̋t�����x�N�g����ݒ�
    //vecLight = D3DXVECTOR4(0.5f, 0.6f, 0.7f,1.0f);
    //pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
    //nor = D3DXVECTOR3(0.0f,1.0f,0.0f);

    //D3DXPlaneFromPointNormal(&plane, &pos, &nor);
    //D3DXMatrixShadow(&mtxshadow,&vecLight,&plane);

    //m_mtxworld * mtxshadow;

    //���[���h�}�g���b�N�X�̐ݒ�
    pDevice->SetTransform(D3DTS_WORLD, &m_mtxworld);

    //�}�e���A�����擾
    pDevice->GetMaterial(&matDef);

    // �_���[�W���̃��f���̃}�e���A���ݒ�
    D3DMATERIAL9 DMGMaterial = {};
    DMGMaterial.Diffuse.r = 1.0f; // ��
    DMGMaterial.Diffuse.g = 0.0f; // ��
    DMGMaterial.Diffuse.b = 0.0f; // ��
    DMGMaterial.Diffuse.a = 1.0f; // �����x

    for (int nCntParts = 0; nCntParts < BOSS_MODEL; nCntParts++)
    {
        //���[���h�}�g���b�N�X�̏�����
        D3DXMatrixIdentity(&m_aModel[nCntParts].mtxworld);

        //�����𔽉f
        D3DXMatrixRotationYawPitchRoll(&mtxRot, m_aModel[nCntParts].rot.y, m_aModel[nCntParts].rot.x, m_aModel[nCntParts].rot.z);
        D3DXMatrixMultiply(&m_aModel[nCntParts].mtxworld, &m_aModel[nCntParts].mtxworld, &mtxRot);

        //�ʒu�𔽉f
        D3DXMatrixTranslation(&mtxTrans, m_aModel[nCntParts].pos.x, m_aModel[nCntParts].pos.y, m_aModel[nCntParts].pos.z);
        D3DXMatrixMultiply(&m_aModel[nCntParts].mtxworld, &m_aModel[nCntParts].mtxworld, &mtxTrans);

        //�e�q�֌W
        D3DXMATRIX mtxParent;

        if (m_aModel[nCntParts].nIdxModelParent == -1)
        {
            mtxParent = m_mtxworld;
        }

        else
        {
            mtxParent = m_aModel[m_aModel[nCntParts].nIdxModelParent].mtxworld;
        }

        D3DXMatrixMultiply(&m_aModel[nCntParts].mtxworld, &m_aModel[nCntParts].mtxworld, &mtxParent);

        //�}�g���b�N�X�̐ݒ�
        pDevice->SetTransform(D3DTS_WORLD, &m_aModel[nCntParts].mtxworld);

        pMat = (D3DXMATERIAL*)m_pBuffMat[nCntParts]->GetBufferPointer();

        D3DVERTEXELEMENT9 aElements[MAX_FVF_DECL_SIZE];

        for (int nCntMat = 0; nCntMat < (int)m_nNumMat[nCntParts]; nCntMat++)
        {
            //�_���[�W���󂯂Ă��Ȃ���
            if (m_bBossDMGState == false)
            {
                //�}�e���A���̐ݒ�
                pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
            }

            //�_���[�W���󂯂Ă��鎞
            if (m_bBossDMGState == true)
            {
                // �����I�ɐԐF�̃}�e���A����ݒ�
                pDevice->SetMaterial(&DMGMaterial);
            }
            //�e�N�X�`���̐ݒ�
            pDevice->SetTexture(0, NULL);

            //�e�N�X�`�������݂���
            if (pMat[nCntMat].pTextureFilename != NULL)
            {
                //�e�N�X�`���̐ݒ�
                pDevice->SetTexture(0, &m_aModel[0].m_pTexture[nCntMat]);
            }

            else
            {
                //�e�N�X�`���̐ݒ�
                pDevice->SetTexture(0, NULL);
            }

            if (bUse == true)
            {
                //���f��(�p�[�c)�̕`��
                m_pMesh[nCntParts]->DrawSubset(nCntMat);

                m_pMesh[nCntParts]->GetDeclaration(m_aElements);
            }
        }

    }

    pDevice->SetMaterial(&matDef);
}

//======================
// �I�u�W�F�N�g��������
//======================
C3dboss* C3dboss::Create(D3DXVECTOR3 pos)
{
    C3dboss* D3Dplayer = nullptr;

    D3Dplayer = new C3dboss;

    //�������ɐ��������ꍇ
    if (SUCCEEDED(D3Dplayer->Init()))
    {
        D3Dplayer->SetType(TYPE::BOSS);

        D3Dplayer->LoadPlayerData();

        D3Dplayer->CObject3D::SetPos(pos);

        D3Dplayer->m_rot.y = 1.57f;

        //D3Dplayer->Load();//�e�N�X�`����ݒ�(��)


        ////�e�N�X�`���̐ݒ�
        //Model->BindTexture(m_pTexBuff);
    }

    return D3Dplayer;
}

//======================
// �v���C���[�ړ�SE�Đ�����
//======================
void C3dboss::PlayerWalkSound()
{
    m_nWalkSoundCnt++;

    if (m_nWalkSoundCnt == 20)
    {
        m_nWalkSoundCnt = 0;
    }

}

//======================
// �e�N�X�`�����[�h����
//======================
HRESULT C3dboss::Load()
{
    LPDIRECT3DDEVICE9 pDevice = nullptr;
    pDevice = CManager::GetRenderer()->GetDevice();

    if (FAILED(D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\samplepos.png", &m_pTexBuff)))
    {
        return E_FAIL;
    }

    return S_OK;
}

//======================
// �e�N�X�`���A�����[�h(�I��)����
//======================
void C3dboss::Unload()
{
    CModel::Unload();
}


//======================
// �v���C���[�̃_���[�W����
//======================
void C3dboss::BossDamage(int nDamage)
{
    m_nLife -= nDamage;
    CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_SE_ENEMY_DAMAGE);
    m_bBossDMGState = true;
}


//===========================
// �O���t�@�C���ǂݍ��ݏ���
//===========================

void C3dboss::LoadPlayerData(void)
{
    char Datacheck[MAX_CHAR];
    int nCnt = 0;
    int EnemyModelSave = 0;
    int nMotionCount = 0;
    int nKeyCount = 0;
    int nKeySetCount = 0;

    m_pFile = fopen("data\\MODEL\\MODEL_BOSS\\Charamotion.txt", "r");//�t�@�C�����J��

    //�t�@�C�������݂��Ȃ��ꍇ
    if (m_pFile == NULL)
    {
        return;
    }

    // END��������܂œǂݍ��݂��J��Ԃ�
    while (1)
    {
        fscanf(m_pFile, "%s", Datacheck);	// ����

        if (!strcmp(Datacheck, "SCRIPT"))
        {
            // END��������܂œǂݍ��݂��J��Ԃ�
            while (1)
            {
                fscanf(m_pFile, "%s", Datacheck);	// ����

                if (!strcmp(Datacheck, "MODEL_FILENAME"))
                {
                    fscanf(m_pFile, "%s", Datacheck);
                    fscanf(m_pFile, "%s", &C3dboss::m_aLoadEnemy[EnemyModelSave].filename[0]);
                    EnemyModelSave++;
                }

                if (!strcmp(Datacheck, "END_SCRIPT"))
                {// �ǂݍ��݂��I��
                    break;
                }

                if (!strcmp(Datacheck, "CHARACTERSET"))
                {
                    // END��������܂œǂݍ��݂��J��Ԃ�
                    while (1)
                    {
                        fscanf(m_pFile, "%s", Datacheck);	// ����

                        if (!strcmp(Datacheck, "END_CHARACTERSET"))
                        {// �ǂݍ��݂��I��
                            //fclose(m_pFile);
                            break;
                        }
                        if (Datacheck[0] == '#')
                        {// �܂�Ԃ�
                            continue;
                        }
                        if (!strcmp(Datacheck, "NUM_PARTS"))
                        {
                            fscanf(m_pFile, "%s", Datacheck);
                            fscanf(m_pFile, "%d", &EnemyModelSave);
                        }


                        if (!strcmp(Datacheck, "PARTSSET"))
                        {
                            // ���ڂ��ƂɃf�[�^����
                            while (1)
                            {
                                fscanf(m_pFile, "%s", Datacheck); // ����

                                if (!strcmp(Datacheck, "END_PARTSSET"))
                                {
                                    break;
                                }			// �ǂݍ��݂��I��
                                else if (!strcmp(Datacheck, "INDEX"))
                                {
                                    fscanf(m_pFile, "%s", Datacheck);
                                    fscanf(m_pFile, "%d", &C3dboss::m_aLoadEnemy[nCnt].index);
                                }		// ���
                                else if (!strcmp(Datacheck, "PARENT"))
                                {
                                    fscanf(m_pFile, "%s", Datacheck);
                                    fscanf(m_pFile, "%d", &C3dboss::m_aLoadEnemy[nCnt].parent);
                                }		// ��
                                else if (!strcmp(Datacheck, "POS"))
                                {
                                    fscanf(m_pFile, "%s", Datacheck);
                                    fscanf(m_pFile, "%f", &C3dboss::m_aLoadEnemy[nCnt].pos.x);
                                    fscanf(m_pFile, "%f", &C3dboss::m_aLoadEnemy[nCnt].pos.y);
                                    fscanf(m_pFile, "%f", &C3dboss::m_aLoadEnemy[nCnt].pos.z);
                                }	// ����
                                else if (!strcmp(Datacheck, "ROT"))
                                {
                                    fscanf(m_pFile, "%s", Datacheck);
                                    fscanf(m_pFile, "%f", &C3dboss::m_aLoadEnemy[nCnt].rot.x);
                                    fscanf(m_pFile, "%f", &C3dboss::m_aLoadEnemy[nCnt].rot.y);
                                    fscanf(m_pFile, "%f", &C3dboss::m_aLoadEnemy[nCnt].rot.z);
                                }		// ���s��

                            }
                            nCnt++;	// �f�[�^�����Z
                        }
                    }
                }

                //============���[�V�����̓ǂݍ���==============================================
                if (!strcmp(Datacheck, "MOTIONSET"))
                {
                    int LoopType = 0;
                    // ���ڂ��ƂɃf�[�^����
                    while (1)
                    {
                        fscanf(m_pFile, "%s", Datacheck); // ����

                        if (Datacheck[0] == '#')
                        {// �܂�Ԃ�
                            continue;
                            fgets(Datacheck, 40, m_pFile);
                        }
                        if (!strcmp(Datacheck, "END_MOTIONSET"))
                        {
                            break;
                        }			// �ǂݍ��݂��I��
                        else if (!strcmp(Datacheck, "LOOP")) //���[�v�̓ǂݍ���
                        {
                            fscanf(m_pFile, "%s", Datacheck);
                            fscanf(m_pFile, "%d", &LoopType);
                            if (LoopType == 0)
                            {
                                C3dboss::MotionSet[nMotionCount].Loop = false;
                            }
                            else
                            {
                                C3dboss::MotionSet[nMotionCount].Loop = true;
                            }
                        }		// ���
                        else if (!strcmp(Datacheck, "NUM_KEY")) //�L�[���̓ǂݍ���
                        {
                            fscanf(m_pFile, "%s", Datacheck);
                            fscanf(m_pFile, "%d", &C3dboss::MotionSet[nMotionCount].NumKey);
                        }		// ��

                        if (!strcmp(Datacheck, "KEYSET")) //�L�[�Z�b�g�̓ǂݍ���
                        {
                            // ���ڂ��ƂɃf�[�^����
                            while (1)
                            {
                                fscanf(m_pFile, "%s", Datacheck); // ����

                                if (Datacheck[0] == '#')
                                {// �܂�Ԃ�
                                    fgets(Datacheck, 20, m_pFile);
                                    continue;
                                }
                                if (!strcmp(Datacheck, "END_KEYSET"))
                                {
                                    break;
                                }			// �ǂݍ��݂��I��
                                //�t���[�����̓ǂݍ���
                                if (!strcmp(Datacheck, "FRAME"))
                                {
                                    fscanf(m_pFile, "%s", Datacheck);
                                    fscanf(m_pFile, "%d", &C3dboss::MotionSet[nMotionCount].KeySet[nKeySetCount].Frame);
                                }

                                if (!strcmp(Datacheck, "KEY")) //�L�[�̓ǂݍ���
                                {
                                    // ���ڂ��ƂɃf�[�^����
                                    while (1)
                                    {
                                        fscanf(m_pFile, "%s", Datacheck); // ����

                                        if (Datacheck[0] == '#')
                                        {// �܂�Ԃ�
                                            continue;
                                            fgets(Datacheck, 40, m_pFile);
                                        }
                                        if (!strcmp(Datacheck, "POS"))
                                        {
                                            fscanf(m_pFile, "%s", Datacheck);
                                            fscanf(m_pFile, "%f", &C3dboss::MotionSet[nMotionCount].KeySet[nKeySetCount].aKey[nKeyCount].pos.x);
                                            fscanf(m_pFile, "%f", &C3dboss::MotionSet[nMotionCount].KeySet[nKeySetCount].aKey[nKeyCount].pos.y);
                                            fscanf(m_pFile, "%f", &C3dboss::MotionSet[nMotionCount].KeySet[nKeySetCount].aKey[nKeyCount].pos.z);
                                        }
                                        else if (!strcmp(Datacheck, "ROT"))
                                        {
                                            fscanf(m_pFile, "%s", Datacheck);
                                            fscanf(m_pFile, "%f", &C3dboss::MotionSet[nMotionCount].KeySet[nKeySetCount].aKey[nKeyCount].rot.x);
                                            fscanf(m_pFile, "%f", &C3dboss::MotionSet[nMotionCount].KeySet[nKeySetCount].aKey[nKeyCount].rot.y);
                                            fscanf(m_pFile, "%f", &C3dboss::MotionSet[nMotionCount].KeySet[nKeySetCount].aKey[nKeyCount].rot.z);
                                        }

                                        if (!strcmp(Datacheck, "END_KEY"))
                                        {
                                            break;
                                        }			// �ǂݍ��݂��I��

                                    }
                                    nKeyCount++; //�f�[�^�̉��Z
                                }
                            }
                            nKeyCount = 0;
                            nKeySetCount++; //�f�[�^�̉��Z
                        }
                    }
                    nKeySetCount = 0; //�J�E���g�̏�����
                    nMotionCount++; //�f�[�^�̉��Z
                }
            }
            fclose(m_pFile);
            break;
        }
    }

    //�f�o�C�X�̎擾
    LPDIRECT3DDEVICE9 pDevice = nullptr;
    pDevice = CManager::GetRenderer()->GetDevice();



    for (int nInfoCount = 0; nInfoCount < EnemyModelSave; nInfoCount++)
    {
        //X�t�@�C���̓ǂݍ���
        D3DXLoadMeshFromX(&C3dboss::m_aLoadEnemy[nInfoCount].filename[0], D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[nInfoCount], NULL, &m_nNumMat[nInfoCount], &m_pMesh[nInfoCount]);

        //�ʒu�̏�����
        m_aModel[nInfoCount].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
        m_aModel[nInfoCount].nIdxModelParent = C3dboss::m_aLoadEnemy[nInfoCount].parent;
        m_aModel[nInfoCount].pos = D3DXVECTOR3(C3dboss::m_aLoadEnemy[nInfoCount].pos.x, C3dboss::m_aLoadEnemy[nInfoCount].pos.y, C3dboss::m_aLoadEnemy[nInfoCount].pos.z);
        m_aModel[nInfoCount].rot = D3DXVECTOR3(C3dboss::m_aLoadEnemy[nInfoCount].rot.x, C3dboss::m_aLoadEnemy[nInfoCount].rot.y, C3dboss::m_aLoadEnemy[nInfoCount].rot.z);

        m_aModel[nInfoCount].pos += C3dboss::MotionSet[0].KeySet[0].aKey[nInfoCount].pos;
        m_aModel[nInfoCount].rot += C3dboss::MotionSet[0].KeySet[0].aKey[nInfoCount].rot;
    }
}

//======================
// ���[�V�����̎w��
//======================
void C3dboss::SetPlayerMotion(BOSSMOTION motion)
{
    if (C3dboss::Motion != motion && C3dboss::MotionUse == false) //���݂̃��[�V�����ƈ������
    {
        C3dboss::Motion = motion; //���[�V������ݒ�
        C3dboss::m_nMotionCnt = 0; //���[�V�����̃J�E���g��������
        C3dboss::m_nFrameCnt = 0;  //�t���[���̃J�E���g�̏�����

        // ���f���̃p�[�c���J��Ԃ��Ĉʒu�Ɖ�]��������
        for (int nModelCount = 0; nModelCount < BOSS_MODEL; nModelCount++)
        {
            m_aModel[nModelCount].pos = m_aLoadEnemy[nModelCount].pos + C3dboss::MotionSet[motion].KeySet[0].aKey[nModelCount].pos;
            m_aModel[nModelCount].rot = m_aLoadEnemy[nModelCount].rot + C3dboss::MotionSet[motion].KeySet[0].aKey[nModelCount].rot;
        }
    }
}


//======================
// ���f���̃��[�V��������
//======================
void C3dboss::ModelMotion()
{
    // ���f���̃p�[�c���J��Ԃ�
    for (int nModelCount = 0; nModelCount < BOSS_MODEL; nModelCount++)
    {
        // ���݂̃��[�V�����̃L�[�Z�b�g���擾
        const auto& currentKey = C3dboss::MotionSet[Motion].KeySet[m_nMotionCnt];
        const auto& nextKey = C3dboss::MotionSet[Motion].KeySet[(m_nMotionCnt + 1) % C3dboss::MotionSet[Motion].NumKey];

        // ���`��Ԃ�p���Ĉʒu�Ɖ�]�̍������v�Z
        D3DXVECTOR3 Movepos = (nextKey.aKey[nModelCount].pos - currentKey.aKey[nModelCount].pos) / currentKey.Frame;
        D3DXVECTOR3 Moverot = (nextKey.aKey[nModelCount].rot - currentKey.aKey[nModelCount].rot) / currentKey.Frame;

        // ���������Z
        m_aModel[nModelCount].pos += Movepos;
        m_aModel[nModelCount].rot += Moverot;
    }

    // �t���[���̉��Z
    m_nFrameCnt++;

    // �L�[�t���[���I�����̏���
    if (m_nFrameCnt >= C3dboss::MotionSet[C3dboss::Motion].KeySet[m_nMotionCnt].Frame)
    {
        m_nFrameCnt = 0;           // �J�E���g��������
        m_nMotionCnt++;            // ���[�V�����̃J�E���g�𑝉�

        // ���[�V�����̏I���������`�F�b�N
        if (m_nMotionCnt >= C3dboss::MotionSet[C3dboss::Motion].NumKey)
        {
            m_nMotionCnt = 0; // �J�E���g��0�ɂ���

            // ���[�v���Ȃ��ꍇ�A���[�V�������~
            if (!C3dboss::MotionSet[C3dboss::Motion].Loop)
            {
                C3dboss::MotionUse = false;    // ���[�V�����̔����off�ɂ���
                SetPlayerMotion(MOTION_NORMAL);  // ���[�V�����̏��̐؂�ւ�
            }
        }
    }
}

//===========================
// �G�̓����蔻��
//===========================
bool C3dboss::Collision3DBoss(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3* pMove, float fWidth, float fBlockHeight)
{
    bool bLanding = false; // �d�͂�K�������ꍇ�̂ݎg�p
    float fBlockWidth = 90.0f;
    float fBlockDepth = 30.0f;
    float fHeight = 0.0f;

    D3DXVECTOR3 Pos = CObject3D::GetPos();

    if (bUse == true)
    {
        // �E�������蔻��
        if (pPos->x - fWidth <= Pos.x + fBlockWidth && pPosOld->x - fWidth >= Pos.x + fBlockWidth && pPos->z - fHeight < Pos.z + fBlockDepth && pPos->z > Pos.z - fBlockDepth && pPos->y < Pos.y + fBlockHeight && pPos->y > Pos.y - fBlockHeight + 120.0f)
        {
            pPos->x = Pos.x + fBlockWidth + fWidth;
        }
        // ���������蔻��
        else if (pPos->x + fWidth >= Pos.x - fBlockWidth && pPosOld->x + fWidth <= Pos.x - fBlockWidth && pPos->z - fHeight < Pos.z + fBlockDepth && pPos->z > Pos.z - fBlockDepth && pPos->y < Pos.y + fBlockHeight && pPos->y > Pos.y - fBlockHeight + 120.0f)
        {
            pPos->x = Pos.x - fBlockWidth - fWidth;
        }
        // �O�������蔻��
        if (pPos->x - fWidth < Pos.x + fBlockWidth && pPos->x + fWidth > Pos.x - fBlockWidth && pPos->z - fHeight <= Pos.z + fBlockDepth - 30.0f && pPosOld->z - fHeight >= Pos.z + fBlockDepth - 30.0f && pPos->y < Pos.y + fBlockHeight && pPos->y > Pos.y - fBlockHeight)
        {
            pPos->z = Pos.z + fBlockDepth - 40.0f + fHeight;
        }

        // �㑤�����蔻��
        else if (pPos->x - fWidth < Pos.x + fBlockWidth && pPos->x + fWidth > Pos.x - fBlockWidth && pPos->z >= Pos.z - fBlockDepth && pPosOld->z <= Pos.z - fBlockDepth && pPos->y < Pos.y + fBlockHeight && pPos->y > Pos.y - fBlockHeight)
        {
            pPos->z = Pos.z - fBlockDepth + 50.0f - fHeight;
            bLanding = true;
        }
        // �㑤�����蔻��
        if (pPos->x - fWidth < Pos.x + fBlockWidth && pPos->x + fWidth > Pos.x - fBlockWidth && pPos->y - fHeight <= Pos.y + fBlockHeight && pPosOld->y - fHeight >= Pos.y + fBlockHeight && pPos->z < Pos.z + fBlockDepth && pPos->z > Pos.z - fBlockDepth)
        {
            pPos->y = Pos.y + fBlockHeight + fHeight;
            bLanding = true;
        }

        // ���������蔻��
        else if (pPos->x - fWidth < Pos.x + fBlockWidth && pPos->x + fWidth > Pos.x - fBlockWidth && pPos->y + fHeight >= Pos.y - (fBlockHeight - 110.0f) && pPosOld->y + fHeight <= Pos.y - (fBlockHeight - 110.0f) && pPos->z < Pos.z + fBlockDepth && pPos->z > Pos.z - fBlockDepth)
        {
            pPos->y = Pos.y - (fBlockHeight - 110.0f) - fHeight;
        }
    }


    return bLanding;
}
