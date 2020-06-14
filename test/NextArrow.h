#pragma once

#include "Mover.h"

#define ARROW_ANIM_SPEED 6

class CNextArrow : public CMover
{
private:
	int ChipNum;

protected:

public:
	//! x,y,w,h‚Í“–‚½‚è”»’è—p‚É
	CNextArrow() : CMover(SH->ArrowList, SCREEN_WIDTH * 0.5, 0, ARROW_SIZE_HARF, ARROW_SIZE_HARF), ChipNum(0) {}

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

