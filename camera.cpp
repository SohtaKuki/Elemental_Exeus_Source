//=================================================
//
// �J�������� (camera.cpp)
// Author: Sohta Kuki
//
//=================================================

#include "camera.h"
#include "manager.h"
#include "object.h"
#include "3dplayer.h"
#include "3dgoalobj.h"
#include "bosscallui.h"
#include "3dboss.h"

int CCamera::m_nShakeframe = 0;
float CCamera::m_fShake = 0.0f;

//======================
// �R���X�g���N�^
//======================
CCamera::CCamera()
{

}

//======================
// �f�X�g���N�^
//======================
CCamera::~CCamera()
{

}

//======================
// ����������
//======================
HRESULT CCamera::Init()
{
    m_posV = D3DXVECTOR3(220.0f, 10.0f, 1250.0f);
    m_posR = D3DXVECTOR3(220.0f, 110.0f, -680.0f);
    m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
    m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    m_fDistance = sqrtf((0.0f * 0.0f * 100.0f) + (m_posV.z * m_posV.z));
    m_fStartPos = 10.0f;
    m_fEndPos = 10000.0f;
    m_fFogDisity = 0.0000f;
    m_fBlizCnt = 0.00055f;
    m_bBlizSwitch = false;

    m_targetPosV = m_posV;
    m_targetPosR = m_posR;
    m_followSpeed = 0.1f; // �J�����Ǐ]���x

    return S_OK;
}

//======================
// �I������
//======================
void CCamera::Uninit()
{

}

//======================
// �X�V����
//======================
void CCamera::Update()
{
    if (C3dgoalobj::GetStageNum() == 0 || C3dgoalobj::GetStageNum() == 1)
    {
        CObject* pObj = CObject::GetObj(3, 1);

        if (pObj != nullptr)
        {
            CObject::TYPE type = pObj->GetType();

            C3dplayer* p3dPlayer = (C3dplayer*)pObj;

            if (C3dgoalobj::GetStageNum() == 0)
            {
                // �v���C���[�ɃJ������Ǐ]����
                m_targetPosV.x = p3dPlayer->GetPos().x + 220.0f;
                m_targetPosR.x = p3dPlayer->GetPos().x + 220.0f;

                // �v���C���[��y���W�ɍ��킹�ăJ������Ǐ]����
                if (p3dPlayer->GetPos().y >= 320.0f)
                {
                    m_targetPosV.y = p3dPlayer->GetPos().y - 155.0f;
                    m_targetPosR.y = p3dPlayer->GetPos().y - 150.0f;
                    m_targetPosV.z = p3dPlayer->GetPos().z + 1250.0f;
                    m_targetPosR.z = p3dPlayer->GetPos().z - 400.0f;
                }
                else
                {
                    m_targetPosV.y = 195.0f;
                    m_targetPosR.y = 190.0f;
                    m_targetPosV.z = p3dPlayer->GetPos().z + 1250.0f;
                    m_targetPosR.z = p3dPlayer->GetPos().z - 400.0f;
                }
            }

            if (C3dgoalobj::GetStageNum() == 1)
            {
                // �v���C���[�ɃJ������Ǐ]����
                m_targetPosV.x = p3dPlayer->GetPos().x + 220.0f;
                m_targetPosR.x = p3dPlayer->GetPos().x + 220.0f;

                // �v���C���[��y���W�ɍ��킹�ăJ������Ǐ]����
                if (p3dPlayer->GetPos().y >= 410.0f)
                {
                    m_targetPosV.y = p3dPlayer->GetPos().y - 15.0f;
                    m_targetPosR.y = p3dPlayer->GetPos().y - 0.0f;
                    m_targetPosV.z = p3dPlayer->GetPos().z + 1250.0f;
                    m_targetPosR.z = p3dPlayer->GetPos().z - 400.0f;
                }
                else
                {
                    m_targetPosV.y = 195.0f;
                    m_targetPosR.y = 190.0f;
                    m_targetPosV.z = p3dPlayer->GetPos().z + 1250.0f;
                    m_targetPosR.z = p3dPlayer->GetPos().z - 400.0f;
                }
            }
        }
    }

    if (C3dgoalobj::GetStageNum() == 2)
    {
        // �{�X�o���O�A�o����̃J�������_
        if (C3dgoalobj::GetStageNum() == 2 && CBossCallUI::GetEndStat() == false && C3dboss::GetBossEntry() == false ||
            C3dgoalobj::GetStageNum() == 2 && CBossCallUI::GetEndStat() == true && C3dboss::GetBossEntry() == true)
        {

            m_targetPosV = D3DXVECTOR3(270.0f, 280.0f, 1400.0f);
            m_targetPosR = D3DXVECTOR3(270.0f, 275.0f, -680.0f);

            m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
        }

        // �o�����̃J�������_
        if (C3dgoalobj::GetStageNum() == 2 && CBossCallUI::GetEndStat() == true && C3dboss::GetBossEntry() == false)
        {
            m_targetPosV = D3DXVECTOR3(338.0f, 80.0f, -13.0f);
            m_targetPosR = D3DXVECTOR3(368.0f, C3dboss::GetBossPosCamera().y + 67.5f, -13.0f);

            m_rot.y = 1.57f;
        }
    }

    // ���݂̃J�����ʒu��ڕW�J�����ʒu�ɐ��`���
    m_posV += (m_targetPosV - m_posV) * m_followSpeed;
    m_posR += (m_targetPosR - m_posR) * m_followSpeed;

    m_posV.x = m_posR.x - sinf(m_rot.y) * 500;
    m_posV.z = m_posR.z - cosf(m_rot.y) * 500;
}

