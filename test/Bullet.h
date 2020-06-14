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
protected:
	// 移動範囲
	static const int MinX = RLWALL_AND_PLAYER, MaxX = SCREEN_WIDTH - MinX;
	static const int MinY = TBWALL_AND_PLAYER, MaxY = SCREEN_WIDTH - MinY;

public:
	int Count;
	int nDefCount;
	int nAtack;

	// コンストラクタ
	CBullet(float x, float y, int Def, int Atack)
		: CMover(SH->BulletList, x, y, BULLET_CHIP_SIZE_HARF), Count(0), nDefCount(Def), nAtack(Atack) {};

	void* operator new(size_t t) {
		return operator_new(t, SH->BulletList);
	}
	void operator delete(void* p) {
		operator_delete(p, SH->BulletList);
	}

};

//=============================================================
// 通常弾クラス
//=============================================================
class CDirBullet : public CBullet {
private:
	//// 壁範囲
	//static const int MinX = RLWALL_AND_PLAYER, MaxX = SCREEN_WIDTH - MinX;
	//static const int MinY = TBWALL_AND_PLAYER, MaxY = SCREEN_WIDTH - MinY;

public:
	// 速度、加速度
	float vx, vy, AX, AY;

	// コンストラクタ
	CDirBullet(float x, float y, float dir, float spd, float accel, int Def, int Atack);

	// 移動、描画
	virtual bool Move();
	virtual void Draw();
};

//=============================================================
// ホーミング弾クラス
//=============================================================
class CHoomBullet : public CBullet
{
private:
	float vx, vy;
	int Timer;
	float rad;

public:
	CHoomBullet(float x, float y, float dir, float spd, int Def, int Atack);

};