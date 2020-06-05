#pragma once

#include "Mover.h"

class CPortal : public CMover
{
protected:
	int nCount;
	int nRotSpeed;
	double dRotdir;

public:
	int nChipNam;
	float dPortaldir;
	bool bSetPortal;

	CPortal(float x, float y, double dir);

	void* operator new(size_t t) {
		return operator_new(t, SH->PortalList);
	}
	void operator delete(void* p) {
		operator_delete(p, SH->PortalList);
	}

	// ˆÚ“®A•`‰æ
	virtual bool Move();
	virtual void Draw();
};

class CSpownPortal {
public:
	CSpownPortal();

	static CPortal* New(float x, float y, float dir) { return new CPortal(x, y, dir); }

};