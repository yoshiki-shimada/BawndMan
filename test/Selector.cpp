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
#include "NextArrow.h"
#include "Fade.h"
#include "LoadScript.h"

CStage *CS;

//--------------------------------------------------------------------------------------------
/*************************************************
* @brief タイトルクラス
*************************************************/
CTitle::CTitle() : nCount(0), /*bFade(false),*/ bClick(true)
{
	SH->Count = 1;
	SH->bSceneFlag = false;
	SH->NFadeList->DeleteTask();
	new CNFade(FADEIN);
	new CTitleText();
	PlayMusic(TITLEBG_SE, DX_PLAYTYPE_LOOP);
}

/*****************************************
* @brief 移動
*****************************************/
bool CTitle::Move() {
	////! Textの点滅　改造すること
	//	if (i <= 0) i = 256;
	//ClearDrawScreen();
	//DrawBlendGraph(0, 0, GrHandle1, FALSE, BlendGraph, i, 128);
	//ScreenFlip();
	//i -= 2;

	if (SH->Key[KEY_INPUT_UP] == 1 && SH->TitleMenuPos > 0 && bClick) SH->TitleMenuPos--;
	else if (SH->Key[KEY_INPUT_DOWN] == 1 && SH->TitleMenuPos < MENU_MAX - 1 && bClick) SH->TitleMenuPos++;
	else if (SH->Key[KEY_INPUT_SPACE] == 1 && bClick) {
		PlaySoundMem(SH->SHClick, DX_PLAYTYPE_BACK);
		bClick = !bClick;
		SH->Key[KEY_INPUT_SPACE]++;

		//! Fadeのnew前にDelete
		SH->NFadeList->DeleteTask();
		//! フェードアウト処理
		new CNFade(FADEOUT);
	}

	if (SH->bSceneFlag) {
		switch (SH->TitleMenuPos) {
		case MENU_FIRST:
			StopMusic();
			CS = new CStage(0);
			return false;
			break;
		case MENU_SECOND:
			StopMusic();
			PostQuitMessage(0);
			break;
		}

	}

	return true;
}

/*****************************************
* @brief 描画
*****************************************/
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
/*****************************************
* @breaf 最初はFadeアウト
*****************************************/
CStage::CStage(int Num)
	: Time(0), m_eLine(TOP), nIDCount(0), /*nAlphaID(-1),*/ bFadeFlag(false)
{
	nStageNum = Num;
	SH->bMoveFlag = false;
	SH->m_eStagePhase = RunStage;
	SH->ECount = 0;
	//! NFadeを消す前にSFadeをnew
	//! SFadeはnewせずAlphaを変えてあげる
	//CreateSFade();
	SH->TTextList->DeleteTask();
	//fadeの削除
	SH->NFadeList->DeleteTask();
	//SH->ClearOverList->DeleteTask();

	new CNFade(FADEIN);
	new CBGStage1(0);
	new CSpownBumper(nStageNum);
	SH->Script[nStageNum]->Init();
	SH->Script[nStageNum]->Run();
	new CSpownPortal(nStageNum);
	new CNormalPlayer(SCREEN_WIDTH * 0.5, SCREEN_HEIGHT * 0.5, (int)rand() % 360);
	new CUI();

	PlayMusic(STAGE_SE, DX_PLAYTYPE_LOOP);
}

/*****************************************
* @breaf 移動
*****************************************/
bool CStage::Move() {
	//if (nAlphaID >= 0)
		//FadeOut();

	//! ゲームオーバー処理
	if (SH->Count == -1) {
		SH->m_eStagePhase = GameOver;
	}

	switch (SH->m_eStagePhase)
	{
	case RunStage:
		Time++;
		break;

	case GameOver:
		if (!bFadeFlag) {
			bFadeFlag = !bFadeFlag;
			SH->bMoveFlag = true;
			//! Fadeのnew前にDelete
			SH->NFadeList->DeleteTask();
			//! フェードアウト処理
			new CNFade(FADEOUT);
		}
		break;

	case NextStage:
		//! m_eStagePhase=StageClearへの切替はPlayerで
		SH->m_ePhase = End;
		SH->m_eStagePhase = RunStage;
		new CNextArrow();
		break;

	case StageClear:
		if (!bFadeFlag) {
			bFadeFlag = !bFadeFlag;
			SH->bMoveFlag = true;
			//! Fadeのnew前にDelete
			SH->NFadeList->DeleteTask();
			//! フェードアウト処理
			new CNFade(FADEOUT);
		}
		break;

	case GameClear:
		if (!bFadeFlag) {
			bFadeFlag = !bFadeFlag;
			SH->bMoveFlag = true;
			//! Fadeのnew前にDelete
			SH->NFadeList->DeleteTask();
			new CNFade(FADEOUT);
		}
		break;
	}

	if (SH->bSceneFlag) {
		switch (SH->m_eStagePhase) {
		case GameOver:
			StopMusic();
			new CGOver();
			return false;
			break;

		case StageClear:
			//! ステージMaxサイズ
			if (nStageNum >= 4) {
				SH->m_eStagePhase = GameClear;
				break;
			}
			//SH->bMoveFlag = true;
			//! Fadeのnew前にDelete
			SH->NFadeList->DeleteTask();
			//! フェードアウト処理
			new CWait(nStageNum);
			return false;
			break;

		case GameClear:
			StopMusic();
			new CGCreal();
			return false;
			break;

		}
	}

	return true;
}

