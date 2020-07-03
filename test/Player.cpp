/*******************************************************************
* @file		Player.cpp
* @brief	player用.cpp
* @author	yshimada
* @data		2019120
*******************************************************************/

#include "DxLib.h"
#include "ShoutingHockey.h"
#include "Player.h"
#include "Enemy.h"
#include "Enemy02.h"
#include "Enemy03.h"
#include "Enemy04.h"
#include "Bullet.h"
#include "Portal.h"
#include "Bumper.h"
#include "NextArrow.h"
#include "Effect.h"
#include <math.h>


/******************************************************************
* @brief コンストラクタ
******************************************************************/
CPlayer::CPlayer(float x, float y, float dir) : CMover(SH->PlayerList, x, y, PLAYER_SIZE_HARF),
Speed(PLAYER_SPEED), nSDownCount(0), fSDown(1.0)
{
	// レベルの初期化
	SH->Count = SH->Count;
	// 加速度の初期化
	faccel = 1.0f + ((SH->Count - 1) *0.5);
	vx = cosf(dir) * Speed;
	vy = -sinf(dir) * Speed;
}

/*
* @brief	速度分解,反射用関数
* @param	[in]	Uxs,Uys x,y方向の速度	UVal1 自球衝突前進行方向
* @return	自分x,y 相手x,y の配列を返す
*/
bool CPlayer::Move() {
	// 移動範囲
	static const int MinX = RLWALL_AND_PLAYER, MaxX = SCREEN_WIDTH - MinX;
	static const int MinY = TBWALL_AND_PLAYER, MaxY = SCREEN_WIDTH - MinY;

	if (nSDownCount <= 0)
		fSDown = 1.0;
	else {
		fSDown = 0.6;
		nSDownCount--;
	}


	//! 移動
	X += vx * faccel * fSDown;
	Y += vy * faccel * fSDown;

	//--------------------------------------------------------------
	//! Bumperとの当たり判定
	for (CRemTaskIter i(SH->BumperList); i.HasNext();) {
		CBumper *Bumper = (CBumper*)i.Next();
		//! 当たったとき
		if (CSHit(Bumper, Bumper->fRad, PLAYER_SIZE_HARF, PLAYER_SIZE_HARF)) {
			PlaySoundMem(SH->SHSDown, DX_PLAYTYPE_BACK);
			nSDownCount += 50;
		}
	}
	//! NextArrowとの当たり判定
	for (CRemTaskIter i(SH->ArrowList); i.HasNext();) {
		CNextArrow *Arrow = (CNextArrow*)i.Next();
		if (CSHit(Arrow, PLAYER_SIZE_HARF, PLAYER_SIZE_HARF)) {
			PlaySoundMem(SH->SHNextStage, DX_PLAYTYPE_BACK);
			SH->m_eStagePhase = StageClear;
			PlaySoundMem(SH->SHNextStage, DX_PLAYTYPE_BACK);
		}
	}
	//--------------------------------------------------------------

	// 壁での反射判定
	if (X < MinX && vx < 0) {
		PlaySoundMem(SH->SHRef, DX_PLAYTYPE_BACK);
		vx = -vx;
		if (SH->Count < (PLAYER_PATTERN - 1)) {
			PlaySoundMem(SH->SHLeverUP, DX_PLAYTYPE_BACK);
			SH->Count++;
			faccel += 0.5;
		}
	}
	if (Y < MinY && vy < 0) {
		PlaySoundMem(SH->SHRef, DX_PLAYTYPE_BACK);
		vy = -vy;
		if (SH->Count < (PLAYER_PATTERN - 1)) {
			PlaySoundMem(SH->SHLeverUP, DX_PLAYTYPE_BACK);
			SH->Count++;
			faccel += 0.5;
		}
	}
	if (X > MaxX && vx > 0) {
		PlaySoundMem(SH->SHRef, DX_PLAYTYPE_BACK);
		vx = -vx;
		if (SH->Count < (PLAYER_PATTERN - 1)) {
			PlaySoundMem(SH->SHLeverUP, DX_PLAYTYPE_BACK);
			SH->Count++;
			faccel += 0.5;
		}
	}
	if (Y > MaxY && vy > 0) {
		PlaySoundMem(SH->SHRef, DX_PLAYTYPE_BACK);
		vy = -vy;
		if (SH->Count < (PLAYER_PATTERN - 1)) {
			PlaySoundMem(SH->SHLeverUP, DX_PLAYTYPE_BACK);
			SH->Count++;
			faccel += 0.5;
		}
	}

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
		SH->GHPlayer[SH->Count],
		TRUE
	);
}

