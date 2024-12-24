//=================================================
//
// 3D���f���̃u���b�N�̕\������ (3dbosstornado.cpp)
// Author: Sohta Kuki
//
//=================================================

#include "3dbosstornado.h"
#include "3dplayer.h"
#include "3denemy.h"
#include "3dboss.h"
#include "camera.h"

LPDIRECT3DTEXTURE9 C3dbosstornado::m_pTexBuff = nullptr;
int C3dbosstornado::m_nMaxBlock = 0;
int C3dbosstornado::m_nNumBosstornado = 0;

//======================
// �R���X�g���N�^
//======================
C3dbosstornado::C3dbosstornado(int nPriority) : CObject3D(nPriority)
{
    m_nTurnCnt = 0;
    m_bTurn = false;
    m_bMoveSwitchL = false;
    m_nSpawnAtkTimer = 0;
}

//======================
// �f�X�g���N�^
//======================
C3dbosstornado::~C3dbosstornado()
{

}

//======================
// ����������
//======================
HRESULT C3dbosstornado::Init()
{
    //������
    if (FAILED(CObject3D::Init()))
    {
        return E_FAIL;
    }

    //�u���b�N�����J�E���g
    m_nMaxBlock++;
    m_nTimer = 0;
    
    m_bMoveSwitch = false;
    m_nNumBosstornado++;

    if (m_nNumBosstornado >= 2 && (C3dbosstornado::m_nATKType == C3dbosstornado::BOSSTORNADO_STATE::BOSSTORNADO_SET || C3dbosstornado::m_nATKType == C3dbosstornado::BOSSTORNADO_STATE::BOSSTORNADO_ATK))
    {
        m_nNumBosstornado = 2;
    }

    return S_OK;
}

void C3dbosstornado::Uninit()
{
    // ���łɉ������Ă���ꍇ�͏������X�L�b�v
    if (m_pTexBuff != nullptr)
    {
        m_pTexBuff->Release();
        m_pTexBuff = nullptr;
    }

    // ���b�V����}�e���A���̉��
    for (int i = 0; i < BOSSTORNADO_MODEL; i++)
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

    // �u���b�N�������炷
    m_nMaxBlock--;

    m_nNumBosstornado--;

    // ���N���X�̏I���������Ăяo��
    CObject3D::Uninit();
}

