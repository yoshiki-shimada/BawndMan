/*******************************************************************
* @file		Portal.h
* @brief	ポータル用.h(画像の名前はリングにしました)
* @author	yshimada
* @data		20191217
*******************************************************************/

#pragma once

#include "Mover.h"

enum PortalPattern {
	REFPORTAL,
	NOTREFPORTAL,
	MAXNUM
};

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
	//! trueでバンパー
	bool bRefPortal;

	PortalPattern m_ePortal;

	CPortal(float x, float y, double dir);

	void* operator new(size_t t) {
		return operator_new(t, SH->PortalList);
	}
	void operator delete(void* p) {
		operator_delete(p, SH->PortalList);
	}

	// 移動、描画
	virtual bool Move();
	virtual void Draw();

	void CheckRefPortal();
	void SetHit();

};

class CSpownPortal {
public:
	CSpownPortal(int Num);

	static CPortal* New(float x, float y, float dir) { return new CPortal(x, y, dir); }

};