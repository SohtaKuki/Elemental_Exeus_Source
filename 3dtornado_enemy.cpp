//=================================================
//
// 3D���f���̃u���b�N�̕\������ (3dtornadoEnemy.cpp)
// Author: Sohta Kuki
//
//=================================================

#include "3dtornado_enemy.h"
#include "3dplayer.h"
#include "3denemy.h"
#include "camera.h"
#include "3dhiteffect.h"
#include "3dblock.h"

LPDIRECT3DTEXTURE9 C3dtornadoEnemy::m_pTexBuff = nullptr;
int C3dtornadoEnemy::m_nMaxBlock = 0;
int C3dtornadoEnemy::m_nNumTornado = 2;
float C3dtornadoEnemy::m_nHeightTorPos = 0.0f;
bool C3dtornadoEnemy::m_bTorUpper = false;

//======================
// �R���X�g���N�^
//======================
C3dtornadoEnemy::C3dtornadoEnemy(int nPriority) : CObject3D(nPriority)
{
    m_nTurnCnt = 0;
    m_bTurn = false;
    m_bMoveSwitchL = false;
    m_nSpawnAtkTimer = 0;
    m_bTorUpper = false;
    m_fMovetornadoHeight = 70.0f;
}

//======================
// �f�X�g���N�^
//======================
C3dtornadoEnemy::~C3dtornadoEnemy()
{

}

//======================
// ����������
//======================
HRESULT C3dtornadoEnemy::Init()
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
    m_nNumTornado--;

    if (m_nNumTornado == 0 && (m_nType == C3dtornadoEnemy::TORNADO_STATE::TORNADO_SET || m_nType == C3dtornadoEnemy::TORNADO_STATE::TORNADO_ATK))
    {
        m_nNumTornado = 0;
    }

    return S_OK;
}

void C3dtornadoEnemy::Uninit()
{
    // ���łɉ������Ă���ꍇ�͏������X�L�b�v
    if (m_pTexBuff != nullptr)
    {
        m_pTexBuff->Release();
        m_pTexBuff = nullptr;
    }

    // ���b�V����}�e���A���̉��
    for (int i = 0; i < TORNADO_MODEL; i++)
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

    m_nNumTornado++;

    m_bTorUpper = false;

    // ���N���X�̏I���������Ăяo��
    CObject3D::Uninit();
}