//======================
// �X�V����
//======================
void C3dbosstornado::Update()
{
    //�Q�[�����i�s�\�̎��̂ݒʂ�
    if (CScene::GetUpdateStat() == true)
    {
        D3DXVECTOR3 Pos = CObject3D::GetPos();

        for (int nCntPriority = 0; nCntPriority < MAX_PRIORITY; nCntPriority++)
        {
            //�X���b�V���E�B���h�̓����蔻��
            for (int nCntObj = 0; nCntObj < C3dbosstornado::MAX_BOSSTORNADO; nCntObj++)
            {
                CObject* pObj = CObject::GetObj(nCntPriority, nCntObj);

                if (pObj != nullptr)
                {
                    CObject::TYPE type = pObj->GetType();

                    //�X���b�V���E�B���h�������ꍇ
                    if (type == CObject::TYPE::BOSS_TORNADO)
                    {

                        //X���W�̈ړ��ʂ��X�V
                        m_nMove.x += (0.0f - m_nMove.x) * 0.1f;

                        //Y���W�̈ړ��ʂ��X�V
                        m_nMove.y += (0.0f - m_nMove.y) * 0.1f;

                        //Z���W�̈ړ��ʂ��X�V
                        m_nMove.z += (0.0f - m_nMove.z) * 0.1f;

                    }

                }
            }
        }

        //���R���ł̏���
        if (m_bDisplay == true)
        {
            m_nTimer++;

            m_rot.y += 0.3f;

            if (m_nTimer == BOSSTORNADO_TIMER)
            {
                m_bDisplay = false;
                Uninit();
                return;
            }

            //if (m_nMaxBlock > 3)
            //{
            //    m_bDisplay = false;
            //    Uninit();
            //}
        }


        if (m_nDirection == 2 || m_nDirection == 3)
        {
            C3dbosstornado::m_nATKType = BOSSTORNADO_STATE::BOSSTORNADO_BOSS_ATK;
        }


        if (m_nDirection == 1)
        {
            m_nSpawnAtkTimer++;

            if (m_nSpawnAtkTimer == 125)
            {
                m_bMoveSwitchL = true;
                C3dbosstornado::m_nATKType = BOSSTORNADO_STATE::BOSSTORNADO_BOSS_ATK;
                m_bMoveSwitchBossL = true;
            }
        }

        if (m_nDirection == 2)
        {
            m_nSpawnAtkTimer++;

            if (m_nSpawnAtkTimer == 55)
            {
                m_bMoveSwitch = true;
                C3dbosstornado::m_nATKType = BOSSTORNADO_STATE::BOSSTORNADO_BOSS_ATK;
            }
        }

        //�v���C���[���E�������Ă��鎞
        if (m_bMoveSwitch == true)
        {
            m_nMove.x += 1.0f;
        }

        //�v���C���[�����������Ă��鎞
        if (m_bMoveSwitchL == true)
        {
            m_nMove.x -= 1.0f;
        }

        //�{�X�L�����̏ꍇ
        if (m_bMoveBossSwitchLD == true)
        {
            m_nMove.x -= 1.0f;
            m_nMove.y -= 0.8f;
        }


        //�{�X�L�����̏ꍇ
        if (m_bMoveBossSwitchRD == true)
        {
            m_nMove.x += 1.0f;
            m_nMove.y -= 0.8f;
        }

        //�e�ƓG�̓����蔻��
        for (int nCntObj = 0; nCntObj < 90; nCntObj++)
        {
            CObject* pObj = CObject::GetObj(3, nCntObj);

            if (pObj != nullptr)
            {
                CObject::TYPE type = pObj->GetType();

                C3dboss* p3dboss = (C3dboss*)pObj;

                D3DXVECTOR3 BossPos = p3dboss->GetPos();

                //�G�̏ꍇ
                if (type == CObject::TYPE::BOSS && C3dbosstornado::m_nATKType == BOSSTORNADO_STATE::BOSSTORNADO_ATK)
                {
                    if (Pos.x >= BossPos.x - 75
                        && Pos.x <= BossPos.x + 75
                        && Pos.y >= BossPos.y - 25
                        && Pos.y <= BossPos.y + 75
                        && Pos.z >= BossPos.z - 10
                        && Pos.z <= BossPos.z + 10)
                    {
                        p3dboss->BossDamage(8);
                        Uninit();
                        return;
                    }
                }
            }
        }

        //�����ƓG�̓����蔻��
        for (int nCntObj = 0; nCntObj < 2; nCntObj++)
        {
            CObject* pObj = CObject::GetObj(3, nCntObj);

            if (pObj != nullptr)
            {
                CObject::TYPE type = pObj->GetType();

                C3dplayer* p3dplayer = (C3dplayer*)pObj;

                D3DXVECTOR3 PlayerPos = p3dplayer->GetPos();

                //�G�̏ꍇ
                if (type == CObject::TYPE::PLAYER/* && C3dbosstornado::m_nATKType == BOSSTORNADO_STATE::BOSSTORNADO_BOSS_ATK*/)
                {
                    if (Pos.x >= PlayerPos.x - 75
                        && Pos.x <= PlayerPos.x + 75
                        && Pos.y >= PlayerPos.y - 100
                        && Pos.y <= PlayerPos.y + 100
                        && Pos.z >= PlayerPos.z - 10
                        && Pos.z <= PlayerPos.z + 10)
                    {
                        CCamera::SetShake((2), 7.0f);
                        p3dplayer->PlayerDamage(10);
                        Uninit();
                        return;
                    }
                }
            }
        }

        Pos.x += m_nMove.x;
        Pos.y += m_nMove.y;

        SetPos(Pos);

        //X���W�̈ړ��ʂ��X�V
        m_nMove.x += (0.0f - m_nMove.x) * 0.10f;

        //X���W�̈ړ��ʂ��X�V
        m_nMove.y += (0.0f - m_nMove.y) * 0.10f;

        int nFadeState = CFade::GetFadeState();

        if (nFadeState == CFade::FADE_OUT)
        {
            m_bDisplay = true;
            m_nTimer = 0;
            C3dbosstornado::Uninit();
        }
    }
}

