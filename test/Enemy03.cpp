/******************************************************************
* @file		Enemy.cpp
* @brief	敵のcpp
* @author	yshimada
* @data		20191221
*******************************************************************/
#include "DxLib.h"
#include "ShoutingHockey.h"
#include "Enemy03.h"
#include "Bullet.h"
#include "Player.h"
#include "Effect.h"
#include <math.h>

//=============================================================
// @burief イエロー,コンストラクタ
//=============================================================
CZakoEnemy3::CZakoEnemy3(float x, float y)
	: CEnemy03(x, y, ZENEMY_CHIP_HARF, 4, 1, 100), nCount(0), rad(0), fBulletSpeed(1)
{
	SH->ECount++;
}

//=============================================================
// 移動
//=============================================================
bool CZakoEnemy3::Move() {

	if (nCount / 200 == 0) {
		CRemTaskIter i(SH->PlayerList);
		CPlayer *player = (CPlayer*)i.Next();
		rad = atan2(player->Y - Y, player->X - X);
		// 弾の生成
		new CDirBullet(X, Y, rad, 1.0f, 1.0f, 2, 1);
		nCount = 0;
	}
	nCount++;

	//! 消す
	if (Vit <= 0) {
		new CEnemyCrash(X, Y);
		SH->ECount--;
		return false;
	}

	return true;
}

//=============================================================
// 描画
//=============================================================
void CZakoEnemy3::Draw() {
	DrawGraphF(X - ZENEMY_CHIP_HARF, Y - ZENEMY_CHIP_HARF,
		SH->GHZEnemy02[(nCount / ZENEMY_ANIM_SPEED) % ZENEMY_PATTERN],
		TRUE
	);
}

