//=================================================
//
// 3D���f���̃u���b�N�̕\������ (3dslashwindBoss.cpp)
// Author: Sohta Kuki
//
//=================================================

#include "3dslashwind_boss.h"
#include "3dplayer.h"
#include "3denemy.h"
#include "3dtornado.h"
#include "3dboss.h"
#include "3dhiteffect.h"

LPDIRECT3DTEXTURE9 C3dslashwindBoss::m_pTexBuff = nullptr;
int C3dslashwindBoss::m_nMaxBlock = 0;
bool C3dslashwindBoss::m_bComboDest = false;

//======================
// �R���X�g���N�^
//======================
C3dslashwindBoss::C3dslashwindBoss(int nPriority) : CModel(nPriority)
{
    m_nTurnCnt = 0;
    m_bTurn = false;
}

//======================
// �f�X�g���N�^
//======================
C3dslashwindBoss::~C3dslashwindBoss()
{

}

//======================
// ����������
//======================
HRESULT C3dslashwindBoss::Init()
{
    //������
    if (FAILED(CModel::Init()))
    {
        return E_FAIL;
    }

    m_nTimer = 0;
    m_bDisplay = true;

    return S_OK;
}

void C3dslashwindBoss::Uninit()
{
    // ���łɉ������Ă���ꍇ�͏������X�L�b�v
    if (m_pTexBuff != nullptr)
    {
        m_pTexBuff->Release();
        m_pTexBuff = nullptr;
    }

    // ���b�V����}�e���A���̉��
    for (int i = 0; i < SLASHWINDBOSS_MODEL; i++)
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

    // ���N���X�̏I���������Ăяo��
    CModel::Uninit();
}

//======================
// �X�V����
//======================
void C3dslashwindBoss::Update()
{
    D3DXVECTOR3 Pos = CObject3D::GetPos();
    D3DXVECTOR3 PlayerRot = C3dplayer::GetPlayerRot();


    SetPos(Pos);

    //���R���ł̏���
    if (m_bDisplay == true)
    {
        m_nTimer++;

        m_rot.y += 0.3f;

        if (m_nTimer == SLASHWINDBOSS_TIMER)
        {
            m_bDisplay = false;
            Uninit();
        }

    }

    //�R���{�U���̑O��o���������̍폜
    if (m_bComboDest == true)
    {
        m_bDisplay = false;

        m_bComboDest = false;
    }

    //�e�ƓG�̓����蔻��
    for (int nCntObj = 0; nCntObj < C3dslashwindBoss::MAX_SLASHWINDBOSS; nCntObj++)
    {
        CObject* pObj = CObject::GetObj(3, nCntObj);

        if (pObj != nullptr)
        {
            CObject::TYPE type = pObj->GetType();

            C3dplayer* p3dplayer = (C3dplayer*)pObj;

            D3DXVECTOR3 PlayerPos = p3dplayer->GetPos();

            //�G�̏ꍇ
            if (type == CObject::TYPE::PLAYER)
            {
                if (Pos.x >= PlayerPos.x - 75
                    && Pos.x <= PlayerPos.x + 75
                    && Pos.y >= PlayerPos.y - 100
                    && Pos.y <= PlayerPos.y + 100
                    && Pos.z >= PlayerPos.z - 10
                    && Pos.z <= PlayerPos.z + 10)
                {
                    m_bDisplay = false;
                    p3dplayer->PlayerDamage(10);
                    C3dhiteffect::Create(CObject3D::GetPos(), D3DXVECTOR3(70.0f, 70.0f, 0.0f), m_rot);
                    CCamera::SetShake((2), 7.0f);
                    m_nTimer = 0;
                    C3dslashwindBoss::Uninit();
                    return;
                }
            }
        }
    }


    //�t�F�[�h�̏�Ԃ��擾
    int nFadeState = CFade::GetFadeState();

    if (nFadeState == CFade::FADE_OUT)
    {
        m_bComboDest = true;
        m_nTimer = 0;

    }
}

