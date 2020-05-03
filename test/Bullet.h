#pragma once
//-------------------------------------------------------------
#include "Mover.h"

//-------------------------------------------------------------
// 定数
//-------------------------------------------------------------
#define BULLET_ANIM_SPEED 5


//=============================================================
// 弾クラス
//=============================================================
class CBullet : public CMover {

public:
	int Count;

	// コンストラクタ
	CBullet(float x, float y);

	void* operator new(size_t t) {
		return operator_new(t, SH->BulletList);
	}
	void operator delete(void* p) {
		operator_delete(p, SH->BulletList);
	}

	// 移動、描画
	virtual bool Move();
	virtual void Draw();
};

//=============================================================
// 通常弾クラス
//=============================================================
class CDirBullet : public CBullet {

public:
	// 速度、加速度
	float VX, VY, AX, AY;

	// コンストラクタ
	CDirBullet(float x, float y, float dir, float spd, float accel);

	// 移動、描画
	virtual bool Move();
};