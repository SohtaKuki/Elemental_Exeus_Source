//=================================================
//
// �X�e�[�W�}�l�[�W���[���� (texture.cpp)
// Author: Sohta Kuki
//
//=================================================

#include "stagemanager.h"

#include "3denemy.h"
#include "3dblock.h"
#include "startobj.h"
#include "3ditem.h"
#include "objectX.h"
#include "3dplayer.h"
#include "3dgoalobj.h"
#include "billboard.h"
#include "timer.h"
#include "floor.h"
#include "3dmoveblock.h"
#include "blizardfloor.h"
#include "3dbackground.h"
#include "floorBG.h"
#include "3denemy_air.h"
#include "3dboss_switch.h"

//======================
//�R���X�g���N�^
//======================
CStageManager::CStageManager()
{

}

//======================
//�f�X�g���N�^
//======================
CStageManager::~CStageManager()
{

}

//======================
//����������
//======================
HRESULT CStageManager::Init()
{
	return S_OK;
}

//======================
// �I������
//======================
void CStageManager::Uninit()
{

}

//======================
// �X�V����
//======================
void CStageManager::Update()
{

}

//======================
// �`�揈��
//======================
void CStageManager::Draw()
{

}

//======================
// �I�u�W�F�N�g��������
//======================
CStageManager* CStageManager::Create(int nType)
{
    CStageManager* D3DStageManager = nullptr;

    D3DStageManager = new CStageManager;

    //�������ɐ��������ꍇ
    if (SUCCEEDED(D3DStageManager->Init()))
    {
        D3DStageManager->m_nType = nType;

        D3DStageManager->LoadStageData();
    }

    return D3DStageManager;
}

