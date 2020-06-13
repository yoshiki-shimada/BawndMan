#pragma once

#include "Mover.h"

#define ARROW_ANIM_SPEED 6

class CNextArrow : public CMover
{
private:
	int ChipNum;

protected:

public:
	CNextArrow() : CMover(SH->ArrowList, SCREEN_WIDTH * 0.5 - ARROW_SIZE_HARF, 100, ARROW_SIZE_X, ARROW_SIZE_Y), ChipNum(0) {}

	void* operator new(size_t t) {
		return operator_new(t, SH->ArrowList);
	}
	void operator delete(void* p) {
		operator_delete(p, SH->ArrowList);
	}

	// ˆÚ“®A•`‰æ
	virtual bool Move();
	virtual void Draw();
};

