#include "DxLib.h"
#include "ShoutingHockey.h"
#include "Portal.h"
#include "Selector.h"

#define PI2 PI * 2

CPortal::CPortal(float x, float y, double dir)
	: CMover(SH->PortalList, x, y, PORTAL_SIZE_HARFCOLLI),
	nCount(0), nRotSpeed(5), nChipNam(0), dPortaldir(dir), dRotdir(PI * 0.25 * 0.25), bSetPortal(false)
{
}


bool CPortal::Move() {
	nCount++;

	if (nCount >= nRotSpeed) {
		dPortaldir += dRotdir;
		if (dPortaldir > PI2)
			dPortaldir -= PI2;

		nCount = 0;
	}

	return true;
}

void CPortal::Draw() {


	DrawRotaGraph(X, Y, 1.0, dPortaldir,
		SH->GHPortal[nChipNam], TRUE);
}

CSpownPortal::CSpownPortal()
{
	new CPortal(SCREEN_WIDTH * 0.75, SCREEN_HEIGHT * 0.75, PI);
	new CPortal(SCREEN_WIDTH * 0.75, SCREEN_HEIGHT * 0.25, PI * 180);
	new CPortal(SCREEN_WIDTH * 0.25, SCREEN_HEIGHT * 0.25, PI);
	new CPortal(SCREEN_WIDTH * 0.25, SCREEN_HEIGHT * 0.75, PI * 180);
}