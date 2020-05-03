#pragma once
//-------------------------------------------------------------
#include "Mover.h"

//-------------------------------------------------------------
// �萔
//-------------------------------------------------------------
#define BULLET_ANIM_SPEED 5


//=============================================================
// �e�N���X
//=============================================================
class CBullet : public CMover {

public:
	int Count;

	// �R���X�g���N�^
	CBullet(float x, float y);

	void* operator new(size_t t) {
		return operator_new(t, SH->BulletList);
	}
	void operator delete(void* p) {
		operator_delete(p, SH->BulletList);
	}

	// �ړ��A�`��
	virtual bool Move();
	virtual void Draw();
};

//=============================================================
// �ʏ�e�N���X
//=============================================================
class CDirBullet : public CBullet {

public:
	// ���x�A�����x
	float VX, VY, AX, AY;

	// �R���X�g���N�^
	CDirBullet(float x, float y, float dir, float spd, float accel);

	// �ړ��A�`��
	virtual bool Move();
};