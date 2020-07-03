/*******************************************************************
* @file		Player.h
* @brief	自機用.h
* @author	yshimada
* @data		20191218
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
	//float fRad;
	int nSDownCount;
	float fSDown;

protected:

public:
	// 移動方向用
	float vx, vy;
	// 初速度
	float Speed;
	// スピードアップ
	float faccel;

	// コンストラクタ
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
// @brief	反射等の処理で使う
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
	//int nInPortal;
	// 当たり判定用 trueあたっていない　falseあたっている
	bool bHitportal;
	//! 反射時のスピード調整用
	float fUpS;
	int FlagCount;

	// 速度分解用関数
	float *Disperse(float Pvx, float Pvy, float PVal);

public:
	// playerの攻撃値
	int PlayerAP;

	// コンストラクタ
	CNormalPlayer(float x, float y, float dir);

	// 移動
	virtual bool Move();
};