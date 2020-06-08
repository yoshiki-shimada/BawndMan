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
class CEnemy04 : public CMover {

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
	CEnemy04(float x, float y, float r, int vit, int Atack, int score)
		: CMover(SH->Enemy01List, x, y, r), Vit(vit), nAtack(Atack), Score(score)
	{}


	void* operator new(size_t t) {
		return operator_new(t, SH->Enemy04List);
	}
	void operator delete(void* p) {
		operator_delete(p, SH->Enemy04List);
	}

};

//-------------------------------------------------------------
// 定数
//-------------------------------------------------------------
#define ZENEMY_ANIM_SPEED 5


//=============================================================
// ブルー敵クラス
// 一定間隔で全方向放射弾を飛ばしてくる
//=============================================================
class CZakoEnemy4 : public CEnemy04 {
private:
	float fBulletSpeed;
	int nCount;

public:
	float rad;

	// コンストラクタ
	CZakoEnemy4(float x, float y);


	// 移動、描画
	virtual bool Move();
	virtual void Draw();

	static CEnemy04* New(float x, float y) { return new CZakoEnemy4(x, y); }
};