//======================
// �X�e�[�W�z�u���ǂݍ��ݏ���
//======================
void CStageManager::LoadStageData()
{
    char Datacheck[MAX_CHAR];
    int nCntObjectData = 0;
    int CreateObjType[MAX_OBJ];
    int CreateObjType2[MAX_OBJ];

    //�X�e�[�W�𐶐�����f�[�^��ǂݍ��ސ��int�Ŏ���
    if (m_nType == 0)
    {
        m_pFile = fopen("data\\LOADSTAGE\\loadstage000.txt", "r");//�t�@�C�����J��
    }

    if (m_nType == 1)
    {
        m_pFile = fopen("data\\LOADSTAGE\\loadstage001.txt", "r");//�t�@�C�����J��
    }

    if (m_nType == 2)
    {
        m_pFile = fopen("data\\LOADSTAGE\\loadstage002.txt", "r");//�t�@�C�����J��
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


            if (Datacheck[0] == '#')
            {
                continue;
            }

            //�t�@�C�������
            if (!strcmp(Datacheck, "END_STAGESET"))
            {
                fclose(m_pFile);
                break;
            }

            //�������Ԃ̐ݒ�
            if (!strcmp(Datacheck, "TIMERSET"))
            {
                fscanf(m_pFile, "%s", Datacheck);
                fscanf(m_pFile, "%d", &m_nTimer);
                continue;
            }

            //�I�u�W�F�N�g�̊e��ݒ�
            if (!strcmp(Datacheck, "OBJECTSET"))
            {
                while (1)
                {
                    fscanf(m_pFile, "%s", Datacheck);

                    //�I�u�W�F�N�g���ǂݍ��݂̏I��
                    if (!strcmp(Datacheck, "END_OBJECTSET"))
                    {
                        break;
                    }

                    //��������I�u�W�F�N�g�̎��
                    if (!strcmp(Datacheck, "OBJ_TYPE"))
                    {
                        fscanf(m_pFile, "%s", Datacheck);
                        fscanf(m_pFile, "%d", &CreateObjType[nCntObjectData]);
                    }

                    //�I�u�W�F�N�g�̍��W
                    if (!strcmp(Datacheck, "POS"))
                    {
                        fscanf(m_pFile, "%s", Datacheck);
                        fscanf(m_pFile, "%f", &m_nPos[nCntObjectData].x);
                        fscanf(m_pFile, "%f", &m_nPos[nCntObjectData].y);
                        fscanf(m_pFile, "%f", &m_nPos[nCntObjectData].z);
                    }

                    //�I�u�W�F�N�g�̌���
                    if (!strcmp(Datacheck, "ROT"))
                    {
                        fscanf(m_pFile, "%s", Datacheck);
                        fscanf(m_pFile, "%f", &m_nRot[nCntObjectData].x);
                        fscanf(m_pFile, "%f", &m_nRot[nCntObjectData].y);
                        fscanf(m_pFile, "%f", &m_nRot[nCntObjectData].z);
                    }

                    //�I�u�W�F�N�g�̌���
                    if (!strcmp(Datacheck, "SIZE"))
                    {
                        fscanf(m_pFile, "%s", Datacheck);
                        fscanf(m_pFile, "%f", &m_nSize[nCntObjectData].x);
                        fscanf(m_pFile, "%f", &m_nSize[nCntObjectData].y);
                        fscanf(m_pFile, "%f", &m_nSize[nCntObjectData].z);
                    }

                    //�I�u�W�F�N�g�̏ڍאݒ� (�ꕔ�̃I�u�W�F�N�g�ł����g�p���Ȃ�)
                    if (!strcmp(Datacheck, "OBJ_TYPE2"))
                    {
                        fscanf(m_pFile, "%s", Datacheck);
                        fscanf(m_pFile, "%d", &CreateObjType2[nCntObjectData]);
                    }
                }

                nCntObjectData++;
            }

    }

    //�f�o�C�X�̎擾
    LPDIRECT3DDEVICE9 pDevice = nullptr;
    pDevice = CManager::GetRenderer()->GetDevice();

    //�������Ԃ���
    CTimer::AddTimer(m_nTimer);

    //��L�œ���������
    for (int nCnt = 0; nCnt < nCntObjectData; nCnt++)
    {
        //�v���C���[�����̏ꍇ
        if (CreateObjType[nCnt] == 0)
        {
            C3dplayer::Create(D3DXVECTOR3(m_nPos[nCnt].x, m_nPos[nCnt].y, m_nPos[nCnt].z));
            C3dstartobj::Create();
        }

        //�G�����̏ꍇ
        if (CreateObjType[nCnt] == 1)
        {
            C3denemy::Create(D3DXVECTOR3(m_nPos[nCnt].x, m_nPos[nCnt].y, m_nPos[nCnt].z), CreateObjType2[nCnt]);
        }

        //�u���b�N�����̏ꍇ
        if (CreateObjType[nCnt] == 2)
        {
            C3dblock::Create(D3DXVECTOR3(m_nPos[nCnt].x, m_nPos[nCnt].y, m_nPos[nCnt].z),(CreateObjType2[nCnt]));
        }

        //�A�C�e�������̏ꍇ
        if (CreateObjType[nCnt] == 4)
        {
            C3ditem::Create(D3DXVECTOR3(m_nPos[nCnt].x, m_nPos[nCnt].y, m_nPos[nCnt].z), CreateObjType2[nCnt]);
        }

        //�S�[���}�[�J�[�̏ꍇ
        if (CreateObjType[nCnt] == 6)
        {
            C3dgoalobj::Create(D3DXVECTOR3(m_nPos[nCnt].x, m_nPos[nCnt].y, m_nPos[nCnt].z), CreateObjType2[nCnt]);
        }

        //���̐���
        if (CreateObjType[nCnt] == 7)
        {
            CFloor::Create(D3DXVECTOR3(m_nPos[nCnt].x, m_nPos[nCnt].y, m_nPos[nCnt].z) ,D3DXVECTOR3(m_nSize[nCnt].x, m_nSize[nCnt].y, m_nSize[nCnt].z), CreateObjType2[nCnt]);
        }

        //�ړ����u���b�N�����̏ꍇ
        if (CreateObjType[nCnt] == 8)
        {
            C3dmoveblock::Create(D3DXVECTOR3(m_nPos[nCnt].x, m_nPos[nCnt].y, m_nPos[nCnt].z),CreateObjType2[nCnt]);
        }

        //���Ᏸ�u���b�N�̏ꍇ
        if (CreateObjType[nCnt] == 9)
        {
            CBlizardfloor ::Create(D3DXVECTOR3(m_nPos[nCnt].x, m_nPos[nCnt].y, m_nPos[nCnt].z), D3DXVECTOR3(m_nSize[nCnt].x, m_nSize[nCnt].y, m_nSize[nCnt].z));
        }

        //���̐���
        if (CreateObjType[nCnt] == 10)
        {
            CFloorBG::Create(D3DXVECTOR3(m_nPos[nCnt].x, m_nPos[nCnt].y, m_nPos[nCnt].z), D3DXVECTOR3(m_nSize[nCnt].x, m_nSize[nCnt].y, m_nSize[nCnt].z), CreateObjType2[nCnt]);
        }

        //�G�����̏ꍇ
        if (CreateObjType[nCnt] == 11)
        {
            C3denemyair::Create(D3DXVECTOR3(m_nPos[nCnt].x, m_nPos[nCnt].y, m_nPos[nCnt].z), CreateObjType2[nCnt]);
        }

        //�u���b�N�����̏ꍇ
        if (CreateObjType[nCnt] == 12)
        {
            C3dswitchbs::Create(D3DXVECTOR3(m_nPos[nCnt].x, m_nPos[nCnt].y, m_nPos[nCnt].z), (CreateObjType2[nCnt]));
        }
    }
}