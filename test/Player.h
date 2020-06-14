/*******************************************************************
* @file		Player.h
* @brief	playerクラス
* @author	yshimada
* @data		2019120
*******************************************************************/

#pragma once

#include "Mover.h"

//-------------------------------------------------------------
// 定数
//-------------------------------------------------------------
#define PLAYER_ANIM_SPEED 5
#define PLAYER_SPEED 6

//#define MAX_SHOT_TIME 15

//! 描画関係クラス
class CPlayer :public CMover
{
private:
	float fRad;
	int nSDownCount;
	float fSDown;

protected:

public:
	float vx, vy;
	float Speed;
	float faccel;
	float x, y;

	CPlayer(float x, float y, float dir);

	void* operator new(size_t t) {
		return operator_new(t, SH->PlayerList);
	}
	void operator delete(void* p) {
		operator_delete(p, SH->PlayerList);
	}

	// 移動、描画
	virtual bool Move();
	virtual void Draw();
};

//=============================================================
// 自機クラス（通常時）
//=============================================================
class CNormalPlayer : public CPlayer
{
private:
	//! プレイヤー、敵の移動方向
	float PEVal, EPVal;
	//! 反射用
	float *V1, *V2;
	//! 値を返すため
	float V3[4];
	float SV0, SV1, SV2;
	float UVal2;
	float kakuSA;
	float Vxs, Vys;
	float SteyVx, SteyVy;
	//! 衝突時移動用
	float fatanZ;
	// ポータルエリア内、ダメージを受けるエリア内にいるかどうか
	int nInPortal;
	// 当たり判定用 trueあたっていない　falseあたっている
	bool bHitportal;
	//! 反射時のスピード調整用
	float fUpS;
	int FlagCount;

	float *Disperse(float Pvx, float Pvy, float PVal);

public:
	// playerの攻撃値
	int PlayerAP;

	// コンストラクタ
	CNormalPlayer(float x, float y, float dir);

	// 移動
	virtual bool Move();
};

//=============================================================
// 自機クラス（復活時）（点滅して当たり判定なし）
//=============================================================
class CRevivalMyShip : public CPlayer {

protected:
	// タイマー
	int Time;

public:
	// コンストラクタ
	CRevivalMyShip(float x, float y, float dir);

	// 移動、描画
	virtual bool Move();
	virtual void Draw();
};