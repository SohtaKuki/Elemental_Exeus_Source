//=================================================
//
// ビルボードの処理 (billboard.cpp)
// Author: Sohta Kuki
//
//=================================================

#include "3dbossatk_ui.h"
#include "3dboss.h"

bool C3dBossATKUI::m_bUse = {};
int C3dBossATKUI::m_nType = {};

//======================
// コンストラクタ
//======================
C3dBossATKUI::C3dBossATKUI(int nPriority) : CObject3D(nPriority)
{
	m_bUse = false;
	m_pVtxBuff = nullptr;
}

//======================
// デストラクタ
//======================
C3dBossATKUI::~C3dBossATKUI()
{

}

//======================
// 初期化処理
//======================
HRESULT C3dBossATKUI::Init()
{
	CRenderer* Renderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = Renderer->GetDevice();

	//テクスチャの読込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\bossATK_UI.png", &m_pTexture);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4 * 1, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);

	//頂点情報のポインタ
	VERTEX_3D* pVtx;

	//頂点バッファをロックし頂点情報時へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(-m_nSize.x, m_nSize.y, m_nSize.z);
	pVtx[1].pos = D3DXVECTOR3(m_nSize.x, m_nSize.y, m_nSize.z);
	pVtx[2].pos = D3DXVECTOR3(-m_nSize.x, -m_nSize.y, m_nSize.z);
	pVtx[3].pos = D3DXVECTOR3(m_nSize.x, -m_nSize.y, m_nSize.z);

	//法線ベクトルの設定
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//頂点カラーの初期設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//テクスチャ座標の初期設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	pVtx += 4;

	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();

	return S_OK;

}

//======================
//終了処理
//======================
void C3dBossATKUI::Uninit()
{
	CObject3D::Uninit();
}

//======================
//終了処理
//======================
void C3dBossATKUI::Update()
{	
	//ゲームが進行可能の時のみ通す
	if (CScene::GetUpdateStat() == true)
	{
		//頂点情報のポインタ
		VERTEX_3D* pVtx;

		//頂点バッファをロックし頂点情報時へのポインタを取得
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(-m_nSize.x, m_nSize.y, m_nSize.z);
		pVtx[1].pos = D3DXVECTOR3(m_nSize.x * 2, m_nSize.y, m_nSize.z);
		pVtx[2].pos = D3DXVECTOR3(-m_nSize.x, -m_nSize.y, m_nSize.z);
		pVtx[3].pos = D3DXVECTOR3(m_nSize.x * 2, -m_nSize.y, m_nSize.z);

		//法線ベクトルの設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		//頂点カラーの初期設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テクスチャ座標の初期設定
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

		//ボスの体力が0になったら非表示にする
		if (C3dboss::GetBossLife() <= 0)
		{
			m_bUse = false;
		}

		//頂点バッファをアンロック
		m_pVtxBuff->Unlock();
	}

	//フェードの状態を取得
	int nFadeState = CFade::GetFadeState();

	//フェードアウトになった場合、終了処理に移行
	if (nFadeState == CFade::FADE_OUT)
	{
		C3dBossATKUI::Uninit();
	}
}

//======================
// 描画処理
//======================
void C3dBossATKUI::Draw()
{
	CRenderer* Renderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = Renderer->GetDevice();

	D3DXMATRIX mtxTrans;	//計算用マトリックス

	//ビューマトリックス取得
	D3DXMATRIX mtxView;

	////ライトを無効にする
	//pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//=========================
	// 壁めり込み防止コード
	//=========================

	////Zの比較方法変更
	//pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);

	////Zバッファに書き込まない
	//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	//アルファテストを有効化
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);


	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//ビューマトリックス取得
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	//ポリゴンをカメラの正面に向け続ける
	D3DXMatrixInverse(&m_mtxWorld, NULL, &mtxView);	//逆行列を求める

	m_mtxWorld._41 = 0.0f;
	m_mtxWorld._42 = 0.0f;
	m_mtxWorld._43 = 0.0f;

	D3DXMatrixTranslation(&mtxTrans, m_nPos.x, m_nPos.y, m_nPos.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	if (m_bUse == true)
	{
		//ビルボードの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}

	//アルファテストを元に戻す
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);


	//=========================
	// 壁めり込み防止コード
	//=========================

	////Zの比較方法変更
	//pDevice->SetRenderState(D3DRS_ZFUNC,D3DCMP_LESSEQUAL);

	////Zバッファに書き込む
	//pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	////ライトを無効にする
	//pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//======================
// オブジェクト生成処理
//======================
C3dBossATKUI* C3dBossATKUI::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	C3dBossATKUI* p3dBossATKUI = new C3dBossATKUI;

	//初期化に成功した場合
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
	//表示する場合
	if (DisplayOption == C3dBossATKUI::UIDISPLAY::UI_DISPLAY)
	{
		m_bUse = true;
	}

	//非表示にする場合
	if (DisplayOption == C3dBossATKUI::UIDISPLAY::UI_HIDDEN)
	{
		m_bUse = false;
	}

	m_nType = nDisplayID;

	return m_bUse;
}