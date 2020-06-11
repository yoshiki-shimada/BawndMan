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
class CEnemy03 : public CMover {

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
	CEnemy03(float x, float y, float r, int vit, int Atack, int score)
		: CMover(SH->Enemy03List, x, y, r), Vit(vit), nAtack(Atack), Score(score)
	{}

	void* operator new(size_t t) {
		return operator_new(t, SH->Enemy03List);
	}
	void operator delete(void* p) {
		operator_delete(p, SH->Enemy03List);
	}


};

//-------------------------------------------------------------
// 定数
//-------------------------------------------------------------
#define ZENEMY_ANIM_SPEED 5

//=============================================================
// ブルー敵クラス
// スピードのある球を一定間隔で狙って打ってくる、タンクと同じように一度跳ね返る球
//=============================================================
class CZakoEnemy3 : public CEnemy03 {
private:
	float fBulletSpeed;
	int nCount;

public:
	float rad;

	// コンストラクタ
	CZakoEnemy3(float x, float y);


	
	// 移動、描画
	virtual bool Move();
	virtual void Draw();

	static CEnemy03* New(float x, float y) { return new CZakoEnemy3(x, y); }
};

