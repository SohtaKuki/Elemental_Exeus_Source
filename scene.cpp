//=================================================
//
// ��ʑJ�ڏ��� (scene.cpp)
// Author: Sohta Kuki
//
//=================================================

#include "scene.h"
#include "objbg.h"
#include "stagemanager.h"
#include "floor.h"
#include "timer.h"
#include "playerhpbar.h"
#include "result.h"
#include "object2D.h"
#include "result.h"
#include "titlebg.h"
#include "gameui.h"
#include "score.h"
#include "resultscore.h"
#include "3dbuffui.h"
#include "scorewindow.h"
#include "playerwindow.h"
#include "blizardfloor.h"
#include "stageselect.h"
#include "pause.h"
#include "startcallui.h"
#include "endcallui.h"
#include "tutorialui.h"
#include "stageselectbg.h"
#include "3dparticle.h"
#include "3dgoalobj.h"
#include "3dmeshfield.h"
#include "billboard.h"
#include "3dboss.h"
#include "3dbackground.h"
#include "3dcirclemesh.h"
#include "bossui.h"
#include "sound.h"
#include "3dboss_switch.h"
#include "bosscallui.h"
#include "letterbox.h"
#include "bossname_entry.h"
#include "bossatk_UI.h"
#include "3dbossatk_ui.h"
#include "3dbossatk_ui_diag.h"
#include "3dtutorialui.h"
#include "3dfireeffect.h"
#include "result_bonusHPscore.h"
#include "result_TimebonusScore.h"
#include "ranking.h"
#include "result_rank.h"

bool CScene::bUpdate = {};
bool CScene::m_bScreenSwitch = false;

//======================
//�R���X�g���N�^
//======================
CScene::CScene()
{
	m_nScreenFadeTime = 0;
	m_bScreenSwitch = false;
}

//======================
//�f�X�g���N�^
//======================
CScene::~CScene()
{

}

//======================
//����������
//======================
HRESULT CScene::Init()
{
	bUpdate = true; //�Q�[�����X�V��L���ɂ��邩�ǂ���
	return S_OK;
}

//======================
//�I������
//======================
void CScene::Uninit()
{

	CObject::ReleaseAll();
}

//======================
//�X�V����
//======================
void CScene::Update()
{

}

//======================
//�`�揈��
//======================
void CScene::Draw()
{

}

//======================
// �I�u�W�F�N�g��������
//======================
CScene* CScene::Create(MODE mode)
{
	CScene* Scene = nullptr;

	switch (mode)
	{
	case MODE_TITLE:
		Scene = new CTitle();
		break;
	case MODE_STAGESELECT:
		Scene = new CStageSelectSc();
		break;
	case MODE_GAME:
		Scene = new CGame;
		break;
	case MODE_RESULT:
		Scene = new CResult;
		break;
	case MODE_RESULTFAIL:
		Scene = new CResultFail;
		break;
	case MODE_RANKING:
		Scene = new CRankingSc;
		break;
	default:
		break;

	}

	//�V�[���̏�����
	if (Scene != nullptr)
	{
		Scene->Init();

		return Scene;
	}


	return nullptr;
}

//=====================================
// �ꕔ�I�u�W�F�N�g�̍X�V�����邩�ǂ���
//=====================================
void CScene::UpdateSwitch(int nType)
{
	if (nType == 0)
	{
		bUpdate = false;
	}

	if (nType == 1)
	{
		bUpdate = true;
	}
}

//======================
//�R���X�g���N�^
//======================
CGame::CGame()
{

}

//======================
//�f�X�g���N�^
//======================
CGame::~CGame()
{

}

