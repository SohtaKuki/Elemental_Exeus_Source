//=================================================
//
// 3D���f���̃v���C���[�̕\������ (3dplayer.cpp)
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
#include "3dtornado.h"
#include "3dboss_switch.h"
#include "bosscallui.h"
#include "3dboss.h"
#include "3dtornado_effect.h"
#include "3denemy_air.h"
#include "startcallui.h"
#include "letterbox.h"
#include "3dhiteffect.h"
#include "3dboss.h"

LPDIRECT3DTEXTURE9 C3dplayer::m_pTexBuff = nullptr;
int C3dplayer::m_nLife = 0;
bool C3dplayer::m_bAButtonPressed = false;
int C3dplayer::m_nNumTornado = 2;

D3DXVECTOR3 C3dplayer::m_rot = D3DXVECTOR3(0.0f,0.0f,0.0f);
D3DVERTEXELEMENT9 C3dplayer::m_aElements[MAX_FVF_DECL_SIZE] = {};


//======================
// �R���X�g���N�^
//======================
C3dplayer::C3dplayer(int nPriority) : CModel(nPriority)
{
    m_bPlayerBuff = false;
    m_bInstantShot = false;
    m_nBuffTime = 0;
    m_nInstantShotTime = 0;
    m_nLife = PLAYER_LIFE;
    m_bAButtonPressStartTime = false;
    m_bSuperJump = false;
    m_bAButtonPressed = 0;
    m_nJumpCnt = 0;
    m_nWalkSoundCnt = 0;
    m_nJumpType = DOUBLE_JUMP;
    m_bIsCollision = false;
    m_bAirStep = false;
    m_nAirStepTimer = 0;
    m_bJumping = false;
    m_bTorUPPER = false;
    m_nJumpTimer = 0;
    m_nNumTornado = 2;
    m_nTorReloadTimer = 0;
    m_bDamageState = false;
    m_nDmgColorTimer = 0;
}

//======================
// �f�X�g���N�^
//======================
C3dplayer::~C3dplayer()
{

}

//======================
// ����������
//======================
HRESULT C3dplayer::Init()
{
    //������
    if (FAILED(CModel::Init()))
    {
        return E_FAIL;
    }

    //���[�V�����̏�����
    for (int nCount = 0;nCount < MAX_MOTION ; nCount++)
    {
        MotionSet[nCount].Loop = false;
        MotionSet[nCount].NumKey = 0;
        for (int nKeySetCount = 0; nKeySetCount < MAX_KEYSET; nKeySetCount++)
        {
            MotionSet[nCount].KeySet[nKeySetCount].Frame = 0;

            for (int nKeyCount = 0; nKeyCount < PLAYER_MODEL; nKeyCount++)
            {
               MotionSet[nCount].KeySet[nKeySetCount].aKey[nKeyCount].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
               MotionSet[nCount].KeySet[nKeySetCount].aKey[nKeyCount].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
            }
        }
    }

    for (int nCnt = 0; nCnt < PLAYER_MODEL; nCnt++)
    {
        m_pBuffMat[nCnt] = 0;
        m_bUse[nCnt] = true;
    }


    m_nAtkCombo = 0;


    return S_OK;
}

