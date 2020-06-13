/******************************************************************
* @file		Enemy.cpp
* @brief	敵のcpp
* @author	yshimada
* @data		20191221
*******************************************************************/
#include "DxLib.h"
#include "ShoutingHockey.h"
#include "Enemy04.h"
#include "Bullet.h"
#include "Player.h"
#include "Effect.h"
#include <math.h>


//=============================================================
// @burief レッド,コンストラクタ
//=============================================================
CZakoEnemy4::CZakoEnemy4(float x, float y)
	: CEnemy04(x, y, ZENEMY_CHIP_HARF, 4, 1, 100), nCount(0), rad(0.0f), fBulletSpeed(1)
{
	SH->ECount++;
}

//=============================================================
// 移動
//=============================================================
bool CZakoEnemy4::Move() {

	if (nCount / 200 == 0) {
		// 弾の生成
		for (int r = 0.0f; r < 20; r++) {
			rad = (int)rand() % 360;
			new CDirBullet(X, Y, rad, 1.2f, 1.2f, 1, 2);
		}
		nCount = 0;
	}
	nCount++;

	//! 消す
	if (Vit <= 0) {
		new CEnemyCrash(X, Y);
		SH->ECount--;
		//! ゲームクリア処理
		if (SH->ECount <= 0) {
			SH->m_eStagePhase = NextStage;
		}
		return false;
	}

	return true;
}

//=============================================================
// 描画
//=============================================================
void CZakoEnemy4::Draw() {
	DrawGraphF(X - ZENEMY_CHIP_HARF, Y - ZENEMY_CHIP_HARF,
		SH->GHZEnemy02[(nCount / ZENEMY_ANIM_SPEED) % ZENEMY_PATTERN],
		TRUE
	);
}