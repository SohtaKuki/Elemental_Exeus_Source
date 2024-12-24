//=================================================
//
// 3D�p�[�e�B�N���̏��� (3dmeshfield.cpp)
// Author: Sohta Kuki
//
//=================================================

#include "3dparticle.h"

//======================
// �R���X�g���N�^
//======================
CParticle::CParticle(int nPriority) : CObject3D(nPriority)
{
    // ������
    m_vVelocity = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    m_vAcceleration = D3DXVECTOR3(0.0f, -0.001f, 0.0f); // �d�͉����x���V�~�����[�V����
    m_fLifeTime = 1.0f; // ������ݒ�i1�b�j
    m_fAlphaDecay = 1.0f; // �A���t�@�l�̌�����
}

//======================
// �f�X�g���N�^
//======================
CParticle::~CParticle()
{
}

//======================
// ����������
//======================
HRESULT CParticle::Init()
{
    CRenderer* Renderer = CManager::GetRenderer();
    LPDIRECT3DDEVICE9 pDevice = Renderer->GetDevice();

    //�e�N�X�`���̓Ǎ���
    D3DXCreateTextureFromFile(pDevice, "data\\texture\\billboard000.png", &m_pTexture);

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
// �I������
//======================
void CParticle::Uninit()
{
    CObject3D::Uninit();
}

//======================
// �X�V����
//======================
void CParticle::Update()
{

    //// �����̌���
    //m_fLifeTime -= 0.01f;

    //// ���x�ƈʒu�̍X�V
    //m_vVelocity += m_vAcceleration;
    //m_nPos += m_vVelocity;

    //// �A���t�@�l�̌���
    //float alpha = max(0.0f, m_fLifeTime * m_fAlphaDecay);

    //// �T�C�Y�̌���
    //float sizeFactor = max(0.1f, m_fLifeTime); // �������Z���Ȃ�قǃT�C�Y���������Ȃ�
    //m_nSize = D3DXVECTOR3(sizeFactor, sizeFactor, sizeFactor);

    // ���_�o�b�t�@�̃��b�N
    VERTEX_3D* pVtx;
    m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);


    // �T�C�Y���l���������_���W�̐ݒ�
    pVtx[0].pos = D3DXVECTOR3(-m_nSize.x, m_nSize.y, m_nSize.z);
    pVtx[1].pos = D3DXVECTOR3(m_nSize.x, m_nSize.y, m_nSize.z);
    pVtx[2].pos = D3DXVECTOR3(-m_nSize.x, -m_nSize.y, m_nSize.z);
    pVtx[3].pos = D3DXVECTOR3(m_nSize.x, -m_nSize.y, m_nSize.z);

    // ���_�J���[�̐ݒ�
    pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
    pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
    pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
    pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);


    // ���_�o�b�t�@���A�����b�N
    m_pVtxBuff->Unlock();

    // �p�[�e�B�N���̏���
    if (m_fLifeTime <= 0.0f)
    {
        this->Uninit();
    }
}


//======================
// �`�揈��
//======================
void CParticle::Draw()
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

    //�r���{�[�h�̕`��
    pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

    //�A���t�@�e�X�g�����ɖ߂�
    pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//======================
// �I�u�W�F�N�g��������
//======================
CParticle* CParticle::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
    CParticle* Particle = new CParticle;

    // �������ɐ��������ꍇ
    if (SUCCEEDED(Particle->Init()))
    {
        Particle->m_nPos = pos;
        Particle->m_nSize = size;
    }

    return Particle;
}
