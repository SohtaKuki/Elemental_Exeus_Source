//=================================================
//
// 3D���f���̃u���b�N�̕\������ (3dswitchbs.cpp)
// Author: Sohta Kuki
//
//=================================================

#include "3dboss_switch.h"
#include "3dplayer.h"

LPDIRECT3DTEXTURE9 C3dswitchbs::m_pTexBuff = nullptr;
int C3dswitchbs::m_nMaxSwitchbs = 0;

//======================
// �R���X�g���N�^
//======================
C3dswitchbs::C3dswitchbs(int nPriority) : CModel(nPriority)
{
    m_nTurnCnt = 0;
    m_bTurn = false;
}

//======================
// �f�X�g���N�^
//======================
C3dswitchbs::~C3dswitchbs()
{

}

//======================
// ����������
//======================
HRESULT C3dswitchbs::Init()
{
    //������
    if (FAILED(CModel::Init()))
    {
        return E_FAIL;
    }

    //�u���b�N�����J�E���g
    m_nMaxSwitchbs++;

    return S_OK;
}
//======================
// �I������
//======================
void C3dswitchbs::Uninit()
{


    // ���b�V����}�e���A���̉��
    for (int i = 0; i < SWITCH_BS_MODEL; i++)
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

    // ���łɉ������Ă���ꍇ�͏������X�L�b�v
    if (m_pTexBuff != nullptr) {
        m_pTexBuff->Release();
        m_pTexBuff = nullptr;
    }

    // �u���b�N�������炷
    m_nMaxSwitchbs--;

    // ���N���X�̏I���������Ăяo��
    CModel::Uninit();
}

//======================
// �X�V����
//======================
void C3dswitchbs::Update()
{	
    //�Q�[�����i�s�\�̎��̂ݒʂ�
    if (CScene::GetUpdateStat() == true)
    {
        for (int nCntPriority = 0; nCntPriority < MAX_PRIORITY; nCntPriority++)
        {
            //�u���b�N�̓����蔻��
            for (int nCntObj = 0; nCntObj < C3dswitchbs::MAX_SWITCH_BS; nCntObj++)
            {
                CObject* pObj = CObject::GetObj(nCntPriority, nCntObj);

                if (pObj != nullptr)
                {
                    CObject::TYPE type = pObj->GetType();

                    //�u���b�N�������ꍇ
                    if (type == CObject::TYPE::SWITCH_BS)
                    {
                        D3DXVECTOR3 Pos = CObject3D::GetPos();


                        SetPos(Pos);

                        //X���W�̈ړ��ʂ��X�V
                        m_nMove.x += (0.0f - m_nMove.x) * 0.1f;

                        //Z���W�̈ړ��ʂ��X�V
                        m_nMove.z += (0.0f - m_nMove.z) * 0.1f;

                    }

                }
            }
        }
    }

    int nFadeState = CFade::GetFadeState();

    if (nFadeState == CFade::FADE_OUT)
    {
        C3dswitchbs::Uninit();
    }
}

//======================
// �`�揈��
//======================
void C3dswitchbs::Draw()
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

    for (int nCntParts = 0; nCntParts < SWITCH_BS_MODEL; nCntParts++)
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
// �I�u�W�F�N�g��������
//======================
C3dswitchbs* C3dswitchbs::Create(D3DXVECTOR3 pos, int nType)
{
    C3dswitchbs* D3DSwitchbs = nullptr;

    D3DSwitchbs = new C3dswitchbs;

    //�������ɐ��������ꍇ
    if (SUCCEEDED(D3DSwitchbs->Init()))
    {

        D3DSwitchbs->SetType(TYPE::SWITCH_BS);

        D3DSwitchbs->m_nType = nType;

        D3DSwitchbs->LoadSwitchbsData();

        //D3DSwitchbs->Load();//�e�N�X�`����ݒ�(��)

        D3DSwitchbs->CObject3D::SetPos(pos);

        ////�e�N�X�`���̐ݒ�
        //Model->BindTexture(m_pTexBuff);


    }

    return D3DSwitchbs;
}