//======================
// �`�揈��
//======================
void C3dslashwindBoss::Draw()
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

    for (int nCntParts = 0; nCntParts < SLASHWINDBOSS_MODEL; nCntParts++)
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

//�R���{�U�����̕��폜����
void C3dslashwindBoss::Reset()
{
    m_bComboDest = true;
}


//======================
// �I�u�W�F�N�g��������
//======================
C3dslashwindBoss* C3dslashwindBoss::Create(D3DXVECTOR3 pos)
{
    C3dslashwindBoss* D3DSlashWind = nullptr;

    D3DSlashWind = new C3dslashwindBoss;

    //�������ɐ��������ꍇ
    if (SUCCEEDED(D3DSlashWind->Init()))
    {
        D3DSlashWind->SetType(TYPE::SLASHWINDBOSS);

        D3DSlashWind->LoadBlockData();

        //D3DBlock->Load();//�e�N�X�`����ݒ�(��)

        D3DSlashWind->CObject3D::SetPos(pos);

        ////�e�N�X�`���̐ݒ�
        //Model->BindTexture(m_pTexBuff);
    }

    return D3DSlashWind;
}

//======================
// �e�N�X�`�����[�h����
//======================
HRESULT C3dslashwindBoss::Load()
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
void C3dslashwindBoss::Unload()
{
    CModel::Unload();
}



//===========================
// �O���t�@�C���ǂݍ��ݏ���
//===========================
void C3dslashwindBoss::LoadBlockData(void)
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
            fscanf(m_pFile, "%s", &CModel::m_aLoadEnemy[EnemyModelSave].filename[0]);
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
                    fscanf(m_pFile, "%d", &CModel::m_aLoadEnemy[nCntEnemyData].index);
                }

                //�e�ݒ�
                else if (!strcmp(Datacheck, "PARENT"))
                {
                    fscanf(m_pFile, "%s", Datacheck);
                    fscanf(m_pFile, "%d", &CModel::m_aLoadEnemy[nCntEnemyData].parent);
                }

                //�����ʒu
                else if (!strcmp(Datacheck, "POS"))
                {
                    fscanf(m_pFile, "%s", Datacheck);
                    fscanf(m_pFile, "%f", &CModel::m_aLoadEnemy[nCntEnemyData].pos.x);
                    fscanf(m_pFile, "%f", &CModel::m_aLoadEnemy[nCntEnemyData].pos.y);
                    fscanf(m_pFile, "%f", &CModel::m_aLoadEnemy[nCntEnemyData].pos.z);
                }

                //����
                else if (!strcmp(Datacheck, "ROT"))
                {
                    fscanf(m_pFile, "%s", Datacheck);
                    fscanf(m_pFile, "%f", &CModel::m_aLoadEnemy[nCntEnemyData].rot.x);
                    fscanf(m_pFile, "%f", &CModel::m_aLoadEnemy[nCntEnemyData].rot.y);
                    fscanf(m_pFile, "%f", &CModel::m_aLoadEnemy[nCntEnemyData].rot.z);
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
        D3DXLoadMeshFromX(&CModel::m_aLoadEnemy[nCnt].filename[0], D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[nCnt], NULL, &m_nNumMat[nCnt], &m_pMesh[nCnt]);
        //D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\golden000.jpg", &g_pTextureEnemy);
        m_aModel[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
        m_aModel[nCnt].nLife = 4;
        m_aModel[nCnt].nIdxModelParent = CModel::m_aLoadEnemy[nCnt].parent;
        m_aModel[nCnt].bUse = true;

        //�G�̗����ʒu������
        //m_nPos = D3DXVECTOR3(-0.0f, -0.0f, 0.0f);
        //m_aEnemy.rot = D3DXVECTOR3(-0.0f, 0.0f, 0.0f);

        m_aModel[nCnt].pos = D3DXVECTOR3(CModel::m_aLoadEnemy[nCnt].pos.x, CModel::m_aLoadEnemy[nCnt].pos.y, CModel::m_aLoadEnemy[nCnt].pos.z);
        m_aModel[nCnt].rot = D3DXVECTOR3(CModel::m_aLoadEnemy[nCnt].rot.x, CModel::m_aLoadEnemy[nCnt].rot.y, CModel::m_aLoadEnemy[nCnt].rot.z);
    }
}