/*****************************************
* @breaf SFAde用
*****************************************/
//void CStage::FadeIn()
//{
//	int w = 0;
//	int h = 0;
//	bool bBreak = false;
//	while (true) {
//		if (nFadeCount[w][h] != 0) {
//			switch (m_eLine) {
//			case TOP:
//				w--;
//				nAlphaID--;
//				m_eLine = RIGHT;
//				break;
//
//			case RIGHT:
//				h--;
//				nAlphaID--;
//				m_eLine = BOTTOM;
//				break;
//
//			case BOTTOM:
//				w++;
//				nAlphaID--;
//				m_eLine = LEFT;
//				break;
//
//			case LEFT:
//				h++;
//				nAlphaID--;
//				m_eLine = TOP;
//				break;
//
//			}
//
//			// 通常通り進める
//			switch (m_eLine) {
//			case TOP:
//				w++;
//				nAlphaID++;
//				break;
//
//			case RIGHT:
//				h++;
//				nAlphaID++;
//				break;
//
//			case BOTTOM:
//				w--;
//				nAlphaID++;
//				break;
//
//			case LEFT:
//				h--;
//				nAlphaID++;
//				break;
//
//			}
//
//			//! 右に曲がっても1がある場合はいる
//			//! return Point
//			if (nFadeCount[w][h] != 0)
//				return;
//
//		}
//
//		//! 配列に数字を入れ
//		//! newする
//		nFadeCount[w][h] = 1;
//		new CSFade(w, h, nIDCount);
//
//
//		switch (m_eLine) {
//		case TOP:
//			w++;
//			nAlphaID++;
//			break;
//
//		case RIGHT:
//			h++;
//			nAlphaID++;
//			break;
//
//		case BOTTOM:
//			w--;
//			nAlphaID++;
//			break;
//
//		case LEFT:
//			h--;
//			nAlphaID++;
//			break;
//
//		}
//	}
//}
//
//void CStage::FadeOut()
//{
//	nAlphaID--;
//
//	if (nAlphaID <= 0) {
//		for (int x = 0; x < FADE_MAX; x++) {
//			for (int y = 0; y < FADE_MAX; y++) {
//				nFadeCount[x][y] = 0;	// 配列にゼロを入れていく
//			}
//		}
//	}
//}

/*****************************************
* @breaf SFAde用
*****************************************/
//void CStage::CreateSFade()
//{
//	// 配列に数字を入れていく、配列を使っているか判定
//	// その配列数の場所にnew、その前にIDをふやす
//	// 前検知横（右）検知をしてどちらとも!= 0ならbreak;
//	for (int x = 0; x < FADE_MAX; x++) {
//		for (int y = 0; y < FADE_MAX; y++) {
//			nFadeCount[x][y] = 0;	// 配列にゼロを入れていく
//		}
//	}
//
//	int w = 0;
//	int h = 0;
//	bool bBreak = false;
//	while (true) {
//		if (nFadeCount[w][h] != 0) {
//			switch (m_eLine) {
//			case TOP:
//				w--;
//				nAlphaID--;
//				m_eLine = RIGHT;
//				break;
//
//			case RIGHT:
//				h--;
//				nAlphaID--;
//				m_eLine = BOTTOM;
//				break;
//
//			case BOTTOM:
//				w++;
//				nAlphaID--;
//				m_eLine = LEFT;
//				break;
//
//			case LEFT:
//				h++;
//				nAlphaID--;
//				m_eLine = TOP;
//				break;
//
//			}
//
//			// 通常通り進める
//			switch (m_eLine) {
//			case TOP:
//				w++;
//				nAlphaID++;
//				break;
//
//			case RIGHT:
//				h++;
//				nAlphaID++;
//				break;
//
//			case BOTTOM:
//				w--;
//				nAlphaID++;
//				break;
//
//			case LEFT:
//				h--;
//				nAlphaID++;
//				break;
//
//			}
//
//			//! 右に曲がっても1がある場合はいる
//			//! return Point
//			if (nFadeCount[w][h] != 0)
//				return;
//
//		}
//
//		//! 配列に数字を入れ
//		//! newする
//		nFadeCount[w][h] = 1;
//		new CSFade(w, h, nIDCount);
//
//
//		switch (m_eLine) {
//		case TOP:
//			w++;
//			nAlphaID++;
//			break;
//
//		case RIGHT:
//			h++;
//			nAlphaID++;
//			break;
//
//		case BOTTOM:
//			w--;
//			nAlphaID++;
//			break;
//
//		case LEFT:
//			h--;
//			nAlphaID++;
//			break;
//
//		}
//	}
//
//}