//======================
// �X�V����
//======================
void C3dtornadoEnemy::Update()
{
    //�Q�[�����i�s�\�̎��̂ݒʂ�
    if (CScene::GetUpdateStat() == true)
    {
        D3DXVECTOR3 Pos = CObject3D::GetPos();

        // ���R���ł̏���
        if (C3dtornadoEnemy::m_bDisplay == true )
        {
            m_nTimer++;

            m_rot.y += 0.3f; // ��]����

            if (m_nTimer == TORNADO_TIMER)
            {
                C3dtornadoEnemy::m_bDisplay = false;
                Uninit();
                return;
            }
        }

        // �v���C���[���E�������Ă��鎞
        if (m_bMoveSwitch == true)
        {
            m_nMove.x += 1.0f;
        }

        // �v���C���[�����������Ă��鎞
        if (m_bMoveSwitchL == true)
        {
            m_nMove.x -= 1.0f;
        }


        if (m_bMoveSwitchLD == true)
        {
            m_nMove.x -= 0.4f;
            m_nMove.y -= 0.25f;
        }

        //�e�ƓG�̓����蔻��
        for (int nCntObj = 0; nCntObj < 4; nCntObj++)
        {
            CObject* pObj = CObject::GetObj(3, nCntObj);

            if (pObj != nullptr)
            {
                CObject::TYPE type = pObj->GetType();

                C3dplayer* p3dplayer = (C3dplayer*)pObj;

                D3DXVECTOR3 PlayerPos = p3dplayer->GetPos();

                //�G�̏ꍇ
                if (type == CObject::TYPE::PLAYER && m_nType == TORNADO_STATE::TORNADO_ATK)
                {
                    if (Pos.x >= PlayerPos.x - 25
                        && Pos.x <= PlayerPos.x + 25
                        && Pos.y >= PlayerPos.y - 20
                        && Pos.y <= PlayerPos.y + 50
                        && Pos.z >= PlayerPos.z - 10
                        && Pos.z <= PlayerPos.z + 10)
                    {
                        C3dhiteffect::Create(D3DXVECTOR3(CObject3D::GetPos().x, CObject3D::GetPos().y + 35.0f, CObject3D::GetPos().z), D3DXVECTOR3(90.0f, 90.0f, 0.0f), m_rot);
                        p3dplayer->PlayerDamage(8);
                        Uninit();
                        return;
                    }
                }
            }
        }

        //�e�ƓG�̓����蔻��
        for (int nCntObj = 0; nCntObj < 200; nCntObj++)
        {
            CObject* pObj = CObject::GetObj(3, nCntObj);

            if (pObj != nullptr)
            {
                CObject::TYPE type = pObj->GetType();

                C3dblock* p3dblock = (C3dblock*)pObj;

                D3DXVECTOR3 BlockPos = p3dblock->GetPos();

                //�G�̏ꍇ
                if (type == CObject::TYPE::BLOCK && m_nType == TORNADO_STATE::TORNADO_ATK)
                {
                    if (Pos.x >= BlockPos.x - 55
                        && Pos.x <= BlockPos.x + 55
                        && Pos.y >= BlockPos.y - 60
                        && Pos.y <= BlockPos.y + 10)
                    {
                        C3dhiteffect::Create(D3DXVECTOR3(CObject3D::GetPos().x, CObject3D::GetPos().y + 35.0f, CObject3D::GetPos().z), D3DXVECTOR3(90.0f, 90.0f, 0.0f), m_rot);
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
    }

    int nFadeState = CFade::GetFadeState();

    if (nFadeState == CFade::FADE_OUT)
    {
        C3dtornadoEnemy::m_bDisplay = true;
        m_nTimer = 0;
        C3dtornadoEnemy::Uninit();
    }
}

//======================
// �`�揈��
//======================
void C3dtornadoEnemy::Draw()
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

    for (int nCntParts = 0; nCntParts < TORNADO_MODEL; nCntParts++)
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
void C3dtornadoEnemy::TornadoAtk(int nDirection)
{
    if (nDirection == 0)
    {
        m_bMoveSwitch = true;
        m_nType = TORNADO_STATE::TORNADO_ATK;
    }

    if (nDirection == 1)
    {
        m_bMoveSwitchL = true;
        m_nType = TORNADO_STATE::TORNADO_ATK;
    }

    if (nDirection == 2)
    {
        m_bMoveSwitchLD = true;
        m_nType = TORNADO_STATE::TORNADO_ATK;
    }
}


//======================
// �I�u�W�F�N�g��������
//======================
C3dtornadoEnemy* C3dtornadoEnemy::Create(D3DXVECTOR3 pos, int nDirection)
{
    C3dtornadoEnemy* D3DSlashWind = nullptr;

    D3DSlashWind = new C3dtornadoEnemy;

    //�������ɐ��������ꍇ
    if (SUCCEEDED(D3DSlashWind->Init()))
    {
        D3DSlashWind->m_bDisplay = true;

        D3DSlashWind->SetType(TYPE::SLASHTORNADO_ENEMY);

        D3DSlashWind->LoadBlockData();

        D3DSlashWind->m_nDirection = nDirection;

        //D3DBlock->Load();//�e�N�X�`����ݒ�(��)

        D3DSlashWind->CObject3D::SetPos(pos);

        D3DSlashWind->m_nPos = pos;

        D3DSlashWind->m_bMoveSwitchLD = true; //���������ɔ�΂�����

        D3DSlashWind->m_nType = C3dtornadoEnemy::TORNADO_STATE::TORNADO_ATK;

        ////�e�N�X�`���̐ݒ�
        //Model->BindTexture(m_pTexBuff);
    }

    return D3DSlashWind;
}

//======================
// �e�N�X�`�����[�h����
//======================
HRESULT C3dtornadoEnemy::Load()
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
void C3dtornadoEnemy::Unload()
{
    CModel::Unload();
}



//===========================
// �O���t�@�C���ǂݍ��ݏ���
//===========================
void C3dtornadoEnemy::LoadBlockData(void)
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
bool C3dtornadoEnemy::Collision3DTornadoEnemy(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3* pMove, float fWidth, float fHeight)
{
    bool bLanding = false; // �d�͂��K�p���ꂽ�ꍇ�̂ݎg�p
    m_bTorUpper = false;
    float fMovetornadoWidth = 10.0f;
    float fMovetornadoDepth = 40.0f;

    D3DXVECTOR3 Pos = CObject3D::GetPos();

    // �E�������蔻��
    if (pPos->x - fWidth <= Pos.x + fMovetornadoWidth && pPosOld->x - fWidth >= Pos.x + fMovetornadoWidth && pPos->z - fHeight < Pos.z + fMovetornadoDepth && pPos->z > Pos.z - fMovetornadoDepth && pPos->y < Pos.y + m_fMovetornadoHeight && pPos->y > Pos.y - m_fMovetornadoHeight)
    {
        bLanding = true;
    }
    // ���������蔻��
    else if (pPos->x + fWidth >= Pos.x - fMovetornadoWidth && pPosOld->x + fWidth <= Pos.x - fMovetornadoWidth && pPos->z - fHeight < Pos.z + fMovetornadoDepth && pPos->z > Pos.z - fMovetornadoDepth && pPos->y < Pos.y + m_fMovetornadoHeight && pPos->y > Pos.y - m_fMovetornadoHeight)
    {
        bLanding = true;
    }
    // �O�������蔻��
    if (pPos->x - fWidth < Pos.x + fMovetornadoWidth && pPos->x + fWidth > Pos.x - fMovetornadoWidth && pPos->z - fHeight <= Pos.z + fMovetornadoDepth && pPosOld->z - fHeight >= Pos.z + fMovetornadoDepth && pPos->y < Pos.y + m_fMovetornadoHeight && pPos->y > Pos.y - m_fMovetornadoHeight)
    {
        pPos->y = Pos.y + m_fMovetornadoHeight + fHeight;

        bLanding = true;
    }
    // �㑤�����蔻��
    else if (pPos->x - fWidth < Pos.x + fMovetornadoWidth && pPos->x + fWidth > Pos.x - fMovetornadoWidth && pPos->z >= Pos.z - fMovetornadoDepth && pPosOld->z <= Pos.z - fMovetornadoDepth && pPos->y < Pos.y + m_fMovetornadoHeight && pPos->y > Pos.y - m_fMovetornadoHeight)
    {
        pPos->y = Pos.y + m_fMovetornadoHeight + fHeight;
        bLanding = true;
    }
    // �㑤�����蔻��
    if (pPos->x - fWidth < Pos.x + fMovetornadoWidth && pPos->x + fWidth > Pos.x - fMovetornadoWidth && pPos->y - fHeight <= Pos.y + m_fMovetornadoHeight && pPosOld->y - fHeight >= Pos.y + m_fMovetornadoHeight && pPos->z < Pos.z + fMovetornadoDepth && pPos->z > Pos.z - fMovetornadoDepth)
    {
        pPos->y = Pos.y + m_fMovetornadoHeight + fHeight;
        m_bTorUpper = true;
    }
    // ���������蔻��
    else if (pPos->x - fWidth < Pos.x + fMovetornadoWidth && pPos->x + fWidth > Pos.x - fMovetornadoWidth && pPos->y >= Pos.y - m_fMovetornadoHeight && pPosOld->y <= Pos.y - m_fMovetornadoHeight && pPos->z < Pos.z + fMovetornadoDepth && pPos->z > Pos.z - fMovetornadoDepth)
    {
        pPos->y = Pos.y + m_fMovetornadoHeight + fHeight;
        bLanding = true;
    }

    return bLanding;
}
