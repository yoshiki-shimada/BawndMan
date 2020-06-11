/*******************************************************************
* @file		Selector.cpp
* @brief	シーン管理.cpp
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
* @brief タイトルクラス
*************************************************/
CTitle::CTitle() : nCount(0), bFade(false)
{
	SH->NFadeList->DeleteTask();
	new CNFade(FADEIN);
	new CTitleText();
}

bool CTitle::Move() {
	////! Textの点滅　改造すること
	//	if (i <= 0) i = 256;
	//ClearDrawScreen();
	//DrawBlendGraph(0, 0, GrHandle1, FALSE, BlendGraph, i, 128);
	//ScreenFlip();
	//i -= 2;

	if (SH->Key[KEY_INPUT_UP] == 1 && SH->TitleMenuPos > 0) SH->TitleMenuPos--;
	else if (SH->Key[KEY_INPUT_DOWN] == 1 && SH->TitleMenuPos < MENU_MAX - 1) SH->TitleMenuPos++;
	else if (SH->Key[KEY_INPUT_SPACE] == 1) {
		SH->Key[KEY_INPUT_SPACE]++;

		//! Fadeのnew前にDelete
		SH->NFadeList->DeleteTask();
		//! フェードアウト処理
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
//	// 文字列の描画
//	DrawString(SCREEN_WIDTH * 0.5 - 45, SCREEN_HEIGHT / 2 - 30,
//		"ShoutingHockey",
//		(GetColor(255, 255, 255))
//	);
//	DrawString(SCREEN_WIDTH / 2 - 20, SCREEN_HEIGHT / 2 + 20,
//		"スタート",
//		(MenuPos == MENU_FIRST ? GetColor(255, 0, 0) : GetColor(255, 255, 255))
//	);
//	DrawString(SCREEN_WIDTH / 2 - 10, SCREEN_HEIGHT / 2 + 40,
//		"エンド",
//		(MenuPos == MENU_SECOND ? GetColor(255, 0, 0) : GetColor(255, 255, 255))
//	);
//}

//--------------------------------------------------------------------------------------------

//=============================================================
// ステージクラス
//=============================================================
/*
* @breaf 最初はFadeアウト
*/
CStage::CStage(int Num)
	: Time(0), m_eLine(TOP), nIDCount(0), nAlphaID(-1)
{
	//! NFadeを消す前にSFadeをnew
	//! SFadeはnewせずAlphaを変えてあげる
	//CreateSFade();
	SH->TTextList->DeleteTask();
	//fadeの削除
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

	//! ゲームオーバー処理
	if (SH->Count <= -1) {
		//! Fadeのnew前にDelete
		SH->NFadeList->DeleteTask();
		//! フェードアウト処理
		new CNFade(FADEOUT);
		new CGOver();
		return false;
	}

	//! ゲームクリア処理
	if (SH->ECount <= 0) {
		//! Fadeのnew前にDelete
		SH->NFadeList->DeleteTask();
		SH->m_ePhase = End;
		//! フェードアウト処理
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

			// 通常通り進める
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

			//! 右に曲がっても1がある場合はいる
			//! return Point
			if (nFadeCount[w][h] != 0)
				return;

		}

		//! 配列に数字を入れ
		//! newする
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
				nFadeCount[x][y] = 0;	// 配列にゼロを入れていく
			}
		}
	}
}

void CStage::CreateSFade()
{
	// 配列に数字を入れていく、配列を使っているか判定
	// その配列数の場所にnew、その前にIDをふやす
	// 前検知横（右）検知をしてどちらとも!= 0ならbreak;
	for (int x = 0; x < FADE_MAX; x++) {
		for (int y = 0; y < FADE_MAX; y++) {
			nFadeCount[x][y] = 0;	// 配列にゼロを入れていく
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

			// 通常通り進める
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

			//! 右に曲がっても1がある場合はいる
			//! return Point
			if (nFadeCount[w][h] != 0)
				return;

		}

		//! 配列に数字を入れ
		//! newする
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
	//new せず使いまわせるものは使いまわす。
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
	//! ゲームシーンの使ったものを消す
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
	// 文字列の描画
	DrawString(SCREEN_WIDTH * 0.5 - 45, SCREEN_HEIGHT / 2 - 30,
		"GameOver",
		(GetColor(255, 255, 255))
	);
	DrawString(SCREEN_WIDTH / 2 - 20, SCREEN_HEIGHT / 2 + 20,
		"コンテニュー",
		(MenuPos == MENU_FIRST ? GetColor(255, 0, 0) : GetColor(255, 255, 255))
	);
	DrawString(SCREEN_WIDTH / 2 - 10, SCREEN_HEIGHT / 2 + 40,
		"タイトルに戻る",
		(MenuPos == MENU_SECOND ? GetColor(255, 0, 0) : GetColor(255, 255, 255))
	);
}

//--------------------------------------------------------------------------------------------

CGCreal::CGCreal() : MenuPos(MENU_FIRST)
{
	//! ゲームシーンの使ったものを消す
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
	// 文字列の描画
	DrawString(SCREEN_WIDTH * 0.5 - 45, SCREEN_HEIGHT / 2 - 30,
		"GameClear",
		(GetColor(255, 255, 255))
	);
	DrawString(SCREEN_WIDTH / 2 - 20, SCREEN_HEIGHT / 2 + 40,
		"もう一度プレイ",
		(MenuPos == MENU_FIRST ? GetColor(255, 0, 0) : GetColor(255, 255, 255))
	);
	DrawString(SCREEN_WIDTH / 2 - 10, SCREEN_HEIGHT / 2 + 60,
		"タイトルに戻る",
		(MenuPos == MENU_SECOND ? GetColor(255, 0, 0) : GetColor(255, 255, 255))
	);
}
