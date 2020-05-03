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
	return true;
}

// •`‰æ
void CBGStage1::Draw()
{
	// °
	DrawGraphF((SCREEN_WIDTH - BGSTAGE1_SIZE_X) * 0.5, 0,
		SH->GHStageFloor,
		TRUE
	);
	// •Ç
	DrawGraphF((SCREEN_WIDTH - BGSTAGE1_SIZE_X) * 0.5, 0,
		SH->GHStageWall,
		TRUE
	);
}
