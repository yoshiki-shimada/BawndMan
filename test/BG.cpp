#include "DxLib.h"
#include "ShoutingHockey.h"
#include "BG.h"
#include "Selector.h"

/*****************************************
* @brief �w�i�N���X
*****************************************/
// �w�i�̕ύX�@������������X�e�[�W�ǉ����邩��
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

// �`��
void CBGStage1::Draw()
{
	// ��
	DrawGraphF((SCREEN_WIDTH - BGSTAGE1_SIZE_X) * 0.5, 0,
		SH->GHStageFloor[BGChipNum],
		TRUE
	);
}
