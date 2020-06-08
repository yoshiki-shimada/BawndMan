#include "DxLib.h"
#include "ShoutingHockey.h"
#include "UI.h"

void CUI::Draw()
{
	DrawGraphF(SCREEN_WIDTH_ANDUI - METAR_CHIP_SIZE_X, 0,
		SH->GHMetar[SH->Count + 1],
		TRUE
	);
}