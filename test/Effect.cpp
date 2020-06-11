#include "DxLib.h"
#include "ShoutingHockey.h"
#include "Effect.h"

//=============================================================
// コンストラクタ
//=============================================================
CPlayerCrash::CPlayerCrash(float x, float y)
	: CEffect(x, y), Time(0), Count(0)
{
	//PlaySoundMem(SH->SHCrash, DX_PLAYTYPE_BACK);
}

//=============================================================
// 移動
//=============================================================
bool CPlayerCrash::Move() {

	Time++;
	Count++;

	if (Time >= 85) {
		// 新しい自機を復活させる
		//new CRevivalMyShip(X, Y);

		// 爆発を消す
		return false;
	}

	return true;
}

//=============================================================
// 描画
//=============================================================
void CPlayerCrash::Draw() {
	DrawGraphF(X - (CRASH_CHIP_SIZE_X / 2), Y - (CRASH_CHIP_SIZE_Y / 2),
		SH->GHPCrash[(Count / CRASH_ANIM_SPEED) % CRASH_PATTERN],
		TRUE
	);
}

//=============================================================
// コンストラクタ
//=============================================================
CEnemyCrash::CEnemyCrash(float x, float y)
	: CEffect(x, y), Time(0), Count(0)
{
	//PlaySoundMem(SH->SHCrash, DX_PLAYTYPE_BACK);
}

//=============================================================
// 移動
//=============================================================
bool CEnemyCrash::Move() {

	Time++;
	Count++;

	if (Time >= 30) {
		// 爆発を消す
		return false;
	}

	return true;
}

//=============================================================
// 描画
//=============================================================
void CEnemyCrash::Draw() {
	DrawGraphF(X - (CRASH_CHIP_SIZE_X / 2), Y - (CRASH_CHIP_SIZE_Y / 2),
		SH->GHECrash[(Count / CRASH_ANIM_SPEED) % CRASH_PATTERN],
		TRUE
	);
}