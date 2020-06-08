#pragma once

#include "Mover.h"

class CUI : public CMover
{
private:
public:
	CUI() : CMover(SH->UiList, 0, 0) {};

	void* operator new(size_t t) {
		return operator_new(t, SH->UiList);
	}
	void operator delete(void* p) {
		operator_delete(p, SH->UiList);
	}

	// •`‰æ
	virtual void Draw();
};