//======================
// �J�����̐U������
//======================
void CCamera::SetShake(int shakeframe, float shake)
{
    m_nShakeframe = shakeframe;
    m_fShake = shake;
}

//======================
// �J�����̐ݒ菈��
//======================
void CCamera::SetCamera()
{
    CRenderer* Renderer = CManager::GetRenderer();
    LPDIRECT3DDEVICE9 pDevice = Renderer->GetDevice();

    // �v���W�F�N�V�����}�g���b�N�X�̏�����
    D3DXMatrixIdentity(&m_mtxProjection);

    // �v���W�F�N�V�����}�g���b�N�X���쐬
    D3DXMatrixPerspectiveFovLH(&m_mtxProjection, D3DXToRadian(30.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 10.0f, 12000.0f);

    // �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
    pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

    // �r���[�}�g���b�N�X�̏�����
    D3DXMatrixIdentity(&m_mtxView);

    D3DXVECTOR3 adjust = D3DXVECTOR3(0, 0, 0);
    D3DXVECTOR3 PosV = D3DXVECTOR3(0, 0, 0);
    D3DXVECTOR3 PosR = D3DXVECTOR3(0, 0, 0);

    if (m_nShakeframe > 0)
    {
        m_nShakeframe--;
        adjust = D3DXVECTOR3(rand() & (int)m_fShake, rand() & (int)m_fShake, rand() & (int)m_fShake);
    }

    PosV = m_posV + adjust;
    PosR = m_posR + adjust;

    // �r���[�}�g���b�N�X�̍쐬
    D3DXMatrixLookAtLH(&m_mtxView, &PosV, &PosR, &m_vecU);

    // �r���[�}�g���b�N�X�̐ݒ�
    pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);

    //�t�H�O�֌W�̏���
    //pDevice->SetRenderState(D3DRS_FOGENABLE,TRUE);
    
    //pDevice->SetRenderState(D3DRS_FOGCOLOR, 0x00FFFFFF);
    
    //pDevice->SetRenderState(D3DRS_FOGTABLEMODE, D3DFOG_EXP);
    
    //pDevice->SetRenderState(D3DRS_FOGDENSITY,*(DWORD*)(&m_fBlizCnt));
    
    //pDevice->SetRenderState(D3DRS_SHADEMODE, 2);
    
    //pDevice->SetRenderState(D3DRS_DEPTHBIAS, 1);
    
    //pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
    
    //�t�H�O�֌W�̏���(�����v�Z���@���͎g��Ȃ�)
    //pDevice->SetRenderState(D3DRS_FOGSTART,*(DWORD*)(&m_fStartPos));
    //pDevice->SetRenderState(D3DRS_FOGEND,*(DWORD*)(&m_fEndPos));
}