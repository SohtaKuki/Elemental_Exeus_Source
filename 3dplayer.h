//=================================================
//
// 3D���f���̃v���C���[�̕\������ (3dplayer.h)
// Author: Sohta Kuki
//
//=================================================

#ifndef _3DPLAYER_H_
#define _3DPLAYER_H_

#include "object3D.h"
#include "objectX.h"

#define MAX_CHAR (256) //�s�̓ǂݍ��ސ�
#define PLAYER_MODEL (15) //���f���̐�
#define MAX_KEYSET (20) // �L�[�̍ő�l
#define MAX_MOTION (20) //���[�V����

static const float PLAYER_MOVE_SPD = 0.4f; //�v���C���[�̈ړ����x
static const float PLAYER_MOVE_BOOST = 1.3f; //�v���C���[�̈ړ����x�㏸�̔{��


//�I�u�W�F�N�g3D�N���X
class C3dplayer : public CModel
{
public:

	typedef enum
	{
		MOTION_NORMAL = 0,
		MOTION_WALK,
		MOTION_ACTION,
		MOTION_JUMP,
		MOTION_LAND,
		MOTION_ACTION2,
		MOTION_ACTION3,
		MOTION_TORNADO,
		MOTION_MAX
	}PLAYERMOTION;

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
		Key aKey[PLAYER_MODEL];
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

	C3dplayer(int nPriority = 3);
	~C3dplayer() override;
	HRESULT Init()override;
	void Uninit()override;
	void Update()override;
	void Draw()override;
	void ModelMotion();
	//void SetPlayerPos();
	static C3dplayer* Create(D3DXVECTOR3 pos);
	//void BindTexture(LPDIRECT3DTEXTURE9 pTex);
	static HRESULT Load();
	static void Unload();
	void PlayerDamage(int nDamage);
	void LoadPlayerData();
	void PlayerWalkSound();
	static int GetPlayerLife() {return m_nLife ; }
	static int GetTorNum() { return m_nDisplayTorNum; }
	D3DXVECTOR3& GetPlayerPos() { return m_nOld3DPlayerPos; }//���W�̎擾
	static D3DXVECTOR3& GetPlayerRot() { return m_rot; }//���W�̎擾
	static bool GetShotButtonPreesed() { return m_bAButtonPressed; }//�ˌ��{�^���̉�����Ԃ��擾
	static const int PLAYER_LIFE = 48;
	static const int JUMP_TIMER = 7;
	PLAYERMOTION Motion;
	void SetPlayerMotion(PLAYERMOTION motion);
private:
	D3DXMATRIX m_mtxworld;
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	static LPDIRECT3DTEXTURE9 m_pTexBuff;
	LPDIRECT3DTEXTURE9 m_pTexture;
	D3DXVECTOR3 m_nOld3DPlayerPos;
	D3DXVECTOR3 m_nSize;
	D3DXMATRIX m_mtxWorld;
	LPD3DXMESH m_pMesh[PLAYER_MODEL];
	LPD3DXBUFFER m_pBuffMat[PLAYER_MODEL];
	DWORD m_nNumMat[PLAYER_MODEL];
	static D3DVERTEXELEMENT9 m_aElements[MAX_FVF_DECL_SIZE];
	//Enemy m_aEnemy;
	LoadEnemy m_aLoadEnemy[PLAYER_MODEL];
	ModelPartsEnemy m_aModel[PLAYER_MODEL];
	MotionSet MotionSet[MAX_MOTION];
	bool bUse;
	DWORD m_bAButtonPressStartTime; //�{�^��������������
	static bool m_bAButtonPressed; //�{�^�������������ǂ���(����������)
	FILE* m_pFile;//�t�@�C���|�C���^��錾
	bool m_bPlayerBuff; //�v���C���[�̃o�t���t�^����Ă��邩
	bool m_bInstantShot; //�`���[�W�V���b�g���L�����ǂ���
	bool m_bWalkSound; //���s�����Ȃ炷���ǂ���
	bool m_bSuperJump; //��W�����v���\���ǂ���
	int m_nBuffTime; //�v���C���[�̃o�t�t�^����
	int m_nInstantShotTime; //�`���[�W�V���b�g��ł�������
	int m_nJumpCnt; //�W�����v������
	int m_nWalkSoundCnt; //���sSE�̍Đ�����Ԋu
	int m_nAtkCombo; //�U���{�^������������
	int m_nAirStepTimer;
	float m_fAtkTimer; //�R���{�U���̃^�C�}�[
	int m_nFreeFlyTimer; //�󒆕��V�̃^�C�}�[
	int m_nJumpType; //�W�����v���
	int m_nMotionCnt; //���[�V������
	int m_nFrameCnt; //���[�V�����̃t���[����
	static int m_nLife; //�v���C���[�̗̑�
	bool MotionUse; //���[�V�������g�p���Ă��邩
	bool m_bIsCollision;
	bool m_bIsTorCollision;
	bool m_bAirStep;
	int m_nNextMotion;             // ���̃��[�V����ID
	int m_nJumpAnimTimer;
	bool m_bWalking; //���s�����ǂ���
	bool m_bJumping; //�W�����v�����ǂ���
	bool m_bTorColision;
	bool m_bUse[PLAYER_MODEL];
	int m_nComboNum; //�R���{��
	bool m_bTorUPPER;
	int m_nJumpTimer; //�W�����v���̎���
	static int m_nDisplayTorNum;

protected:
	D3DXVECTOR3 m_n3DPlayerMove;
	static D3DXVECTOR3 m_rot;

};

#endif