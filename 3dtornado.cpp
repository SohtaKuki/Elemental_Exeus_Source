//=================================================
//
// 3Dモデルのブロックの表示処理 (3dtornado.cpp)
// Author: Sohta Kuki
//
//=================================================

#include "3dtornado.h"
#include "3dplayer.h"
#include "3denemy.h"
#include "3dboss.h"
#include "camera.h"
#include "3denemy_air.h"
#include "3dhiteffect.h"
#include "3dblock.h"
#include "tornado_reloadUI.h"

LPDIRECT3DTEXTURE9 C3dtornado::m_pTexBuff = nullptr;
int C3dtornado::m_nMaxBlock = 0;
int C3dtornado::m_nNumTornado = 2;
float C3dtornado::m_nHeightTorPos = 0.0f;
bool C3dtornado::m_bTorUpper = false;

//======================
// コンストラクタ
//======================
C3dtornado::C3dtornado(int nPriority) : CObject3D(nPriority)
{
    m_nTurnCnt = 0;
    m_bTurn = false;
    m_bMoveSwitchL = false;
    m_nSpawnAtkTimer = 0;
    m_bTorUpper = false;
    m_fMovetornadoHeight = 70.0f;
}

//======================
// デストラクタ
//======================
C3dtornado::~C3dtornado()
{

}

//======================
// 初期化処理
//======================
HRESULT C3dtornado::Init()
{
    //初期化
    if (FAILED(CObject3D::Init()))
    {
        return E_FAIL;
    }

    //ブロック数をカウント
    m_nMaxBlock++;
    m_nTimer = 0;

    m_bMoveSwitch = false;
    //m_nNumTornado--;

    if (m_nNumTornado == 0 && (m_nType == C3dtornado::TORNADO_STATE::TORNADO_SET|| m_nType == C3dtornado::TORNADO_STATE::TORNADO_ATK))
    {
        m_nNumTornado = 0;
    }

    return S_OK;
}

void C3dtornado::Uninit()
{
    // すでに解放されている場合は処理をスキップ
    if (m_pTexBuff != nullptr)
    {
        m_pTexBuff->Release();
        m_pTexBuff = nullptr;
    }

    // メッシュやマテリアルの解放
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

    // ブロック数を減らす
    m_nMaxBlock--;

    m_bTorUpper = false;

    // 基底クラスの終了処理を呼び出す
    CObject3D::Uninit();
}

