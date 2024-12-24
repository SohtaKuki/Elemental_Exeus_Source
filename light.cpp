//=================================================
//
// ���C�g���� (light.cpp)
// Author: Sohta Kuki
//
//=================================================

#include "light.h"
#include "main.h"
#include "object.h"
#include "3dgoalobj.h"
#include "3dplayer.h"


CLight::CLight()
{
	//���C�g�̏����N���A����
	ZeroMemory(&m_alight, sizeof(D3DLIGHT9));
}

CLight::~CLight()
{

}

//======================
// ����������
//======================
HRESULT CLight::Init()
{
	CRenderer* Renderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = Renderer->GetDevice();

	m_alight->Type = D3DLIGHT_DIRECTIONAL;

	m_alight->Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	for (int nCnt = 0; nCnt < MAX_LIGHT; nCnt++)
	{

		switch (nCnt)
		{
		case 0:
			//���C�g�̕�����ݒ�
			m_avecDir[nCnt] = D3DXVECTOR3(0.2f, -0.8f, -0.3f);
			break;
		case 1:
			//���C�g�̕�����ݒ�
			m_avecDir[nCnt] = D3DXVECTOR3(-0.96f, -0.22f, -0.102f);
			break;
		case 2:
			//���C�g�̕�����ݒ�
			m_avecDir[nCnt] = D3DXVECTOR3(2.9f, -1.3f, 1.1f);
			break;
		case 3:
			//���C�g�̕�����ݒ�
			m_avecDir[nCnt] = D3DXVECTOR3(2.4f, 2.6f, 0.4f);
			break;

		}
	}

	for (int nCnt = 0; nCnt < MAX_LIGHT; nCnt++)
	{
		D3DXVec3Normalize(&m_avecDir[nCnt], &m_avecDir[nCnt]);
		m_alight->Direction = m_avecDir[nCnt];

		//���C�g��ݒ�
		pDevice->SetLight(nCnt, m_alight);

		//���C�g��L���ɂ���
		pDevice->LightEnable(nCnt, TRUE);
	}

	return S_OK;
}

//======================
// �I������
//======================
void CLight::Uninit()
{

}

//======================
// �X�V����
//======================
void CLight::Update()
{
	CRenderer* Renderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = Renderer->GetDevice();



	if (C3dgoalobj::GetStageNum() == 2)
	{
		//for (int nCnt = 0; nCnt < MAX_LIGHT; nCnt++)
		//{

		//	switch (nCnt)
		//	{
		//	case 0:
		//		//���C�g�̕�����ݒ�
		//		m_avecDir[nCnt] = D3DXVECTOR3(0.2f, -0.8f, -0.9f);
		//		break;
		//	case 1:
		//		//���C�g�̕�����ݒ�
		//		m_avecDir[nCnt] = D3DXVECTOR3(0.5f, -0.9f, -0.4f);
		//		break;
		//	case 2:
		//		//���C�g�̕�����ݒ�
		//		m_avecDir[nCnt] = D3DXVECTOR3(2.9f, -1.3f, 1.1f);
		//		break;
		//	case 3:
		//		//���C�g�̕�����ݒ�
		//		m_avecDir[nCnt] = D3DXVECTOR3(2.4f, 2.6f, 0.4f);
		//		break;

		//	}
		//}


	}


	
	for (int nCnt = 0; nCnt < MAX_LIGHT; nCnt++)
	{
		D3DXVec3Normalize(&m_avecDir[nCnt], &m_avecDir[nCnt]);
		m_alight->Direction = m_avecDir[nCnt];

		//���C�g��ݒ�
		pDevice->SetLight(nCnt, m_alight);

		//���C�g��L���ɂ���
		pDevice->LightEnable(nCnt, TRUE);
	}
}