//======================
// �I������
//======================
void C3dplayer::Uninit()
{

    if (m_pTexBuff != nullptr)
    {
        m_pTexBuff->Release();
        m_pTexBuff = nullptr;
    }

    for (int i = 0; i < PLAYER_MODEL; i++)
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
void C3dplayer::Update()
{
    if (CScene::GetUpdateStat() == true)
    {
        D3DXVECTOR3 Pos = CObject3D::GetPos();

        //�{�X���o���̏���
        if (CBossCallUI::GetEndStat() == true && C3dboss::GetBossEntry() == false && C3dgoalobj::GetStageNum() == 2)
        {
            for (int nCntParts = 0; nCntParts < PLAYER_MODEL; nCntParts++)
            {

                m_bUse[nCntParts] = false;
            }
        }

        //�{�X���o���I�������ۂ̏���
        if (CBossCallUI::GetEndStat() == true && C3dboss::GetBossEntry() == true && C3dgoalobj::GetStageNum() == 2)
        {
            for (int nCntParts = 0; nCntParts < PLAYER_MODEL; nCntParts++)
            {
                m_bUse[nCntParts] = true;
            }
        }

        //�{�X��J�n���Ɋ���̍��W�ɋ����ړ�
        if (CBossCallUI::GetEndStat() == true && C3dboss::GetBossEntry() == false)
        {
            Pos.x = 60.0f;
            Pos.y = 30.0f;
        }

        //����̃X�e�[�W�ƁA�Q�[�����i�s�\�̏ꍇ�̂ݒʂ�(�{�X���o���͒ʂ��Ȃ�)
        if (C3dgoalobj::GetStageNum() == 0 && CScene::GetUpdateStat() == true ||
            C3dgoalobj::GetStageNum() == 1 && CScene::GetUpdateStat() == true ||
            (CBossCallUI::GetEndStat() == false && C3dboss::GetBossEntry() == false && C3dgoalobj::GetStageNum() == 2) ||
            (CBossCallUI::GetEndStat() == true && C3dboss::GetBossEntry() == true && C3dgoalobj::GetStageNum() == 2))
        {


            //SetPlayerPos();

            int nCnt = 0;
            bool bMove = false;
            bool bJump = false;

            D3DXVECTOR2 leftStickPos = CManager::GetJoypad()->GetStickPosition(CInputJoypad::STICKTYPE_LEFT);
            D3DXVECTOR2 RightStickPos = CManager::GetJoypad()->GetStickPosition(CInputJoypad::STICKTYPE_RIGHT);
            D3DXVECTOR2 LeftTriggerPos = CManager::GetJoypad()->GetTriggerPosition(CInputJoypad::JOYKEY_LT);
            D3DXVECTOR2 RightTriggerPos = CManager::GetJoypad()->GetTriggerPosition(CInputJoypad::JOYKEY_RT);

            //�v���C���[�̍ő�̗͒l�𒴂��Ȃ��悤�ɂ���
            if (m_nLife >= PLAYER_LIFE)
            {
                m_nLife = PLAYER_LIFE;
            }


            C3dplayer::ModelMotion();

            if (m_bJumping == false)
            {
                if (m_bAirStep == false || (m_bIsTorCollision == true && C3dtornado::GetUpperTor() == false))
                {
                    m_nJumpTimer++;

                    //��юn�߂̏d�͂͒�߂ɐݒ肷��
                    if (m_nJumpTimer <= JUMP_TIMER)
                    {
                        //�d�͂̓K�p
                        m_n3DPlayerMove.y -= 0.7f;
                    }

                    if (m_nJumpTimer > JUMP_TIMER)
                    {
                        m_n3DPlayerMove.y -= 0.9f;

                    }

                }

                if (m_bAirStep == true)
                {
                    m_n3DPlayerMove.y = 0.0f;
                }

                if (C3dtornado::GetUpperTor() == true)
                {
                    m_n3DPlayerMove.y = 0.0f;
                }

            }



            //�v���C���[��HP��0�ȏ�̏ꍇ�̂ݒʂ�
            if (m_nLife > 0 && CBossCallUI::GetBeginCallUI() == false)
            {
                D3DXVECTOR3 moveDirection = { 0.0f, 0.0f, 0.0f };

                // �ړ�����
                if (CManager::GetKeyboard()->GetPress(DIK_A) || CManager::GetJoypad()->GetPress(CInputJoypad::JOYKEY_LEFT) || leftStickPos.x <= -0.3f)
                {
                    PlayerWalkSound();
                    m_n3DPlayerMove.x -= PLAYER_MOVE_SPD;
                    moveDirection.x += PLAYER_MOVE_SPD * (m_bPlayerBuff ? PLAYER_MOVE_BOOST : 1.0f);
                    bMove = true;
                }

                if (CManager::GetKeyboard()->GetPress(DIK_D) || CManager::GetJoypad()->GetPress(CInputJoypad::JOYKEY_RIGHT) || leftStickPos.x >= 0.3f)
                {
                    PlayerWalkSound();
                    m_n3DPlayerMove.x += PLAYER_MOVE_SPD;
                    moveDirection.x -= PLAYER_MOVE_SPD * (m_bPlayerBuff ? PLAYER_MOVE_BOOST : 1.0f);
                    bMove = true;
                }


                //if (CManager::GetKeyboard()->GetPress(DIK_S) || CManager::GetJoypad()->GetPress(CInputJoypad::JOYKEY_DOWN) || leftStickPos.y <= -0.3f)
                //{
                //        m_n3DPlayerMove.z -= PLAYER_MOVE_SPD;
                //        moveDirection.z += PLAYER_MOVE_SPD * (m_bPlayerBuff ? PLAYER_MOVE_BOOST : 1.0f);
                //}

                //if (CManager::GetKeyboard()->GetPress(DIK_W) || CManager::GetJoypad()->GetPress(CInputJoypad::JOYKEY_UP) || leftStickPos.y >= 0.3f)
                //{
                //        m_n3DPlayerMove.z += PLAYER_MOVE_SPD;
                //        moveDirection.z -= PLAYER_MOVE_SPD * (m_bPlayerBuff ? PLAYER_MOVE_BOOST : 1.0f);
                //}

                ////====================================
                ////�W�����v��ʐ؂�ւ�
                //if (CManager::GetKeyboard()->GetTrigger(DIK_1))
                //{
                //    m_nJumpType = DOUBLE_JUMP;
                //}

                //if (CManager::GetKeyboard()->GetTrigger(DIK_2))
                //{
                //    m_nJumpType = FREE_FLY;
                //}
                ////====================================

                // �����̉��Z�␳
                if (moveDirection.x != 0.0f || moveDirection.z != 0.0f)
                {
                    // ���݂̌�������V�����������v�Z
                    float targetAngle = atan2(moveDirection.x, moveDirection.z);
                    float deltaAngle = targetAngle - m_rot.y;

                    // �p�x�� -�� ���� �� �͈̔͂Ɏ��߂�
                    while (deltaAngle > D3DX_PI) deltaAngle -= 2 * D3DX_PI;
                    while (deltaAngle < -D3DX_PI) deltaAngle += 2 * D3DX_PI;

                    // �p�x���������␳����i�X���[�Y�Ȍ����ύX�j
                    const float rotationSpeed = 0.7f; // ��]���x�̒���
                    if (fabs(deltaAngle) > rotationSpeed)
                    {
                        m_rot.y += (deltaAngle > 0 ? rotationSpeed : -rotationSpeed);
                    }
                    else
                    {
                        m_rot.y = targetAngle; // �ڕW�p�x�ɒ��ڃZ�b�g
                    }
                }

                ////�v���C���[�̃X�e�b�v����
                //if (CManager::GetKeyboard()->GetTrigger(DIK_L))
                //{
                //    //�E�������Ă��鎞
                //    if (m_rot.y >= -1.6f && m_rot.y <= -0.1f)
                //    {
                //        if (m_bIsCollision == false)
                //        {
                //            m_bAirStep = true;
                //            m_n3DPlayerMove.x += 18.0f;
                //        }
                //    }

                //    //���������Ă��鎞
                //    if (m_rot.y >= 0.1f && m_rot.y <= 1.6f)
                //    {
                //        if (m_bIsCollision == false)
                //        {
                //            m_bAirStep = true;
                //            m_n3DPlayerMove.x -= 18.0f;
                //        }
                //    }
                //}

                //�󒆃X�e�b�v���L���̏ꍇ
                if (m_bAirStep == true)
                {
                    m_nAirStepTimer++; // �󒆑؋�^�C�}�[�����Z����

                    if (m_nAirStepTimer >= 13)
                    {
                        m_bAirStep = false;
                        m_nAirStepTimer = 0;
                    }
                }


                //2�i�W�����v���[�h�̏ꍇ
                if (m_nJumpType == DOUBLE_JUMP && m_bSuperJump == false)
                {
                    //�v���C���[�̃W�����v����
                    if ((CManager::GetKeyboard()->GetTrigger(DIK_SPACE) || CManager::GetJoypad()->GetTrigger(CInputJoypad::JOYKEY_A)) && m_bJumping == false)
                    {
                        //�v���C���[�̃W�����v����0�̏ꍇ(2�i�ȏ�̃W�����v�h�~)
                        if (m_nJumpCnt == 0)
                        {
                            CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_SE_PLAYER_JUMP);

                            if (m_bTorUPPER == false)
                            {
                                m_n3DPlayerMove.y += 15.5f;
                            }

                            if (m_bTorUPPER == true)
                            {
                                m_n3DPlayerMove.y += 40.0f;
                            }

                            m_bJumping = true;

                            bJump = true;

                            m_nJumpCnt++;
                        }

                    }
                }

                // �X���b�V���E�C���h�𔭓�
                if (CManager::GetKeyboard()->GetTrigger(DIK_K) || CManager::GetJoypad()->GetPress(CInputJoypad::JOYKEY_X))
                {
                    // �v���C���[���E���Ɍ����Ă���ꍇ
                    if (m_rot.y >= -1.6f && m_rot.y <= -0.1f)
                    {
                        // �R���{�̐i�s���Z�b�g����
                        if (m_fAtkTimer >= 60.0f) // 1�b�o�� (60�t���[��)
                        {
                            m_nAtkCombo = 0;
                            m_fAtkTimer = 0.0f;
                        }

                        // �R���{�̐i�s����
                        if (m_fAtkTimer >= m_nAtkCombo * 20) // �e�U����0.5�b�̊Ԋu
                        {
                            m_nAtkCombo++;

                            // 1�i�ڂ̍U��
                            if (m_nAtkCombo == 1)
                            {
                                CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_SE_SLASHWIND_1ST);
                                C3dslashwind::Create(D3DXVECTOR3(Pos.x + 60.0f, Pos.y, Pos.z));
                                C3dexplosion::Create(D3DXVECTOR3(Pos.x + 60.0f, Pos.y - 10.0f, Pos.z), D3DXVECTOR3(75.0f, 75.0f, 0.0f), m_rot, 0);
                                SetPlayerMotion(MOTION_ACTION);
                                MotionUse = true;
                            }
                            // 2�i�ڂ̍U��
                            else if (m_nAtkCombo == 2)
                            {
                                CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_SE_SLASHWIND_2ND);
                                MotionUse = false;
                                C3dslashwind::Create(D3DXVECTOR3(Pos.x + 40.0f, Pos.y, Pos.z));
                                C3dslashwind::Create(D3DXVECTOR3(Pos.x + 60.0f, Pos.y, Pos.z));
                                C3dslashwind::Create(D3DXVECTOR3(Pos.x + 80.0f, Pos.y, Pos.z));

                                C3dexplosion::Create(D3DXVECTOR3(Pos.x + 40.0f, Pos.y - 10.0f, Pos.z), D3DXVECTOR3(75.0f, 75.0f, 0.0f), m_rot, 0);
                                C3dexplosion::Create(D3DXVECTOR3(Pos.x + 60.0f, Pos.y - 10.0f, Pos.z), D3DXVECTOR3(75.0f, 75.0f, 0.0f), m_rot, 0);
                                C3dexplosion::Create(D3DXVECTOR3(Pos.x + 80.0f, Pos.y - 10.0f, Pos.z), D3DXVECTOR3(75.0f, 75.0f, 0.0f), m_rot, 0);
                                SetPlayerMotion(MOTION_ACTION2);
                                MotionUse = true;
                            }
                            // 3�i�ڂ̍U��
                            else if (m_nAtkCombo == 3)
                            {
                                CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_SE_SLASHWIND_3RD);
                                MotionUse = false;
                                C3dslashwind::Create(D3DXVECTOR3(Pos.x + 40.0f, Pos.y, Pos.z));
                                C3dslashwind::Create(D3DXVECTOR3(Pos.x + 80.0f, Pos.y, Pos.z));
                                C3dslashwind::Create(D3DXVECTOR3(Pos.x + 120.0f, Pos.y, Pos.z));

                                C3dexplosion::Create(D3DXVECTOR3(Pos.x + 40.0f, Pos.y - 10.0f, Pos.z), D3DXVECTOR3(75.0f, 75.0f, 0.0f), m_rot, 0);
                                C3dexplosion::Create(D3DXVECTOR3(Pos.x + 80.0f, Pos.y - 10.0f, Pos.z), D3DXVECTOR3(75.0f, 75.0f, 0.0f), m_rot, 0);
                                C3dexplosion::Create(D3DXVECTOR3(Pos.x + 120.0f, Pos.y - 10.0f, Pos.z), D3DXVECTOR3(75.0f, 75.0f, 0.0f), m_rot, 0);
                                SetPlayerMotion(MOTION_ACTION3);
                                MotionUse = true;

                                // �R���{�̃��Z�b�g
                                m_nAtkCombo = 0;
                            }

                            m_fAtkTimer = 0.0f;  // �^�C�}�[�����Z�b�g���ĐV�����U���̃J�E���g���J�n
                        }
                    }

                    // �v���C���[�������Ɍ����Ă���ꍇ
                    else if (m_rot.y >= 0.1f && m_rot.y <= 1.6f)
                    {
                        if (m_fAtkTimer >= 60.0f) // 1�b�o�� (60�t���[��)
                        {
                            m_nAtkCombo = 0;
                            m_fAtkTimer = 0.0f;
                        }

                        if (m_fAtkTimer >= m_nAtkCombo * 20.0f) // �e�U����0.5�b�̊Ԋu
                        {
                            m_nAtkCombo++;
                            m_fAtkTimer = 0.0f;

                            // 1�i�ڂ̍U��
                            if (m_nAtkCombo == 1)
                            {
                                CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_SE_SLASHWIND_1ST);
                                MotionUse = false;
                                C3dslashwind::Create(D3DXVECTOR3(Pos.x - 60.0f, Pos.y, Pos.z));

                                C3dexplosion::Create(D3DXVECTOR3(Pos.x - 60.0f, Pos.y - 10.0f, Pos.z), D3DXVECTOR3(75.0f, 75.0f, 0.0f), m_rot, 0);
                                SetPlayerMotion(MOTION_ACTION);
                                MotionUse = true;
                            }

                            // 2�i�ڂ̍U��
                            else if (m_nAtkCombo == 2)
                            {
                                CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_SE_SLASHWIND_2ND);
                                MotionUse = false;
                                C3dslashwind::Create(D3DXVECTOR3(Pos.x - 40.0f, Pos.y, Pos.z));
                                C3dslashwind::Create(D3DXVECTOR3(Pos.x - 60.0f, Pos.y, Pos.z));
                                C3dslashwind::Create(D3DXVECTOR3(Pos.x - 80.0f, Pos.y, Pos.z));

                                C3dexplosion::Create(D3DXVECTOR3(Pos.x - 40.0f, Pos.y - 10.0f, Pos.z), D3DXVECTOR3(75.0f, 75.0f, 0.0f), m_rot, 0);
                                C3dexplosion::Create(D3DXVECTOR3(Pos.x - 60.0f, Pos.y - 10.0f, Pos.z), D3DXVECTOR3(75.0f, 75.0f, 0.0f), m_rot, 0);
                                C3dexplosion::Create(D3DXVECTOR3(Pos.x - 80.0f, Pos.y - 10.0f, Pos.z), D3DXVECTOR3(75.0f, 75.0f, 0.0f), m_rot, 0);
                                SetPlayerMotion(MOTION_ACTION2);
                                MotionUse = true;
                            }
                            // 3�i�ڂ̍U��
                            else if (m_nAtkCombo == 3)
                            {
                                CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_SE_SLASHWIND_3RD);
                                MotionUse = false;
                                C3dslashwind::Create(D3DXVECTOR3(Pos.x - 40.0f, Pos.y, Pos.z));
                                C3dslashwind::Create(D3DXVECTOR3(Pos.x - 80.0f, Pos.y, Pos.z));
                                C3dslashwind::Create(D3DXVECTOR3(Pos.x - 120.0f, Pos.y, Pos.z));

                                C3dexplosion::Create(D3DXVECTOR3(Pos.x - 40.0f, Pos.y - 10.0f, Pos.z), D3DXVECTOR3(75.0f, 75.0f, 0.0f), m_rot, 0);
                                C3dexplosion::Create(D3DXVECTOR3(Pos.x - 80.0f, Pos.y - 10.0f, Pos.z), D3DXVECTOR3(75.0f, 75.0f, 0.0f), m_rot, 0);
                                C3dexplosion::Create(D3DXVECTOR3(Pos.x - 120.0f, Pos.y - 10.0f, Pos.z), D3DXVECTOR3(75.0f, 75.0f, 0.0f), m_rot, 0);
                                SetPlayerMotion(MOTION_ACTION3);
                                MotionUse = true;

                                m_nAtkCombo = 0; // �R���{�̃��Z�b�g
                            }
                        }
                    }
                }


                //�������o������
                if (CManager::GetKeyboard()->GetTrigger(DIK_J) || CManager::GetJoypad()->GetTrigger(CInputJoypad::JOYKEY_Y))
                {
                    if (m_nNumTornado > 0)
                    {
                        if (m_nDisplayTorNum <= 2)
                        {
                            CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_SE_TORNADO_STARTUP);

                            // �v���C���[�������Ɍ����Ă���ꍇ
                            if (m_rot.y >= -1.6f && m_rot.y <= -0.1f)
                            {
                                C3dtornado::Create(D3DXVECTOR3(Pos.x + 60.0f, Pos.y, Pos.z), (0));
                                C3dtornadoeffect::Create(D3DXVECTOR3(Pos.x + 60.0f, Pos.y - 20.0f, Pos.z), D3DXVECTOR3(65.0f, 85.0f, 0.0f), m_rot, 0);
                                MotionUse = false;
                                SetPlayerMotion(MOTION_TORNADO);
                                MotionUse = true;
                            }

                            // �v���C���[���E���Ɍ����Ă���ꍇ
                            if (m_rot.y >= 0.1f && m_rot.y <= 1.6f)
                            {
                                C3dtornado::Create(D3DXVECTOR3(Pos.x - 60.0f, Pos.y, Pos.z), (0));
                                C3dtornadoeffect::Create(D3DXVECTOR3(Pos.x - 60.0f, Pos.y - 20.0f, Pos.z), D3DXVECTOR3(65.0f, 85.0f, 0.0f), m_rot, 0);
                                MotionUse = false;
                                SetPlayerMotion(MOTION_TORNADO);
                                MotionUse = true;
                            }

                            m_nNumTornado--;
                            m_nDisplayTorNum++;
                        }
                    }
                }


                //�󒆕��V���[�h�̏ꍇ
                if (m_nJumpType == FREE_FLY && m_bSuperJump == false)
                {
                    // �X�y�[�X�L�[��������Ă���ԁA�v���C���[���󒆕��V����
                    if (CManager::GetKeyboard()->GetPress(DIK_SPACE))
                    {
                        // ���V�^�C�}�[��60�t���[��(1�b)�ȓ��̏ꍇ
                        if (m_nFreeFlyTimer <= 50)
                        {
                            // �㏸������
                            m_n3DPlayerMove.y += 1.3f;


                            // ���V�^�C�}�[�����Z
                            m_nFreeFlyTimer++;
                        }
                    }

                    else
                    {
                        // �X�y�[�X�L�[�������ꂽ��^�C�}�[�����Z�b�g
                        m_nFreeFlyTimer = 0;
                    }
                }
            }

            //�W�����v���̏ꍇ
            if (m_bJumping == true)
            {
                SetPlayerMotion(MOTION_JUMP);
                MotionUse = true;

                m_nJumpAnimTimer++;

                if (m_nJumpAnimTimer == 18)
                {
                    m_nJumpAnimTimer = 0;
                    m_bJumping = false;
                    MotionUse = false;
                }
            }


            //�v���C���[�̗̑͂�0�ȉ��ɂȂ����ꍇ���U���g��ʂ֑J��
            if (m_nLife <= 0)
            {

                for (int nCnt = 0; nCnt < PLAYER_MODEL; nCnt++)
                {
                    m_bUse[nCnt] = false;
                }


                m_nDeathTimer++;

                if (m_nDeathTimer == 1)
                {
                    C3dhiteffect::Create(CObject3D::GetPos(), D3DXVECTOR3(70.0f, 70.0f, 0.0f), m_rot);
                }

                if (m_nDeathTimer == 90)
                {
                    CEndCallUI::DisplayEndCallUI(CEndCallUI::ICONDISPLAY::ICON_FAILED, CEndCallUI::UIDISPLAY::UI_DISPLAY);
                    Uninit();
                }

                //CEndCallUI::DisplayEndCallUI(CEndCallUI::ICONDISPLAY::ICON_FAILED, CEndCallUI::UIDISPLAY::UI_DISPLAY);

                return;
            }

