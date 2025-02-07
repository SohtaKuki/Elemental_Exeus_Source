//=================================================
//
// �r���{�[�h�̏��� (billboard.cpp)
// Author: Sohta Kuki
//
//=================================================

#include "3dbossatk_ui_diag.h"
#include "3dboss.h"

bool C3dBossATKUIDiag::m_bUse[NUM_UI] = {};
int C3dBossATKUIDiag::m_nType = {};


//======================
// �R���X�g���N�^
//======================
C3dBossATKUIDiag::C3dBossATKUIDiag(int nPriority) : CObject3D(nPriority)
{
	m_pVtxBuff = nullptr;
}

//======================
// �f�X�g���N�^
//======================
C3dBossATKUIDiag::~C3dBossATKUIDiag()
{

}

//======================
// ����������
//======================
HRESULT C3dBossATKUIDiag::Init()
{
	CRenderer* Renderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = Renderer->GetDevice();

	for (int nCnt = 0; nCnt < NUM_UI; nCnt++)
	{
		m_bUse[nCnt] = false;

		switch (nCnt)
		{
		case 0:
			//�e�N�X�`���̓Ǎ���
			D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\BSATKWARNING_UI\\warning_L_AIRATK.png", &m_pTexture[nCnt]);
			break;
		case 1:
			//�e�N�X�`���̓Ǎ���
			D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\BSATKWARNING_UI\\warning_R_AIRATK.png", &m_pTexture[nCnt]);
			break;
		}
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * NUM_UI, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);

	//���_���̃|�C���^
	VERTEX_3D* pVtx;

	//���_�o�b�t�@�����b�N�����_��񎞂ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < NUM_UI; nCnt++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-m_nSize[nCnt].x, m_nSize[nCnt].y, m_nSize[nCnt].z);
		pVtx[1].pos = D3DXVECTOR3(m_nSize[nCnt].x, m_nSize[nCnt].y, m_nSize[nCnt].z);
		pVtx[2].pos = D3DXVECTOR3(-m_nSize[nCnt].x, -m_nSize[nCnt].y, m_nSize[nCnt].z);
		pVtx[3].pos = D3DXVECTOR3(m_nSize[nCnt].x, -m_nSize[nCnt].y, m_nSize[nCnt].z);

		//�@���x�N�g���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//���_�J���[�̏����ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`�����W�̏����ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();

	return S_OK;
}

//======================
//�I������
//======================
void C3dBossATKUIDiag::Uninit()
{
	CObject3D::Uninit();
}

//======================
//�I������
//======================
void C3dBossATKUIDiag::Update()
{
	if (CScene::GetUpdateStat() == true)
	{
		//���_���̃|�C���^
		VERTEX_3D* pVtx;

		//���_�o�b�t�@�����b�N�����_��񎞂ւ̃|�C���^���擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);


		for (int nCnt = 0; nCnt < NUM_UI; nCnt++)
		{
			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(m_nPos[nCnt].x - m_nSize[nCnt].x, m_nPos[nCnt].y + m_nSize[nCnt].y, m_nPos[nCnt].z);
			pVtx[1].pos = D3DXVECTOR3(m_nPos[nCnt].x + m_nSize[nCnt].x * 2, m_nPos[nCnt].y + m_nSize[nCnt].y, m_nPos[nCnt].z);
			pVtx[2].pos = D3DXVECTOR3(m_nPos[nCnt].x - m_nSize[nCnt].x, m_nPos[nCnt].y - m_nSize[nCnt].y, m_nPos[nCnt].z);
			pVtx[3].pos = D3DXVECTOR3(m_nPos[nCnt].x + m_nSize[nCnt].x * 2, m_nPos[nCnt].y - m_nSize[nCnt].y, m_nPos[nCnt].z);

			//�@���x�N�g���̐ݒ�
			pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			//���_�J���[�̏����ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//�e�N�X�`�����W�̏����ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

			pVtx += 4;
		}

		//�{�X�U���͈̓}�[�J�[�̍��W���T�C�Y(�E)
		if (m_nType == C3dBossATKUIDiag::ATKUI_DISPLAY::BSUI_R_DIAGATK)
		{
			m_nPos[m_nType].x = 110.0f;
			m_nPos[m_nType].y = 130.0f;

			m_nSize[m_nType].x = 400.0f;
			m_nSize[m_nType].y = 320.0f;
		}

		//�{�X�U���͈̓}�[�J�[�̍��W���T�C�Y(��)
		if (m_nType == C3dBossATKUIDiag::ATKUI_DISPLAY::BSUI_L_DIAGATK)
		{
			m_nPos[m_nType].x = 0.0f;
			m_nPos[m_nType].y = 130.0f;

			m_nSize[m_nType].x = 400.0f;
			m_nSize[m_nType].y = 320.0f;
		}



		//���_�o�b�t�@���A�����b�N
		m_pVtxBuff->Unlock();

		//�t�F�[�h�̏�Ԃ��擾
		int nFadeState = CFade::GetFadeState();

		//�t�F�[�h�A�E�g�ɂȂ����ꍇ�A�I�������Ɉڍs
		if (nFadeState == CFade::FADE_OUT)
		{
			C3dBossATKUIDiag::Uninit();
		}
	}
}

