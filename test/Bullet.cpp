#include "DxLib.h"
#include "ShoutingHockey.h"
#include "Bullet.h"
#include <math.h>

//=============================================================
// コンストラクタ
//=============================================================
CBullet::CBullet(float x, float y)
	: CMover(SH->BulletList, x, y, 2.0), Count(0)
{
}

//=============================================================
// 移動
//=============================================================
bool CBullet::Move() {

	Count++;

	return !Out(4);
}

//=============================================================
// 描画
//=============================================================
void CBullet::Draw() {
	DrawGraphF(X - (BULLET_CHIP_SIZE_X / 2), Y - (BULLET_CHIP_SIZE_Y / 2),
		SH->GHBullet[(Count / BULLET_ANIM_SPEED) % BULLET_PATTERN],
		TRUE
	);
}

//=============================================================
// コンストラクタ
//=============================================================
CDirBullet::CDirBullet(float x, float y, float dir, float spd, float accel)
	: CBullet(x, y)
{
	float c = cosf(DegToRad * dir), s = sinf(DegToRad * dir);
	// 速度
	VX = spd * c;
	VY = spd * s;

	// 加速度
	AX = accel * c;
	AY = accel * s;
}

//=============================================================
// 移動
//=============================================================
bool CDirBullet::Move() {
	// 座標の更新
	X += VX;
	Y += VY;

	// 速度の更新
	VX += AX;
	VY += AY;

	// 弾の共通処理（画面外に出たかどうかの判定）
	return CBullet::Move();
}