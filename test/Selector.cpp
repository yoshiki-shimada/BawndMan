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
#include "TitleText.h"
#include "Bumper.h"
#include "Portal.h"
#include "Player.h"
#include "Enemy.h"
#include "UI.h"
#include "Fade.h"
#include "LoadScript.h"

CStage *CS;

/*************************************************
* @brief �^�C�g���N���X
*************************************************/
CTitle::CTitle() : nCount(0), bFade(false)
{
	SH->NFadeList->DeleteTask();
	new CNFade(FADEIN);
	new CTitleText();
}

bool CTitle::Move() {
	////! Text�̓_�Ł@�������邱��
	//	if (i <= 0) i = 256;
	//ClearDrawScreen();
	//DrawBlendGraph(0, 0, GrHandle1, FALSE, BlendGraph, i, 128);
	//ScreenFlip();
	//i -= 2;

	if (SH->Key[KEY_INPUT_UP] == 1 && SH->TitleMenuPos > 0) SH->TitleMenuPos--;
	else if (SH->Key[KEY_INPUT_DOWN] == 1 && SH->TitleMenuPos < MENU_MAX - 1) SH->TitleMenuPos++;
	else if (SH->Key[KEY_INPUT_SPACE] == 1) {
		SH->Key[KEY_INPUT_SPACE]++;

		//! Fade��new�O��Delete
		SH->NFadeList->DeleteTask();
		//! �t�F�[�h�A�E�g����
		new CNFade(FADEOUT);
	}

	if (SH->bSceneFlag) {
		SH->bSceneFlag = false;
		switch (SH->TitleMenuPos) {
		case MENU_FIRST:
			CS = new CStage(nStageNum);
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
//void CTitle::Draw() {
//	DrawGraphF(0, 0,
//		SH->GHTitle,
//		FALSE
//	);
//	// ������̕`��
//	DrawString(SCREEN_WIDTH * 0.5 - 45, SCREEN_HEIGHT / 2 - 30,
//		"ShoutingHockey",
//		(GetColor(255, 255, 255))
//	);
//	DrawString(SCREEN_WIDTH / 2 - 20, SCREEN_HEIGHT / 2 + 20,
//		"�X�^�[�g",
//		(MenuPos == MENU_FIRST ? GetColor(255, 0, 0) : GetColor(255, 255, 255))
//	);
//	DrawString(SCREEN_WIDTH / 2 - 10, SCREEN_HEIGHT / 2 + 40,
//		"�G���h",
//		(MenuPos == MENU_SECOND ? GetColor(255, 0, 0) : GetColor(255, 255, 255))
//	);
//}

//--------------------------------------------------------------------------------------------

//=============================================================
// �X�e�[�W�N���X
//=============================================================
/*
* @breaf �ŏ���Fade�A�E�g
*/
CStage::CStage(int Num)
	: Time(0), m_eLine(TOP), nIDCount(0), nAlphaID(-1)
{
	//! NFade�������O��SFade��new
	//! SFade��new����Alpha��ς��Ă�����
	//CreateSFade();
	SH->TTextList->DeleteTask();
	//fade�̍폜
	SH->NFadeList->DeleteTask();

	new CNFade(FADEIN);
	new CBGStage1(0);
	new CSpownBumper();
	SH->Script[Num]->Init();
	SH->Script[Num]->Run();
	new CSpownPortal();
	new CNormalPlayer(SCREEN_WIDTH * 0.5, SCREEN_HEIGHT * 0.5, PI * -0.25);
	new CUI();

	//PlayMusic("Res\\Stage.mp3", DX_PLAYTYPE_LOOP);
}

//=============================================================
bool CStage::Move() {
	//if (nAlphaID >= 0)
		//FadeOut();

	Time++;

	//! �Q�[���I�[�o�[����
	if (SH->Count <= -1) {
		//! Fade��new�O��Delete
		SH->NFadeList->DeleteTask();
		//! �t�F�[�h�A�E�g����
		new CNFade(FADEOUT);
		new CGOver();
		return false;
	}

	//! �Q�[���N���A����
	if (SH->ECount <= 0) {
		//! Fade��new�O��Delete
		SH->NFadeList->DeleteTask();
		SH->m_ePhase = End;
		//! �t�F�[�h�A�E�g����
		new CNFade(FADEOUT);
		nStageNum++;
		new CWait(nStageNum);
		//new CGCreal();
		return false;
	}

	return true;
}

void CStage::FadeIn()
{
	int w = 0;
	int h = 0;
	bool bBreak = false;
	while (true) {
		if (nFadeCount[w][h] != 0) {
			switch (m_eLine) {
			case TOP:
				w--;
				nAlphaID--;
				m_eLine = RIGHT;
				break;

			case RIGHT:
				h--;
				nAlphaID--;
				m_eLine = BOTTOM;
				break;

			case BOTTOM:
				w++;
				nAlphaID--;
				m_eLine = LEFT;
				break;

			case LEFT:
				h++;
				nAlphaID--;
				m_eLine = TOP;
				break;

			}

			// �ʏ�ʂ�i�߂�
			switch (m_eLine) {
			case TOP:
				w++;
				nAlphaID++;
				break;

			case RIGHT:
				h++;
				nAlphaID++;
				break;

			case BOTTOM:
				w--;
				nAlphaID++;
				break;

			case LEFT:
				h--;
				nAlphaID++;
				break;

			}

			//! �E�ɋȂ����Ă�1������ꍇ�͂���
			//! return Point
			if (nFadeCount[w][h] != 0)
				return;

		}

		//! �z��ɐ��������
		//! new����
		nFadeCount[w][h] = 1;
		new CSFade(w, h, nIDCount);


		switch (m_eLine) {
		case TOP:
			w++;
			nAlphaID++;
			break;

		case RIGHT:
			h++;
			nAlphaID++;
			break;

		case BOTTOM:
			w--;
			nAlphaID++;
			break;

		case LEFT:
			h--;
			nAlphaID++;
			break;

		}
	}
}

void CStage::FadeOut()
{
	nAlphaID--;

	if (nAlphaID <= 0) {
		for (int x = 0; x < FADE_MAX; x++) {
			for (int y = 0; y < FADE_MAX; y++) {
				nFadeCount[x][y] = 0;	// �z��Ƀ[�������Ă���
			}
		}
	}
}

void CStage::CreateSFade()
{
	// �z��ɐ��������Ă����A�z����g���Ă��邩����
	// ���̔z�񐔂̏ꏊ��new�A���̑O��ID���ӂ₷
	// �O���m���i�E�j���m�����Ăǂ���Ƃ�!= 0�Ȃ�break;
	for (int x = 0; x < FADE_MAX; x++) {
		for (int y = 0; y < FADE_MAX; y++) {
			nFadeCount[x][y] = 0;	// �z��Ƀ[�������Ă���
		}
	}

	int w = 0;
	int h = 0;
	bool bBreak = false;
	while (true) {
		if (nFadeCount[w][h] != 0) {
			switch (m_eLine) {
			case TOP:
				w--;
				nAlphaID--;
				m_eLine = RIGHT;
				break;

			case RIGHT:
				h--;
				nAlphaID--;
				m_eLine = BOTTOM;
				break;

			case BOTTOM:
				w++;
				nAlphaID--;
				m_eLine = LEFT;
				break;

			case LEFT:
				h++;
				nAlphaID--;
				m_eLine = TOP;
				break;

			}

			// �ʏ�ʂ�i�߂�
			switch (m_eLine) {
			case TOP:
				w++;
				nAlphaID++;
				break;

			case RIGHT:
				h++;
				nAlphaID++;
				break;

			case BOTTOM:
				w--;
				nAlphaID++;
				break;

			case LEFT:
				h--;
				nAlphaID++;
				break;

			}

			//! �E�ɋȂ����Ă�1������ꍇ�͂���
			//! return Point
			if (nFadeCount[w][h] != 0)
				return;

		}

		//! �z��ɐ��������
		//! new����
		nFadeCount[w][h] = 1;
		new CSFade(w, h, nIDCount);


		switch (m_eLine) {
		case TOP:
			w++;
			nAlphaID++;
			break;

		case RIGHT:
			h++;
			nAlphaID++;
			break;

		case BOTTOM:
			w--;
			nAlphaID++;
			break;

		case LEFT:
			h--;
			nAlphaID++;
			break;

		}
	}

}

//--------------------------------------------------------------------------------------------

CWait::CWait(int Num) : CMover(SH->WaitList, 0, 0), nNum(Num), nCount(40)
{
	//new �����g���܂킹����͎̂g���܂킷�B
	//SH->NFadeList->DeleteTask();
	SH->BGList->DeleteTask();
	SH->BumperList->DeleteTask();
	SH->PortalList->DeleteTask();
	SH->Enemy01List->DeleteTask();
	SH->PlayerList->DeleteTask();
}

bool CWait::Move() {
	if (nCount < 0) {
		//SH->SceneList->DeleteTask();
		SH->m_ePhase = Run;
		new CStage(nNum);
		return false;
	}
	nCount--;

	return true;
}

//--------------------------------------------------------------------------------------------

CGOver::CGOver() : MenuPos(MENU_FIRST)
{
	//! �Q�[���V�[���̎g�������̂�����
	SH->NFadeList->DeleteTask();
	//SH->SceneList->DeleteTask();
	SH->BGList->DeleteTask();
	SH->BumperList->DeleteTask();
	SH->PortalList->DeleteTask();
	SH->Enemy01List->DeleteTask();
	SH->PlayerList->DeleteTask();
}

bool CGOver::Move() {
	if (SH->Key[KEY_INPUT_UP] == 1 && MenuPos > 0) MenuPos--;
	else if (SH->Key[KEY_INPUT_DOWN] == 1 && MenuPos < MENU_MAX - 1) MenuPos++;
	else if (SH->Key[KEY_INPUT_SPACE] == 1) {
		SH->Key[KEY_INPUT_SPACE]++;
		switch (MenuPos) {
		case MENU_FIRST:
			new CStage(nStageNum);
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
	SH->NFadeList->DeleteTask();
	SH->BGList->DeleteTask();
	SH->BumperList->DeleteTask();
	SH->PortalList->DeleteTask();
	SH->Enemy01List->DeleteTask();
	SH->PlayerList->DeleteTask();
}

bool CGCreal::Move() {
	if (SH->Key[KEY_INPUT_UP] == 1 && MenuPos > 0) MenuPos--;
	else if (SH->Key[KEY_INPUT_DOWN] == 1 && MenuPos < MENU_MAX - 1) MenuPos++;
	else if (SH->Key[KEY_INPUT_SPACE] == 1) {
		SH->Key[KEY_INPUT_SPACE]++;
		switch (MenuPos) {
		case MENU_FIRST:
			new CStage(nStageNum);
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
