#pragma once
//-------------------------------------------------------------
#include "RemTask.h"
#include <math.h>

//=============================================================
// 移動物体クラス
// 丸型当たり判定
//=============================================================
class CMover : public CRemTask {

public:
	// 座標
	float X, Y;

	// 当たり判定の半径
	float R;
	// 当たり判定の
	float W, H;

	//! 丸用コンストラクタ
	//! コンストラクタ（当たり判定を指定する）
	CMover(
		CRemTaskList* task_list,
		float x, float y, float r
	)
		: CRemTask(task_list), X(x), Y(y), R(r)
	{}
	//! コンストラクタ（当たり判定を指定しない）
	CMover(CRemTaskList* task_list, float x, float y)
		: CRemTask(task_list), X(x), Y(y), R(0)
	{}

	//! 四角用コンストラクタ
	//! 面倒なので指定しないものは作らない
	CMover(
		CRemTaskList* task_list,
		float x, float y,
		float w, float h
	)
		: CRemTask(task_list), X(x), Y(y), W(w), H(h)
	{}


	// 移動、描画
	virtual bool Move() { return true; }
	virtual void Draw() {}

	// 壁の判定処理都思ったけど一つにそれ以上の当たり判定が多すぎるので使わん
	bool Out(float size) {
		return (
			X < (0 - size) || X >(SCREEN_WIDTH + size) ||
			Y < (0 - size) || Y >(SCREEN_HEIGHT + size)
			);
	}

	//! 丸の当たり判定
	bool CCHit(CMover* m) {
		return(powf(X - m->X, 2) + powf(Y - m->Y, 2) <= powf(R + m->R, 2));
	}
	//! 自分のWHの指定をする場合（大きさが変わる時に書くべき）

	//! 四角の当たり判定
	bool CSHit(CMover* m) {
		return (
			(X - W) < (m->X + m->W) && (X + W) > (m->X - m->W) &&
			(Y - H) < (m->Y + m->H) && (Y + H) > (m->Y - m->H)
			);
	}
	//! 自分のWHの指定をする,当る対象が回転しているものがある時
	bool CSHit(CMover* m,float fRad, float w, float h) {
		//! 90度回転している場合
		if (fRad == PI_HARF) {
			return (
				(X - w) < (m->X + m->H) && (X + w) > (m->X - m->H) &&
				(Y - h) < (m->Y + m->W) && (Y + h) > (m->Y - m->W)
				);
		}
		//! 通常角度
		else {
			return (
				(X - w) < (m->X + m->W) && (X + w) > (m->X - m->W) &&
				(Y - h) < (m->Y + m->H) && (Y + h) > (m->Y - m->H)
				);
		}
	}
};