#if _DEBUG
            //�^�C�}�[�̏����𖳌��ɂ��Ă鎞�̂ݎg�p
            if (CManager::GetKeyboard()->GetTrigger(DIK_RETURN))
            {
                CManager::GetFade()->SetFade(CScene::MODE_GAME);
                Uninit();
                return;
            }
#endif

            //�v���C���[�����������ۂ̏���
            if (Pos.y <= -300.0f)
            {

                CEndCallUI::DisplayEndCallUI(CEndCallUI::ICONDISPLAY::ICON_FAILED, CEndCallUI::UIDISPLAY::UI_DISPLAY);
                //Uninit();
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
                }
            }
        }


            //�ߋ����W��ۑ�
            m_nOld3DPlayerPos = Pos;

            Pos.x += m_n3DPlayerMove.x;
            Pos.y += m_n3DPlayerMove.y;
            Pos.z += m_n3DPlayerMove.z;

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

                            bool bIsCollision = p3dblock->Collision3DBlock(&Pos, &m_nOld3DPlayerPos, &m_n3DPlayerMove, 50.0f, 0.0f);

                            if (bIsCollision == true)
                            {
                                m_nJumpTimer = 0; //�W�����v���̎��Ԃ����Z�b�g����
                                m_bJumping = false;
                                m_nJumpCnt = 0;
                                m_n3DPlayerMove.y = 0.0f;

                                m_nDisplayTorNum = 0;

                                m_bTorUPPER = false;
                            }

                        }

                    }
                }
            }


            //�G�Ƃ̓����蔻��̕␳
            for (int nCntPriority = 0; nCntPriority < MAX_PRIORITY; nCntPriority++)
            {
                for (int nCntObj = 0; nCntObj < C3denemy::GetMaxEnemy() + 200; nCntObj++)
                {
                    CObject* pObj = CObject::GetObj(nCntPriority, nCntObj);

                    if (pObj != nullptr)
                    {
                        CObject::TYPE type = pObj->GetType();

                        if (type == CObject::TYPE::ENEMY_NORMAL)
                        {
                            C3denemy* p3denemy = (C3denemy*)pObj;

                            bool bIsCollision = p3denemy->Collision3DEnemy(&Pos, &m_nOld3DPlayerPos, &m_n3DPlayerMove, 20.0f, 70.0f);

                            if (bIsCollision == true)
                            {
                                m_nJumpTimer = 0; //�W�����v���̎��Ԃ����Z�b�g����
                                m_bJumping = false;
                                m_nJumpCnt = 0;

                                C3dplayer::PlayerBlown(0);

                                m_nDisplayTorNum = 0;

                                m_bTorUPPER = false;

                                PlayerDamage(5);
                            }

                        }

                    }
                }
            }

            //�G�Ƃ̓����蔻��̕␳
            for (int nCntPriority = 0; nCntPriority < MAX_PRIORITY; nCntPriority++)
            {
                for (int nCntObj = 0; nCntObj < C3denemy::GetMaxEnemy() + 200; nCntObj++)
                {
                    CObject* pObj = CObject::GetObj(nCntPriority, nCntObj);

                    if (pObj != nullptr)
                    {
                        CObject::TYPE type = pObj->GetType();

                        if (type == CObject::TYPE::ENEMY_FLYMOVE)
                        {
                            C3denemyair* p3denemyair = (C3denemyair*)pObj;

                            bool bIsCollision = p3denemyair->Collision3DEnemyAir(&Pos, &m_nOld3DPlayerPos, &m_n3DPlayerMove, 20.0f, 70.0f);

                            if (bIsCollision == true)
                            {
                                m_nJumpTimer = 0; //�W�����v���̎��Ԃ����Z�b�g����
                                m_bJumping = false;
                                m_nJumpCnt = 0;
                                m_n3DPlayerMove.y = 0.0f;

                                C3dplayer::PlayerBlown(0);

                                m_nDisplayTorNum = 0;

                                m_bTorUPPER = false;
                            }

                        }

                    }
                }
            }

            //�G�Ƃ̓����蔻��̕␳
            for (int nCntPriority = 0; nCntPriority < MAX_PRIORITY; nCntPriority++)
            {
                for (int nCntObj = 0; nCntObj < 10; nCntObj++)
                {
                    CObject* pObj = CObject::GetObj(nCntPriority, nCntObj);

                    if (pObj != nullptr)
                    {
                        CObject::TYPE type = pObj->GetType();

                        if (type == CObject::TYPE::BOSS)
                        {
                            C3dboss* p3dboss = (C3dboss*)pObj;

                            bool bIsCollision = p3dboss->Collision3DBoss(&Pos, &m_nOld3DPlayerPos, &m_n3DPlayerMove, 20.0f, 190.0f);

                            if (bIsCollision == true)
                            {
                                m_nJumpTimer = 0; //�W�����v���̎��Ԃ����Z�b�g����
                                m_bJumping = false;
                                m_nJumpCnt = 0;

                                C3dplayer::PlayerBlown(1);

                                PlayerDamage(5);

                                m_nDisplayTorNum = 0;

                                m_bTorUPPER = false;
                            }

                        }

                    }
                }
            }

            //�u���b�N�Ƃ̓����蔻��̕␳
            for (int nCntPriority = 0; nCntPriority < MAX_PRIORITY; nCntPriority++)
            {
                for (int nCntObj = 0; nCntObj < C3dswitchbs::GetMaxSwitchbs() + 60; nCntObj++)
                {
                    CObject* pObj = CObject::GetObj(nCntPriority, nCntObj);

                    if (pObj != nullptr)
                    {
                        CObject::TYPE type = pObj->GetType();

                        if (type == CObject::TYPE::SWITCH_BS)
                        {
                            C3dswitchbs* p3dblock = (C3dswitchbs*)pObj;

                            bool bIsCollision = p3dblock->Collision3DSwitchbs(&Pos, &m_nOld3DPlayerPos, &m_n3DPlayerMove, 50.0f, 0.0f);

                            if (bIsCollision == true)
                            {
                                CBossCallUI::StartCallUIBossFlag();
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

                            m_bIsCollision = p3dmoveblock->Collision3DMoveblock(&Pos, &m_nOld3DPlayerPos, &m_n3DPlayerMove, 20.0f, 50.0f);

                            if (m_bIsCollision == true)
                            {

                                m_n3DPlayerMove.y = 0.0f;
                                m_nJumpCnt = 0;
                                Pos.x += (p3dmoveblock->GetMoveBlock().x * 1.1);
                                m_nDisplayTorNum = 0;

                                m_bTorUPPER = false;
                            }
                        }

                        if (type == CObject::TYPE::MOVEBLOCK_Z)
                        {
                            C3dmoveblock* p3dmoveblock = (C3dmoveblock*)pObj;

                            bool bIsCollision = p3dmoveblock->Collision3DMoveblock(&Pos, &m_nOld3DPlayerPos, &m_n3DPlayerMove, 50.0f, 50.0f);

                            if (bIsCollision == true)
                            {
                                m_nJumpTimer = 0; //�W�����v���̎��Ԃ����Z�b�g����
                                m_n3DPlayerMove.y = 0.0f;
                                m_nJumpCnt = 0;
                                Pos.z += (p3dmoveblock->GetMoveBlock().z);
                            }

                        }

                    }
                }
            }

            //�o�t�A�C�e���̓����蔻��
            for (int nCntObj = 0; nCntObj < C3ditem::MAX_ITEM; nCntObj++)
            {
                CObject* pObj = CObject::GetObj(3, nCntObj);

                if (pObj != nullptr)
                {
                    CObject::TYPE type = pObj->GetType();

                    C3ditem* p3dItem = (C3ditem*)pObj;

                    D3DXVECTOR3 EnemyPos = p3dItem->GetPos();

                    //�̗͒ǉ��A�C�e���̏ꍇ
                    if (type == CObject::TYPE::ITEM_ADDLIFE)
                    {
                        if (CObject3D::GetPos().x >= EnemyPos.x - 40
                            && CObject3D::GetPos().x <= EnemyPos.x + 40
                            && CObject3D::GetPos().y >= EnemyPos.y - 40
                            && CObject3D::GetPos().y <= EnemyPos.y + 40
                            && CObject3D::GetPos().z >= EnemyPos.z - 40
                            && CObject3D::GetPos().z <= EnemyPos.z + 40)
                        {
                            CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_SE_PLAYER_ADDLIFE);
                            m_nLife += 15;
                            p3dItem->Uninit();
                            return;
                        }
                    }
                }
            }

            //�S�[���}�[�J�[�Ƃ̓����蔻��̕␳
            for (int nCntPriority = 0; nCntPriority < MAX_PRIORITY; nCntPriority++)
            {
                for (int nCntObj = 0; nCntObj < C3dblock::MAX_BLOCK; nCntObj++)
                {
                    CObject* pObj = CObject::GetObj(nCntPriority, nCntObj);

                    if (pObj != nullptr)
                    {
                        CObject::TYPE type = pObj->GetType();

                        if (type == CObject::TYPE::GOAL)
                        {
                            C3dgoalobj* p3dgoalobj = (C3dgoalobj*)pObj;

                            bool bIsCollision = p3dgoalobj->Collision3DGoalobj(&Pos, &m_nOld3DPlayerPos, &m_n3DPlayerMove, 50.0f, 50.0f);
                        }
                    }
                }
            }

            //�����Ƃ̓����蔻��̕␳
            for (int nCntPriority = 0; nCntPriority < MAX_PRIORITY; nCntPriority++)
            {
                for (int nCntObj = 0; nCntObj < C3dtornado::MAX_TORNADO + 200; nCntObj++)
                {
                    CObject* pObj = CObject::GetObj(nCntPriority, nCntObj);

                    if (pObj != nullptr)
                    {
                        CObject::TYPE type = pObj->GetType();

                        if (type == CObject::TYPE::SLASHTORNADO)
                        {
                            C3dtornado* p3dtornado = (C3dtornado*)pObj;

                            m_bIsTorCollision = p3dtornado->Collision3DTornado(&Pos, &m_nOld3DPlayerPos, &m_n3DPlayerMove, 20.0f, 20.0f);


                            if (m_bIsTorCollision == true && C3dtornado::GetUpperTor() == false)
                            {
                                CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_SE_TORNADO_JUMP);

                                m_n3DPlayerMove.y += 22.0f;
                            }


                            if (C3dtornado::GetUpperTor() == true)
                            {
                                m_nJumpCnt = 0;

                                Pos.y += 0.5f;

                                C3dplayer::m_bTorUPPER = true;
                            }

                            else
                            {
                                m_bSuperJump = false;
                            }
                        }
                    }
                }
            }

            //if (m_bIsTorCollision == true)
            //{
            //    CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_SE_TORNADO_JUMP);

            //    if (Pos.y <= Pos.y + C3dtornado::GetTorHeightPos())
            //    {
            //        Pos.y += 0.0f;
            //    }

            //    if (Pos.y >= Pos.y + C3dtornado::GetTorHeightPos())
            //    {
            //        C3dtornado::GetTorHeightPos();
            //    }

            //    m_nJumpCnt++;
            //}

            //���W��ݒ�
            SetPos(Pos);

           

            // �^�C�}�[�̍X�V����
            if (m_nAtkCombo > 0)
            {
                m_fAtkTimer += 1.0f; // �t���[�����ƂɃ^�C�}�[�����Z

                // 1�i�ڂ̍U������1�b�o�߂��Ă�����R���{�����Z�b�g
                if (m_fAtkTimer >= 60.0f)
                {
                    m_nAtkCombo = 0;
                    m_fAtkTimer = 0.0f;
                }
            }



           

            if (m_nNumTornado == 1 || m_nNumTornado == 0)
            {
                m_nTorReloadTimer++;

                if (m_nTorReloadTimer >= 240)
                {
                    m_nNumTornado++;
                    m_nTorReloadTimer = 0;
                }
            }

            //�_���[�W���󂯂���
            if (m_bDamageState == true)
            {
                m_nDmgColorTimer++;

                if (m_nDmgColorTimer >= 5)
                {
                    m_bDamageState = false; //�}�e���A���̐F��߂�
                    m_nDmgColorTimer = 0;

                }
            }