//======================
// �e�N�X�`�����[�h����
//======================
HRESULT C3dswitchbs::Load()
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
void C3dswitchbs::Unload()
{
    CModel::Unload();
}



//===========================
// �O���t�@�C���ǂݍ��ݏ���
//===========================
void C3dswitchbs::LoadSwitchbsData(void)
{
    char Datacheck[MAX_CHAR];
    int nCntEnemyData = 0;
    int EnemyModelSave = 0;

    if (m_nType == 0)
    {
        m_pFile = fopen("data\\MODEL\\MODEL_FLOOR\\block.txt", "r");//�t�@�C�����J��
    }

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
        m_aModel[nCnt].bUse = false;

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
bool C3dswitchbs::Collision3DSwitchbs(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3* pMove, float fWidth, float fHeight)
{
    bool bLanding = false; // �d�͂�K�������ꍇ�̂ݎg�p
    float fSwitchbsWidth = 20.0f;
    float fSwitchbsDepth = 30.0f;
    float fSwitchbsHeight = 30.0f;

    D3DXVECTOR3 Pos = CObject3D::GetPos();

    // �E�������蔻��
    if (pPos->x - fWidth <= Pos.x + fSwitchbsWidth && pPosOld->x - fWidth >= Pos.x + fSwitchbsWidth && pPos->z - fHeight < Pos.z + fSwitchbsDepth && pPos->z > Pos.z - fSwitchbsDepth && pPos->y < Pos.y + fSwitchbsHeight - 5.0f && pPos->y > Pos.y - fSwitchbsHeight - 60.0f)
    {

    }
    // ���������蔻��
    else if (pPos->x + fWidth >= Pos.x - fSwitchbsWidth && pPosOld->x + fWidth <= Pos.x - fSwitchbsWidth && pPos->z - fHeight < Pos.z + fSwitchbsDepth && pPos->z > Pos.z - fSwitchbsDepth && pPos->y < Pos.y + fSwitchbsHeight - 5.0f && pPos->y > Pos.y - fSwitchbsHeight - 120.0f)
    {

        bLanding = true;

    }
    // �O�������蔻��
    if (pPos->x - fWidth < Pos.x + fSwitchbsWidth && pPos->x + fWidth > Pos.x - fSwitchbsWidth && pPos->z - fHeight <= Pos.z + fSwitchbsDepth - 30.0f && pPosOld->z - fHeight >= Pos.z + fSwitchbsDepth - 30.0f && pPos->y < Pos.y + fSwitchbsHeight && pPos->y > Pos.y - fSwitchbsHeight)
    {

    }

    // �㑤�����蔻��
    else if (pPos->x - fWidth < Pos.x + fSwitchbsWidth && pPos->x + fWidth > Pos.x - fSwitchbsWidth && pPos->z >= Pos.z - fSwitchbsDepth && pPosOld->z <= Pos.z - fSwitchbsDepth && pPos->y < Pos.y + fSwitchbsHeight && pPos->y > Pos.y - fSwitchbsHeight)
    {


    }
    // �㑤�����蔻��
    if (pPos->x - fWidth < Pos.x + fSwitchbsWidth - 10.0f && pPos->x + fWidth > Pos.x - fSwitchbsWidth + 10.0f && pPos->y - fHeight <= Pos.y + fSwitchbsHeight && pPosOld->y - fHeight >= Pos.y + fSwitchbsHeight && pPos->z < Pos.z + fSwitchbsDepth && pPos->z > Pos.z - fSwitchbsDepth)
    {


    }

    // ���������蔻��
    else if (pPos->x - fWidth < Pos.x + fSwitchbsWidth && pPos->x + fWidth > Pos.x - fSwitchbsWidth && pPos->y + fHeight >= Pos.y - (fSwitchbsHeight + 80.0f) && pPosOld->y + fHeight <= Pos.y - (fSwitchbsHeight + 80.0f) && pPos->z < Pos.z + fSwitchbsDepth && pPos->z > Pos.z - fSwitchbsDepth)
    {

    }


    return bLanding;
}