//======================
//����������
//======================
HRESULT CGame::Init()
{
	CScene::Init();
	CScore::Create(D3DXVECTOR3(1065.0f, 48.0f, 0.0f), D3DXVECTOR3(33.0f, 33.0f, 0.0f));
	CPlayerHpBar::Create(D3DXVECTOR3(85.0f, 679.4f, 0.0f), D3DXVECTOR3(-104.0f, -35.8f, 0.0f),(0));

	CPlayerHpBar::Create(D3DXVECTOR3(85.0f, 719.0f, 0.0f), D3DXVECTOR3(-54.0f, -35.8f, 0.0f), (2));

	CTimer::Create(D3DXVECTOR3(500.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//�X�e�[�W���Ƃɐ������鏈����ς���
	if (C3dgoalobj::GetStageNum() == 0)
	{
		CStartCallUI::Create(D3DXVECTOR3(640.0f, 160.0f, 0.0f), D3DXVECTOR3(180.0f, 150.0f, 0));
		CStageManager::Create(0);
		CBillboard::Create(D3DXVECTOR3(-200.0f, -170.0f, 7150.0f), D3DXVECTOR3(600.0f, 300.0f, 0.0f));
		CBillboard::Create(D3DXVECTOR3(1600.0f, -100.0f, 7150.0f), D3DXVECTOR3(600.0f, 300.0f, 0.0f));
		C3dbackground::Create(D3DXVECTOR3(-1000.0f, 620.0f, 1000.0f), 0);
		C3dbackground::Create(D3DXVECTOR3(-1000.0f, 620.0f, 1800.0f), 0);
		C3dbackground::Create(D3DXVECTOR3(-1000.0f, 620.0f, 2600.0f), 0);
		C3dbackground::Create(D3DXVECTOR3(-1000.0f, 620.0f, 3400.0f), 0);

		C3dbackground::Create(D3DXVECTOR3(-5000.0f, 500.0f, 4000.0f), 3);
		C3dbackground::Create(D3DXVECTOR3(-2500.0f, 500.0f, 4000.0f), 3);
		C3dbackground::Create(D3DXVECTOR3(0.0f, 500.0f, 4000.0f), 3);

		C3dbackground::Create(D3DXVECTOR3(2500.0f, 500.0f, 4000.0f), 3);
		C3dbackground::Create(D3DXVECTOR3(5000.0f, 500.0f, 4000.0f), 3);

		C3dbackground::Create(D3DXVECTOR3(-5000.0f, 2000.0f, 4000.0f), 3);
		C3dbackground::Create(D3DXVECTOR3(-2500.0f, 2000.0f, 4000.0f), 3);
		C3dbackground::Create(D3DXVECTOR3(0.0f, 2000.0f, 4000.0f), 3);
		C3dbackground::Create(D3DXVECTOR3(2500.0f, 2000.0f, 4000.0f), 3);
		C3dbackground::Create(D3DXVECTOR3(5000.0f, 2000.0f, 4000.0f), 3);

		C3dTutorialUI::Create(D3DXVECTOR3(-100.0f, 100.0f, 300.0f), D3DXVECTOR3(100.0f, 100.0f, 0),0);
		C3dTutorialUI::Create(D3DXVECTOR3(150.0f, 100.0f, 300.0f), D3DXVECTOR3(100.0f, 80.0f, 0),1);
		C3dTutorialUI::Create(D3DXVECTOR3(450.0f, 150.0f, 300.0f), D3DXVECTOR3(120.0f, 140.0f, 0), 2);
		C3dTutorialUI::Create(D3DXVECTOR3(700.0f, 100.0f, 300.0f), D3DXVECTOR3(100.0f, 80.0f, 0), 3);
		C3dTutorialUI::Create(D3DXVECTOR3(900.0f, 100.0f, 300.0f), D3DXVECTOR3(100.0f, 80.0f, 0), 4);
		CScoreWindow::Create(D3DXVECTOR3(1100.0f, -20.0f, 0.0f), D3DXVECTOR3(180.0f, 180.0f, 0.0f));
		CEndCallUI::Create(D3DXVECTOR3(640.0f, -100.0f, 0.0f), D3DXVECTOR3(180.0f, 150.0f, 0));

		CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_BGM_STAGE_1);
	}

	//1�X�e�[�W�ڂ̏ꍇ
	if (C3dgoalobj::GetStageNum() == 1)
	{
		CStageManager::Create(1);
		C3dbackground::Create(D3DXVECTOR3(-1000.0f, 620.0f, 1000.0f),1);
		C3dbackground::Create(D3DXVECTOR3(-1000.0f, 620.0f, 1800.0f),1);
		C3dbackground::Create(D3DXVECTOR3(-1000.0f, 620.0f, 2600.0f),1);
		C3dbackground::Create(D3DXVECTOR3(-1000.0f, 620.0f, 3400.0f),1);

		C3dbackground::Create(D3DXVECTOR3(-5000.0f, 500.0f, 4000.0f), 3);
		C3dbackground::Create(D3DXVECTOR3(-2500.0f, 500.0f, 4000.0f), 3);
		C3dbackground::Create(D3DXVECTOR3(0.0f, 500.0f, 4000.0f), 3);
		C3dbackground::Create(D3DXVECTOR3(2500.0f, 500.0f, 4000.0f), 3);
		C3dbackground::Create(D3DXVECTOR3(5000.0f, 500.0f, 4000.0f), 3);

		C3dbackground::Create(D3DXVECTOR3(-5000.0f, 2000.0f, 4000.0f), 3);
		C3dbackground::Create(D3DXVECTOR3(-2500.0f, 2000.0f, 4000.0f), 3);
		C3dbackground::Create(D3DXVECTOR3(0.0f, 2000.0f, 4000.0f), 3);
		C3dbackground::Create(D3DXVECTOR3(2500.0f, 2000.0f, 4000.0f), 3);
		C3dbackground::Create(D3DXVECTOR3(5000.0f, 2000.0f, 4000.0f), 3);
		CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_BGM_STAGE_2);
		CEndCallUI::Create(D3DXVECTOR3(640.0f, -100.0f, 0.0f), D3DXVECTOR3(180.0f, 150.0f, 0));
		CScoreWindow::Create(D3DXVECTOR3(1100.0f, -20.0f, 0.0f), D3DXVECTOR3(180.0f, 180.0f, 0.0f));
	}

	//2�X�e�[�W�ڂ̏ꍇ
	if (C3dgoalobj::GetStageNum() == 2)
	{

		C3dboss::Create(D3DXVECTOR3(450.0f, 300.0f, 0.0f));
		CStageManager::Create(2);

		CBossCallUI::Create(D3DXVECTOR3(640.0f, -253.0f, 0.0f), D3DXVECTOR3(180.0f, 80.0f, 0));
		CPlayerHpBar::Create(D3DXVECTOR3(574.0f, 692.0f, 0.0f), D3DXVECTOR3(-25.0f, -17.0f, 0.0f), (1));

		CBossEntryUI::Create(D3DXVECTOR3(640.0f, 700.0f, 0.0f), D3DXVECTOR3(420.0f, 340.0f, 0));
		CLetterbox::Create(D3DXVECTOR3(640.0f, -250.0f, 0.0f), D3DXVECTOR3(180.0f, 70.0f, 0));
		C3dbackground::Create(D3DXVECTOR3(-700.0f, 340.0f, 1800.0f), 2);
		C3dbackground::Create(D3DXVECTOR3(400.0f, 340.0f, 1800.0f), 2);
		C3dbackground::Create(D3DXVECTOR3(1400.0f, 340.0f, 1800.0f), 2);
		C3dfireeffect::Create(D3DXVECTOR3(-130.0f, 365.0f, -50.0f), D3DXVECTOR3(75.0f, 95.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
		C3dfireeffect::Create(D3DXVECTOR3(285.0f, 365.0f, -50.0f), D3DXVECTOR3(75.0f, 95.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);
		C3dfireeffect::Create(D3DXVECTOR3(665.0f, 365.0f, -50.0f), D3DXVECTOR3(75.0f, 95.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);


		CBossui::Create(D3DXVECTOR3(824.0f, 625.0f, 0.0f), D3DXVECTOR3(390.0f, 90.0f, 0.0f));
		
		CEndCallUI::Create(D3DXVECTOR3(640.0f, -100.0f, 0.0f), D3DXVECTOR3(180.0f, 150.0f, 0));
		C3dBossATKUIDiag::Create(D3DXVECTOR3(0.0f, 0.0f, 50.0f), D3DXVECTOR3(0.0f, 0.0f, 0));

		C3dBossATKUI::Create(D3DXVECTOR3(0.0f, 0.0f, 50.0f), D3DXVECTOR3(0.0f, 0.0f, 0));
	}

	CPlayerWindow::Create(D3DXVECTOR3(185.0f, 585.0f, 0.0f), D3DXVECTOR3(210.0f, 150.0f, 0.0f));

	CMeshField::Create(D3DXVECTOR3(50.0f, 3000.0f, 200.0f));

	CPauseSelect::Create();



	return S_OK;
}

//======================
//�I������
//======================
void CGame::Uninit()
{
	CScene::Uninit();
	CManager::GetSound()->Stop();
}

//======================
//�X�V����
//======================
void CGame::Update()
{
	//�|�[�Y��ʂɂăQ�[����ʂɖ߂�ꍇ
	if (CManager::GetKeyboard()->GetTrigger(DIK_RETURN) && CPauseSelect::GetPauseSelect() == 0 || CManager::GetJoypad()->GetTrigger(CInputJoypad::JOYKEY_A) && CPauseSelect::GetPauseSelect() == 0)
	{
		CPauseSelect::bUseSwitch(0);
	}

	//�|�[�Y��ʂɂăX�e�[�W�Z���N�g�ɖ߂�ꍇ
	else if (CManager::GetKeyboard()->GetTrigger(DIK_RETURN) && CPauseSelect::GetPauseSelect() == 1 || CManager::GetJoypad()->GetTrigger(CInputJoypad::JOYKEY_A) && CPauseSelect::GetPauseSelect() == 1 )
	{
		CManager::GetFade()->SetFade(CScene::MODE_GAME);
		CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_SE_DECIDE);
	}

	//�|�[�Y��ʂɂă^�C�g����ʂɖ߂�ꍇ
	else if (CManager::GetKeyboard()->GetTrigger(DIK_RETURN) && CPauseSelect::GetPauseSelect() == 2 || CManager::GetJoypad()->GetTrigger(CInputJoypad::JOYKEY_A) && CPauseSelect::GetPauseSelect() == 2 && CPauseSelect::GetbUseStat() == true)
	{
		CManager::GetFade()->SetFade(CScene::MODE_TITLE);
		CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_SE_DECIDE);
	}
}

//======================
//�`�揈��
//======================
void CGame::Draw()
{

}

//======================
//�R���X�g���N�^
//======================
CResult::CResult()
{

}

//======================
//�f�X�g���N�^
//======================
CResult::~CResult()
{

}

//======================
//����������
//======================
HRESULT CResult::Init()
{
	CResultBG::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f),0);
	CResultScore::Create(D3DXVECTOR3(150.0f, 400.0f, 0.0f), D3DXVECTOR3(100.0f, 100.0f, 0.0f));
	CResultHPBScore::Create(D3DXVECTOR3(450.0f, 200.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f));
	CResultTIMEBScore::Create(D3DXVECTOR3(450.0f, 250.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f));
	CResultRank::Create(D3DXVECTOR3(1050.0f, 250.0f, 0.0f), D3DXVECTOR3(120.0f, 240.0f, 0.0f));
	CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_BGM_RESULT);

	return S_OK;
}

