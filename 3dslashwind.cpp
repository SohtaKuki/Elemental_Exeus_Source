//=================================================
//
// 3D���f���̃u���b�N�̕\������ (3dslashwind.cpp)
// Author: Sohta Kuki
//
//=================================================

#include "3dslashwind.h"
#include "3dplayer.h"
#include "3denemy.h"
#include "3dtornado.h"
#include "3dboss.h"
#include "3denemy_air.h"
#include "3dhiteffect.h"

LPDIRECT3DTEXTURE9 C3dslashwind::m_pTexBuff = nullptr;
int C3dslashwind::m_nMaxBlock = 0;
bool C3dslashwind::m_bComboDest = false;

//======================
// �R���X�g���N�^
//======================
C3dslashwind::C3dslashwind(int nPriority) : CModel(nPriority)
{
    m_nTurnCnt = 0;
    m_bTurn = false;
}

//======================
// �f�X�g���N�^
//======================
C3dslashwind::~C3dslashwind()
{

}

//======================
// ����������
//======================
HRESULT C3dslashwind::Init()
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

void C3dslashwind::Uninit()
{
    // ���łɉ������Ă���ꍇ�͏������X�L�b�v
    if (m_pTexBuff != nullptr) 
    {
        m_pTexBuff->Release();
        m_pTexBuff = nullptr;
    }

    // ���b�V����}�e���A���̉��
    for (int i = 0; i < SLASHWIND_MODEL; i++)
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
void C3dslashwind::Update()
{
    D3DXVECTOR3 Pos = CObject3D::GetPos();
    D3DXVECTOR3 PlayerRot = C3dplayer::GetPlayerRot();

    for (int nCntPriority = 0; nCntPriority < MAX_PRIORITY; nCntPriority++)
    {
        //�u���b�N�̓����蔻��
        for (int nCntObj = 0; nCntObj < C3dslashwind::MAX_SLASHWIND; nCntObj++)
        {
            CObject* pObj = CObject::GetObj(nCntPriority, nCntObj);

            if (pObj != nullptr)
            {
                CObject::TYPE type = pObj->GetType();

                //�u���b�N�������ꍇ
                if (type == CObject::TYPE::SLASHTORNADO)
                {
                    //X���W�̈ړ��ʂ��X�V
                    m_nMove.x += (0.0f - m_nMove.x) * 0.1f;

                    //Z���W�̈ړ��ʂ��X�V
                    m_nMove.z += (0.0f - m_nMove.z) * 0.1f;

                }

            }

        }
    }

    SetPos(Pos);

    //���R���ł̏���
    if (m_bDisplay == true)
    {
        m_nTimer++;

        m_rot.y += 0.3f;

        if (m_nTimer == SLASHWIND_TIMER)
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
    for (int nCntObj = 0; nCntObj < C3dslashwind::MAX_SLASHWIND; nCntObj++)
    {
        CObject* pObj = CObject::GetObj(3, nCntObj);

        if (pObj != nullptr)
        {
            CObject::TYPE type = pObj->GetType();

            C3denemy* p3denemy = (C3denemy*)pObj;

            D3DXVECTOR3 EnemyPos = p3denemy->GetPos();

            //�G�̏ꍇ
            if (type == CObject::TYPE::ENEMY_NORMALMOVE || type == CObject::TYPE::ENEMY_NORMAL)
            {
                if (Pos.x >= EnemyPos.x - 50
                     && Pos.x <= EnemyPos.x + 50
                    && Pos.y >= EnemyPos.y - 30
                    && Pos.y <= EnemyPos.y + 30
                    && Pos.z >= EnemyPos.z - 10
                    && Pos.z <= EnemyPos.z + 10)
                {
                    m_bDisplay = false;
                    p3denemy->EnemyDamage();
                    C3dhiteffect::Create(D3DXVECTOR3(CObject3D::GetPos().x, CObject3D::GetPos().y + 35.0f, CObject3D::GetPos().z), D3DXVECTOR3(90.0f, 90.0f, 0.0f), m_rot);
                    Uninit();
                    return;
                }
            }
        }
    }

    //�e�ƓG�̓����蔻��
    for (int nCntObj = 0; nCntObj < C3dslashwind::MAX_SLASHWIND; nCntObj++)
    {
        CObject* pObj = CObject::GetObj(3, nCntObj);

        if (pObj != nullptr)
        {
            CObject::TYPE type = pObj->GetType();

            C3denemyair* p3denemyair = (C3denemyair*)pObj;

            D3DXVECTOR3 EnemyPos = p3denemyair->GetPos();

            //�G�̏ꍇ
            if (type == CObject::TYPE::ENEMY_FLYMOVE)
            {
                if (Pos.x >= EnemyPos.x - 50
                    && Pos.x <= EnemyPos.x + 50
                    && Pos.y >= EnemyPos.y - 30
                    && Pos.y <= EnemyPos.y + 30
                    && Pos.z >= EnemyPos.z - 10
                    && Pos.z <= EnemyPos.z + 10)
                {
                    m_bDisplay = false;
                    p3denemyair->EnemyDamage();
                    C3dhiteffect::Create(D3DXVECTOR3(CObject3D::GetPos().x, CObject3D::GetPos().y + 35.0f, CObject3D::GetPos().z), D3DXVECTOR3(90.0f, 90.0f, 0.0f), m_rot);
                    Uninit();
                    return;
                }
            }
        }
    }

    //�e�ƓG�̓����蔻��
    for (int nCntObj = 0; nCntObj < C3dslashwind::MAX_SLASHWIND; nCntObj++)
    {
        CObject* pObj = CObject::GetObj(20, nCntObj);

        if (pObj != nullptr)
        {
            CObject::TYPE type = pObj->GetType();

            C3dboss* p3dboss = (C3dboss*)pObj;

            D3DXVECTOR3 BossPos = p3dboss->GetPos();

            //�{�X�G�̏ꍇ
            if (type == CObject::TYPE::BOSS)
            {
                if (Pos.x >= BossPos.x - 75
                    && Pos.x <= BossPos.x + 75
                    && Pos.y >= BossPos.y - 25
                    && Pos.y <= BossPos.y + 75
                    && Pos.z >= BossPos.z - 10
                    && Pos.z <= BossPos.z + 10)
                {
                    m_bDisplay = false;
                    p3dboss->BossDamage(10);
                    C3dhiteffect::Create(D3DXVECTOR3(CObject3D::GetPos().x, CObject3D::GetPos().y + 35.0f, CObject3D::GetPos().z), D3DXVECTOR3(90.0f, 90.0f, 0.0f), m_rot);
                    Uninit();
                    return;
                }
            }
        }
    }

    //�e�ƓG�̓����蔻��
    for (int nCntObj = 0; nCntObj < C3dslashwind::MAX_SLASHWIND; nCntObj++)
    {
        CObject* pObj = CObject::GetObj(3, nCntObj);

        if (pObj != nullptr)
        {
            CObject::TYPE type = pObj->GetType();

            C3dtornado* p3dtornado = (C3dtornado*)pObj;

            D3DXVECTOR3 TornadoPos = p3dtornado->GetPos();

            //�G�̏ꍇ
            if (type == CObject::TYPE::SLASHTORNADO)
            {
                if (Pos.x >= TornadoPos.x - 25
                    && Pos.x <= TornadoPos.x + 25
                    && Pos.y >= TornadoPos.y - 20
                    && Pos.y <= TornadoPos.y + 20
                    && Pos.z >= TornadoPos.z - 10
                    && Pos.z <= TornadoPos.z + 10)
                {


                    //�v���C���[���E�������Ă��鎞
                    if (PlayerRot.y >= -1.6f && PlayerRot.y <= -0.1f)
                    {
                        CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_SE_TORNADO_SHOT);
                        p3dtornado->TornadoAtk(0);                    

                    }

                    //�v���C���[�����������Ă��鎞
                    if (PlayerRot.y >= 0.1f && PlayerRot.y <= 1.6f)
                    {
                        CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_SE_TORNADO_SHOT);
                        p3dtornado->TornadoAtk(1);

                    }


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
void C3dslashwind::Draw()
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

    for (int nCntParts = 0; nCntParts < SLASHWIND_MODEL; nCntParts++)
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
void C3dslashwind::Reset()
{
    m_bComboDest = true;
}


//======================
// �I�u�W�F�N�g��������
//======================
C3dslashwind* C3dslashwind::Create(D3DXVECTOR3 pos)
{
    C3dslashwind* D3DSlashWind= nullptr;

    D3DSlashWind = new C3dslashwind;

    //�������ɐ��������ꍇ
    if (SUCCEEDED(D3DSlashWind->Init()))
    {
        D3DSlashWind->SetType(TYPE::SLASHWIND);

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
HRESULT C3dslashwind::Load()
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
void C3dslashwind::Unload()
{
    CModel::Unload();
}



//===========================
// �O���t�@�C���ǂݍ��ݏ���
//===========================
void C3dslashwind::LoadBlockData(void)
{
    char Datacheck[MAX_CHAR];
    int nCntEnemyData = 0;
    int EnemyModelSave = 0;

    m_pFile = fopen("data\\MODEL\\MODEL_TORNADO\\tornado_profile.txt", "r");//�t�@�C�����J��

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
bool C3dslashwind::Collision3DBlock(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3* pMove, float fWidth, float fHeight)
{
    bool bLanding = false; // �d�͂��K�p���ꂽ�ꍇ�̂ݎg�p
    float fMoveslashwindWidth = 25.0f;
    float fMoveslashwindDepth = 70.0f;
    float fMoveslashwindHeight = 25.0f;

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
