//=================================================
//
// �r���{�[�h�`�掮�e�̏��� (3dtornadoeffect.cpp)
// Author: Sohta Kuki
//
//=================================================

#include "3dfireeffect.h"
#include "3dblock.h"
#include "3denemy.h"
#include "score.h"
#include "camera.h"
#include "scene.h"
#include "bosscallui.h"
#include "3dboss.h"
#include "3dgoalobj.h"

//======================
// �R���X�g���N�^
//======================
C3dfireeffect::C3dfireeffect(int nPriority) : CObject3D(nPriority)
{
	m_bUse = true;
	m_nPatternAnimExpl = 1;
}

//======================
// �f�X�g���N�^
//======================
C3dfireeffect::~C3dfireeffect()
{

}

//======================
// ����������
//======================
HRESULT C3dfireeffect::Init()
{
	CRenderer* Renderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = Renderer->GetDevice();

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\fire000.png", &m_pTexture);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * 1, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);

	//���_���̃|�C���^
	VERTEX_3D* pVtx;

	//���_�o�b�t�@�����b�N�����_��񎞂ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3((-m_nSize.x), (m_nSize.y), (m_nSize.z));
	pVtx[1].pos = D3DXVECTOR3((m_nSize.x), (m_nSize.y), (m_nSize.z));
	pVtx[2].pos = D3DXVECTOR3((-m_nSize.x), (-m_nSize.y), (m_nSize.z));
	pVtx[3].pos = D3DXVECTOR3((m_nSize.x), (-m_nSize.y), (m_nSize.z));

	//�@���x�N�g���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//���_�J���[�̏����ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);



	pVtx += 4;

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();


	// 0����6�܂ł̗����𐶐�
	m_nPatternAnimExpl = rand() % 21;

	return S_OK;
}

//======================
//�I������
//======================
void C3dfireeffect::Uninit()
{
	if (m_pTexture != nullptr)
	{
		m_pTexture->Release();
		m_pTexture = nullptr;
	}

	CObject3D::Uninit();
}

//======================
//�X�V����
//======================
void C3dfireeffect::Update()
{
	//�t�F�[�h�̏�Ԃ��擾
	int nFadeState = CFade::GetFadeState();

	//�t�F�[�h�A�E�g�����狭���폜
	if (nFadeState == CFade::FADE_OUT)
	{
		C3dfireeffect::Uninit();
		return;
	}

	if (CScene::GetUpdateStat() == true)
	{
		//���_���̃|�C���^
		VERTEX_3D* pVtx;

		//���_�o�b�t�@�����b�N�����_��񎞂ւ̃|�C���^���擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		//�{�X���o���̏���
		if (CBossCallUI::GetEndStat() == true && C3dboss::GetBossEntry() == false && C3dgoalobj::GetStageNum() == 2)
		{
			m_bUse = false;
		}

		//�{�X���o���I�������ۂ̏���
		if (CBossCallUI::GetEndStat() == true && C3dboss::GetBossEntry() == true && C3dgoalobj::GetStageNum() == 2)
		{
			m_bUse = true;
		}


		if (m_bUse == true)
		{

			m_nCounterAnim++;

			if (m_nCounterAnim % C3dfireeffect::DELAY_ANIM == 0)
			{
				m_nCounterAnim = 0;

				//�A�j���؂�ւ�����
				m_nPatternAnimExpl++;


				//�e�N�X�`�����W�̐ݒ�
				pVtx[0].tex = D3DXVECTOR2((1.0f / EFCT_TORNADO_PATTERN_ANIM) * m_nPatternAnimExpl - (1.0f / EFCT_TORNADO_PATTERN_ANIM), 0.0f);
				pVtx[1].tex = D3DXVECTOR2((1.0f / EFCT_TORNADO_PATTERN_ANIM) * m_nPatternAnimExpl, 0.0f);
				pVtx[2].tex = D3DXVECTOR2((1.0f / EFCT_TORNADO_PATTERN_ANIM) * m_nPatternAnimExpl - (1.0f / EFCT_TORNADO_PATTERN_ANIM), 1.0f);
				pVtx[3].tex = D3DXVECTOR2((1.0f / EFCT_TORNADO_PATTERN_ANIM) * m_nPatternAnimExpl, 1.0f);
			}

			if (m_nPatternAnimExpl >= 17)
			{
				m_nPatternAnimExpl = 1;
			}


		}

		pVtx += 4;

		////�G�t�F�N�g�𗳊��ɒǏ]����
		//for (int nCntObj = 0; nCntObj < 80; nCntObj++)
		//{
		//	CObject* pObj = CObject::GetObj(3, nCntObj);

		//	if (pObj != nullptr)
		//	{
		//		CObject::TYPE type = pObj->GetType();

		//		m_p3dTornado = (C3dtornado*)pObj;

		//		if (type == CObject::TYPE::SLASHTORNADO)
		//		{
		//			D3DXVECTOR3 EnemyPos = m_p3dTornado->GetPos();

		//			m_nPos.x = EnemyPos.x;
		//		}
		//	}
		//}

		//���_�o�b�t�@���A�����b�N
		m_pVtxBuff->Unlock();
	}
}

//======================
// �`�揈��
//======================
void C3dfireeffect::Draw()
{
	CRenderer* Renderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = Renderer->GetDevice();

	D3DXMATRIX mtxTrans;	//�v�Z�p�}�g���b�N�X

	//�r���[�}�g���b�N�X�擾
	D3DXMATRIX mtxView;

	//���C�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//=========================
	// �ǂ߂荞�ݖh�~�R�[�h
	//=========================

	//Z�̔�r���@�ύX
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);

	//Z�o�b�t�@�ɏ������܂Ȃ�
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	//�A���t�@�e�X�g��L����
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);


	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�r���[�}�g���b�N�X�擾
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	//�|���S�����J�����̐��ʂɌ���������
	D3DXMatrixInverse(&m_mtxWorld, NULL, &mtxView);	//�t�s������߂�

	m_mtxWorld._41 = 0.0f;
	m_mtxWorld._42 = 0.0f;
	m_mtxWorld._43 = 0.0f;

	D3DXMatrixTranslation(&mtxTrans, m_nPos.x, m_nPos.y, m_nPos.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�g�p�ς݂̏ꍇ�̂ݒʂ�
	if (m_bUse == true)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, m_pTexture);

		//�r���{�[�h�̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}


	//�A���t�@�e�X�g�����ɖ߂�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);


	//=========================
	// �ǂ߂荞�ݖh�~�R�[�h
	//=========================

	//Z�̔�r���@�ύX
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);

	//Z�o�b�t�@�ɏ�������
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	//���C�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//======================
// �I�u�W�F�N�g��������
//======================
C3dfireeffect* C3dfireeffect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, int type)
{
	C3dfireeffect* fireeffect3d = new C3dfireeffect;

	fireeffect3d->m_nPos = pos;

	fireeffect3d->m_rot = rot;

	fireeffect3d->m_nSize = size;

	//�������ɐ��������ꍇ
	if (SUCCEEDED(fireeffect3d->Init()))
	{
		fireeffect3d->m_nType = type;

		if (type == 0)
		{
			fireeffect3d->SetType(TYPE::PLAYER_EFCT_TORNADO);
		}

		if (type == 1)
		{
			fireeffect3d->SetType(TYPE::ENEMY_EFCT_TORNADO);
		}

		fireeffect3d->m_nLife = 180;


	}

	return fireeffect3d;
}

void C3dfireeffect::SetExplosionSub(D3DXVECTOR3 pos, D3DXCOLOR col)
{

}