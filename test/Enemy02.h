/*******************************************************************
* @file		Enemy02.h
* @brief	敵2用.h
* @author	yshimada
* @data		20200107
*******************************************************************/

#pragma once

#include "Mover.h"

/****************
* @brief 敵描画関連クラス
****************/
class CEnemy02 : public CMover {

protected:
	// タイマー
	//int Time;

public:
	// 耐久力、スコア
	int Vit;
	float Vx, Vy;
	int Score;
	int nAtack;

	// コンストラクタ
	CEnemy02(float x, float y, float r, int vit, int Atack, int score)
		: CMover(SH->Enemy02List, x, y, r), Vit(vit), nAtack(Atack), Score(score)
	{}


	void* operator new(size_t t) {
		return operator_new(t, SH->Enemy02List);
	}
	void operator delete(void* p) {
		operator_delete(p, SH->Enemy02List);
	}

};

//-------------------------------------------------------------
// 定数
//-------------------------------------------------------------
#define ZENEMY_ANIM_SPEED 5

//=============================================================
// ブルー敵クラス
// ある程度のスピードの球をねらって打ってくる跳ね返らない
//=============================================================
class CZakoEnemy2 : public CEnemy02 {
private:
	float fBulletSpeed;
	int nCount;

public:
	// 弾角度
	float rad;

	// コンストラクタ
	CZakoEnemy2(float x, float y);

	// 移動、描画
	virtual bool Move();
	virtual void Draw();

	static CEnemy02* New(float x, float y) { return new CZakoEnemy2(x, y); }
};