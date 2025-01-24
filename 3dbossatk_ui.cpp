//=================================================
//
// �r���{�[�h�̏��� (billboard.cpp)
// Author: Sohta Kuki
//
//=================================================

#include "3dbossatk_ui.h"
#include "3dboss.h"

bool C3dBossATKUI::m_bUse = {};
int C3dBossATKUI::m_nType = {};

//======================
// �R���X�g���N�^
//======================
C3dBossATKUI::C3dBossATKUI(int nPriority) : CObject3D(nPriority)
{
	m_bUse = false;
	m_pVtxBuff = nullptr;
}

//======================
// �f�X�g���N�^
//======================
C3dBossATKUI::~C3dBossATKUI()
{

}

//======================
// ����������
//======================
HRESULT C3dBossATKUI::Init()
{
	CRenderer* Renderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = Renderer->GetDevice();

	//�e�N�X�`���̓Ǎ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\bossATK_UI.png", &m_pTexture);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * 1, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);

	//���_���̃|�C���^
	VERTEX_3D* pVtx;

	//���_�o�b�t�@�����b�N�����_��񎞂ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-m_nSize.x, m_nSize.y, m_nSize.z);
	pVtx[1].pos = D3DXVECTOR3(m_nSize.x, m_nSize.y, m_nSize.z);
	pVtx[2].pos = D3DXVECTOR3(-m_nSize.x, -m_nSize.y, m_nSize.z);
	pVtx[3].pos = D3DXVECTOR3(m_nSize.x, -m_nSize.y, m_nSize.z);

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

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();

	return S_OK;

}

//======================
//�I������
//======================
void C3dBossATKUI::Uninit()
{
	CObject3D::Uninit();
}

//======================
//�I������
//======================
void C3dBossATKUI::Update()
{	
	//�Q�[�����i�s�\�̎��̂ݒʂ�
	if (CScene::GetUpdateStat() == true)
	{
		//���_���̃|�C���^
		VERTEX_3D* pVtx;

		//���_�o�b�t�@�����b�N�����_��񎞂ւ̃|�C���^���擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(-m_nSize.x, m_nSize.y, m_nSize.z);
		pVtx[1].pos = D3DXVECTOR3(m_nSize.x * 2, m_nSize.y, m_nSize.z);
		pVtx[2].pos = D3DXVECTOR3(-m_nSize.x, -m_nSize.y, m_nSize.z);
		pVtx[3].pos = D3DXVECTOR3(m_nSize.x * 2, -m_nSize.y, m_nSize.z);

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

		if (m_nType == C3dBossATKUI::ATKUI_DISPLAY::BSUI_R_LOWERDASHATK)
		{
			m_nPos.x = 70.0f;
			m_nPos.y = 170.0f;

			m_nSize.x = 180.0f;
			m_nSize.y = 140.0f;
		}

		if (m_nType == C3dBossATKUI::ATKUI_DISPLAY::BSUI_L_LOWERDASHATK)
		{
			m_nPos.x = 300.0f;
			m_nPos.y = 170.0f;

			m_nSize.x = 180.0f;
			m_nSize.y = 140.0f;
		}

		if (m_nType == C3dBossATKUI::ATKUI_DISPLAY::BSUI_R_UPPERDASHATK)
		{
			m_nPos.x = 70.0f;
			m_nPos.y = 350.0f;

			m_nSize.x = 180.0f;
			m_nSize.y = 140.0f;
		}

		if (m_nType == C3dBossATKUI::ATKUI_DISPLAY::BSUI_L_UPPERDASHATK)
		{
			m_nPos.x = 300.0f;
			m_nPos.y = 350.0f;

			m_nSize.x = 180.0f;
			m_nSize.y = 140.0f;
		}

		if (m_nType == C3dBossATKUI::ATKUI_DISPLAY::BSUI_R_LOWERDASHATK)
		{
			m_nPos.x = 140.0f;
			m_nPos.y = 170.0f;

			m_nSize.x = 180.0f;
			m_nSize.y = 140.0f;
		}

		if (m_nType == C3dBossATKUI::ATKUI_DISPLAY::BSUI_L_MELEEATK)
		{
			m_nPos.x = C3dboss::GetBossPosCamera().x + 200.0f;
			m_nPos.y = C3dboss::GetBossPosCamera().y + 100.0f;

			m_nSize.x = 140.0f;
			m_nSize.y = 110.0f;
		}

		if (m_nType == C3dBossATKUI::ATKUI_DISPLAY::BSUI_R_MELEEATK)
		{
			m_nPos.x = C3dboss::GetBossPosCamera().x - 250.0f;
			m_nPos.y = C3dboss::GetBossPosCamera().y + 100.0f;

			m_nSize.x = 140.0f;
			m_nSize.y = 110.0f;
		}

		if (m_nType == C3dBossATKUI::ATKUI_DISPLAY::BSUI_WIREDATK)
		{
			m_nPos.x = C3dboss::GetBossPosCamera().x - 200.0f;
			m_nPos.y = C3dboss::GetBossPosCamera().y + 100.0f;

			m_nSize.x = 1000.0f;
			m_nSize.y = 110.0f;
		}

		if (m_nType == C3dBossATKUI::BSUI_L_UPPERDOUBLEATK)
		{
			m_nPos.x = 500.0f;
			m_nPos.y = 350.0f;

			m_nSize.x = 180.0f;
			m_nSize.y = 740.0f;
		}

		if (m_nType == C3dBossATKUI::BSUI_R_UPPERDOUBLEATK)
		{
			m_nPos.x = -100.0f;
			m_nPos.y = 350.0f;

			m_nSize.x = 180.0f;
			m_nSize.y = 740.0f;
		}

		//�{�X�̗̑͂�0�ɂȂ������\���ɂ���
		if (C3dboss::GetBossLife() <= 0)
		{
			m_bUse = false;
		}

		//���_�o�b�t�@���A�����b�N
		m_pVtxBuff->Unlock();
	}

	//�t�F�[�h�̏�Ԃ��擾
	int nFadeState = CFade::GetFadeState();

	//�t�F�[�h�A�E�g�ɂȂ����ꍇ�A�I�������Ɉڍs
	if (nFadeState == CFade::FADE_OUT)
	{
		C3dBossATKUI::Uninit();
	}
}

//======================
// �`�揈��
//======================
void C3dBossATKUI::Draw()
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

	D3DXMatrixTranslation(&mtxTrans, m_nPos.x, m_nPos.y, m_nPos.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	if (m_bUse == true)
	{
		//�r���{�[�h�̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
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
C3dBossATKUI* C3dBossATKUI::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	C3dBossATKUI* p3dBossATKUI = new C3dBossATKUI;

	//�������ɐ��������ꍇ
	if (SUCCEEDED(p3dBossATKUI->Init()))
	{
		p3dBossATKUI->SetType(TYPE::BOSS_ATKUI);

		p3dBossATKUI->m_nPos = pos;

		p3dBossATKUI->m_nSize = size;
	}



	return p3dBossATKUI;
}

bool C3dBossATKUI::DisplayBossATKUI(int nDisplayID, int DisplayOption)
{
	//�\������ꍇ
	if (DisplayOption == C3dBossATKUI::UIDISPLAY::UI_DISPLAY)
	{
		m_bUse = true;
	}

	//��\���ɂ���ꍇ
	if (DisplayOption == C3dBossATKUI::UIDISPLAY::UI_HIDDEN)
	{
		m_bUse = false;
	}

	m_nType = nDisplayID;

	return m_bUse;
}