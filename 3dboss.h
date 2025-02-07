//=================================================
//
// 3D���f���̃v���C���[�̕\������ (3dplayer.h)
// Author: Sohta Kuki
//
//=================================================

#ifndef _3DBOSS_H_
#define _3DBOSS_H_

#include "object3D.h"
#include "objectX.h"

#define MAX_CHAR (256) //�s�̓ǂݍ��ސ�
#define BOSS_MODEL (9) //���f���̐�
#define MAX_KEYSET (30) // �L�[�̍ő�l
#define MAX_MOTION (15) //���[�V����

static const float BOSS_MOVE_SPD = 0.38f; //�v���C���[�̈ړ����x
static const float BOSS_MOVE_BOOST = 1.3f; //�v���C���[�̈ړ����x�㏸�̔{��


//�I�u�W�F�N�g3D�N���X
class C3dboss : public CModel
{
public:

	//�{�X�̃��[�V����
	typedef enum
	{
		MOTION_NORMAL = 0,
		MOTION_WALK,
		MOTION_ACTION,
		MOTION_JUMP,
		MOTION_LAND,
		MOTION_ACTION2,
		MOTION_DEAD,
		MOTION_ACTION_WIRED,
		MOTION_SP_AIRATK,
		MOTION_ENTRY,
		MOTION_MELEEATK,
		MOTION_TORUPATK,
		MOTION_SHORTMELEEATK,
		MOTION_MAX
	}BOSSMOTION;

	//�{�X�̍U��
	typedef enum
	{
		ACTION_NONE = 0,
		ACTION_DASHATK,
		ACTION_WIREDATK,
		ACTION_UPPERATK,
		ACTION_MELEE,
		ACTION_SPATK,
		ACTION_UP,
		ACTION_DOWN,
		ACTION_TORATK,
		ACTION_SHORTMELEE,
		ACTION_MAX
	}BOSSACTION;

	//�{�X�̗����ʒu
	typedef enum
	{
		POSITION_NOPOS = 0,
		POSTION_LEFT,
		POSTION_RIGHT,
		POSTION_MAX,
	}BOSS_LRPOSTION;

	typedef struct
	{
		char filename[MAX_CHAR];
		int index;
		int parent;
		D3DXVECTOR3 pos;
		D3DXVECTOR3 rot;
	}LoadEnemy;

	//���f���̍\����
	typedef struct
	{

		D3DXMATRIX mtxworld;
		D3DXVECTOR3 pos;
		D3DXVECTOR3 targetPos;
		D3DXVECTOR3 targetRot;
		D3DXVECTOR3 rot;
		LPDIRECT3DTEXTURE9 m_pTexture;
		int nLife;
		bool bUse;
		int nCounterState;
		int nIdxModelParent;	//�e���f���̃C���f�b�N�X

	}ModelPartsEnemy;

	//�L�[�̍\����
	typedef struct {
		D3DXVECTOR3 pos;
		D3DXVECTOR3 rot;
	}Key;

	//�L�[�Z�b�g�̍\����
	typedef struct {
		int Frame;
		Key aKey[BOSS_MODEL];
	}KeySet;

	//���[�V�����̍\����
	typedef struct {
		bool Loop;
		int NumKey;
		KeySet KeySet[MAX_KEYSET];
	}MotionSet;

	typedef enum
	{
		DOUBLE_JUMP = 0,
		FREE_FLY,
		JUMP_TYPE_MAX
	}JUMP_TYPE;

