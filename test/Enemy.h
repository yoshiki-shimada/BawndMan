/*******************************************************************
* @file		Enemy.h
* @brief	�G�̃w�b�_�[
* @author	yshimada
* @data		20191221
*******************************************************************/

#pragma once

#include "Mover.h"

/****************
* @brief �G�`��֘A�N���X
****************/
class CEnemy : public CMover {

protected:
	// �^�C�}�[
	int Time;

public:
	// �ϋv�́A�X�R�A
	int Vit;
	float Vx, Vy;
	int Score;
	int nAtack;
	bool NockBackFlag;

	// �R���X�g���N�^
	CEnemy(float x, float y, float r, int vit, int Atack, int score)
		: CMover(SH->EnemyList, x, y, r), Time(0), Vit(vit), nAtack(Atack), Score(score), NockBackFlag(false)
	{}

	void* operator new(size_t t) {
		return operator_new(t, SH->EnemyList);
	}
	void operator delete(void* p) {
		operator_delete(p, SH->EnemyList);
	}
};

//-------------------------------------------------------------
// �萔
//-------------------------------------------------------------
#define ZENEMY_ANIM_SPEED 5

//=============================================================
// ���G�N���X
//=============================================================
class CZakoEnemy1 : public CEnemy {
private:
	float vx, vy;
	float Speed;
	int Count;
	int nNocCount;

public:
	float rad;

	// �R���X�g���N�^
	CZakoEnemy1(float x, float y);

	// �ړ��A�`��
	virtual bool Move();
	virtual void Draw();

	static CEnemy* New(float x, float y) { return new CZakoEnemy1(x, y); }
};


//=============================================================
// �G����
//=============================================================
class CSpownEnemy {
public:
	// �R���X�g���N�^
	CSpownEnemy();
};