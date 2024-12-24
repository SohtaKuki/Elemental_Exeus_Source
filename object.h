//=================================================
//
// �I�u�W�F�N�g�̏��� (object.h)
// Author: Sohta Kuki
//
//=================================================

#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "main.h"
#include "manager.h"

//�I�u�W�F�N�g�N���X
class CObject
{
public:
	typedef struct
	{
		D3DXVECTOR3 pos;
		float rhw;
		D3DCOLOR col;
		D3DXVECTOR2 tex;
	}VERTEX_2D;

	//���_���[3D]�̍\���̂��`
	typedef struct
	{
		D3DXVECTOR3 pos;
		D3DXVECTOR3 nor;
		D3DCOLOR col;
		D3DXVECTOR2 tex;

	}VERTEX_3D;

	typedef enum
	{
		NONE = 0,
		ENEMY, //�G(2DObject�p)
		ENEMY_NORMAL, //�G(3DObject�p �m�[�}��)
		ENEMY_NORMALMOVE, //�G(3DObject�p �m�[�}��)
		ENEMY_FLY, //�G(X���W�ړ�)
		ENEMY_FLYMOVE, //�G(Z���W�ړ�)
		START, //�X�^�[�g�}�[�J�[
		GOAL, //�S�[���}�[�J�[
		PLAYER, //�v���C���[
		BLOCK, //�u���b�N
		BROKENBLOCK, //�j��\�u���b�N
		MOVEBLOCK_X, //�ړ��u���b�N�iX���j
		MOVEBLOCK_X_REV, //�ړ��u���b�N (X�����])
		MOVEBLOCK_Z, //�ړ��u���b�N�iZ���j
		MOVEBLOCK_Z_REV, //�ړ��u���b�N�iZ���j
		WALL_WIDTH, //�� (����)
		WALL_HEIGHT, //�� (�c��)
		WALL_WIDTH_SHORT,//�� (�����V���[�g)
		WALL_HEIGHT_SHORT, //��(�c���V���[�g)
		D2DITEM, //2DObject�p�A�C�e��
		TIMER, //�^�C�}�[
		FADE, //�t�F�[�h
		D2DBULLET, //2D�p�v���C���[�e
		PLAYER_BULLET, //�v���C���[�ʏ�e
		CHBULLET, //�v���C���[����e(�`���[�W�V���b�g)
		TORNADO_ATK, //�g���l�[�h��O���ɏo��
		ENEMY_BULLET, //�G�ʏ�e
		SLASHWIND, //�v���C���[�ߐڍU��
		SLASHWINDENEMY, //�G�ߐڍU��
		SLASHWINDBOSS, //�{�X�ߐڍU��
		ITEM_ADDLIFE, //�A�C�e��(�̗͉�)
		FLOOR, //��
		FLOOR_BG, //��2�w��
		SCORE, //�X�R�A
		PLAYER_EXPLOSION, //�v���C���[����
		ENEMY_EXPLOSION, //�G����
		SLASHTORNADO, //�ݒu�ł��闳��
		BOSS,//�{�X
		BACKGROUND,//�w�i�I�u�W�F�N�g
		SWITCH_BS,//�{�X�p�̓��ꌟ�m�I�u�W�F�N�g
		BOSS_ATKUI, //�{�X�̍U���}�[�J�[
		PLAYER_EXPLOSION_SUB, //�v���C���[�̔���(�T�u)
		ENEMY_EXPLOSION_SUB, //�G�̔���(�T�u)
		PLAYER_EFCT_TORNADO, //�v���C���[�̗����G�t�F�N�g
		ENEMY_EFCT_TORNADO, //�G�̗����G�t�F�N�g
		BOSS_TORNADO, //�{�X�p�̗���
		HIT_EFCT, //�q�b�g���̃G�t�F�N�g
		RANKING, //�����L���O
		MAX_TYPE,
	}TYPE;

	CObject(int nPriority = 3);
	virtual ~CObject();
	virtual HRESULT Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	static void ReleaseAll();
	static void UpdateAll();
	static void DrawAll();
	static const int MAX_OBJECT = 1024;	//�I�u�W�F�N�g�ő吔
	static CObject* GetObj(int nPriority ,int nIdx);
	TYPE GetType() { return m_type; }
	void SetType(TYPE type);
	void Release();
private:
	static CObject* m_apObject[MAX_PRIORITY][MAX_OBJECT];	//�I�u�W�F�N�g�Ǘ�
	TYPE m_type;
	static int m_nNumAll;	//�I�u�W�F�N�g�̑���
	int m_nID;	// �������g��ID
	int m_nPriority;
protected:
};

#endif