//======================
//�I������
//======================
void CResult::Uninit()
{
	
	CScene::Uninit();
}

//======================
//�X�V����
//======================
void CResult::Update()
{

	//�G���^�[�L�[�������ꂽ�Ƃ�
	if (CManager::GetKeyboard()->GetTrigger(DIK_P) || CManager::GetJoypad()->GetTrigger(CInputJoypad::JOYKEY_RB))
	{
		CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_SE_DECIDE);
		CManager::GetFade()->SetFade(CScene::MODE_GAME);
		CManager::GetSound()->Stop(CSound::SOUND_LABEL_BGM_RESULT);
	}

	//�G���^�[�L�[�������ꂽ�Ƃ�
	if (CManager::GetKeyboard()->GetTrigger(DIK_RETURN) || CManager::GetJoypad()->GetTrigger(CInputJoypad::JOYKEY_A))
	{
		CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_SE_DECIDE);
		CManager::GetFade()->SetFade(CScene::MODE_RANKING);
		CManager::GetSound()->Stop(CSound::SOUND_LABEL_BGM_RESULT);
	}
}

//======================
//�`�揈��
//======================
void CResult::Draw()
{

}

//======================
//�R���X�g���N�^
//======================
CTitle::CTitle()
{

}

//======================
//�f�X�g���N�^
//======================
CTitle::~CTitle()
{

}

