//=================================================
//
// �X�e�[�W�}�l�[�W���[���� (texture.cpp)
// Author: Sohta Kuki
//
//=================================================

#include "addlifespawner.h"

#include "3ditem.h"
#include "3dhiteffect.h"
#include "ItemdropUI.h"


//======================
//�R���X�g���N�^
//======================
CAddLifeSpawner::CAddLifeSpawner()
{

}

//======================
//�f�X�g���N�^
//======================
CAddLifeSpawner::~CAddLifeSpawner()
{

}

//======================
//����������
//======================
HRESULT CAddLifeSpawner::Init()
{
    return S_OK;
}

//======================
// �I������
//======================
void CAddLifeSpawner::Uninit()
{

}

//======================
// �X�V����
//======================
void CAddLifeSpawner::Update()
{
    if (C3dplayer::GetPlayerLife() <= 24 && C3ditem::GetItemNum() == 1)
    {
        m_nTimer++;


        if (m_nTimer == 120)
        {
            CItemDropUI::DisplayAddLifeUI(); //�A�C�e�����o������UI��\������

            int randoms[] = { ADDLIFE_SPAWNER_POS::ADDLIFE_POS_R_LOWER , ADDLIFE_SPAWNER_POS::ADDLIFE_POS_L_LOWER,
                             ADDLIFE_SPAWNER_POS::ADDLIFE_POS_R_UPPER,ADDLIFE_SPAWNER_POS::ADDLIFE_POS_L_UPPER };

            // 0����6�܂ł̗����𐶐�
            m_nRandSelect = randoms[rand() % 3];

            CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_SE_ITEM_SPAWN);

            if (m_nRandSelect == ADDLIFE_SPAWNER_POS::ADDLIFE_POS_R_LOWER)
            {
                C3ditem::Create(D3DXVECTOR3(700.0f ,50.0f ,- 10.0f), 3);
                C3dhiteffect::Create(D3DXVECTOR3(700.0f, 50.0f, -10.0f), D3DXVECTOR3(90.0f, 90.0f, 0.0f), m_rot);
            }

            if (m_nRandSelect == ADDLIFE_SPAWNER_POS::ADDLIFE_POS_R_UPPER)
            {
                C3ditem::Create(D3DXVECTOR3(700.0f, 280.0f, -10.0f), 3);
                C3dhiteffect::Create(D3DXVECTOR3(700.0f, 280.0f, -10.0f), D3DXVECTOR3(90.0f, 90.0f, 0.0f), m_rot);
            }

            if (m_nRandSelect == ADDLIFE_SPAWNER_POS::ADDLIFE_POS_L_LOWER)
            {
                C3ditem::Create(D3DXVECTOR3(-150.0f ,50.0f ,-10.0f), 3);
                C3dhiteffect::Create(D3DXVECTOR3(-150.0f, 50.0f, -10.0f), D3DXVECTOR3(90.0f, 90.0f, 0.0f), m_rot);
            }

            if (m_nRandSelect == ADDLIFE_SPAWNER_POS::ADDLIFE_POS_L_UPPER)
            {
                C3ditem::Create(D3DXVECTOR3(-150.0f, 280.0f, -10.0f), 3);
                C3dhiteffect::Create(D3DXVECTOR3(-150.0f, 280.0f, -10.0f), D3DXVECTOR3(90.0f, 90.0f, 0.0f), m_rot);
            }

            m_nTimer = 0;
        }
    }
}

//======================
// �`�揈��
//======================
void CAddLifeSpawner::Draw()
{

}

//======================
// �I�u�W�F�N�g��������
//======================
CAddLifeSpawner* CAddLifeSpawner::Create(int nType)
{
    CAddLifeSpawner* D3DAddLifeSpawner = nullptr;

    D3DAddLifeSpawner = new CAddLifeSpawner;

    //�������ɐ��������ꍇ
    if (SUCCEEDED(D3DAddLifeSpawner->Init()))
    {
        
    }

    return D3DAddLifeSpawner;
}