//======================
// �`�揈��
//======================
void C3dbosstornado::Draw()
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

    //���[���h�}�g���b�N�X�̐ݒ�
    pDevice->SetTransform(D3DTS_WORLD, &m_mtxworld);

    //�}�e���A�����擾
    pDevice->GetMaterial(&matDef);

    for (int nCntParts = 0; nCntParts < BOSSTORNADO_MODEL; nCntParts++)
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

        if (m_aModel[nCntParts].bUse == true)
        {
            //�}�g���b�N�X�̐ݒ�
            pDevice->SetTransform(D3DTS_WORLD, &m_aModel[nCntParts].mtxworld);

            pMat = (D3DXMATERIAL*)m_pBuffMat[nCntParts]->GetBufferPointer();

            for (int nCntMat = 0; nCntMat < (int)m_nNumMat[nCntParts]; nCntMat++)
            {
                //�}�e���A���̐ݒ�
                pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

                //�e�N�X�`���̐ݒ�
                pDevice->SetTexture(0, m_pTexBuff);

                //���f��(�p�[�c)�̕`��
                m_pMesh[nCntParts]->DrawSubset(nCntMat);
            }
        }

    }

    pDevice->SetMaterial(&matDef);
}

//======================
// �����U������
//======================
void C3dbosstornado::BosstornadoAtk(int nDirection)
{
    if (nDirection == 0)
    {
        m_bMoveSwitch = true;
        C3dbosstornado::m_nATKType = BOSSTORNADO_STATE::BOSSTORNADO_ATK;
    }

    if (nDirection == 1)
    {
        m_bMoveSwitchL = true;
        C3dbosstornado::m_nATKType = BOSSTORNADO_STATE::BOSSTORNADO_ATK;
    }

    if (nDirection == 2)
    {
        m_bMoveBossSwitchLD = true;
    }

    if (nDirection == 3)
    {
        m_bMoveBossSwitchRD = true;
    }
}


//======================
// �I�u�W�F�N�g��������
//======================
C3dbosstornado* C3dbosstornado::Create(D3DXVECTOR3 pos, int nDirection)
{
    C3dbosstornado* D3DBossTornado = nullptr;

    D3DBossTornado = new C3dbosstornado;

    //�������ɐ��������ꍇ
    if (SUCCEEDED(D3DBossTornado->Init()))
    {
        D3DBossTornado->SetType(TYPE::BOSS_TORNADO);

        D3DBossTornado->LoadBlockData();

        D3DBossTornado->m_bDisplay = true;

        D3DBossTornado->m_nDirection = nDirection;

        //D3DBlock->Load();//�e�N�X�`����ݒ�(��)

        D3DBossTornado->CObject3D::SetPos(pos);

        D3DBossTornado->m_nPos = pos;

        D3DBossTornado->C3dbosstornado::m_nATKType = C3dbosstornado::BOSSTORNADO_STATE::BOSSTORNADO_SET;

        ////�e�N�X�`���̐ݒ�
        //Model->BindTexture(m_pTexBuff);
    }

    return D3DBossTornado;
}

//======================
// �e�N�X�`�����[�h����
//======================
HRESULT C3dbosstornado::Load()
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
void C3dbosstornado::Unload()
{
    CModel::Unload();
}



