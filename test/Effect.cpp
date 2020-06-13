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

	if (Time >= 60) {
		// 新しい自機を復活させる
		//new CRevivalMyShip(X, Y);
		//! ゲームオーバーのFlagを切り替える
		SH->Count = -1;

		// 爆発を消す
		return false;
	}

	return true;
}

//=============================================================
// 描画
//=============================================================
void CPlayerCrash::Draw() {
	DrawGraphF(X - (PCRASH_CHIP_SIZE / 2), Y - (PCRASH_CHIP_SIZE / 2),
		SH->GHPCrash[(Count / CRASH_ANIM_SPEED) % PCRASH_PATTERN],
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
	DrawGraphF(X - (ECRASH_CHIP_SIZE / 2), Y - (ECRASH_CHIP_SIZE / 2),
		SH->GHECrash[(Count / CRASH_ANIM_SPEED) % ECRASH_PATTERN],
		TRUE
	);
}


//=============================================================
// コンストラクタ
//=============================================================
CPortalEffect::CPortalEffect(float x, float y)
	: CEffect(x, y), Time(0), Count(0)
{
	//PlaySoundMem(SH->SHCrash, DX_PLAYTYPE_BACK);
}

//=============================================================
// 移動
//=============================================================
bool CPortalEffect::Move() {

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
void CPortalEffect::Draw() {
	DrawGraphF(X - (PORTAL_EFFECT_SIZE / 2), Y - (PORTAL_EFFECT_SIZE / 2),
		SH->GHPortalEffect[(Count / CRASH_ANIM_SPEED) % PORTAL_EFFECT_PATTERN],
		TRUE
	);
}