//======================
//����������
//======================
HRESULT CTitle::Init()
{
	CTitleBG::Create();
	//CObjectBG::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));

	return S_OK;
}

//======================
//�I������
//======================
void CTitle::Uninit()
{
	CManager::GetSound()->Stop(CSound::SOUND_LABEL_BGM);
	CScene::Uninit();
}

//======================
//�X�V����
//======================
void CTitle::Update()
{
	if (CManager::GetKeyboard()->GetTrigger(DIK_RETURN) || CManager::GetJoypad()->GetTrigger(CInputJoypad::JOYKEY_A))
	{
		if (m_bScreenSwitch == false)
		{
			CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_SE_STARTBTN);
			m_bScreenSwitch = true;
		}
	}

	if (m_bScreenSwitch == true)
	{
		m_nScreenFadeTime++;
	}

	if (m_nScreenFadeTime == 60)
	{
		CManager::GetFade()->SetFade(CScene::MODE_GAME);
		m_bScreenSwitch = false;
		m_nScreenFadeTime = 0;
	}

}

//======================
//�`�揈��
//======================
void CTitle::Draw()
{

}

//======================
//�R���X�g���N�^
//======================
CStageSelectSc::CStageSelectSc()
{

}

//======================
//�f�X�g���N�^
//======================
CStageSelectSc::~CStageSelectSc()
{

}

