//================================
//
// �����L���O���� (ranking.h)
// Author: Sohta Kuki
//
//================================

#ifndef _RANKING_H_
#define _RANKING_H_

#include "object.h"
#include "object2D.h"

//�}�N����`
#define MAX_RANK (5)//�\�����鏇�ʐ� (�X�R�A����)
#define MAX_RANKINGBG (2)//�����L���O��ʂ̔w�i
#define SCORE_NUM_SPACE (70) //�X�R�A�����Ԋu
#define SCORE_NUM_SCALEX (45) //�X�R�A�����傫�� X
#define SCORE_NUM_SCALEY (40) //�X�R�A�����傫�� Y
#define MAX_SCORE (30)//�X�R�A�̍ő�\����

class CRanking :public CObject2D
{
public:

	//�����L���O�X�R�A�\����
	typedef struct
	{
		D3DXVECTOR3 pos;
		int nScore;
	}RankScore;

	//�v���g�^�C�v�錾
	CRanking(int nPriority = 10);
	~CRanking();
	HRESULT Init(void)override;
	void Uninit(void)override;
	void Update(void)override;
	void Draw(void)override;
	void ResetRanking(void);
	void SetRanking(int nScore);
	void WriteRankingData(void);
	void SetRankingPos(D3DXVECTOR3 pos, int rank);
	static CRanking* Create();
private:
	LPDIRECT3DTEXTURE9 m_pTextureRanking[MAX_RANKINGBG] = {};
	LPDIRECT3DTEXTURE9 m_pTextureRankingscore = NULL;
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffRanking = NULL;
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffRankingscore = NULL;
	RankScore m_aRankScore[MAX_RANK];
	int m_nRankingTimer;//�����L���O��ʕ\���p�^�C�}�[
	int m_nRankUpdate = -1;
	int m_nCounterRankingState = 0;//��ԊǗ��J�E���^�[
	int m_aPosTexU[MAX_RANK][8];
};

#endif