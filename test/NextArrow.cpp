/*******************************************************************
* @file		NextArrow.cpp
* @brief	次のステージに行くための矢印用.cpp
* @author	yshimada
* @data		20200109
*******************************************************************/

#include "DxLib.h"
#include "ShoutingHockey.h"
#include "NextArrow.h"

//bool CNextArrow::Move() {
//	ChipNum++;
//
//	return true;
//}

/*****************************************
* @brief 描画
*****************************************/
void CNextArrow::Draw() {
	ChipNum++;

	DrawGraphF(X - ARROW_SIZE_HARF, 100.0f,
		SH->GHArrow[(ChipNum / ARROW_ANIM_SPEED) % ARROW_PATTERN],
		TRUE
	);
}