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

	if (fYajiX <= 0.0f) {
		fYajiX = 20.0f;
	}
	fYajiX -= 0.5f;

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
		TRUE
	);
	DrawGraphF(((SCREEN_WIDTH *0.5) - (TEXT02_SIZE_X * 0.5)), TEXT_POS_Y_1,
		SH->GHText02,
		TRUE
	);
	DrawGraphF(((SCREEN_WIDTH *0.5) - (TEXT01_SIZE_X * 0.5) - YAJI_SIZE_X - 10.0f) + fYajiX, fYajiY + TEXT_HARFHARF_Y,
		SH->GHYaji,
		TRUE
	);

}