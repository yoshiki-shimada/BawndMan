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
	//int Time;

public:
	// 耐久力、スコア
	int Vit;
	float Vx, Vy;
	int Score;
	int nAtack;
	bool NockBackFlag;

	// コンストラクタ
	CEnemy(float x, float y, float r, int vit, int Atack, int score)
		: CMover(SH->Enemy01List, x, y, r), Vit(vit), nAtack(Atack), Score(score), NockBackFlag(false)
	{}

	void* operator new(size_t t) {
		return operator_new(t, SH->Enemy01List);
	}
	void operator delete(void* p) {
		operator_delete(p, SH->Enemy01List);
	}

};

//-------------------------------------------------------------
// 定数
//-------------------------------------------------------------
#define ZENEMY_ANIM_SPEED 5
#define SARTH_COUNT 20

//=============================================================
// ブルー敵クラス
// ぶつかってくる
// ノックバックしてデリート
//=============================================================
class CZakoEnemy1 : public CEnemy {
private:
	float vx, vy;
	float Speed;
	int Count;
	int nNocCount;
	float *V1, *V2, Valx, Valy;
	//! 衝突時移動用
	float fatanZ;
	//! 値を返すため
	float V3[2];
	float SV0, SV1, SV2;
	float UVal2;
	float kakuSA;
	float Vxs, Vys;

	void Ref(float Ex, float Ey);
	float *Disperse(float Pvx, float Pvy, float PVal);

public:
	float rad;

	// コンストラクタ
	CZakoEnemy1(float x, float y);

	// 移動、描画
	virtual bool Move();
	virtual void Draw();

	static CEnemy* New(float x, float y) { return new CZakoEnemy1(x, y); }
};
