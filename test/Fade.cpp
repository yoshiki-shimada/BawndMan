/*******************************************************************
* @file		Fade.cpp
* @brief	フェード用.cpp
* @author	yshimada
* @data		20191220
*******************************************************************/

#include "DxLib.h"
#include "ShoutingHockey.h"
#include "Selector.h"
#include "Fade.h"

/*
* @brief 普通のフェードコンストラクタ
*/
CNFade::CNFade(FadePhase m_Phase) : CMover(SH->NFadeList, 0, 0), m_ePhase(m_Phase), nAlphaCount(0)
{
	if (m_ePhase == FADEIN)
		nAlpha = 0;
	else
		nAlpha = 255;
}

/*****************************************
* @brief 移動
*****************************************/
bool CNFade::Move() {
	if (m_ePhase == FADEIN) {
		if (nAlpha >= 255) {
			SH->bSceneFlag = false;
			// 動くようにする
			SH->bMoveFlag = false;
			return false;
		}

		nAlphaCount++;
		if (nAlphaCount > 2) {
			nAlpha += 5;
			nAlphaCount = 0;
		}
	}
	else
	{
		if (nAlpha <= 0) {
			SH->bSceneFlag = true;
			return false;
		}

		nAlphaCount++;
		if (nAlphaCount > 2) {
			nAlpha -= 5;
			nAlphaCount = 0;
			// 動かないようにする
			SH->bMoveFlag = true;
		}
	}

	return true;
}

/*****************************************
* @brief 描画
*****************************************/
void CNFade::Draw() {
	// 透過処理
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, nAlpha);
	// 描画処理
	DrawGraphF(0, 0,
		SH->GHNFade,
		TRUE
	);
	//// 透過を削除
	//SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}


///*
//* @brief 少し変わったフェード
//*/
//CSFade::CSFade(int x, int y, int ID)
//	: CMover(SH -> SFadeList, 0, 0), X(x), Y(y), nID(ID)
//{
//}
//
//bool CSFade::Move() {
//
//	if (nID > CS->nAlphaID) {
//		return false;
//	}
//
//	return true;
//}
//
//void CSFade::Draw() {
//	// 描画処理
//	// 見える
//	DrawGraphF(FADE_SIZE_XY * X, FADE_SIZE_XY * Y,
//		SH->GHSFade,
//		TRUE
//	);
//
//}