//--------------------------------------------------------------------------------------------
/*****************************************
* @breaf 遷移時のロードコンストラクタ
*****************************************/
CWait::CWait(int Num) : CMover(SH->WaitList, 0, 0), nNum(Num), nCount(100)
{
	//new せず使いまわせるものは使いまわす。
	SH->BGList->DeleteTask();
	SH->ArrowList->DeleteTask();
	SH->BumperList->DeleteTask();
	SH->PortalList->DeleteTask();
	SH->Enemy01List->DeleteTask();
	SH->Enemy02List->DeleteTask();
	SH->Enemy03List->DeleteTask();
	SH->Enemy04List->DeleteTask();
	SH->BulletList->DeleteTask();
	SH->PlayerList->DeleteTask();
	SH->UiList->DeleteTask();
}

/*****************************************
* @breaf 移動
*****************************************/
bool CWait::Move() {
	if (nCount < 0) {
		//SH->SceneList->DeleteTask();
		SH->m_ePhase = Run;
		CS = new CStage(++nNum);
		return false;
	}
	nCount--;

	return true;
}

//--------------------------------------------------------------------------------------------
/*****************************************
* @breaf ゲームオーバーコンストラクタ
*****************************************/
CGOver::CGOver() : MenuPos(MENU_FIRST), bFadeFlag(false)
{
	// レベルの初期化
	SH->Count = 1;

	//! ゲームシーンの使ったものを消す
	SH->bSceneFlag = false;
	SH->NFadeList->DeleteTask();
	new CNFade(FADEIN);
	SH->BGList->DeleteTask();
	SH->ArrowList->DeleteTask();
	SH->BumperList->DeleteTask();
	SH->PortalList->DeleteTask();
	SH->Enemy01List->DeleteTask();
	SH->Enemy02List->DeleteTask();
	SH->Enemy03List->DeleteTask();
	SH->Enemy04List->DeleteTask();
	SH->BulletList->DeleteTask();
	SH->PlayerList->DeleteTask();
	SH->UiList->DeleteTask();

	PlayMusic(OVER_SE, DX_PLAYTYPE_LOOP);
}

/*****************************************
* @breaf 移動
*****************************************/
bool CGOver::Move() {
	if (SH->Key[KEY_INPUT_UP] == 1 && MenuPos > 0 && !bFadeFlag) MenuPos--;
	else if (SH->Key[KEY_INPUT_DOWN] == 1 && MenuPos < MENU_MAX - 1 && !bFadeFlag) MenuPos++;
	else if (SH->Key[KEY_INPUT_SPACE] == 1 && !bFadeFlag) {
		PlaySoundMem(SH->SHClick, DX_PLAYTYPE_BACK);
		bFadeFlag = true;
		SH->Key[KEY_INPUT_SPACE]++;
		//! Fadeのnew前にDelete
		SH->NFadeList->DeleteTask();
		//! フェードアウト処理
		new CNFade(FADEOUT);

		//switch (MenuPos) {
		//case MENU_FIRST:
		//	//! Fadeのnew前にDelete
		//	SH->NFadeList->DeleteTask();
		//	//! フェードアウト処理
		//	new CNFade(FADEOUT);
		//	break;

		//case MENU_SECOND:
		//	//! Fadeのnew前にDelete
		//	SH->NFadeList->DeleteTask();
		//	//! フェードアウト処理
		//	new CNFade(FADEOUT);
		//	break;
		//}
	}

	if (SH->bSceneFlag) {
		switch (MenuPos) {
		case MENU_FIRST:
			StopMusic();
			new CWait(-1);
			return false;
			break;

		case MENU_SECOND:
			StopMusic();
			new CTitle();
			return false;
			break;

		}
	}

	return true;
}

