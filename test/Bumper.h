#pragma once
//--------------------------------------------------------------
#include "Mover.h"


#define BUMPER_POS 45
#define BUMPER_HARF_X BUMPER_SIZE_X * 0.5
#define BUMPER_HARF_Y BUMPER_SIZE_Y * 0.5

/*************************************************
* @brief ステージクラス
*************************************************/
class CBumper : public CMover
{
private:

public:
	float fRad;

	CBumper(float x, float y,float dir);

	void* operator new(size_t t) {
		return operator_new(t, SH->BumperList);
	}
	void operator delete(void* p) {
		operator_delete(p, SH->BumperList);
	}

	// 移動、描画
	virtual bool Move();
	virtual void Draw();
};

class CSpownBumper
{
public:
	CSpownBumper();
};