//======================
//����������
//======================
HRESULT CStageSelectSc::Init()
{
	CStageSelectBG::Create();
	CStageSelect::Create();

	return S_OK;
}

//======================
//�I������
//======================
void CStageSelectSc::Uninit()
{

	CScene::Uninit();
}

//======================
//�X�V����
//======================
void CStageSelectSc::Update()
{

	if (CManager::GetKeyboard()->GetTrigger(DIK_BACKSPACE) || CManager::GetJoypad()->GetTrigger(CInputJoypad::JOYKEY_B))
	{
		CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_SE_STARTBTN);
		CManager::GetFade()->SetFade(CScene::MODE_TITLE);
	}

	//�G���^�[�L�[�������ꂽ�Ƃ�
	if (CManager::GetKeyboard()->GetTrigger(DIK_RETURN) || CManager::GetJoypad()->GetTrigger(CInputJoypad::JOYKEY_A))
	{
		CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_SE_DECIDE);

		CManager::GetSound()->Stop(CSound::SOUND_LABEL_BGM_STAGE_SELECT);
		CManager::GetFade()->SetFade(CScene::MODE_GAME);

	}
}

//======================
//�`�揈��
//======================
void CStageSelectSc::Draw()
{

}

//======================
//�R���X�g���N�^
//======================
CResultFail::CResultFail()
{

}

//======================
//�f�X�g���N�^
//======================
CResultFail::~CResultFail()
{

}

//======================
//����������
//======================
HRESULT CResultFail::Init()
{
	CMeshField::Create(D3DXVECTOR3(50.0f, 3000.0f, 200.0f));
	CResultBG::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f), 1);
	CResultScore::Create(D3DXVECTOR3(150.0f, 400.0f, 0.0f), D3DXVECTOR3(100.0f, 100.0f, 0.0f));

	return S_OK;
}

//======================
//�I������
//======================
void CResultFail::Uninit()
{
	CScene::Uninit();
}

//======================
//�X�V����
//======================
void CResultFail::Update()
{


	//�G���^�[�L�[�������ꂽ�Ƃ�
	if (CManager::GetKeyboard()->GetTrigger(DIK_RETURN) || CManager::GetJoypad()->GetTrigger(CInputJoypad::JOYKEY_A))
	{
		CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_SE_DECIDE);

		CManager::GetSound()->Stop(CSound::SOUND_LABEL_BGM_STAGE_SELECT);
		CManager::GetFade()->SetFade(CScene::MODE_TITLE);

	}
}

//======================
//�`�揈��
//======================
void CResultFail::Draw()
{

}

//======================
//�R���X�g���N�^
//======================
CRankingSc::CRankingSc()
{

}

//======================
//�f�X�g���N�^
//======================
CRankingSc::~CRankingSc()
{

}

//======================
//����������
//======================
HRESULT CRankingSc::Init()
{
	CMeshField::Create(D3DXVECTOR3(50.0f, 3000.0f, 200.0f));
	CRanking::Create();
	CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_BGM_RANKING);

	return S_OK;
}

//======================
//�I������
//======================
void CRankingSc::Uninit()
{

	CScene::Uninit();
}

//======================
//�X�V����
//======================
void CRankingSc::Update()
{

	//�G���^�[�L�[�������ꂽ�Ƃ�
	if (CManager::GetKeyboard()->GetTrigger(DIK_RETURN) || CManager::GetJoypad()->GetTrigger(CInputJoypad::JOYKEY_A))
	{
		CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_SE_DECIDE);
		CManager::GetFade()->SetFade(CScene::MODE_TITLE);
		CManager::GetSound()->Stop(CSound::SOUND_LABEL_BGM_RANKING);
	}
}

//======================
//�`�揈��
//======================
void CRankingSc::Draw()
{

}

