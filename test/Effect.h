#pragma once
//-------------------------------------------------------------
#include "Mover.h"

//=============================================================
// エフェクトクラス
//=============================================================
class CEffect : public CMover {

public:
	// コンストラクタ
	CEffect(float x, float y)
		: CMover(SH->EffectList, x, y)
	{}

	void* operator new(size_t t) {
		return operator_new(t, SH->EffectList);
	}
	void operator delete(void* p) {
		operator_delete(p, SH->EffectList);
	}
};

//-------------------------------------------------------------
// 定数
//-------------------------------------------------------------
#define CRASH_ANIM_SPEED 5

//=============================================================
// 爆発クラス（自機）
//=============================================================
class CPlayerCrash : public CEffect {

protected:
	// タイマー
	int Time;
	int Count;

public:
	// コンストラクタ
	CPlayerCrash(float x, float y);

	// 移動、描画
	virtual bool Move();
	virtual void Draw();
};

//=============================================================
// 爆発クラス（敵）
//=============================================================
class CEnemyCrash : public CEffect {

protected:
	// タイマー
	int Time;
	int Count;

public:
	// コンストラクタ
	CEnemyCrash(float x, float y);

	// 移動、描画
	virtual bool Move();
	virtual void Draw();
};

//=============================================================
// ポータル変化クラス
//=============================================================
class CPortalEffect : public CEffect {

protected:
	// タイマー
	int Time;
	int Count;

public:
	// コンストラクタ
	CPortalEffect(float x, float y);

	// 移動、描画
	virtual bool Move();
	virtual void Draw();
};