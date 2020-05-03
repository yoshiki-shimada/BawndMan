#include "DxLib.h"
#include "ShoutingHockey.h"
#include "Fade.h"

/*
* @brief 普通のフェード
*/
CNFade::CNFade(FadePhase m_Phase) : CMover(SH->NFadeList, 0, 0), m_ePhase(m_Phase), nAlphaCount(0)
{
	if (m_ePhase == FADEIN)
		nAlpha = 0;
	else
		nAlpha = 255;
}

bool CNFade::Move() {
	if (m_ePhase == FADEIN) {
		if (nAlpha >= 255) {
			SH->bSceneFlag = false;
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
		}
	}

	return true;
}

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


/*
* @brief 少し変わったフェード
*/
CSFade::CSFade(FadePhase m_Phase, int x, int y) : CMover(SH -> SFadeList, 0, 0), m_ePhase(m_Phase)
{
}

bool CSFade::Move() {
	for (int x = FADE_MAX; x <= 0; x++) {
		for (int y = FADE_MAX; y <= 0;) {
			nCount++;
			if (nCount >= 10) {
				nCount = 0;
			}
		}
	}
	return true;
}

void CSFade::Draw() {
	// 描画処理
	DrawGraphF(FADE_SIZE_XY * X, FADE_SIZE_XY * Y,
		SH->GHSFade,
		TRUE
	);
}