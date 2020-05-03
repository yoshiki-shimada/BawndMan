/******************************************************************
* @file		Enemy.cpp
* @brief	敵のcpp
* @author	yshimada
* @data		20191221
*******************************************************************/
#include "DxLib.h"
#include "ShoutingHockey.h"
#include "Enemy.h"
#include "Player.h"
#include <math.h>


//=============================================================
// @burief コンストラクタ
//=============================================================
CZakoEnemy1::CZakoEnemy1(float x, float y, float speed)
	: CEnemy(x, y, ZENEMY_CHIP_HARF, 5, 1, 100), Count(0), vx(0), vy(0), rad(0), Speed(speed), nNocCount(0)
{
	SH->ECount++;
}

//=============================================================
// 移動
//=============================================================
bool CZakoEnemy1::Move() {
	// 移動範囲
	static const int MinX = RLWALL_AND_PLAYER, MaxX = SCREEN_WIDTH - MinX;
	static const int MinY = TBWALL_AND_PLAYER, MaxY = SCREEN_WIDTH - MinY;

	if (Count % 10 == 0 && !NockBackFlag) {
		CRemTaskIter i(SH->PlayerList);
		CPlayer *player = (CPlayer*)i.Next();
		rad = atan2(player->Y - Y, player->X - X);
		vx = cosf(rad) * Speed;
		vy = sinf(rad) * Speed;
		Vx = vx;
		Vy = vy;
	}


	if (NockBackFlag) {
		switch (nNocCount) {
		case 0:
			vx = Vx;
			vy = Vy;
			break;
		case 100:
			NockBackFlag = !NockBackFlag;
			nNocCount = -1;
			break;
		}
		nNocCount++;
	}

	X += vx;
	Y += vy;

	//! 壁での反射判定
	if (X < MinX && vx < 0)
		vx = -vx;
	if (Y < MinY && vy < 0)
		vy = -vy;
	if (X > MaxX && vx > 0)
		vx = -vx;
	if (Y > MaxY && vy > 0)
		vy = -vy;

	if (Time % 200 == 0) {
		int i = GetRand(180);
		//new CDirBullet(X, Y, 1.0f * i, 0.2f, 0.1f);
	}
	Time++;

	Count++;

	//! 消す
	if (Vit <= 0) {
		//new CEnemyCrash(X, Y);
		SH->ECount--;
		return false;
	}

	return true;
}

//=============================================================
// 描画
//=============================================================
void CZakoEnemy1::Draw() {
	DrawGraphF(X - ZENEMY_CHIP_HARF, Y - ZENEMY_CHIP_HARF,
		SH->GHZEnemy[(Count / ZENEMY_ANIM_SPEED) % ZENEMY_PATTERN],
		TRUE
	);
}

CSpownEnemy::CSpownEnemy() {
	new CZakoEnemy1(600, 200, 1);
}