//======================
// 更新処理
//======================
void C3dtornado::Update()
{
    //ゲームが進行可能の時のみ通す
    if (CScene::GetUpdateStat() == true)
    {
        D3DXVECTOR3 Pos = CObject3D::GetPos();

        for (int nCntPriority = 0; nCntPriority < MAX_PRIORITY; nCntPriority++)
        {
            //スラッシュウィンドの当たり判定
            for (int nCntObj = 0; nCntObj < C3dtornado::MAX_TORNADO; nCntObj++)
            {
                CObject* pObj = CObject::GetObj(nCntPriority, nCntObj);

                if (pObj != nullptr)
                {
                    CObject::TYPE type = pObj->GetType();

                    //スラッシュウィンドだった場合
                    if (type == CObject::TYPE::SLASHTORNADO)
                    {

                        //X座標の移動量を更新
                        m_nMove.x += (0.0f - m_nMove.x) * 0.1f;

                        //Y座標の移動量を更新
                        m_nMove.y += (0.0f - m_nMove.y) * 0.1f;

                        //Z座標の移動量を更新
                        m_nMove.z += (0.0f - m_nMove.z) * 0.1f;

                    }

                }
            }
        }

        // 自然消滅の処理
        if (C3dtornado::m_bDisplay == true)
        {
            m_nTimer++;

            m_rot.y += 0.3f; // 回転処理

            if (m_nTimer == TORNADO_TIMER)
            {
                C3dtornado::m_bDisplay = false;

                //m_nNumTornado++;
                Uninit();
                return;
            }
        }

        // プレイヤーが右を向いている時
        if (m_bMoveSwitch == true)
        {
            m_nMove.x += 1.8f;
        }

        // プレイヤーが左を向いている時
        if (m_bMoveSwitchL == true)
        {
            m_nMove.x -= 1.8f;
        }

        if (C3dtornado::m_bDisplay == true) // 表示中のみ処理をする
        {
            static bool movingUp = true; // 上下の切り替えを管理するフラグ

            if (movingUp == true)
            {
                m_fMovetornadoHeight += 0.5f; // 上昇

                if (m_fMovetornadoHeight >= 76.0f) // 上限に達したら方向を変更
                {
                    movingUp = false;
                }
            }
            else
            {
                m_fMovetornadoHeight -= 0.5f; // 下降
                if (m_fMovetornadoHeight <= 70.0f) // 下限に達したら方向を変更
                {
                    movingUp = true;
                }
            }
        }



        //弾と敵の当たり判定
        for (int nCntObj = 0; nCntObj < C3denemy::MAX_ENEMY; nCntObj++)
        {
            CObject* pObj = CObject::GetObj(3, nCntObj);

            if (pObj != nullptr)
            {
                CObject::TYPE type = pObj->GetType();

                C3denemy* p3denemy = (C3denemy*)pObj;

                D3DXVECTOR3 EnemyPos = p3denemy->GetPos();

                //敵の場合
                if (type == CObject::TYPE::ENEMY_NORMALMOVE || type == CObject::TYPE::ENEMY_NORMAL && m_nType == TORNADO_STATE::TORNADO_ATK)
                {
                    if (Pos.x >= EnemyPos.x - 25
                        && Pos.x <= EnemyPos.x + 25
                        && Pos.y >= EnemyPos.y - 20
                        && Pos.y <= EnemyPos.y + 50
                        && Pos.z >= EnemyPos.z - 10
                        && Pos.z <= EnemyPos.z + 10)
                    {
                        C3dhiteffect::Create(D3DXVECTOR3(CObject3D::GetPos().x, CObject3D::GetPos().y + 35.0f, CObject3D::GetPos().z), D3DXVECTOR3(90.0f, 90.0f, 0.0f), m_rot);
                        p3denemy->EnemyDamage(2);
                        Uninit();
                        return;
                    }
                }
            }
        }

        //弾と敵の当たり判定
        for (int nCntObj = 0; nCntObj < C3denemy::MAX_ENEMY; nCntObj++)
        {
            CObject* pObj = CObject::GetObj(3, nCntObj);

            if (pObj != nullptr)
            {
                CObject::TYPE type = pObj->GetType();

                C3denemyair* p3denemyair = (C3denemyair*)pObj;

                D3DXVECTOR3 EnemyPos = p3denemyair->GetPos();

                //敵の場合
                if (type == CObject::TYPE::ENEMY_FLYMOVE && m_nType == TORNADO_STATE::TORNADO_ATK)
                {
                    if (Pos.x >= EnemyPos.x - 25
                        && Pos.x <= EnemyPos.x + 25
                        && Pos.y >= EnemyPos.y - 55
                        && Pos.y <= EnemyPos.y + 55
                        && Pos.z >= EnemyPos.z - 10
                        && Pos.z <= EnemyPos.z + 10)
                    {
                        C3dhiteffect::Create(D3DXVECTOR3(CObject3D::GetPos().x, CObject3D::GetPos().y + 35.0f, CObject3D::GetPos().z), D3DXVECTOR3(90.0f, 90.0f, 0.0f), m_rot);
                        p3denemyair->EnemyDamage(2);
                        Uninit();
                        return;
                    }
                }
            }
        }

        //弾と敵の当たり判定
        for (int nCntObj = 0; nCntObj < 90; nCntObj++)
        {
            CObject* pObj = CObject::GetObj(20, nCntObj);

            if (pObj != nullptr)
            {
                CObject::TYPE type = pObj->GetType();

                C3dboss* p3dboss = (C3dboss*)pObj;

                D3DXVECTOR3 BossPos = p3dboss->GetPos();

                //敵の場合
                if (type == CObject::TYPE::BOSS && m_nType == TORNADO_STATE::TORNADO_ATK)
                {
                    if (Pos.x >= BossPos.x - 75
                        && Pos.x <= BossPos.x + 75
                        && Pos.y >= BossPos.y - 25
                        && Pos.y <= BossPos.y + 155
                        && Pos.z >= BossPos.z - 10
                        && Pos.z <= BossPos.z + 10)
                    {
                        C3dhiteffect::Create(D3DXVECTOR3(CObject3D::GetPos().x, CObject3D::GetPos().y + 35.0f, CObject3D::GetPos().z), D3DXVECTOR3(90.0f, 90.0f, 0.0f), m_rot);
                        p3dboss->BossDamage(24);
                        Uninit();
                        return;
                    }
                }
            }

            //弾と敵の当たり判定
            for (int nCntObj = 0; nCntObj < 200; nCntObj++)
            {
                CObject* pObj = CObject::GetObj(3, nCntObj);

                if (pObj != nullptr)
                {
                    CObject::TYPE type = pObj->GetType();

                    C3dblock* p3dblock = (C3dblock*)pObj;

                    D3DXVECTOR3 BlockPos = p3dblock->GetPos();

                    //敵の場合
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
        }




        Pos.x += m_nMove.x;
        Pos.y += m_nMove.y;

        SetPos(Pos);

        //X座標の移動量を更新
        m_nMove.x += (0.0f - m_nMove.x) * 0.10f;

        //X座標の移動量を更新
        m_nMove.y += (0.0f - m_nMove.y) * 0.10f;
    }

        int nFadeState = CFade::GetFadeState();

        if (nFadeState == CFade::FADE_OUT)
        {
            C3dtornado::m_bDisplay = true;
            m_nTimer = 0;
            C3dtornado::Uninit();
        }
}

//======================
// 描画処理
//======================
void C3dtornado::Draw()
{
    LPDIRECT3DDEVICE9 pDevice = nullptr;
    pDevice = CManager::GetRenderer()->GetDevice();

    D3DXMATRIX mtxRot, mtxTrans; //計算用マトリックス
    D3DMATERIAL9 matDef; //現在のマテリアル保存用
    D3DXMATERIAL* pMat; //マテリアルデータへのポインタ
    D3DXVECTOR3 Pos = CObject3D::GetPos();

    //ワールドマトリックスの初期化
    D3DXMatrixIdentity(&m_mtxworld);

    //向きを反映
    D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
    D3DXMatrixMultiply(&m_mtxworld, &m_mtxworld, &mtxRot);

    //位置を反映
    D3DXMatrixTranslation(&mtxTrans, Pos.x, Pos.y, Pos.z);
    D3DXMatrixMultiply(&m_mtxworld, &m_mtxworld, &mtxTrans);

    //ワールドマトリックスの設定
    pDevice->SetTransform(D3DTS_WORLD, &m_mtxworld);

    //マテリアルを取得
    pDevice->GetMaterial(&matDef);

    for (int nCntParts = 0; nCntParts < TORNADO_MODEL; nCntParts++)
    {
        //ワールドマトリックスの初期化
        D3DXMatrixIdentity(&m_aModel[nCntParts].mtxworld);

        //向きを反映
        D3DXMatrixRotationYawPitchRoll(&mtxRot, m_aModel[nCntParts].rot.y, m_aModel[nCntParts].rot.x, m_aModel[nCntParts].rot.z);
        D3DXMatrixMultiply(&m_aModel[nCntParts].mtxworld, &m_aModel[nCntParts].mtxworld, &mtxRot);

        //位置を反映
        D3DXMatrixTranslation(&mtxTrans, m_aModel[nCntParts].pos.x, m_aModel[nCntParts].pos.y, m_aModel[nCntParts].pos.z);
        D3DXMatrixMultiply(&m_aModel[nCntParts].mtxworld, &m_aModel[nCntParts].mtxworld, &mtxTrans);

        //親子関係
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
            //マトリックスの設定
            pDevice->SetTransform(D3DTS_WORLD, &m_aModel[nCntParts].mtxworld);

            pMat = (D3DXMATERIAL*)m_pBuffMat[nCntParts]->GetBufferPointer();

            for (int nCntMat = 0; nCntMat < (int)m_nNumMat[nCntParts]; nCntMat++)
            {
                //マテリアルの設定
                pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

                //テクスチャの設定
                pDevice->SetTexture(0, m_pTexBuff);

                //モデル(パーツ)の描画
                m_pMesh[nCntParts]->DrawSubset(nCntMat);
            }
        }

    }

    pDevice->SetMaterial(&matDef);
}

//======================
// 竜巻攻撃処理
//======================
void C3dtornado::TornadoAtk(int nDirection)
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
}