/******************************************************************
* @brief	通常時の当たり判定（通常ではない場合は今回実装しまでした）
******************************************************************/
CNormalPlayer::CNormalPlayer(float x, float y, float dir)
	: CPlayer(x, y, dir), bHitportal(true), fUpS(0.0f), FlagCount(0)
{
}

/******************************************************************
* @brief	ステージ上オブジェクトとの当たり判定処理
******************************************************************/
bool CNormalPlayer::Move() {
	// 自機に共通の移動処理
	CPlayer::Move();

	//! FlagCountの初期化
	FlagCount = 0;

	//! Bumperは移動との兼ね合いがあるため上に書きます。
	//! ポータルとの当たり判定
	for (CRemTaskIter i(SH->PortalList); i.HasNext();) {
		CPortal *Portal = (CPortal*)i.Next();
		// ポータル内にいるかどうか
		//if (CCHit(Portal)) {
		//	// すでにセットされている
		//	if (Portal->bSetPortal) {
		//		nInPortal++;
		//		//Portal->m_ePortal = NOTREFPORTAL;
		//	}
		//	else {
		//		//// セットされておらずバンパー状態の時
		//		//if (Portal->bRefPortal)
		//		//	Portal->m_ePortal = REFPORTAL;
		//	}
		//}

		switch (Portal->m_ePortal)
		{
			// バンパー状態の処理
		case REFPORTAL:
			// ヒット
			if (CCHit(Portal)) {
				PlaySoundMem(SH->SHRef, DX_PLAYTYPE_BACK);
				if (SH->Count < (PLAYER_PATTERN - 1)) {
					PlaySoundMem(SH->SHLeverUP, DX_PLAYTYPE_BACK);
					SH->Count++;
				}

				Portal->SetHit();
				//! 反射
				PEVal = atan2(Portal->Y - Y, Portal->X - X);
				EPVal = atan2(Y - Portal->Y, X - Portal->X);
				SteyVx = cosf(EPVal) * Speed;
				SteyVy = sinf(EPVal) * Speed;
				V1 = Disperse(vx, vy, PEVal);
				V2 = Disperse(SteyVx, SteyVy, EPVal);

				//----------------------------
				// ポータルの切替があるのでその時も跳ね返る、関数かする必要がある
				//----------------------------
				//! 行列計算
				vx = *V1 + *(V2 + 2);
				vy = *(V1 + 1) + *(V2 + 3);

				// スピードを少し上げる
				fUpS = atan2(vy, vx);
				vx = cosf(fUpS) * faccel * Speed;
				vy = sinf(fUpS) * faccel * Speed;

				//! 当たり判定のないところまでプレイヤーを移動
				fatanZ = atan2(Y - Portal->Y, X - Portal->X);
				X = (2 * PLAYER_SIZE_HARF + 30) * cos(fatanZ) + Portal->X;
				Y = (2 * PLAYER_SIZE_HARF + 30) * sin(fatanZ) + Portal->Y;
			}
			break;

		case NOTREFPORTAL:
			// ポータルにセット
			if (CCHit(Portal) && !Portal->bSetPortal/* && bHitportal*/) {
				X = Portal->X;
				Y = Portal->Y;
				vx = 0;
				vy = 0;
				Portal->bSetPortal = true;
				bHitportal = false;
				// リングの色を変更
				// キャラのマップチップは0が青なので
				Portal->nChipNam = SH->Count;
				//bSetPortal = true;
			}
			// 発射
			else if (CCHit(Portal) && Portal->bSetPortal) {
				if (SH->Key[KEY_INPUT_SPACE] == 1) {
					PlaySoundMem(SH->SHShot, DX_PLAYTYPE_BACK);
					vx = cosf(Portal->dPortaldir) * Speed;
					vy = sinf(Portal->dPortaldir) * Speed;
					//! 移動
					X += vx * faccel;
					Y += vy * faccel;
					//X += vx;
					//Y += vy;
					bHitportal = true;
				}
				Portal->nChipNam = NULL;
			}
			// ポータルに当たっていない
			else if (!CCHit(Portal)) {
				//bSetPortal = false;
				Portal->bSetPortal = false;
				// リングに入っていない状態の見た目に
				Portal->nChipNam = NULL;
			}

			if (Portal->bSetPortal)
				FlagCount = 1;

			break;

		}

	}

	if (FlagCount == 0)
		bHitportal = true;

	//! バンパーへの切替
	if (bHitportal) {
		if (SH->Key[KEY_INPUT_RETURN] == 1) {
			for (CRemTaskIter i(SH->PortalList); i.HasNext();) {
				CPortal *Portal = (CPortal*)i.Next();
				//Portal->m_ePortal = REFPORTAL;
				Portal->CheckRefPortal();
			}
		}
		if (SH->Key[KEY_INPUT_SPACE] == 20) {
			if (SH->Count >= 3) {
				SH->Count -= 2;
				vx = cosf((float)rand()) * Speed * 1.2;
				vy = sinf((float)rand()) * Speed * 1.2;
			}
		}
	}


	//! Enemy01との当たり判定
	for (CRemTaskIter i(SH->Enemy01List); i.HasNext();) {
		CZakoEnemy1 *Enemy01 = (CZakoEnemy1*)i.Next();
		//! 当たった時
		if (CCHit(Enemy01)) {
			PlaySoundMem(SH->SHDamage, DX_PLAYTYPE_BACK);
			// ポータルにセットされているとき
			if (!bHitportal) {
				SH->Count -= Enemy01->nAtack;
				faccel -= 0.5f;

				PEVal = atan2(Enemy01->Y - Y, Enemy01->X - X);
				EPVal = atan2(Y - Enemy01->Y, X - Enemy01->X);
				V1 = Disperse(vx, vy, PEVal);
				V2 = Disperse(Enemy01->Vx, Enemy01->Vy, EPVal);

				Enemy01->Vx = -(*(V1 + 2) + *V2);
				Enemy01->Vy = -(*(V1 + 3) + *(V2 + 1));

			}
			// ポータルにセットされてないとき
			else {
				Enemy01->Vit -= SH->Count;

				//! 反射
				PEVal = atan2(Enemy01->Y - Y, Enemy01->X - X);
				EPVal = atan2(Y - Enemy01->Y, X - Enemy01->X);
				V1 = Disperse(vx, vy, PEVal);
				V2 = Disperse(Enemy01->Vx, Enemy01->Vy, EPVal);

				//----------------------------
				// ポータルの切替があるのでその時も跳ね返る、関数かする必要がある
				//----------------------------
				//! 行列計算
				vx = *V1 + *(V2 + 2);
				vy = *(V1 + 1) + *(V2 + 3);
				Enemy01->Vx = -(*(V1 + 2) + *V2);
				Enemy01->Vy = -(*(V1 + 3) + *(V2 + 1));

				// スピードを少し上げる
				fUpS = atan2(vy, vx);
				vx = cosf(fUpS) * Speed;
				vy = sinf(fUpS) * Speed;

				//! 当たり判定のないところまでプレイヤーを移動
				fatanZ = atan2(Y - Enemy01->Y, X - Enemy01->X);
				X = (2 * PLAYER_SIZE_HARF + 30) * cos(fatanZ) + Enemy01->X;
				Y = (2 * PLAYER_SIZE_HARF + 30) * sin(fatanZ) + Enemy01->Y;

			}

			//! 跳ね返る
			Enemy01->NockBackFlag = true;

		}
	}
	//! Enemy02との当たり判定
	for (CRemTaskIter i(SH->Enemy02List); i.HasNext();) {
		CZakoEnemy2 *Enemy02 = (CZakoEnemy2*)i.Next();
		//! 当たった時
		if (CCHit(Enemy02)) {
			PlaySoundMem(SH->SHDamage, DX_PLAYTYPE_BACK);
			Enemy02->Vit -= 1 + SH->Count;

			//! 反射
			PEVal = atan2(Enemy02->Y - Y, Enemy02->X - X);
			EPVal = atan2(Y - Enemy02->Y, X - Enemy02->X);
			SteyVx = cosf(EPVal) * Speed;
			SteyVy = sinf(EPVal) * Speed;
			V1 = Disperse(vx, vy, PEVal);
			V2 = Disperse(SteyVx, SteyVy, EPVal);

			//----------------------------
			// ポータルの切替があるのでその時も跳ね返る、関数かする必要がある
			//----------------------------
			//! 行列計算
			vx = *V1 + *(V2 + 2);
			vy = *(V1 + 1) + *(V2 + 3);

			// スピードを少し上げる
			fUpS = atan2(vy, vx);
			vx = cosf(fUpS) * Speed;
			vy = sinf(fUpS) * Speed;

			//! 当たり判定のないところまでプレイヤーを移動
			fatanZ = atan2(Y - Enemy02->Y, X - Enemy02->X);
			X = (2 * PLAYER_SIZE_HARF + 30) * cos(fatanZ) + Enemy02->X;
			Y = (2 * PLAYER_SIZE_HARF + 30) * sin(fatanZ) + Enemy02->Y;

		}
	}
	//! Enemy03との当たり判定
	for (CRemTaskIter i(SH->Enemy03List); i.HasNext();) {
		CZakoEnemy3 *Enemy03 = (CZakoEnemy3*)i.Next();
		//! 当たった時
		if (CCHit(Enemy03)) {
			PlaySoundMem(SH->SHDamage, DX_PLAYTYPE_BACK);
			Enemy03->Vit -= 1 + SH->Count;

			//! 反射
			PEVal = atan2(Enemy03->Y - Y, Enemy03->X - X);
			EPVal = atan2(Y - Enemy03->Y, X - Enemy03->X);
			SteyVx = cosf(EPVal) * Speed;
			SteyVy = sinf(EPVal) * Speed;
			V1 = Disperse(vx, vy, PEVal);
			V2 = Disperse(SteyVx, SteyVy, EPVal);

			//----------------------------
			// ポータルの切替があるのでその時も跳ね返る、関数かする必要がある
			//----------------------------
			//! 行列計算
			vx = *V1 + *(V2 + 2);
			vy = *(V1 + 1) + *(V2 + 3);

			// スピードを少し上げる
			fUpS = atan2(vy, vx);
			vx = cosf(fUpS) * Speed;
			vy = sinf(fUpS) * Speed;

			//! 当たり判定のないところまでプレイヤーを移動
			fatanZ = atan2(Y - Enemy03->Y, X - Enemy03->X);
			X = (2 * PLAYER_SIZE_HARF + 30) * cos(fatanZ) + Enemy03->X;
			Y = (2 * PLAYER_SIZE_HARF + 30) * sin(fatanZ) + Enemy03->Y;

		}
	}
	//! Enemy04との当たり判定
	for (CRemTaskIter i(SH->Enemy04List); i.HasNext();) {
		CZakoEnemy4 *Enemy04 = (CZakoEnemy4*)i.Next();
		//! 当たった時
		if (CCHit(Enemy04)) {
			PlaySoundMem(SH->SHDamage, DX_PLAYTYPE_BACK);
			Enemy04->Vit -= 1 + SH->Count;

			//! 反射
			PEVal = atan2(Enemy04->Y - Y, Enemy04->X - X);
			EPVal = atan2(Y - Enemy04->Y, X - Enemy04->X);
			SteyVx = cosf(EPVal) * Speed;
			SteyVy = sinf(EPVal) * Speed;
			V1 = Disperse(vx, vy, PEVal);
			V2 = Disperse(SteyVx, SteyVy, EPVal);

			//----------------------------
			// ポータルの切替があるのでその時も跳ね返る、関数かする必要がある
			//----------------------------
			//! 行列計算
			vx = *V1 + *(V2 + 2);
			vy = *(V1 + 1) + *(V2 + 3);

			// スピードを少し上げる
			fUpS = atan2(vy, vx);
			vx = cosf(fUpS) * Speed;
			vy = sinf(fUpS) * Speed;

			//! 当たり判定のないところまでプレイヤーを移動
			fatanZ = atan2(Y - Enemy04->Y, X - Enemy04->X);
			X = (2 * PLAYER_SIZE_HARF + 30) * cos(fatanZ) + Enemy04->X;
			Y = (2 * PLAYER_SIZE_HARF + 30) * sin(fatanZ) + Enemy04->Y;

		}
	}


	//! バレットとの当たり判定
	for (CRemTaskIter i(SH->BulletList); i.HasNext();) {
		CBullet *Bullet = (CBullet*)i.Next();
		//! 当たった時
		if (CCHit(Bullet)) {
			PlaySoundMem(SH->SHDamage, DX_PLAYTYPE_BACK);
			SH->Count -= Bullet->nAtack;
			// オーバーで数値を引く
			Bullet->nDefCount -= 2;
			faccel -= 0.5f;
		}
	}

	//! エラー防止
	if (SH->Count <= 0)
		SH->Count = 0;

	// 爆発
	if (SH->Count == 0) {
		PlaySoundMem(SH->SHCrash, DX_PLAYTYPE_BACK);
		new CPlayerCrash(X, Y);
		//DeletePlayer();
		return false;
	}

	return true;
}


/**
* @brief	速度分解,反射用関数
* @param	[in]	Uxs,Uys x,y方向の速度	UVal1 自球衝突前進行方向
* @return	自分x,y 相手x,y の配列を返す
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