//===========================
// �u���b�N�̓����蔻��
//===========================
bool C3dslashwindBoss::Collision3DBlock(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3* pMove, float fWidth, float fHeight)
{
    bool bLanding = false; // �d�͂��K�p���ꂽ�ꍇ�̂ݎg�p
    float fMoveslashwindWidth = 25.0f;
    float fMoveslashwindDepth = 70.0f;
    float fMoveslashwindHeight = -15.0f;

    D3DXVECTOR3 Pos = CObject3D::GetPos();

    // �E�������蔻��
    if (pPos->x - fWidth <= Pos.x + fMoveslashwindWidth && pPosOld->x - fWidth >= Pos.x + fMoveslashwindWidth && pPos->z - fHeight < Pos.z + fMoveslashwindDepth && pPos->z > Pos.z - fMoveslashwindDepth && pPos->y < Pos.y + fMoveslashwindHeight && pPos->y > Pos.y - fMoveslashwindHeight)
    {
        pPos->x = Pos.x + fMoveslashwindWidth + fWidth;
    }
    // ���������蔻��
    else if (pPos->x + fWidth >= Pos.x - fMoveslashwindWidth && pPosOld->x + fWidth <= Pos.x - fMoveslashwindWidth && pPos->z - fHeight < Pos.z + fMoveslashwindDepth && pPos->z > Pos.z - fMoveslashwindDepth && pPos->y < Pos.y + fMoveslashwindHeight && pPos->y > Pos.y - fMoveslashwindHeight)
    {
        pPos->x = Pos.x - fMoveslashwindWidth - fWidth;
    }
    // �O�������蔻��
    if (pPos->x - fWidth < Pos.x + fMoveslashwindWidth && pPos->x + fWidth > Pos.x - fMoveslashwindWidth && pPos->z - fHeight <= Pos.z + fMoveslashwindDepth && pPosOld->z - fHeight >= Pos.z + fMoveslashwindDepth && pPos->y < Pos.y + fMoveslashwindHeight && pPos->y > Pos.y - fMoveslashwindHeight)
    {
        pPos->z = Pos.z + fMoveslashwindDepth + fHeight;
    }
    // �㑤�����蔻��
    else if (pPos->x - fWidth < Pos.x + fMoveslashwindWidth && pPos->x + fWidth > Pos.x - fMoveslashwindWidth && pPos->z >= Pos.z - fMoveslashwindDepth && pPosOld->z <= Pos.z - fMoveslashwindDepth && pPos->y < Pos.y + fMoveslashwindHeight && pPos->y > Pos.y - fMoveslashwindHeight)
    {
        pPos->z = Pos.z - fMoveslashwindDepth - fHeight;
    }
    // �㑤�����蔻��
    if (pPos->x - fWidth < Pos.x + fMoveslashwindWidth && pPos->x + fWidth > Pos.x - fMoveslashwindWidth && pPos->y - fHeight <= Pos.y + fMoveslashwindHeight && pPosOld->y - fHeight >= Pos.y + fMoveslashwindHeight && pPos->z < Pos.z + fMoveslashwindDepth && pPos->z > Pos.z - fMoveslashwindDepth)
    {
        pPos->y = Pos.y + fMoveslashwindHeight + fHeight;
        bLanding = true;
    }
    // ���������蔻��
    else if (pPos->x - fWidth < Pos.x + fMoveslashwindWidth && pPos->x + fWidth > Pos.x - fMoveslashwindWidth && pPos->y >= Pos.y - fMoveslashwindHeight && pPosOld->y <= Pos.y - fMoveslashwindHeight && pPos->z < Pos.z + fMoveslashwindDepth && pPos->z > Pos.z - fMoveslashwindDepth)
    {
        pPos->y = Pos.y - fMoveslashwindHeight - fHeight;
    }

    return bLanding;
}
