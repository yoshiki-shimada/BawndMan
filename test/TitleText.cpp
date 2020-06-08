#include "DxLib.h"
#include "ShoutingHockey.h"
#include "Selector.h"
#include "TitleText.h"

bool CTitleText::Move()
{
	if (SH->TitleMenuPos == MENU_FIRST)
		fYajiY = TEXT_POS_Y_0;
	else
		fYajiY = TEXT_POS_Y_1;

	return true;
}

void CTitleText::Draw()
{
	DrawGraphF(0, 0,
		SH->GHTitle,
		FALSE
	);
	DrawGraphF(((SCREEN_WIDTH *0.5) - (TEXT01_SIZE_X * 0.5)), TEXT_POS_Y_0,
		SH->GHText01,
		FALSE
	);
	DrawGraphF(((SCREEN_WIDTH *0.5) - (TEXT02_SIZE_X * 0.5)), TEXT_POS_Y_1,
		SH->GHText02,
		FALSE
	);
	DrawGraphF(((SCREEN_WIDTH *0.5) - (TEXT01_SIZE_X * 0.5) - YAJI_SIZE_X), fYajiY + TEXT_HARFHARF_Y,
		SH->GHYaji,
		FALSE
	);

}