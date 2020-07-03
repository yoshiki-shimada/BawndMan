/*******************************************************************
* @file		UI.cpp
* @brief	UI用.cpp
* @author	yshimada
* @data		20201210
*******************************************************************/

#include "DxLib.h"
#include "ShoutingHockey.h"
#include "UI.h"

/*****************************************
* @brief 描画
*****************************************/
void CUI::Draw()
{
	// メーター
	DrawGraphF(SCREEN_WIDTH_ANDUI - METAR_CHIP_SIZE_X - 50, 0,
		SH->GHMetar[SH->Count],
		TRUE
	);
	// ルールテキスト
	DrawGraphF(SCREEN_WIDTH_ANDUI - RULE_SIZE, 400,
		SH->GHRule,
		TRUE
	);
}