//======================
// �`�揈��
//======================
void C3dBossATKUIDiag::Draw()
{
	CRenderer* Renderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = Renderer->GetDevice();

	D3DXMATRIX mtxTrans;	//�v�Z�p�}�g���b�N�X

	//�r���[�}�g���b�N�X�擾
	D3DXMATRIX mtxView;

	////���C�g�𖳌��ɂ���
	//pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//=========================
	// �ǂ߂荞�ݖh�~�R�[�h
	//=========================

	////Z�̔�r���@�ύX
	//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);

	////Z�o�b�t�@�ɏ������܂Ȃ�
	//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

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

	for (int nCnt = 0; nCnt < NUM_UI; nCnt++)
	{
		D3DXMatrixTranslation(&mtxTrans, m_nPos[nCnt].x, m_nPos[nCnt].y, m_nPos[nCnt].z);
	}

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	for (int nCnt = 0; nCnt < NUM_UI; nCnt++)
	{
		if (m_bUse[nCnt] == true)
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, m_pTexture[nCnt]);

			//�r���{�[�h�̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCnt *  4, 2);

		}
	}



	//�A���t�@�e�X�g�����ɖ߂�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);


	//=========================
	// �ǂ߂荞�ݖh�~�R�[�h
	//=========================

	////Z�̔�r���@�ύX
	//pDevice->SetRenderState(D3DRS_ZFUNC,D3DCMP_LESSEQUAL);

	////Z�o�b�t�@�ɏ�������
	//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	////���C�g�𖳌��ɂ���
	//pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//======================
// �I�u�W�F�N�g��������
//======================
C3dBossATKUIDiag* C3dBossATKUIDiag::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	C3dBossATKUIDiag* p3dBossATKUI = nullptr;

	 p3dBossATKUI = new C3dBossATKUIDiag;

	 for (int nCnt = 0; nCnt < NUM_UI; nCnt++)
	 {
		 p3dBossATKUI->m_nPos[nCnt] = pos;

		 p3dBossATKUI->m_nSize[nCnt] = size;
	 }

	//�������ɐ��������ꍇ
	if (SUCCEEDED(p3dBossATKUI->Init()))
	{
		p3dBossATKUI->SetType(TYPE::BOSS_ATKUI);
	}



	return p3dBossATKUI;
}

bool C3dBossATKUIDiag::DisplayBossATKUI(int nDisplayID, int DisplayOption)
{
	//�\������ꍇ
	if (DisplayOption == C3dBossATKUIDiag::UIDISPLAY::UI_DISPLAY)
	{
		m_bUse[nDisplayID] = true;
	}

	//��\���ɂ���ꍇ
	if (DisplayOption == C3dBossATKUIDiag::UIDISPLAY::UI_HIDDEN)
	{
		m_bUse[nDisplayID] = false;
	}

	m_nType = nDisplayID;

	return m_bUse[nDisplayID];
}