#if _DEBUG
            if (CManager::GetKeyboard()->GetPress(DIK_B))
            {
                m_nLife--;
            }
#endif

            //X���W�̈ړ��ʂ��X�V
            m_n3DPlayerMove.x += (Length_value2 - m_n3DPlayerMove.x) * Attenuation_value;

            //Y���W�̈ړ��ʂ��X�V
            m_n3DPlayerMove.y += (Length_value2 - m_n3DPlayerMove.y) * Attenuation_value;

            //Z���W�̈ړ��ʂ��X�V
            m_n3DPlayerMove.z += (Length_value2 - m_n3DPlayerMove.z) * Attenuation_value;

            //�W�����v���ĂȂ����͕��sSE�𗬂��Ȃ�
            if (m_n3DPlayerMove.y < 0.0f)
            {
                CManager::GetSound()->Stop(CSound::SOUND_LABEL_SE_PLAYER_WALK);
            }

    }


    int nFadeState = CFade::GetFadeState();

    if (nFadeState == CFade::FADE_OUT)
    {
        C3dplayer::Uninit();
        return;
    }
 
}


//======================
// �`�揈��
//======================
void C3dplayer::Draw()
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
    D3DXMatrixMultiply(&m_mtxworld, &m_mtxworld , &mtxTrans);

    // �_���[�W���̃��f���̃}�e���A���ݒ�
    D3DMATERIAL9 DMGMaterial = {};
    DMGMaterial.Diffuse.r = 1.0f; // ��
    DMGMaterial.Diffuse.g = 0.0f; // ��
    DMGMaterial.Diffuse.b = 0.0f; // ��
    DMGMaterial.Diffuse.a = 1.0f; // �����x

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

    for (int nCntParts = 0; nCntParts < PLAYER_MODEL; nCntParts++)
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



            for (int nCntMat = 0; nCntMat < (int)m_nNumMat[nCntParts]; nCntMat++)
            {
                //�_���[�W���󂯂Ă��Ȃ���
                if (m_bDamageState == false)
                {
                    //�}�e���A���̐ݒ�
                    pDevice->SetMaterial(&pMat[nCntMat].MatD3D);
                }

                //�_���[�W���󂯂Ă��鎞
                if (m_bDamageState == true)
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
                    pDevice->SetTexture(0,&m_aModel[0].m_pTexture[nCntMat]);
                }

                else
                {
                    //�e�N�X�`���̐ݒ�
                    pDevice->SetTexture(0, NULL);
                }

                if (m_bUse[nCntParts] == true)
                {
                    //���f��(�p�[�c)�̕`��
                    m_pMesh[nCntParts]->DrawSubset(nCntMat);
                }



                m_pMesh[nCntParts]->GetDeclaration(m_aElements);

            }

    }

    pDevice->SetMaterial(&matDef);
}

