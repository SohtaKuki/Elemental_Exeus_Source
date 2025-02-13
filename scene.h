//=================================================
//
// 画面遷移処理 (scene.h)
// Author: Sohta Kuki
//
//=================================================

#ifndef _SCENE_H_
#define _SCENE_H_

#include "main.h"

class CScene
{
public:
	typedef enum
	{
		MODE_TITLE = 0,
		MODE_STAGESELECT,
		MODE_GAME,
		MODE_RESULT,
		MODE_RESULTFAIL,
		MODE_RANKING,
		MODE_MAX,
	}MODE;
	CScene();
	virtual ~CScene();
	virtual HRESULT Init();
	virtual void Uninit();
	virtual void Update();
	virtual void Draw();
	static CScene* Create(MODE mode);
	static bool GetUpdateStat() { return bUpdate; }
	static void UpdateSwitch(int nType);
	static bool GetScreenSwitch() { return m_bScreenSwitch;}
private:
	MODE m_mode;
	static bool bUpdate;
protected:
	int m_nScreenFadeTime;
	static int m_nPlayerRemain;
	static bool m_bScreenSwitch;
};

class CTitle : public CScene
{
public:
	CTitle();
	~CTitle();
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	static bool GetTitleState() {return m_bTitleEnter; }
private:
	static bool m_bTitleEnter;
};

class CStageSelectSc : public CScene
{
public:
	CStageSelectSc();
	~CStageSelectSc();
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
private:
};

class CGame : public CScene
{
public:
	CGame();
	~CGame() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
private:

};



class CResult : public CScene
{
public:
	CResult();
	~CResult();
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
private:
};

class CResultFail : public CScene
{
public:
	CResultFail();
	~CResultFail();
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
private:
};

class CRankingSc : public CScene
{
public:
	CRankingSc();
	~CRankingSc();
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
private:
};


#endif