/*******************************************************************
* @file		Player.cpp
* @brief	playerクラス
* @author	yshimada
* @data		2019120
*******************************************************************/

#include "DxLib.h"
#include "ShoutingHockey.h"
#include "Player.h"
#include "Enemy.h"
#include "Portal.h"
#include "Bumper.h"
#include <math.h>


/******************************************************************
* @brief コンストラクタ
******************************************************************/
CPlayer::CPlayer(float x, float y, float dir) : CMover(SH->PlayerList, x, y, PLAYER_SIZE_HARF),
Dir(MOVE_DIR_NORMAL), Speed(PLAYER_SPEED)
{
	SH->Count = 0;
	vx = cosf(dir) * Speed;
	vy = -sinf(dir) * Speed;
}

/******************************************************************
* @brief player移動
******************************************************************/
bool CPlayer::Move() {
	// 移動範囲
	static const int MinX = RLWALL_AND_PLAYER, MaxX = SCREEN_WIDTH - MinX;
	static const int MinY = TBWALL_AND_PLAYER, MaxY = SCREEN_WIDTH - MinY;


	//! 移動
	X += vx;
	Y += vy;

	//--------------------------------------------------------------
	//! Bumperとの当たり判定
	for (CRemTaskIter i(SH->BumperList); i.HasNext();) {
		CBumper *Bumper = (CBumper*)i.Next();
		//! 当たったとき
		if (CSHit(Bumper, Bumper->fRad, PLAYER_SIZE_HARF, PLAYER_SIZE_HARF)) {
			if (Speed > 2) {
				Speed--;
				fRad = atan2(vy, vx);
				vx = cosf(fRad) * Speed;
				vy = sinf(fRad) * Speed;
			}
		}
	}
	//--------------------------------------------------------------

	// 壁での反射判定
	if (X < MinX && vx < 0) {
		vx = -vx;
		SH->Count++;
	}
	if (Y < MinY && vy < 0) {
		vy = -vy;
		SH->Count++;
	}
	if (X > MaxX && vx > 0) {
		vx = -vx;
		SH->Count++;
	}
	if (Y > MaxY && vy > 0) {
		vy = -vy;
		SH->Count++;
	}
	if (SH->Count > 3)
		SH->Count = 3;

	// 移動範囲の制限
	if (X < MinX)
		X = MinX;
	else if (X > MaxX)
		X = MaxX;
	if (Y < MinY)
		Y = MinY;
	else if (Y > MaxY)
		Y = MaxY;

	return true;
}

/******************************************************************
* @brief 描画
******************************************************************/
void CPlayer::Draw() {
	DrawGraphF(X - (PLAYER_SIZE_HARF), Y - (PLAYER_SIZE_HARF),
		SH->GHPlayer[(Dir * PLAYER_PATTERN) + SH->Count],
		TRUE
	);
}

/******************************************************************
* @brief player当たり判定等
******************************************************************/
CNormalPlayer::CNormalPlayer(float x, float y, float dir)
	: CPlayer(x, y, dir), nInPortal(0)
{
}

//=============================================================
// 移動
//=============================================================
bool CNormalPlayer::Move() {
	// 自機に共通の移動処理
	CPlayer::Move();

	//! nPortalの初期化
	nInPortal = 0;

	//! Bumperは移動との兼ね合いがあるため上に書きます。
	//! ポータルとの当たり判定
	for (CRemTaskIter i(SH->PortalList); i.HasNext();) {
		CPortal *Portal = (CPortal*)i.Next();
		// ポータル内にいるかどうか
		if (CCHit(Portal))
			nInPortal++;

		// ポータルにセット
		if (CCHit(Portal) && !Portal->bSetPortal) {
			X = Portal->X;
			Y = Portal->Y;
			vx = 0;
			vy = 0;
			Portal->bSetPortal = true;
			//bSetPortal = true;
		}
		// 発射
		else if (CCHit(Portal) && Portal->bSetPortal) {
			if (SH->Key[KEY_INPUT_SPACE] == 1) {
				vx = cosf(Portal->dPortaldir) * Speed;
				vy = sinf(Portal->dPortaldir) * Speed;
			}
		}
		else if (!CCHit(Portal)) {
			//bSetPortal = false;
			Portal->bSetPortal = false;
		}
	}

	//! 敵との当たり判定
	for (CRemTaskIter i(SH->EnemyList); i.HasNext();) {
		CEnemy *Enemy = (CEnemy*)i.Next();
		//! 当たった時
		if (CCHit(Enemy)) {
			// ポータルにセットされているとき
			if (nInPortal > 0) {
				SH->Count -= Enemy->nAtack;
			}
			// ポータルにセットされてないとき
			else {
				Enemy->Vit -= 1 + SH->Count;
			}

			//! 跳ね返る
			Enemy->NockBackFlag = true;

			PEVal = atan2(Enemy->Y - Y, Enemy->X - X);
			EPVal = atan2(Y - Enemy->Y, X - Enemy->X);
			V1 = Disperse(vx, vy, PEVal);
			V2 = Disperse(Enemy->Vx, Enemy->Vy, EPVal);
			//! 行列計算
			vx = *V1 + *(V2 + 2);
			vy = *(V1 + 1) + *(V2 + 3);
			Enemy->Vx = -(*(V1 + 2) + *V2);
			Enemy->Vy = -(*(V1 + 3) + *(V2 + 1));

			// スピードを少し上げる
			float fUpS = atan2(vy, vx);
			vx = cosf(fUpS) * 1.5;
			vy = sinf(fUpS) * 1.5;

			//! 当たり判定のないところまでプレイヤーを移動
			fatanZ = atan2(Y - Enemy->Y, X - Enemy->X);
			X = (2 * PLAYER_SIZE_HARF + 15) * cos(fatanZ) + Enemy->X;
			Y = (2 * PLAYER_SIZE_HARF + 15) * sin(fatanZ) + Enemy->Y;

			//! 連鎖

		}
	}

	//// 爆発
	//if (Vit <= 0) {
	//	new CMyShipCrash(X, Y);
	//  DeletePlayer();
	//	DeleteBeam();
	//	return false;
	//}

	return true;
}

/*
* @brief 反射用関数
*/
float *CNormalPlayer::Disperse(float Uxs, float Uys, float UVal1)
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

//=============================================================
CRevivalMyShip::CRevivalMyShip(float x, float y, float dir)
	: CPlayer(x, y, dir), Time(0)
{
}

//=============================================================
// 移動
//=============================================================
bool CRevivalMyShip::Move() {
	// 自機に共通の移動処理
	CPlayer::Move();

	Time++;
	if (Time > 120) {
		new CNormalPlayer(X, Y, PI * -0.25);
		return false;
	}


	return true;
}

//=============================================================
// 描画
//=============================================================
void CRevivalMyShip::Draw() {
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 122);
	DrawGraphF(X - (PLAYER_SIZE_HARF), Y - (PLAYER_SIZE_HARF),
		SH->GHPlayer[(Dir * PLAYER_PATTERN) + SH->Count],
		TRUE
	);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}