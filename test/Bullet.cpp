#include "DxLib.h"
#include "ShoutingHockey.h"
#include "Bullet.h"
#include <math.h>


//=============================================================
// �R���X�g���N�^
//=============================================================
CDirBullet::CDirBullet(float x, float y, float dir, float spd, float accel, int Def, int Atack)
	: CBullet(x, y, Def, Atack)
{
	float c = cosf(DegToRad * dir), s = sinf(DegToRad * dir);
	// ���x
	vx = spd * c;
	vy = spd * s;

	// �����x
	AX = accel * c;
	AY = accel * s;
}

//=============================================================
// �ړ�
//=============================================================
bool CDirBullet::Move() {

	// ���W�̍X�V
	X += vx;
	Y += vy;

	// ���x�̍X�V
	vx += AX;
	vy += AY;

	// �����蔻��
	//! �ǂł̔��˔���
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
// �`��
//=============================================================
void CDirBullet::Draw() {
	DrawGraphF(X - BULLET_CHIP_SIZE_HARF, Y - BULLET_CHIP_SIZE_HARF,
		SH->GHBullet[(Count / BULLET_ANIM_SPEED) % BULLET_PATTERN],
		TRUE
	);
}