//======================
// �I�u�W�F�N�g��������
//======================
C3dplayer* C3dplayer::Create(D3DXVECTOR3 pos)
{
    C3dplayer* D3Dplayer = nullptr;

    D3Dplayer = new C3dplayer;

    //�������ɐ��������ꍇ
    if (SUCCEEDED(D3Dplayer->Init()))
    {
        D3Dplayer->SetType(TYPE::PLAYER);

        D3Dplayer->LoadPlayerData();

        D3Dplayer->CObject3D::SetPos(pos);

        D3Dplayer->m_rot.y = -1.57f;

        //D3Dplayer->Load();//�e�N�X�`����ݒ�(��)


        ////�e�N�X�`���̐ݒ�
        //Model->BindTexture(m_pTexBuff);
    }

    return D3Dplayer;
}

//======================
// �v���C���[��������΂���鋓���̏���
//======================
void C3dplayer::PlayerBlown(int nType)
{
    //������������т̋����̏ꍇ
    if (nType == 0)
    {
        //�v���C���[�������Ɍ����Ă���ꍇ
        if (m_rot.y >= 0.1f && m_rot.y <= 1.6f)
        {
            m_n3DPlayerMove.y += 28.0f;
            m_n3DPlayerMove.x += 15.0f;
        }

        // �v���C���[���E���Ɍ����Ă���ꍇ
        else if (m_rot.y >= -1.6f && m_rot.y <= -0.1f)
        {
            m_n3DPlayerMove.y += 28.0f;
            m_n3DPlayerMove.x -= 15.0f;
        }
    }

    //�傫��������т̋����̏ꍇ
    if (nType == 1)
    {
        //�v���C���[�������Ɍ����Ă���ꍇ
        if (m_rot.y >= 0.1f && m_rot.y <= 1.6f)
        {
            m_n3DPlayerMove.y += 28.0f;
            m_n3DPlayerMove.x -= 32.0f;
        }

        // �v���C���[���E���Ɍ����Ă���ꍇ
        else if (m_rot.y >= -1.6f && m_rot.y <= -0.1f)
        {
            m_n3DPlayerMove.y += 28.0f;
            m_n3DPlayerMove.x += 32.0f;
        }
    }

    //�傫��������т̋����̏ꍇ(�{�X���p)
    if (nType == 2)
    {
        //�{�X�������Ɍ����Ă���ꍇ
        if (C3dboss::GetBossRot().y >= 0.1f && C3dboss::GetBossRot().y <= 1.68f)
        {
            m_n3DPlayerMove.y += 28.0f;
            m_n3DPlayerMove.x -= 32.0f;
        }

        // �{�X���E���Ɍ����Ă���ꍇ
        else if (C3dboss::GetBossRot().y >= -1.68f && C3dboss::GetBossRot().y <= -0.1f)
        {
            m_n3DPlayerMove.y += 28.0f;
            m_n3DPlayerMove.x += 32.0f;
        }
    }
}

