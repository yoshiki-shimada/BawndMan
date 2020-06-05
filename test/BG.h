#pragma once
//--------------------------------------------------------------
#include "Mover.h"

/*************************************************
* @brief ステージクラス
*************************************************/
class CBGStage1 : public CMover
{
private:
	int BGChipNum;

protected:

public:
	CBGStage1(int ChipNum) : CMover(SH->BGList, 0, 0), BGChipNum(ChipNum) {}

	void* operator new(size_t t) {
		return operator_new(t, SH->BGList);
	}
	void operator delete(void* p) {
		operator_delete(p, SH->BGList);
	}

	// 移動、描画
	virtual bool Move();
	virtual void Draw();
};