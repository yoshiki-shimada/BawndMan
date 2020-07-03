/*******************************************************************
* @file		UI.h
* @brief	UI用.h
* @author	yshimada
* @data		20201210
*******************************************************************/

#pragma once

#include "Mover.h"

class CUI : public CMover
{
public:
	// コンストラクタ
	CUI() : CMover(SH->UiList, 0, 0) {};

	void* operator new(size_t t) {
		return operator_new(t, SH->UiList);
	}
	void operator delete(void* p) {
		operator_delete(p, SH->UiList);
	}

	// 描画
	virtual void Draw();
};