#include "DxLib.h"
#include "ShoutingHockey.h"
#include "Bumper.h"
#include "Selector.h"

/*****************************************
* @brief バンパークラス
*****************************************/
CBumper::CBumper(float x, float y, float rad) : CMover(SH->BumperList, x, y, BUMPER_HARF_X, BUMPER_HARF_Y), fRad(rad)
{
}

bool CBumper::Move()
{
	return true;
}

// 描画
void CBumper::Draw()
{
	// バンパー
	DrawRotaGraph(X, Y, 1.0, fRad,
		SH->GHBumper,
		TRUE);
}

CSpownBumper::CSpownBumper()
{
	new CBumper(SCREEN_WIDTH * 0.5, BUMPER_POS - BUMPER_SIZE_Y, PI);
	new CBumper(SCREEN_WIDTH * 0.5, (SCREEN_HEIGHT - BUMPER_POS) + BUMPER_SIZE_Y, PI);
	new CBumper(BUMPER_POS - BUMPER_SIZE_Y, SCREEN_HEIGHT * 0.5, PI_HARF);
	new CBumper((SCREEN_WIDTH - BUMPER_POS) + BUMPER_SIZE_Y, SCREEN_HEIGHT * 0.5, PI_HARF);
}