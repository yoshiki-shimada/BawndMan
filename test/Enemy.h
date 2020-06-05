/*******************************************************************
* @file		Enemy.h
* @brief	敵のヘッダー
* @author	yshimada
* @data		20191221
*******************************************************************/

#pragma once

#include "Mover.h"

/****************
* @brief 敵描画関連クラス
****************/
class CEnemy : public CMover {

protected:
	// タイマー
	int Time;

public:
	// 耐久力、スコア
	int Vit;
	float Vx, Vy;
	int Score;
	int nAtack;
	bool NockBackFlag;

	// コンストラクタ
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
// 定数
//-------------------------------------------------------------
#define ZENEMY_ANIM_SPEED 5

//=============================================================
// 小敵クラス
//=============================================================
class CZakoEnemy1 : public CEnemy {
private:
	float vx, vy;
	float Speed;
	int Count;
	int nNocCount;

public:
	float rad;

	// コンストラクタ
	CZakoEnemy1(float x, float y);

	// 移動、描画
	virtual bool Move();
	virtual void Draw();

	static CEnemy* New(float x, float y) { return new CZakoEnemy1(x, y); }
};


//=============================================================
// 敵生成
//=============================================================
class CSpownEnemy {
public:
	// コンストラクタ
	CSpownEnemy();
};