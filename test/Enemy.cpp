/******************************************************************
* @file		Enemy.cpp
* @brief	敵のcpp
* @author	yshimada
* @data		20191221
*******************************************************************/
#include "DxLib.h"
#include "ShoutingHockey.h"
#include "Enemy.h"
#include "Enemy02.h"
#include "Enemy03.h"
#include "Enemy04.h"
#include "Bullet.h"
#include "Player.h"
#include "Effect.h"
#include <math.h>


//=============================================================
// @burief ブルー,コンストラクタ
//=============================================================
CZakoEnemy1::CZakoEnemy1(float x, float y)
	: CEnemy(x, y, ZENEMY_CHIP_HARF, 4, 1, 100), Count(0), vx(0), vy(0), rad(0), Speed(1), nNocCount(0)
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

	Count++;

	//! 連鎖
	for (CRemTaskIter i(SH->Enemy02List); i.HasNext();) {
		CZakoEnemy2 *Enemy02 = (CZakoEnemy2*)i.Next();
		//! 当たった時
		if (CCHit(Enemy02) && NockBackFlag) {
			Enemy02->Vit -= nAtack;

			Ref(Enemy02->X, Enemy02->Y);
		}
	}
	for (CRemTaskIter i(SH->Enemy03List); i.HasNext();) {
		CZakoEnemy3 *Enemy03 = (CZakoEnemy3*)i.Next();
		//! 当たった時
		if (CCHit(Enemy03) && NockBackFlag) {
			Enemy03->Vit -= nAtack;

			Ref(Enemy03->X, Enemy03->Y);
		}
	}
	for (CRemTaskIter i(SH->Enemy04List); i.HasNext();) {
		CZakoEnemy4 *Enemy04 = (CZakoEnemy4*)i.Next();
		//! 当たった時
		if (CCHit(Enemy04) && NockBackFlag) {
			Enemy04->Vit -= nAtack;

			Ref(Enemy04->X, Enemy04->Y);
		}
	}

	//! 消す
	if (Vit <= 0 && !NockBackFlag) {
		new CEnemyCrash(X, Y);
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
		SH->GHZEnemy01[(Count / ZENEMY_ANIM_SPEED) % ZENEMY_PATTERN],
		TRUE
	);
}


void CZakoEnemy1::Ref(float Ex, float Ey)
{
	Valx = atan2(Ey - Y, Ex - X);
	Valy = atan2(Y - Ey, X - Ex);
	V1 = Disperse(vx, vy, Valx);
	V2 = Disperse(0, 0, Valy);

	//! 行列計算
	vx = *V1 + *(V2 + 2);
	vy = *(V1 + 1) + *(V2 + 3);

	// スピードを少し上げる
	float fUpS = atan2(vy, vx);
	vx = cosf(fUpS) * Speed;
	vy = sinf(fUpS) * Speed;

	//! 当たり判定のないところまでプレイヤーを移動
	fatanZ = atan2(Y - Ey, X - Ex);
	X = (2 * PLAYER_SIZE_HARF + 20) * cos(fatanZ) + Ex;
	Y = (2 * PLAYER_SIZE_HARF + 20) * sin(fatanZ) + Ey;
}


/*
* @brief 反射用関数
*/
float *CZakoEnemy1::Disperse(float Uxs, float Uys, float UVal1)
{
	SV0 = sqrt(Uxs * Uxs + Uys * Uys);//速度(x速度とy速度の合成「対角線の長さ」）
	UVal2 = atan2(Uys, Uxs);//自球進行方向
	kakuSA = UVal2 - UVal1;//「衝突後相手球の進行方向」に対する「自球衝突前進行方向」の角度の差
	SV1 = fabs(SV0 * cos(kakuSA));//衝突後の相手球の速度
	SV2 = fabs(SV0 * sin(kakuSA));//衝突後の自球の速度
	Vxs = SV1 * cos(UVal1);//衝突後の相手球のx速度
	Vys = SV1 * sin(UVal1);//衝突後の相手球のy速度

	if (sin(kakuSA) < 0) {
		Uxs = SV2 * cos(UVal1 - PI / 2);//衝突後の自球のx速度
		Uys = SV2 * sin(UVal1 - PI / 2);//衝突後の自球のy速度
	}
	else {
		Uxs = SV2 * cos(UVal1 + PI / 2);//衝突後の自球のx速度
		Uys = SV2 * sin(UVal1 + PI / 2);//衝突後の自球のy速度
	}

	V3[0] = Uxs;
	V3[1] = Uys;
	V3[2] = Vxs;
	V3[3] = Vys;

	return V3;//出力：衝突後の自球のx速度、y速度、相手球のx速度、y速度
}