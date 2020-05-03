/*******************************************************************
* @file		Selector.cpp
* @brief	�V�[���Ǘ�.cpp
* @author	yshimada
* @data		20191215
*******************************************************************/

#include "DxLib.h"
#include "ShoutingHockey.h"
#include "Selector.h"
#include "BG.h"
#include "Bumper.h"
#include "Portal.h"
#include "Player.h"
#include "Enemy.h"
#include "Fade.h"


/*************************************************
* @brief �^�C�g���N���X
*************************************************/
CTitle::CTitle() : nCount(0), bFade(false), MenuPos(MENU_FIRST)
{
	new CNFade(FADEIN);
}

bool CTitle::Move() {
	////! Text�̓_�Ł@�������邱��
	//	if (i <= 0) i = 256;
	//ClearDrawScreen();
	//DrawBlendGraph(0, 0, GrHandle1, FALSE, BlendGraph, i, 128);
	//ScreenFlip();
	//i -= 2;

	if (SH->Key[KEY_INPUT_UP] == 1 && MenuPos > 0) MenuPos--;
	else if (SH->Key[KEY_INPUT_DOWN] == 1 && MenuPos < MENU_MAX - 1) MenuPos++;
	else if (SH->Key[KEY_INPUT_SPACE] == 1) {
		SH->Key[KEY_INPUT_SPACE]++;
		new CNFade(FADEOUT);
	}

	if (SH->bSceneFlag) {
		SH->bSceneFlag = false;
		switch (MenuPos) {
		case MENU_FIRST:
			//! �t�F�[�h�A�E�g����
			new CStage();
			return false;
			break;
		case MENU_SECOND:
			PostQuitMessage(0);
			break;
		}

	}

	return true;
}

//=============================================================
void CTitle::Draw() {
	DrawGraphF(0, 0,
		SH->GHTitle,
		FALSE
	);
	// ������̕`��
	DrawString(SCREEN_WIDTH * 0.5 - 45, SCREEN_HEIGHT / 2 - 30,
		"ShoutingHockey",
		(GetColor(255, 255, 255))
	);
	DrawString(SCREEN_WIDTH / 2 - 20, SCREEN_HEIGHT / 2 + 20,
		"�X�^�[�g",
		(MenuPos == MENU_FIRST ? GetColor(255, 0, 0) : GetColor(255, 255, 255))
	);
	DrawString(SCREEN_WIDTH / 2 - 10, SCREEN_HEIGHT / 2 + 40,
		"�G���h",
		(MenuPos == MENU_SECOND ? GetColor(255, 0, 0) : GetColor(255, 255, 255))
	);
}

//--------------------------------------------------------------------------------------------

//=============================================================
// �X�e�[�W�N���X
//=============================================================
CStage::CStage()
	: Time(0)
{
	//fade�̍폜
	//SH->NFadeList->DeleteTask();

	new CNFade(FADEIN);
	new CBGStage1();
	new CSpownBumper();
	new CSpownPortal();
	new CSpownEnemy();
	new CNormalPlayer(SCREEN_WIDTH * 0.5, SCREEN_HEIGHT * 0.5, PI * -0.25);

	//PlayMusic("Res\\Stage.mp3", DX_PLAYTYPE_LOOP);
}

//=============================================================
bool CStage::Move() {
	Time++;

	//! �Q�[���I�[�o�[����
	if (SH->Count <= -1) {
		new CGOver();
		return false;
	}

	//! �Q�[���N���A����
	if (SH->ECount <= 0) {
		new CGCreal();
		return false;
	}

	return true;
}

//--------------------------------------------------------------------------------------------

CGOver::CGOver() : MenuPos(MENU_FIRST)
{
	//! �Q�[���V�[���̎g�������̂�����
	SH->BGList->DeleteTask();
	SH->BumperList->DeleteTask();
	SH->PortalList->DeleteTask();
	SH->EnemyList->DeleteTask();
	SH->PlayerList->DeleteTask();
}

bool CGOver::Move() {
	if (SH->Key[KEY_INPUT_UP] == 1 && MenuPos > 0) MenuPos--;
	else if (SH->Key[KEY_INPUT_DOWN] == 1 && MenuPos < MENU_MAX - 1) MenuPos++;
	else if (SH->Key[KEY_INPUT_SPACE] == 1) {
		SH->Key[KEY_INPUT_SPACE]++;
		switch (MenuPos) {
		case MENU_FIRST:
			new CStage();
			return false;
			break;

		case MENU_SECOND:
			new CTitle();
			return false;
			break;
		}
	}

	return true;
}

//=============================================================
void CGOver::Draw() {
	DrawGraphF(0, 0,
		SH->GHTitle,
		FALSE
	);
	// ������̕`��
	DrawString(SCREEN_WIDTH * 0.5 - 45, SCREEN_HEIGHT / 2 - 30,
		"GameOver",
		(GetColor(255, 255, 255))
	);
	DrawString(SCREEN_WIDTH / 2 - 20, SCREEN_HEIGHT / 2 + 20,
		"�R���e�j���[",
		(MenuPos == MENU_FIRST ? GetColor(255, 0, 0) : GetColor(255, 255, 255))
	);
	DrawString(SCREEN_WIDTH / 2 - 10, SCREEN_HEIGHT / 2 + 40,
		"�^�C�g���ɖ߂�",
		(MenuPos == MENU_SECOND ? GetColor(255, 0, 0) : GetColor(255, 255, 255))
	);
}

//--------------------------------------------------------------------------------------------

CGCreal::CGCreal() : MenuPos(MENU_FIRST)
{
	//! �Q�[���V�[���̎g�������̂�����
	SH->BGList->DeleteTask();
	SH->BumperList->DeleteTask();
	SH->PortalList->DeleteTask();
	SH->EnemyList->DeleteTask();
	SH->PlayerList->DeleteTask();
}

bool CGCreal::Move() {
	if (SH->Key[KEY_INPUT_UP] == 1 && MenuPos > 0) MenuPos--;
	else if (SH->Key[KEY_INPUT_DOWN] == 1 && MenuPos < MENU_MAX - 1) MenuPos++;
	else if (SH->Key[KEY_INPUT_SPACE] == 1) {
		SH->Key[KEY_INPUT_SPACE]++;
		switch (MenuPos) {
		case MENU_FIRST:
			new CStage();
			return false;
			break;

		case MENU_SECOND:
			new CTitle();
			return false;
			break;
		}
	}

	return true;
}

//=============================================================
void CGCreal::Draw() {
	DrawGraphF(0, 0,
		SH->GHTitle,
		FALSE
	);
	// ������̕`��
	DrawString(SCREEN_WIDTH * 0.5 - 45, SCREEN_HEIGHT / 2 - 30,
		"GameClear",
		(GetColor(255, 255, 255))
	);
	DrawString(SCREEN_WIDTH / 2 - 20, SCREEN_HEIGHT / 2 + 40,
		"������x�v���C",
		(MenuPos == MENU_FIRST ? GetColor(255, 0, 0) : GetColor(255, 255, 255))
	);
	DrawString(SCREEN_WIDTH / 2 - 10, SCREEN_HEIGHT / 2 + 60,
		"�^�C�g���ɖ߂�",
		(MenuPos == MENU_SECOND ? GetColor(255, 0, 0) : GetColor(255, 255, 255))
	);
}
