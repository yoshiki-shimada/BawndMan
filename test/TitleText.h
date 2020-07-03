/*******************************************************************
* @file		Title.h
* @brief	TitleClass.h
* @author	yshimada
* @data		20200110
*******************************************************************/

#pragma once

#include "Mover.h"

class CTitleText : public CMover
{
private:

public:
	CTitleText() : CMover(SH->TTextList, 20, TEXT_POS_Y_0) {};

	void* operator new(size_t t) {
		return operator_new(t, SH->TTextList);
	}
	void operator delete(void* p) {
		operator_delete(p, SH->TTextList);
	}

	// ˆÚ“®ˆ—A•`‰æŠÖ”
	virtual bool Move();
	virtual void Draw();
};