//======================
// �v���C���[�ړ�SE�Đ�����
//======================
void C3dplayer::PlayerWalkSound()
{
    m_nWalkSoundCnt++;
    
    if (m_nWalkSoundCnt == 20)
    {
        CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_SE_PLAYER_WALK);
        m_nWalkSoundCnt = 0;
    }

}

//======================
// �e�N�X�`�����[�h����
//======================
HRESULT C3dplayer::Load()
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
void C3dplayer::Unload()
{
    CModel::Unload();
}


//======================
// �v���C���[�̃_���[�W����
//======================
void C3dplayer::PlayerDamage(int nDamage)
{
    CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_SE_PLAYER_DAMAGE);
    m_nLife -= nDamage;
    m_bDamageState = true;
}


//===========================
// �O���t�@�C���ǂݍ��ݏ���
//===========================

void C3dplayer::LoadPlayerData(void)
{
    char Datacheck[MAX_CHAR];
    int nCnt= 0;
    int EnemyModelSave = 0;
    int nMotionCount = 0;
    int nKeyCount = 0;
    int nKeySetCount = 0;

    m_pFile = fopen("data\\MODEL\\MODEL_MAGICIAN\\Charamotion.txt", "r");//�t�@�C�����J��

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
                    fscanf(m_pFile, "%s", &C3dplayer::m_aLoadEnemy[EnemyModelSave].filename[0]);
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
                                    fscanf(m_pFile, "%d", &C3dplayer::m_aLoadEnemy[nCnt].index);
                                }		// ���
                                else if (!strcmp(Datacheck, "PARENT"))
                                {
                                    fscanf(m_pFile, "%s", Datacheck);
                                    fscanf(m_pFile, "%d", &C3dplayer::m_aLoadEnemy[nCnt].parent);
                                }		// ��
                                else if (!strcmp(Datacheck, "POS"))
                                {
                                    fscanf(m_pFile, "%s", Datacheck);
                                    fscanf(m_pFile, "%f", &C3dplayer::m_aLoadEnemy[nCnt].pos.x);
                                    fscanf(m_pFile, "%f", &C3dplayer::m_aLoadEnemy[nCnt].pos.y);
                                    fscanf(m_pFile, "%f", &C3dplayer::m_aLoadEnemy[nCnt].pos.z);
                                }	// ����
                                else if (!strcmp(Datacheck, "ROT"))
                                {
                                    fscanf(m_pFile, "%s", Datacheck);
                                    fscanf(m_pFile, "%f", &C3dplayer::m_aLoadEnemy[nCnt].rot.x);
                                    fscanf(m_pFile, "%f", &C3dplayer::m_aLoadEnemy[nCnt].rot.y);
                                    fscanf(m_pFile, "%f", &C3dplayer::m_aLoadEnemy[nCnt].rot.z);
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
                                 C3dplayer::MotionSet[nMotionCount].Loop = false;
                            }
                            else
                            {
                                 C3dplayer::MotionSet[nMotionCount].Loop = true;
                            }
                        }		// ���
                        else if (!strcmp(Datacheck, "NUM_KEY")) //�L�[���̓ǂݍ���
                        {
                            fscanf(m_pFile, "%s", Datacheck);
                            fscanf(m_pFile, "%d", & C3dplayer::MotionSet[nMotionCount].NumKey);
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
                                    fscanf(m_pFile, "%d", & C3dplayer::MotionSet[nMotionCount].KeySet[nKeySetCount].Frame);
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
                                            fscanf(m_pFile, "%f", & C3dplayer::MotionSet[nMotionCount].KeySet[nKeySetCount].aKey[nKeyCount].pos.x);
                                            fscanf(m_pFile, "%f", & C3dplayer::MotionSet[nMotionCount].KeySet[nKeySetCount].aKey[nKeyCount].pos.y);
                                            fscanf(m_pFile, "%f", & C3dplayer::MotionSet[nMotionCount].KeySet[nKeySetCount].aKey[nKeyCount].pos.z);
                                        }
                                        else if (!strcmp(Datacheck, "ROT"))
                                        {
                                            fscanf(m_pFile, "%s", Datacheck);
                                            fscanf(m_pFile, "%f", & C3dplayer::MotionSet[nMotionCount].KeySet[nKeySetCount].aKey[nKeyCount].rot.x);
                                            fscanf(m_pFile, "%f", & C3dplayer::MotionSet[nMotionCount].KeySet[nKeySetCount].aKey[nKeyCount].rot.y);
                                            fscanf(m_pFile, "%f", & C3dplayer::MotionSet[nMotionCount].KeySet[nKeySetCount].aKey[nKeyCount].rot.z);
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
        D3DXLoadMeshFromX(&C3dplayer::m_aLoadEnemy[nInfoCount].filename[0], D3DXMESH_SYSTEMMEM,pDevice,NULL, &m_pBuffMat[nInfoCount],NULL,&m_nNumMat[nInfoCount],&m_pMesh[nInfoCount]);

        //�ʒu�̏�����
        m_aModel[nInfoCount].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
        m_aModel[nInfoCount].nIdxModelParent = C3dplayer::m_aLoadEnemy[nInfoCount].parent;
        m_aModel[nInfoCount].pos = D3DXVECTOR3(C3dplayer::m_aLoadEnemy[nInfoCount].pos.x, C3dplayer::m_aLoadEnemy[nInfoCount].pos.y, C3dplayer::m_aLoadEnemy[nInfoCount].pos.z);
        m_aModel[nInfoCount].rot = D3DXVECTOR3(C3dplayer::m_aLoadEnemy[nInfoCount].rot.x, C3dplayer::m_aLoadEnemy[nInfoCount].rot.y, C3dplayer::m_aLoadEnemy[nInfoCount].rot.z);

        m_aModel[nInfoCount].pos +=C3dplayer::MotionSet[0].KeySet[0].aKey[nInfoCount].pos;
        m_aModel[nInfoCount].rot +=C3dplayer::MotionSet[0].KeySet[0].aKey[nInfoCount].rot;
    }
}

