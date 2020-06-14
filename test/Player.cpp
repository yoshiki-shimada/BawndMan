/*******************************************************************
* @file		Player.cpp
* @brief	player�N���X
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
* @brief �R���X�g���N�^
******************************************************************/
CPlayer::CPlayer(float x, float y, float dir) : CMover(SH->PlayerList, x, y, PLAYER_SIZE_HARF),
Speed(PLAYER_SPEED), nSDownCount(0), fSDown(1.0)
{
	// ���x���̏�����
	SH->Count = SH->Count;
	// �����x�̏�����
	faccel = 1.0f + ((SH->Count - 1) *0.5);
	vx = cosf(dir) * Speed;
	vy = -sinf(dir) * Speed;
}

/******************************************************************
* @brief player�ړ�
******************************************************************/
bool CPlayer::Move() {
	// �ړ��͈�
	static const int MinX = RLWALL_AND_PLAYER, MaxX = SCREEN_WIDTH - MinX;
	static const int MinY = TBWALL_AND_PLAYER, MaxY = SCREEN_WIDTH - MinY;

	if (nSDownCount <= 0)
		fSDown = 1.0;
	else {
		fSDown = 0.6;
		nSDownCount--;
	}


	//! �ړ�
	X += vx * faccel * fSDown;
	Y += vy * faccel * fSDown;

	//--------------------------------------------------------------
	//! Bumper�Ƃ̓����蔻��
	for (CRemTaskIter i(SH->BumperList); i.HasNext();) {
		CBumper *Bumper = (CBumper*)i.Next();
		//! ���������Ƃ�
		if (CSHit(Bumper, Bumper->fRad, PLAYER_SIZE_HARF, PLAYER_SIZE_HARF)) {
			nSDownCount += 50;
		}
	}
	//! NextArrow�Ƃ̓����蔻��
	for (CRemTaskIter i(SH->ArrowList); i.HasNext();) {
		CNextArrow *Arrow = (CNextArrow*)i.Next();
		if (CSHit(Arrow, PLAYER_SIZE_HARF, PLAYER_SIZE_HARF)) {
			SH->m_eStagePhase = StageClear;
		}
	}
	//--------------------------------------------------------------

	// �ǂł̔��˔���
	if (X < MinX && vx < 0) {
		vx = -vx;
		if (SH->Count < (PLAYER_PATTERN - 1)) {
			SH->Count++;
			faccel += 0.5;
		}
	}
	if (Y < MinY && vy < 0) {
		vy = -vy;
		if (SH->Count < (PLAYER_PATTERN - 1)) {
			SH->Count++;
			faccel += 0.5;
		}
	}
	if (X > MaxX && vx > 0) {
		vx = -vx;
		if (SH->Count < (PLAYER_PATTERN - 1)) {
			SH->Count++;
			faccel += 0.5;
		}
	}
	if (Y > MaxY && vy > 0) {
		vy = -vy;
		if (SH->Count < (PLAYER_PATTERN - 1)) {
			SH->Count++;
			faccel += 0.5;
		}
	}

	// �ړ��͈͂̐���
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
* @brief �`��
******************************************************************/
void CPlayer::Draw() {
	DrawGraphF(X - (PLAYER_SIZE_HARF), Y - (PLAYER_SIZE_HARF),
		SH->GHPlayer[SH->Count],
		TRUE
	);
}

/******************************************************************
* @brief player�����蔻�蓙
******************************************************************/
CNormalPlayer::CNormalPlayer(float x, float y, float dir)
	: CPlayer(x, y, dir), nInPortal(0), bHitportal(true), fUpS(0.0f), FlagCount(0)
{
}

//=============================================================
// �ړ�
//=============================================================
bool CNormalPlayer::Move() {
	// ���@�ɋ��ʂ̈ړ�����
	CPlayer::Move();

	//! nPortal�̏������i���t���[���j
	nInPortal = 0;
	//! FlagCount�̏�����
	FlagCount = 0;

	//! Bumper�͈ړ��Ƃ̌��ˍ��������邽�ߏ�ɏ����܂��B
	//! �|�[�^���Ƃ̓����蔻��
	for (CRemTaskIter i(SH->PortalList); i.HasNext();) {
		CPortal *Portal = (CPortal*)i.Next();
		// �|�[�^�����ɂ��邩�ǂ���
		if (CCHit(Portal)) {
			// ���łɃZ�b�g����Ă���
			if (Portal->bSetPortal) {
				nInPortal++;
				//Portal->m_ePortal = NOTREFPORTAL;
			}
			else {
				//// �Z�b�g����Ă��炸�o���p�[��Ԃ̎�
				//if (Portal->bRefPortal)
				//	Portal->m_ePortal = REFPORTAL;
			}
		}

		switch (Portal->m_ePortal)
		{
			// �o���p�[��Ԃ̏���
		case REFPORTAL:
			if (CCHit(Portal)) {
				if (SH->Count < (PLAYER_PATTERN - 1))
					SH->Count++;

				Portal->SetHit();
				//! ����
				PEVal = atan2(Portal->Y - Y, Portal->X - X);
				EPVal = atan2(Y - Portal->Y, X - Portal->X);
				SteyVx = cosf(EPVal) * Speed;
				SteyVy = sinf(EPVal) * Speed;
				V1 = Disperse(vx, vy, PEVal);
				V2 = Disperse(SteyVx, SteyVy, EPVal);
				//V2 = Disperse(0, 0, EPVal);

				//----------------------------
				// �|�[�^���̐ؑւ�����̂ł��̎������˕Ԃ�A�֐�������K�v������
				//----------------------------
				//! �s��v�Z
				vx = *V1 + *(V2 + 2);
				vy = *(V1 + 1) + *(V2 + 3);

				// �X�s�[�h�������グ��
				fUpS = atan2(vy, vx);
				vx = cosf(fUpS) * faccel;
				vy = sinf(fUpS) * faccel;

				//! �����蔻��̂Ȃ��Ƃ���܂Ńv���C���[���ړ�
				fatanZ = atan2(Y - Portal->Y, X - Portal->X);
				X = (2 * PLAYER_SIZE_HARF + 20) * cos(fatanZ) + Portal->X;
				Y = (2 * PLAYER_SIZE_HARF + 20) * sin(fatanZ) + Portal->Y;
			}
			break;

		case NOTREFPORTAL:
			// �|�[�^���ɃZ�b�g
			if (CCHit(Portal) && !Portal->bSetPortal/* && bHitportal*/) {
				X = Portal->X;
				Y = Portal->Y;
				vx = 0;
				vy = 0;
				Portal->bSetPortal = true;
				bHitportal = false;
				// �����O�̐F��ύX
				// �L�����̃}�b�v�`�b�v��0���Ȃ̂�
				Portal->nChipNam = SH->Count;
				//bSetPortal = true;
			}
			// ����
			else if (CCHit(Portal) && Portal->bSetPortal) {
				if (SH->Key[KEY_INPUT_SPACE] == 1) {
					vx = cosf(Portal->dPortaldir) * Speed;
					vy = sinf(Portal->dPortaldir) * Speed;
					//! �ړ�
					X += vx * faccel;
					Y += vy * faccel;
					//X += vx;
					//Y += vy;
					bHitportal = false;
				}
				Portal->nChipNam = SH->Count;
			}
			// �|�[�^���ɓ������Ă��Ȃ�
			else if (!CCHit(Portal)) {
				//bSetPortal = false;
				Portal->bSetPortal = false;
				// �����O�ɓ����Ă��Ȃ���Ԃ̌����ڂ�
				Portal->nChipNam = NULL;
			}

			if (Portal->bSetPortal)
				FlagCount = 1;

			break;

		}

	}

	if (FlagCount == 0)
		bHitportal = true;

	//! �o���p�[�ւ̐ؑ�
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


	//! Enemy01�Ƃ̓����蔻��
	for (CRemTaskIter i(SH->Enemy01List); i.HasNext();) {
		CZakoEnemy1 *Enemy01 = (CZakoEnemy1*)i.Next();
		//! ����������
		if (CCHit(Enemy01)) {
			// �|�[�^���ɃZ�b�g����Ă���Ƃ�
			if (nInPortal > 0) {
				SH->Count -= Enemy01->nAtack;
				faccel -= 0.5f;

				PEVal = atan2(Enemy01->Y - Y, Enemy01->X - X);
				EPVal = atan2(Y - Enemy01->Y, X - Enemy01->X);
				V1 = Disperse(vx, vy, PEVal);
				V2 = Disperse(Enemy01->Vx, Enemy01->Vy, EPVal);

				Enemy01->Vx = -(*(V1 + 2) + *V2);
				Enemy01->Vy = -(*(V1 + 3) + *(V2 + 1));

			}
			// �|�[�^���ɃZ�b�g����ĂȂ��Ƃ�
			else {
				Enemy01->Vit -= SH->Count;

				//! ����
				PEVal = atan2(Enemy01->Y - Y, Enemy01->X - X);
				EPVal = atan2(Y - Enemy01->Y, X - Enemy01->X);
				V1 = Disperse(vx, vy, PEVal);
				V2 = Disperse(Enemy01->Vx, Enemy01->Vy, EPVal);

				//----------------------------
				// �|�[�^���̐ؑւ�����̂ł��̎������˕Ԃ�A�֐�������K�v������
				//----------------------------
				//! �s��v�Z
				vx = *V1 + *(V2 + 2);
				vy = *(V1 + 1) + *(V2 + 3);
				Enemy01->Vx = -(*(V1 + 2) + *V2);
				Enemy01->Vy = -(*(V1 + 3) + *(V2 + 1));

				// �X�s�[�h�������グ��
				fUpS = atan2(vy, vx);
				vx = cosf(fUpS) * Speed;
				vy = sinf(fUpS) * Speed;

				//! �����蔻��̂Ȃ��Ƃ���܂Ńv���C���[���ړ�
				fatanZ = atan2(Y - Enemy01->Y, X - Enemy01->X);
				X = (2 * PLAYER_SIZE_HARF + 30) * cos(fatanZ) + Enemy01->X;
				Y = (2 * PLAYER_SIZE_HARF + 30) * sin(fatanZ) + Enemy01->Y;

			}

			//! ���˕Ԃ�
			Enemy01->NockBackFlag = true;

		}
	}
	//! Enemy02�Ƃ̓����蔻��
	for (CRemTaskIter i(SH->Enemy02List); i.HasNext();) {
		CZakoEnemy2 *Enemy02 = (CZakoEnemy2*)i.Next();
		//! ����������
		if (CCHit(Enemy02)) {
			Enemy02->Vit -= 1 + SH->Count;

			//! ����
			PEVal = atan2(Enemy02->Y - Y, Enemy02->X - X);
			EPVal = atan2(Y - Enemy02->Y, X - Enemy02->X);
			SteyVx = cosf(EPVal) * Speed;
			SteyVy = sinf(EPVal) * Speed;
			V1 = Disperse(vx, vy, PEVal);
			V2 = Disperse(SteyVx, SteyVy, EPVal);

			//----------------------------
			// �|�[�^���̐ؑւ�����̂ł��̎������˕Ԃ�A�֐�������K�v������
			//----------------------------
			//! �s��v�Z
			vx = *V1 + *(V2 + 2);
			vy = *(V1 + 1) + *(V2 + 3);

			// �X�s�[�h�������グ��
			fUpS = atan2(vy, vx);
			vx = cosf(fUpS) * Speed;
			vy = sinf(fUpS) * Speed;

			//! �����蔻��̂Ȃ��Ƃ���܂Ńv���C���[���ړ�
			fatanZ = atan2(Y - Enemy02->Y, X - Enemy02->X);
			X = (2 * PLAYER_SIZE_HARF + 20) * cos(fatanZ) + Enemy02->X;
			Y = (2 * PLAYER_SIZE_HARF + 20) * sin(fatanZ) + Enemy02->Y;

		}
	}
	//! Enemy03�Ƃ̓����蔻��
	for (CRemTaskIter i(SH->Enemy03List); i.HasNext();) {
		CZakoEnemy3 *Enemy03 = (CZakoEnemy3*)i.Next();
		//! ����������
		if (CCHit(Enemy03)) {
			Enemy03->Vit -= 1 + SH->Count;

			//! ����
			PEVal = atan2(Enemy03->Y - Y, Enemy03->X - X);
			EPVal = atan2(Y - Enemy03->Y, X - Enemy03->X);
			SteyVx = cosf(EPVal) * Speed;
			SteyVy = sinf(EPVal) * Speed;
			V1 = Disperse(vx, vy, PEVal);
			V2 = Disperse(SteyVx, SteyVy, EPVal);

			//----------------------------
			// �|�[�^���̐ؑւ�����̂ł��̎������˕Ԃ�A�֐�������K�v������
			//----------------------------
			//! �s��v�Z
			vx = *V1 + *(V2 + 2);
			vy = *(V1 + 1) + *(V2 + 3);

			// �X�s�[�h�������グ��
			fUpS = atan2(vy, vx);
			vx = cosf(fUpS) * Speed;
			vy = sinf(fUpS) * Speed;

			//! �����蔻��̂Ȃ��Ƃ���܂Ńv���C���[���ړ�
			fatanZ = atan2(Y - Enemy03->Y, X - Enemy03->X);
			X = (2 * PLAYER_SIZE_HARF + 20) * cos(fatanZ) + Enemy03->X;
			Y = (2 * PLAYER_SIZE_HARF + 20) * sin(fatanZ) + Enemy03->Y;

		}
	}
	//! Enemy04�Ƃ̓����蔻��
	for (CRemTaskIter i(SH->Enemy04List); i.HasNext();) {
		CZakoEnemy4 *Enemy04 = (CZakoEnemy4*)i.Next();
		//! ����������
		if (CCHit(Enemy04)) {
			Enemy04->Vit -= 1 + SH->Count;

			//! ����
			PEVal = atan2(Enemy04->Y - Y, Enemy04->X - X);
			EPVal = atan2(Y - Enemy04->Y, X - Enemy04->X);
			SteyVx = cosf(EPVal) * Speed;
			SteyVy = sinf(EPVal) * Speed;
			V1 = Disperse(vx, vy, PEVal);
			V2 = Disperse(SteyVx, SteyVy, EPVal);

			//----------------------------
			// �|�[�^���̐ؑւ�����̂ł��̎������˕Ԃ�A�֐�������K�v������
			//----------------------------
			//! �s��v�Z
			vx = *V1 + *(V2 + 2);
			vy = *(V1 + 1) + *(V2 + 3);

			// �X�s�[�h�������グ��
			fUpS = atan2(vy, vx);
			vx = cosf(fUpS) * Speed;
			vy = sinf(fUpS) * Speed;

			//! �����蔻��̂Ȃ��Ƃ���܂Ńv���C���[���ړ�
			fatanZ = atan2(Y - Enemy04->Y, X - Enemy04->X);
			X = (2 * PLAYER_SIZE_HARF + 20) * cos(fatanZ) + Enemy04->X;
			Y = (2 * PLAYER_SIZE_HARF + 20) * sin(fatanZ) + Enemy04->Y;

		}
	}


	//! �o���b�g�Ƃ̓����蔻��
	for (CRemTaskIter i(SH->BulletList); i.HasNext();) {
		CBullet *Bullet = (CBullet*)i.Next();
		//! ����������
		if (CCHit(Bullet)) {
			SH->Count -= Bullet->nAtack;
			// �I�[�o�[�Ő��l������
			Bullet->nDefCount -= 2;
			faccel -= 0.5f;
		}
	}

	//! �G���[�h�~
	if (SH->Count <= 0)
		SH->Count = 0;

	// ����
	if (SH->Count == 0) {
		new CPlayerCrash(X, Y);
		//DeletePlayer();
		return false;
	}

	return true;
}


