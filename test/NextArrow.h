/*******************************************************************
* @file		NextArrow.h
* @brief	次のステージに行くための矢印用.h
* @author	yshimada
* @data		20200109
*******************************************************************/

#pragma once

#include "Mover.h"

#define ARROW_ANIM_SPEED 6

class CNextArrow : public CMover
{
private:
	int ChipNum;

public:
	//! x,y,w,hは当たり判定用に
	CNextArrow() : CMover(SH->ArrowList, SCREEN_WIDTH * 0.5, 0, ARROW_SIZE_HARF, ARROW_SIZE_HARF), ChipNum(0) {}

	void* operator new(size_t t) {
		return operator_new(t, SH->ArrowList);
	}
	void operator delete(void* p) {
		operator_delete(p, SH->ArrowList);
	}

	// 移動、描画
	//virtual bool Move();
	virtual void Draw();
};