//======================
// ���[�V�����̎w��
//======================
void C3dplayer::SetPlayerMotion(PLAYERMOTION motion)
{
    if (C3dplayer::Motion != motion && C3dplayer::MotionUse == false) //���݂̃��[�V�����ƈ������
    {
        C3dplayer::Motion = motion; //���[�V������ݒ�
        C3dplayer::m_nMotionCnt = 0; //���[�V�����̃J�E���g��������
        C3dplayer::m_nFrameCnt = 0;  //�t���[���̃J�E���g�̏�����

        // ���f���̃p�[�c���J��Ԃ��Ĉʒu�Ɖ�]��������
        for (int nModelCount = 0; nModelCount < PLAYER_MODEL; nModelCount++)
        {
            m_aModel[nModelCount].pos = m_aLoadEnemy[nModelCount].pos + C3dplayer::MotionSet[motion].KeySet[0].aKey[nModelCount].pos;
            m_aModel[nModelCount].rot = m_aLoadEnemy[nModelCount].rot + C3dplayer::MotionSet[motion].KeySet[0].aKey[nModelCount].rot;
        }
    }
}

//======================
// ���f���̃��[�V��������
//======================
void C3dplayer::ModelMotion()
{
    // ���f���̃p�[�c���J��Ԃ�
    for (int nModelCount = 0; nModelCount < PLAYER_MODEL; nModelCount++)
    {
        // ���݂̃��[�V�����̃L�[�Z�b�g���擾
        const auto& currentKey = C3dplayer::MotionSet[Motion].KeySet[m_nMotionCnt];
        const auto& nextKey = C3dplayer::MotionSet[Motion].KeySet[(m_nMotionCnt + 1) % C3dplayer::MotionSet[Motion].NumKey];

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
    if (m_nFrameCnt >= C3dplayer::MotionSet[C3dplayer::Motion].KeySet[m_nMotionCnt].Frame)
    {
        m_nFrameCnt = 0;           // �J�E���g��������
        m_nMotionCnt++;            // ���[�V�����̃J�E���g�𑝉�

        // ���[�V�����̏I���������`�F�b�N
        if (m_nMotionCnt >= C3dplayer::MotionSet[C3dplayer::Motion].NumKey)
        {
            m_nMotionCnt = 0; // �J�E���g��0�ɂ���

            // ���[�v���Ȃ��ꍇ�A���[�V�������~
            if (!C3dplayer::MotionSet[C3dplayer::Motion].Loop)
            {
                C3dplayer::MotionUse = false;    // ���[�V�����̔����off�ɂ���
                SetPlayerMotion(MOTION_NORMAL);  // ���[�V�����̏��̐؂�ւ�
            }
        }
    }
}