/*
* @brief ���˗p�֐� ���x����
*/
float *CNormalPlayer::Disperse(float Uxs, float Uys, float UVal1)
{
	SV0 = sqrt(Uxs * Uxs + Uys * Uys);//���x(x���x��y���x�̍����u�Ίp���̒����v�j
	UVal2 = atan2(Uys, Uxs);//�����i�s����
	kakuSA = UVal2 - UVal1;//�u�Փˌ㑊�苅�̐i�s�����v�ɑ΂���u�����ՓˑO�i�s�����v�̊p�x�̍�
	SV1 = fabs(SV0 * cos(kakuSA));//�Փˌ�̑��苅�̑��x
	SV2 = fabs(SV0 * sin(kakuSA));//�Փˌ�̎����̑��x
	Vxs = SV1 * cos(UVal1);//�Փˌ�̑��苅��x���x
	Vys = SV1 * sin(UVal1);//�Փˌ�̑��苅��y���x

	if (sin(kakuSA) < 0) {
		Uxs = SV2 * cos(UVal1 - PI / 2);//�Փˌ�̎�����x���x
		Uys = SV2 * sin(UVal1 - PI / 2);//�Փˌ�̎�����y���x
	}
	else {
		Uxs = SV2 * cos(UVal1 + PI / 2);//�Փˌ�̎�����x���x
		Uys = SV2 * sin(UVal1 + PI / 2);//�Փˌ�̎�����y���x
	}

	V3[0] = Uxs;
	V3[1] = Uys;
	V3[2] = Vxs;
	V3[3] = Vys;

	return V3;//�o�́F�Փˌ�̎�����x���x�Ay���x�A���苅��x���x�Ay���x
}

//=============================================================
CRevivalMyShip::CRevivalMyShip(float x, float y, float dir)
	: CPlayer(x, y, dir), Time(0)
{
}

//=============================================================
// �ړ�
//=============================================================
bool CRevivalMyShip::Move() {
	// ���@�ɋ��ʂ̈ړ�����
	CPlayer::Move();

	Time++;
	if (Time > 120) {
		new CNormalPlayer(X, Y, PI * -0.25);
		return false;
	}


	return true;
}

//=============================================================
// �`��
//=============================================================
void CRevivalMyShip::Draw() {
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 122);
	DrawGraphF(X - (PLAYER_SIZE_HARF), Y - (PLAYER_SIZE_HARF),
		SH->GHPlayer[SH->Count],
		TRUE
	);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}