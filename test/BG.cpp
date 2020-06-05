#include "DxLib.h"
#include "ShoutingHockey.h"
#include "BG.h"
#include "Selector.h"

/*****************************************
* @brief ”wŒiƒNƒ‰ƒX
*****************************************/
// ”wŒi‚Ì•ÏX@‚à‚µ‚©‚µ‚½‚çƒXƒe[ƒW’Ç‰Á‚·‚é‚©‚à
bool CBGStage1::Move()
{
	if (SH->m_ePhase == Run)
		BGChipNum = 0;
	else if (SH->m_ePhase == End)
		BGChipNum = 1;
	else
		BGChipNum = 2;

	return true;
}

// •`‰æ
void CBGStage1::Draw()
{
	// °
	DrawGraphF((SCREEN_WIDTH - BGSTAGE1_SIZE_X) * 0.5, 0,
		SH->GHStageFloor[BGChipNum],
		TRUE
	);
}