/*****************************************
* @breaf 描画
*****************************************/
void CGOver::Draw() {
	DrawGraphF(0, 0,
		SH->GHOverBG,
		FALSE
	);
	//// 文字列の描画
	//DrawString(SCREEN_WIDTH * 0.5 - 45, SCREEN_HEIGHT / 2 - 30,
	//	"GameOver",
	//	(GetColor(255, 255, 255))
	//);
	DrawString(SCREEN_WIDTH * 0.5, SCREEN_HEIGHT * 0.5 + 120,
		"コンテニュー",
		(MenuPos == MENU_FIRST ? GetColor(255, 0, 0) : GetColor(255, 255, 255))
	);
	DrawString(SCREEN_WIDTH * 0.5, SCREEN_HEIGHT * 0.5 + 140,
		"タイトルに戻る",
		(MenuPos == MENU_SECOND ? GetColor(255, 0, 0) : GetColor(255, 255, 255))
	);
}

//--------------------------------------------------------------------------------------------
/*****************************************
* @breaf ゲームクリアコンストラクタ
*****************************************/
CGCreal::CGCreal() : MenuPos(MENU_FIRST), bFadeFlag(false)
{
	// レベルの初期化
	SH->Count = 1;

	//! ゲームシーンの使ったものを消す
	SH->bSceneFlag = false;
	SH->NFadeList->DeleteTask();
	new CNFade(FADEIN);
	SH->BGList->DeleteTask();
	SH->ArrowList->DeleteTask();
	SH->BumperList->DeleteTask();
	SH->PortalList->DeleteTask();
	SH->Enemy01List->DeleteTask();
	SH->Enemy02List->DeleteTask();
	SH->Enemy03List->DeleteTask();
	SH->Enemy04List->DeleteTask();
	SH->BulletList->DeleteTask();
	SH->PlayerList->DeleteTask();
	SH->UiList->DeleteTask();

	PlayMusic(CLEAR_SE, DX_PLAYTYPE_LOOP);
}

/*****************************************
* @breaf 移動
*****************************************/
bool CGCreal::Move() {
	if (SH->Key[KEY_INPUT_UP] == 1 && MenuPos > 0 && !bFadeFlag) MenuPos--;
	else if (SH->Key[KEY_INPUT_DOWN] == 1 && MenuPos < MENU_MAX - 1 && !bFadeFlag) MenuPos++;
	else if (SH->Key[KEY_INPUT_SPACE] == 1 && !bFadeFlag) {
		PlaySoundMem(SH->SHClick, DX_PLAYTYPE_BACK);
		bFadeFlag = true;
		SH->Key[KEY_INPUT_SPACE]++;
		//! Fadeのnew前にDelete
		SH->NFadeList->DeleteTask();
		//! フェードアウト処理
		new CNFade(FADEOUT);

		//switch (MenuPos) {
		//case MENU_FIRST:
		//	//! Fadeのnew前にDelete
		//	SH->NFadeList->DeleteTask();
		//	//! フェードアウト処理
		//	new CNFade(FADEOUT);
		//	new CWait(-1);
		//	return false;
		//	break;

		//case MENU_SECOND:
		//	new CTitle();
		//	return false;
		//	break;
		//}
	}

	if (SH->bSceneFlag) {
		switch (MenuPos) {
		case MENU_FIRST:
			StopMusic();
			new CWait(-1);
			return false;
			break;

		case MENU_SECOND:
			StopMusic();
			new CTitle();
			return false;
			break;

		}
	}

	return true;
}

/*****************************************
* @breaf 描画
*****************************************/
void CGCreal::Draw() {
	// BG
	DrawGraphF(0, 0,
		SH->GHClearBG,
		false
	);
	// ROGO
	DrawGraphF(SCREEN_WIDTH * 0.5 - CLEAR_ROGO_SIZE_X * 0.5, SCREEN_HEIGHT * 0.2,
		SH->GHClearRogo,
		true
	);
	DrawString(SCREEN_WIDTH * 0.5 - 40, SCREEN_HEIGHT * 0.5,
		"もう一度プレイ",
		(MenuPos == MENU_FIRST ? GetColor(0, 0, 255) : GetColor(255, 255, 255))
	);
	DrawString(SCREEN_WIDTH * 0.5 - 40, SCREEN_HEIGHT * 0.5 + 50,
		"タイトルに戻る",
		(MenuPos == MENU_SECOND ? GetColor(0, 0, 255) : GetColor(255, 255, 255))
	);
}
