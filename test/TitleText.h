#pragma once

#include "Mover.h"

class CTitleText : public CMover
{
private:
	float fYajiY;

public:
	CTitleText() : CMover(SH->TTextList, 0, 0), fYajiY(TEXT_POS_Y_0) {};

	void* operator new(size_t t) {
		return operator_new(t, SH->TTextList);
	}
	void operator delete(void* p) {
		operator_delete(p, SH->TTextList);
	}

	virtual bool Move();
	virtual void Draw();
};