//======================
// オブジェクト生成処理
//======================
C3dtornado* C3dtornado::Create(D3DXVECTOR3 pos,int nDirection)
{
    C3dtornado* D3DSlashWind = nullptr;

    D3DSlashWind = new C3dtornado;

    //初期化に成功した場合
    if (SUCCEEDED(D3DSlashWind->Init()))
    {
        D3DSlashWind->m_bDisplay = true;


        D3DSlashWind->SetType(TYPE::SLASHTORNADO);

        D3DSlashWind->LoadBlockData();

        D3DSlashWind->m_nDirection = nDirection;

        //D3DBlock->Load();//テクスチャを設定(仮)

        D3DSlashWind->CObject3D::SetPos(pos);

        D3DSlashWind->m_nPos = pos;

        D3DSlashWind->m_nType = C3dtornado::TORNADO_STATE::TORNADO_SET;

        ////テクスチャの設定
        //Model->BindTexture(m_pTexBuff);
    }

    return D3DSlashWind;
}

//======================
// テクスチャロード処理
//======================
HRESULT C3dtornado::Load()
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
// テクスチャアンロード(終了)処理
//======================
void C3dtornado::Unload()
{
    CModel::Unload();
}



//===========================
// 外部ファイル読み込み処理
//===========================
void C3dtornado::LoadBlockData(void)
{
    char Datacheck[MAX_CHAR];
    int nCntEnemyData = 0;
    int EnemyModelSave = 0;

    m_pFile = fopen("data\\MODEL\\MODEL_TORNADO\\tornado_profile.txt", "r");//ファイルを開く

    //ファイルが存在しない場合
    if (m_pFile == NULL)
    {
        return;
    }

    //外部ファイル文字列読み取り
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

        //パーツ数
        if (!strcmp(Datacheck, "NUM_PARTS"))
        {
            fscanf(m_pFile, "%s", Datacheck);
            fscanf(m_pFile, "%d", &EnemyModelSave);
        }

        //ファイル名
        if (!strcmp(Datacheck, "MODEL_FILENAME"))
        {
            fscanf(m_pFile, "%s", Datacheck);
            fscanf(m_pFile, "%s", &m_aLoadEnemy[EnemyModelSave].filename[0]);
            EnemyModelSave++;
        }

        //パーツの詳細
        if (!strcmp(Datacheck, "PARTSSET"))
        {
            while (1)
            {
                fscanf(m_pFile, "%s", Datacheck);

                //パーツ詳細終わり検知
                if (!strcmp(Datacheck, "END_PARTSSET"))
                {
                    break;
                }

                //インデックス
                else if (!strcmp(Datacheck, "INDEX"))
                {
                    fscanf(m_pFile, "%s", Datacheck);
                    fscanf(m_pFile, "%d", &m_aLoadEnemy[nCntEnemyData].index);
                }

                //親設定
                else if (!strcmp(Datacheck, "PARENT"))
                {
                    fscanf(m_pFile, "%s", Datacheck);
                    fscanf(m_pFile, "%d", &m_aLoadEnemy[nCntEnemyData].parent);
                }

                //立ち位置
                else if (!strcmp(Datacheck, "POS"))
                {
                    fscanf(m_pFile, "%s", Datacheck);
                    fscanf(m_pFile, "%f", &m_aLoadEnemy[nCntEnemyData].pos.x);
                    fscanf(m_pFile, "%f", &m_aLoadEnemy[nCntEnemyData].pos.y);
                    fscanf(m_pFile, "%f", &m_aLoadEnemy[nCntEnemyData].pos.z);
                }

                //向き
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

    //デバイスの取得
    LPDIRECT3DDEVICE9 pDevice = nullptr;
    pDevice = CManager::GetRenderer()->GetDevice();

    //ここで上記の処理で得た数値を代入
    for (int nCnt = 0; nCnt < EnemyModelSave; nCnt++)
    {
        D3DXLoadMeshFromX(&m_aLoadEnemy[nCnt].filename[0], D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat[nCnt], NULL, &m_nNumMat[nCnt], &m_pMesh[nCnt]);
        //D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\golden000.jpg", &g_pTextureEnemy);
        m_aModel[nCnt].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
        m_aModel[nCnt].nLife = 4;
        m_aModel[nCnt].nIdxModelParent = m_aLoadEnemy[nCnt].parent;
        m_aModel[nCnt].bUse = true;

        //敵の立ち位置初期化
        //m_nPos = D3DXVECTOR3(-0.0f, -0.0f, 0.0f);
        //m_aEnemy.rot = D3DXVECTOR3(-0.0f, 0.0f, 0.0f);

        m_aModel[nCnt].pos = D3DXVECTOR3(m_aLoadEnemy[nCnt].pos.x, m_aLoadEnemy[nCnt].pos.y, m_aLoadEnemy[nCnt].pos.z);
        m_aModel[nCnt].rot = D3DXVECTOR3(m_aLoadEnemy[nCnt].rot.x, m_aLoadEnemy[nCnt].rot.y, m_aLoadEnemy[nCnt].rot.z);
    }
}



//===========================
// ブロックの当たり判定
//===========================
bool C3dtornado::Collision3DTornado(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3* pMove, float fWidth, float fHeight)
{
    bool bLanding = false; // 重力が適用された場合のみ使用
    m_bTorUpper = false;
    float fMovetornadoWidth = 10.0f;
    float fMovetornadoDepth = 40.0f;

    D3DXVECTOR3 Pos = CObject3D::GetPos();

    // 右側当たり判定
    if (pPos->x - fWidth <= Pos.x + fMovetornadoWidth && pPosOld->x - fWidth >= Pos.x + fMovetornadoWidth && pPos->z - fHeight < Pos.z + fMovetornadoDepth && pPos->z > Pos.z - fMovetornadoDepth && pPos->y < Pos.y + m_fMovetornadoHeight && pPos->y > Pos.y - m_fMovetornadoHeight)
    {
        bLanding = true;
    }
    // 左側当たり判定
    else if (pPos->x + fWidth >= Pos.x - fMovetornadoWidth && pPosOld->x + fWidth <= Pos.x - fMovetornadoWidth && pPos->z - fHeight < Pos.z + fMovetornadoDepth && pPos->z > Pos.z - fMovetornadoDepth && pPos->y < Pos.y + m_fMovetornadoHeight && pPos->y > Pos.y - m_fMovetornadoHeight)
    {
        bLanding = true;
    }
    // 前側当たり判定
    if (pPos->x - fWidth < Pos.x + fMovetornadoWidth && pPos->x + fWidth > Pos.x - fMovetornadoWidth && pPos->z - fHeight <= Pos.z + fMovetornadoDepth && pPosOld->z - fHeight >= Pos.z + fMovetornadoDepth && pPos->y < Pos.y + m_fMovetornadoHeight && pPos->y > Pos.y - m_fMovetornadoHeight)
    {
        pPos->y = Pos.y + m_fMovetornadoHeight + fHeight;

        bLanding = true;
    }
    // 後側当たり判定
    else if (pPos->x - fWidth < Pos.x + fMovetornadoWidth && pPos->x + fWidth > Pos.x - fMovetornadoWidth && pPos->z >= Pos.z - fMovetornadoDepth && pPosOld->z <= Pos.z - fMovetornadoDepth && pPos->y < Pos.y + m_fMovetornadoHeight && pPos->y > Pos.y - m_fMovetornadoHeight)
    {
        pPos->y = Pos.y + m_fMovetornadoHeight + fHeight;
        bLanding = true;
    }
    // 上側当たり判定
    if (pPos->x - fWidth < Pos.x + fMovetornadoWidth && pPos->x + fWidth > Pos.x - fMovetornadoWidth && pPos->y - fHeight <= Pos.y + m_fMovetornadoHeight && pPosOld->y - fHeight >= Pos.y + m_fMovetornadoHeight && pPos->z < Pos.z + fMovetornadoDepth && pPos->z > Pos.z - fMovetornadoDepth)
    {
        pPos->y = Pos.y + m_fMovetornadoHeight + fHeight;
        m_bTorUpper = true;
    }
    // 下側当たり判定
    else if (pPos->x - fWidth < Pos.x + fMovetornadoWidth && pPos->x + fWidth > Pos.x - fMovetornadoWidth && pPos->y >= Pos.y - m_fMovetornadoHeight && pPosOld->y <= Pos.y - m_fMovetornadoHeight && pPos->z < Pos.z + fMovetornadoDepth && pPos->z > Pos.z - fMovetornadoDepth)
    {
        pPos->y = Pos.y + m_fMovetornadoHeight + fHeight;
        bLanding = true;
    }

    return bLanding;
}
