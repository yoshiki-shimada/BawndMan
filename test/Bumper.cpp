#include "DxLib.h"
#include "ShoutingHockey.h"
#include "Bumper.h"
#include "Selector.h"

/*****************************************
* @brief バンパークラス
*****************************************/
CBumper::CBumper(float x, float y, float rad) : CMover(SH->BumperList, x, y, BUMPER_HARF_X, BUMPER_HARF_Y), fRad(rad), nCount(0)
{
}

bool CBumper::Move()
{
	nCount++;

	return true;
}

// 描画
void CBumper::Draw()
{
	// バンパー
	DrawRotaGraph(X, Y, 1.0, fRad,
		SH->GHBumper[(nCount / BUMPER_ANIM_SPEED) % BUMPER_PATTERN],
		TRUE);
}

CSpownBumper::CSpownBumper(int Num)
{
	switch (Num)
	{
	case 0:
		//new CBumper(SCREEN_WIDTH * 0.5, BUMPER_POS - BUMPER_SIZE_Y, PI);
		//new CBumper(SCREEN_WIDTH * 0.5, (SCREEN_HEIGHT - BUMPER_POS) + BUMPER_SIZE_Y, PI);
		new CBumper(BUMPER_POS - BUMPER_SIZE_Y, SCREEN_HEIGHT * 0.5, PI_HARF);
		new CBumper((SCREEN_WIDTH - BUMPER_POS) + BUMPER_SIZE_Y, SCREEN_HEIGHT * 0.5, PI_HARF);
		break;

	case 1:
		//new CBumper(SCREEN_WIDTH * 0.5, BUMPER_POS - BUMPER_SIZE_Y, PI);
		//new CBumper(SCREEN_WIDTH * 0.5, (SCREEN_HEIGHT - BUMPER_POS) + BUMPER_SIZE_Y, PI);
		new CBumper(BUMPER_POS - BUMPER_SIZE_Y, SCREEN_HEIGHT * 0.5, PI_HARF);
		new CBumper((SCREEN_WIDTH - BUMPER_POS) + BUMPER_SIZE_Y, SCREEN_HEIGHT * 0.5, PI_HARF);
		break;

	case 2:
		//new CBumper(SCREEN_WIDTH * 0.5, BUMPER_POS - BUMPER_SIZE_Y, PI);
		//new CBumper(SCREEN_WIDTH * 0.5, (SCREEN_HEIGHT - BUMPER_POS) + BUMPER_SIZE_Y, PI);
		new CBumper(BUMPER_POS - BUMPER_SIZE_Y, SCREEN_HEIGHT * 0.5, PI_HARF);
		new CBumper((SCREEN_WIDTH - BUMPER_POS) + BUMPER_SIZE_Y, SCREEN_HEIGHT * 0.5, PI_HARF);
		break;

	case 3:
		//new CBumper(SCREEN_WIDTH * 0.5, BUMPER_POS - BUMPER_SIZE_Y, PI);
		//new CBumper(SCREEN_WIDTH * 0.5, (SCREEN_HEIGHT - BUMPER_POS) + BUMPER_SIZE_Y, PI);
		new CBumper(BUMPER_POS - BUMPER_SIZE_Y, SCREEN_HEIGHT * 0.5, PI_HARF);
		new CBumper((SCREEN_WIDTH - BUMPER_POS) + BUMPER_SIZE_Y, SCREEN_HEIGHT * 0.5, PI_HARF);
		break;

	case 4:
		//new CBumper(SCREEN_WIDTH * 0.5, BUMPER_POS - BUMPER_SIZE_Y, PI);
		//new CBumper(SCREEN_WIDTH * 0.5, (SCREEN_HEIGHT - BUMPER_POS) + BUMPER_SIZE_Y, PI);
		new CBumper(BUMPER_POS - BUMPER_SIZE_Y, SCREEN_HEIGHT * 0.5, PI_HARF);
		new CBumper((SCREEN_WIDTH - BUMPER_POS) + BUMPER_SIZE_Y, SCREEN_HEIGHT * 0.5, PI_HARF);
		break;

	}

}