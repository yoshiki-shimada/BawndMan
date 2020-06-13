/******************************************************************
* @file		Enemy.cpp
* @brief	�G��cpp
* @author	yshimada
* @data		20191221
*******************************************************************/
#include "DxLib.h"
#include "ShoutingHockey.h"
#include "Enemy02.h"
#include "Bullet.h"
#include "Player.h"
#include "Effect.h"
#include <math.h>

//=============================================================
// @burief �O���[��,�R���X�g���N�^
//=============================================================
CZakoEnemy2::CZakoEnemy2(float x, float y)
	: CEnemy02(x, y, ZENEMY_CHIP_HARF, 2, 1, 100), nCount(0), rad(0), fBulletSpeed(1)
{
	SH->ECount++;
}

//=============================================================
// �ړ�
//=============================================================
bool CZakoEnemy2::Move() {

	if (nCount % 200 == 0) {
		CRemTaskIter i(SH->PlayerList);
		CPlayer *player = (CPlayer*)i.Next();
		rad = atan2(player->Y - Y, player->X - X);
		// �e�̐���
		new CDirBullet(X, Y, rad, 1.0f, 0.75f, 1, 1);
		nCount = 0;
	}
	nCount++;

	//! ����
	if (Vit <= 0) {
		new CEnemyCrash(X, Y);
		SH->ECount--;
		//! �Q�[���N���A����
		if (SH->ECount <= 0) {
			SH->m_eStagePhase = NextStage;
		}
		return false;
	}

	return true;
}

//=============================================================
// �`��
//=============================================================
void CZakoEnemy2::Draw() {
	DrawGraphF(X - ZENEMY_CHIP_HARF, Y - ZENEMY_CHIP_HARF,
		SH->GHZEnemy02[(nCount / ZENEMY_ANIM_SPEED) % ZENEMY_PATTERN],
		TRUE
	);
}