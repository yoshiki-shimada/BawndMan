#include "DxLib.h"
#include "ShoutingHockey.h"
#include "NextArrow.h"

bool CNextArrow::Move() {
	ChipNum++;

	return true;
}

void CNextArrow::Draw() {
	DrawGraphF(X, Y,
		SH->GHArrow[(ChipNum / ARROW_ANIM_SPEED) % ARROW_PATTERN],
		TRUE
	);
}