	C3dboss(int nPriority = 20);
	~C3dboss() override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	void ModelMotion();
	//void SetPlayerPos();
	static C3dboss* Create(D3DXVECTOR3 pos);
	//void BindTexture(LPDIRECT3DTEXTURE9 pTex);
	static HRESULT Load();
	static void Unload();
	void BossDamage(int nDamage);
	void LoadPlayerData();
	void PlayerWalkSound();
	static int GetBossLife() { return m_nLife; }
	D3DXVECTOR3& GetBossPos() { return m_nOld3DBossPos; }//���W�̎擾
	static bool GetBossEntry() { return m_bEntry; }
	static D3DXVECTOR3& GetBossPosCamera() { return m_nPos; }//���W�̎擾
	static const int BOSS_LIFE = 520;
	BOSSMOTION Motion;
	void SetPlayerMotion(BOSSMOTION motion);
	bool Collision3DBoss(D3DXVECTOR3* pPos, D3DXVECTOR3* pPosOld, D3DXVECTOR3* pMove, float fWidth, float fBlockHeight);
	static D3DXVECTOR3 GetBossRot() {return m_rot ; }
	static bool GetBossDeathState() { return m_bDeathSwitch; } //���j���ꂽ�ǂ���
private:
	D3DXMATRIX m_mtxworld;
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	static LPDIRECT3DTEXTURE9 m_pTexBuff;
	LPDIRECT3DTEXTURE9 m_pTexture;
	D3DXVECTOR3 m_nOld3DBossPos;
	static D3DXVECTOR3 m_nPos;
	D3DXMATRIX m_mtxWorld;
	LPD3DXMESH m_pMesh[BOSS_MODEL];
	LPD3DXBUFFER m_pBuffMat[BOSS_MODEL];
	DWORD m_nNumMat[BOSS_MODEL];
	//Enemy m_aEnemy;
	LoadEnemy m_aLoadEnemy[BOSS_MODEL];
	ModelPartsEnemy m_aModel[BOSS_MODEL];
	MotionSet MotionSet[MAX_MOTION];
	static D3DVERTEXELEMENT9 m_aElements[MAX_FVF_DECL_SIZE];
	bool bUse;
	FILE* m_pFile;//�t�@�C���|�C���^��錾
	bool m_bWalkSound; //���s�����Ȃ炷���ǂ���
	int m_nJumpCnt; //�W�����v������
	int m_nWalkSoundCnt; //���sSE�̍Đ�����Ԋu
	int m_nMotionCnt; //���[�V������
	int m_nFrameCnt; //���[�V�����̃t���[����
	static int m_nLife; //�v���C���[�̗̑�
	int m_nNextMotion;             // ���̃��[�V����ID
	int m_nJumpAnimTimer;
	int m_nComboNum; //�R���{��
	int m_nFlyTimer; //�󒆕��V����
	int m_nEndTimer; //��\���ɂȂ����ۂ̎��Ԍv��
	bool m_bWalking; //���s�����ǂ���
	bool m_bJumping; //�W�����v�����ǂ���
	bool MotionUse; //���[�V�������g�p���Ă��邩
	bool m_bIsCollision; //�����蔻��
	bool m_bFlying; //�󒆕��V���Ă��邩
	bool m_bDashAtk; //�_�b�V���A�^�b�N�U��
	bool m_bWiredAtk; //���[�ɗ������o���Ă��邩
	bool m_bFlyAtk; //�󒆗����U��
	bool m_bBossUPzone; //�{�X����ɂ��邩�ǂ���
	bool m_bBossDownzone; //�{�X�����ɂ��邩�ǂ���
	bool m_bBossSPATK; //����U�������Ă��邩�ǂ���
	bool m_bDashATKDamage; //�ːi�U���̃_���[�W���󂯂���
	static bool m_bDeathSwitch; //���j���ꂽ�ǂ���
	static bool m_bEntry; //�{�X�̓o�ꂪ�I����Ă邩�ǂ���
	int m_nLRPos; //���E�̂ǂ���ɂ��邩
	float m_fRotSpeed; //��]���x
	int m_nACTIONTimer; //�e�s�����Ƃ̊Ԋu
	int random_number; //�{�X�̍s���ϐ�
	int m_nBossDmgColorTimer; //�_���[�W���̃}�e���A����ς��Ă��鎞��
	bool m_bBossPowerUP; //�{�X�����͂ȍU����łĂ邩�ǂ���
	bool m_bBossDMGState; //�{�X���_���[�W���󂯂Ă��邩
	bool m_bATKCollisonState; //�ߐڍU���̓����蔻����쓮�����邩
	D3DXVECTOR3 m_n3DBossMove;
	static D3DXVECTOR3 m_rot;


};

#endif