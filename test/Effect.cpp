#include "DxLib.h"
#include "ShoutingHockey.h"
#include "Effect.h"

//=============================================================
// �R���X�g���N�^
//=============================================================
CPlayerCrash::CPlayerCrash(float x, float y)
	: CEffect(x, y), Time(0), Count(0)
{
	//PlaySoundMem(SH->SHCrash, DX_PLAYTYPE_BACK);
}

//=============================================================
// �ړ�
//=============================================================
bool CPlayerCrash::Move() {

	Time++;
	Count++;

	if (Time >= 85) {
		// �V�������@�𕜊�������
		//new CRevivalMyShip(X, Y);

		// ����������
		return false;
	}

	return true;
}

//=============================================================
// �`��
//=============================================================
void CPlayerCrash::Draw() {
	DrawGraphF(X - (CRASH_CHIP_SIZE_X / 2), Y - (CRASH_CHIP_SIZE_Y / 2),
		SH->GHPCrash[(Count / CRASH_ANIM_SPEED) % CRASH_PATTERN],
		TRUE
	);
}

//=============================================================
// �R���X�g���N�^
//=============================================================
CEnemyCrash::CEnemyCrash(float x, float y)
	: CEffect(x, y), Time(0), Count(0)
{
	//PlaySoundMem(SH->SHCrash, DX_PLAYTYPE_BACK);
}

//=============================================================
// �ړ�
//=============================================================
bool CEnemyCrash::Move() {

	Time++;
	Count++;

	if (Time >= 30) {
		// ����������
		return false;
	}

	return true;
}

//=============================================================
// �`��
//=============================================================
void CEnemyCrash::Draw() {
	DrawGraphF(X - (CRASH_CHIP_SIZE_X / 2), Y - (CRASH_CHIP_SIZE_Y / 2),
		SH->GHECrash[(Count / CRASH_ANIM_SPEED) % CRASH_PATTERN],
		TRUE
	);
}