//===========================
// �O���t�@�C���ǂݍ��ݏ���
//===========================
void C3dbosstornado::LoadBlockData(void)
{
    char Datacheck[MAX_CHAR];
    int nCntEnemyData = 0;
    int EnemyModelSave = 0;

    m_pFile = fopen("data\\MODEL\\MODEL_TORNADO\\bosstornado_profile.txt", "r");//�t�@�C�����J��

    //�t�@�C�������݂��Ȃ��ꍇ
    if (m_pFile == NULL)
    {
        return;
    }

    //�O���t�@�C��������ǂݎ��
    while (1)
    {
        fscanf(m_pFile, "%s", Datacheck);

        if (!strcmp(Datacheck, "END_CHARACTERSET"))
        {
            fclose(m_pFile);
            break;
        }

        if (Datacheck[0] == '#')
        {
            continue;
        }

        //�p�[�c��
        if (!strcmp(Datacheck, "NUM_PARTS"))
        {
            fscanf(m_pFile, "%s", Datacheck);
            fscanf(m_pFile, "%d", &EnemyModelSave);
        }

        //�t�@�C����
        if (!strcmp(Datacheck, "MODEL_FILENAME"))
        {
            fscanf(m_pFile, "%s", Datacheck);
            fscanf(m_pFile, "%s", &m_aLoadEnemy[EnemyModelSave].filename[0]);
            EnemyModelSave++;
        }

        //�p�[�c�̏ڍ�
        if (!strcmp(Datacheck, "PARTSSET"))
        {
            while (1)
            {
                fscanf(m_pFile, "%s", Datacheck);

                //�p�[�c�ڍ׏I��茟�m
                if (!strcmp(Datacheck, "END_PARTSSET"))
                {
                    break;
                }

                //�C���f�b�N�X
                else if (!strcmp(Datacheck, "INDEX"))
                {
                    fscanf(m_pFile, "%s", Datacheck);
                    fscanf(m_pFile, "%d", &m_aLoadEnemy[nCntEnemyData].index);
                }

                //�e�ݒ�
                else if (!strcmp(Datacheck, "PARENT"))
                {
                    fscanf(m_pFile, "%s", Datacheck);
                    fscanf(m_pFile, "%d", &m_aLoadEnemy[nCntEnemyData].parent);
                }

                //�����ʒu
                else if (!strcmp(Datacheck, "POS"))
                {
                    fscanf(m_pFile, "%s", Datacheck);
                    fscanf(m_pFile, "%f", &m_aLoadEnemy[nCntEnemyData].pos.x);
                    fscanf(m_pFile, "%f", &m_aLoadEnemy[nCntEnemyData].pos.y);
                    fscanf(m_pFile, "%f", &m_aLoadEnemy[nCntEnemyData].pos.z);
                }

                //����
                else if (!strcmp(Datacheck, "ROT"))
                {
                    fscanf(m_pFile, "%s", Datacheck);
                    fscanf(m_pFile, "%f", &m_aLoadEnemy[nCntEnemyData].rot.x);
                    fscanf(m_pFile, "%f", &m_aLoadEnemy[nCntEnemyData].rot.y);
                    fscanf(m_pFile, "%f", &m_aLoadEnemy[nCntEnemyData].rot.z);
                }
            }
            nCntEnemyData++;
        }
    }

    //�f�o�C�X�̎擾
    LPDIRECT3DDEVICE9 pDevice = nullptr;
    pDevice = CManager::GetRenderer()->GetDevice();

    //�����ŏ�L�̏����œ������l����
    for (int nCnt = 0; nCnt < EnemyModelSave; nCnt++)
    {
        D3DXLoadMeshFromX(&m_aLoadEnemy[nCnt].filename[0], D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[nCnt], NULL, &m_nNumMat[nCnt], &m_pMesh[nCnt]);
        //D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\golden000.jpg", &g_pTextureEnemy);
        m_aModel[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
        m_aModel[nCnt].nLife = 4;
        m_aModel[nCnt].nIdxModelParent = m_aLoadEnemy[nCnt].parent;
        m_aModel[nCnt].bUse = true;

        //�G�̗����ʒu������
        //m_nPos = D3DXVECTOR3(-0.0f, -0.0f, 0.0f);
        //m_aEnemy.rot = D3DXVECTOR3(-0.0f, 0.0f, 0.0f);

        m_aModel[nCnt].pos = D3DXVECTOR3(m_aLoadEnemy[nCnt].pos.x, m_aLoadEnemy[nCnt].pos.y, m_aLoadEnemy[nCnt].pos.z);
        m_aModel[nCnt].rot = D3DXVECTOR3(m_aLoadEnemy[nCnt].rot.x, m_aLoadEnemy[nCnt].rot.y, m_aLoadEnemy[nCnt].rot.z);
    }
}


//===========================
// �u���b�N�̓����蔻��
//===========================
bool C3dbosstornado::Collision3DBosstornado(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3* pMove, float fWidth, float fHeight)
{
    bool bLanding = false; // �d�͂��K�p���ꂽ�ꍇ�̂ݎg�p
    float fMovebosstornadoWidth = 7.0f;
    float fMovebosstornadoDepth = 40.0f;
    float fMovebosstornadoHeight = 0.0f;

    D3DXVECTOR3 Pos = CObject3D::GetPos();

    // �E�������蔻��
    if (pPos->x - fWidth <= Pos.x + fMovebosstornadoWidth && pPosOld->x - fWidth >= Pos.x + fMovebosstornadoWidth && pPos->z - fHeight < Pos.z + fMovebosstornadoDepth && pPos->z > Pos.z - fMovebosstornadoDepth && pPos->y < Pos.y + fMovebosstornadoHeight && pPos->y > Pos.y - fMovebosstornadoHeight)
    {
        bLanding = true;
    }
    // ���������蔻��
    else if (pPos->x + fWidth >= Pos.x - fMovebosstornadoWidth && pPosOld->x + fWidth <= Pos.x - fMovebosstornadoWidth && pPos->z - fHeight < Pos.z + fMovebosstornadoDepth && pPos->z > Pos.z - fMovebosstornadoDepth && pPos->y < Pos.y + fMovebosstornadoHeight && pPos->y > Pos.y - fMovebosstornadoHeight)
    {
        bLanding = true;
    }
    // �O�������蔻��
    if (pPos->x - fWidth < Pos.x + fMovebosstornadoWidth && pPos->x + fWidth > Pos.x - fMovebosstornadoWidth && pPos->z - fHeight <= Pos.z + fMovebosstornadoDepth && pPosOld->z - fHeight >= Pos.z + fMovebosstornadoDepth && pPos->y < Pos.y + fMovebosstornadoHeight && pPos->y > Pos.y - fMovebosstornadoHeight)
    {
        bLanding = true;
    }
    // �㑤�����蔻��
    else if (pPos->x - fWidth < Pos.x + fMovebosstornadoWidth && pPos->x + fWidth > Pos.x - fMovebosstornadoWidth && pPos->z >= Pos.z - fMovebosstornadoDepth && pPosOld->z <= Pos.z - fMovebosstornadoDepth && pPos->y < Pos.y + fMovebosstornadoHeight && pPos->y > Pos.y - fMovebosstornadoHeight)
    {
        bLanding = true;
    }
    // �㑤�����蔻��
    if (pPos->x - fWidth < Pos.x + fMovebosstornadoWidth && pPos->x + fWidth > Pos.x - fMovebosstornadoWidth && pPos->y - fHeight <= Pos.y + fMovebosstornadoHeight && pPosOld->y - fHeight >= Pos.y + fMovebosstornadoHeight && pPos->z < Pos.z + fMovebosstornadoDepth && pPos->z > Pos.z - fMovebosstornadoDepth)
    {
        bLanding = true;
    }
    // ���������蔻��
    else if (pPos->x - fWidth < Pos.x + fMovebosstornadoWidth && pPos->x + fWidth > Pos.x - fMovebosstornadoWidth && pPos->y >= Pos.y - fMovebosstornadoHeight && pPosOld->y <= Pos.y - fMovebosstornadoHeight && pPos->z < Pos.z + fMovebosstornadoDepth && pPos->z > Pos.z - fMovebosstornadoDepth)
    {
        bLanding = true;
    }

    return bLanding;
}
