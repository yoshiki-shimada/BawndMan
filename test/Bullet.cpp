#include "DxLib.h"
#include "ShoutingHockey.h"
#include "Bullet.h"
#include <math.h>

//=============================================================
// �R���X�g���N�^
//=============================================================
CBullet::CBullet(float x, float y)
	: CMover(SH->BulletList, x, y, 2.0), Count(0)
{
}

//=============================================================
// �ړ�
//=============================================================
bool CBullet::Move() {

	Count++;

	return !Out(4);
}

//=============================================================
// �`��
//=============================================================
void CBullet::Draw() {
	DrawGraphF(X - (BULLET_CHIP_SIZE_X / 2), Y - (BULLET_CHIP_SIZE_Y / 2),
		SH->GHBullet[(Count / BULLET_ANIM_SPEED) % BULLET_PATTERN],
		TRUE
	);
}

//=============================================================
// �R���X�g���N�^
//=============================================================
CDirBullet::CDirBullet(float x, float y, float dir, float spd, float accel)
	: CBullet(x, y)
{
	float c = cosf(DegToRad * dir), s = sinf(DegToRad * dir);
	// ���x
	VX = spd * c;
	VY = spd * s;

	// �����x
	AX = accel * c;
	AY = accel * s;
}

//=============================================================
// �ړ�
//=============================================================
bool CDirBullet::Move() {
	// ���W�̍X�V
	X += VX;
	Y += VY;

	// ���x�̍X�V
	VX += AX;
	VY += AY;

	// �e�̋��ʏ����i��ʊO�ɏo�����ǂ����̔���j
	return CBullet::Move();
}