#include "DxLib.h"
#include "ShoutingHockey.h"
#include "Bullet.h"
#include <math.h>


//=============================================================
// コンストラクタ
//=============================================================
CDirBullet::CDirBullet(float x, float y, float dir, float spd, float accel, int Def, int Atack)
	: CBullet(x, y, Def, Atack)
{
	float c = cosf(DegToRad * dir), s = sinf(DegToRad * dir);
	// 速度
	vx = spd * c;
	vy = spd * s;

	// 加速度
	AX = accel * c;
	AY = accel * s;
}

//=============================================================
// 移動
//=============================================================
bool CDirBullet::Move() {

	// 座標の更新
	X += vx;
	Y += vy;

	// 速度の更新
	vx += AX;
	vy += AY;

	// 当たり判定
	//! 壁での反射判定
	if (X < MinX && vx < 0) {
		vx = -vx;
		nDefCount--;
	}
	if (Y < MinY && vy < 0) {
		vy = -vy;
		nDefCount--;
	}
	if (X > MaxX && vx > 0) {
		vx = -vx;
		nDefCount--;
	}
	if (Y > MaxY && vy > 0) {
		vy = -vy;
		nDefCount--;
	}
	Count++;

	if (nDefCount <= 0)
		return false;


	return true;
}

//=============================================================
// 描画
//=============================================================
void CDirBullet::Draw() {
	DrawGraphF(X - BULLET_CHIP_SIZE_HARF, Y - BULLET_CHIP_SIZE_HARF,
		SH->GHBullet[(Count / BULLET_ANIM_SPEED) % BULLET_PATTERN],
		TRUE
	);
}

