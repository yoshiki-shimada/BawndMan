/*******************************************************************
* @file		SH.h
* @brief	MainClass.cpp
* @author	yshimada
* @data		20191215
*******************************************************************/

#include "DxLib.h"
#include "ShoutingHockey.h"
#include "Selector.h"
#include "TitleText.h"
#include "BG.h"
#include "Bumper.h"
#include "Portal.h"
#include "Player.h"
#include "Enemy.h"
#include "Enemy02.h"
#include "Enemy03.h"
#include "Enemy04.h"
#include "Bullet.h"
#include "UI.h"
#include "NextArrow.h"
#include "Effect.h"
#include "Fade.h"
#include "LoadScript.h"


CShoutingHockey *SH;

//! コンストラクタ
CShoutingHockey::CShoutingHockey() : ECount(0), Count(1), bMoveFlag(false), TitleMenuPos(MENU_FIRST)
{
	SetGraphMode(SCREEN_WIDTH_ANDUI, SCREEN_HEIGHT, SCREEN_COLOR);
	ChangeWindowMode(TRUE);
	DxLib_Init();
	SetDrawScreen(DX_SCREEN_BACK);

	// タスクリストの初期化
	SceneList = new CRemTaskList(sizeof(CStage), 100);
	TTextList = new CRemTaskList(sizeof(CTitleText), 10);
	WaitList = new CRemTaskList(sizeof(CWait), 10);
	BGList = new CRemTaskList(sizeof(CBGStage1), 10);
	BumperList = new CRemTaskList(sizeof(CBumper), 10);
	PortalList = new CRemTaskList(sizeof(CPortal), 100);
	Enemy01List = new CRemTaskList(sizeof(CZakoEnemy1), 100);
	Enemy02List = new CRemTaskList(sizeof(CZakoEnemy2), 100);
	Enemy03List = new CRemTaskList(sizeof(CZakoEnemy3), 100);
	Enemy04List = new CRemTaskList(sizeof(CZakoEnemy4), 100);
	BulletList = new CRemTaskList(sizeof(CDirBullet), 100);
	PlayerList = new CRemTaskList(sizeof(CNormalPlayer), 100);
	EffectList = new CRemTaskList(sizeof(CPlayerCrash), 10);
	UiList = new CRemTaskList(sizeof(CUI), 10);
	ArrowList = new CRemTaskList(sizeof(CNextArrow), 10);
	NFadeList = new CRemTaskList(sizeof(CNFade), 10);
	SFadeList = new CRemTaskList(sizeof(CSFade), 100);


	// グラフィックハンドルの初期化
	//! タイトル
	LoadDivGraph(TITLEBG, 1,
		1, 1,
		TITLE_SIZE_X, TITLE_SIZE_Y,
		&GHTitle
	);
	//! text01
	LoadDivGraph(TITLE_TEXT01, 1,
		1, 1,
		TEXT01_SIZE_X, TEXT01_SIZE_Y,
		&GHText01
	);
	//! text01
	LoadDivGraph(TITLE_TEXT02, 1,
		1, 1,
		TEXT02_SIZE_X, TEXT02_SIZE_Y,
		&GHText02
	);
	LoadDivGraph(TITLE_YAJI, 1,
		1, 1,
		YAJI_SIZE_X, YAJI_SIZE_Y,
		&GHYaji
	);
	//------------------------------------------------------
	//! ステージの床
	LoadDivGraph(BGSTAGEFLOOR, BG_PATTERN,
		BG_PATTERN, 1,
		BGSTAGE1_SIZE_X, BGSTAGE1_SIZE_Y,
		GHStageFloor
	);
	//! バンパー
	LoadDivGraph(BUMPER, BUMPER_PATTERN,
		BUMPER_PATTERN, 1,
		BUMPER_SIZE_X, BUMPER_SIZE_Y,
		GHBumper
	);
	//! ポータル
	LoadDivGraph(PORTAL, PORTAL_PATTERN,
		PORTAL_PATTERN_X, PORTAL_PATTERN_Y,
		PORTAL_SIZE, PORTAL_SIZE,
		GHPortal
	);
	//! プレイヤー
	LoadDivGraph(PLAYER_CHIP, PLAYER_PATTERN,
		PLAYER_PATTERN, 1,
		PLAYER_SIZE, PLAYER_SIZE,
		GHPlayer
	);
	//! エネミー01
	LoadDivGraph(ZENEMY_CHIP01, ZENEMY_PATTERN,
		ZENEMY_PATTERN, 1,
		ZENEMY_CHIP_SIZE_X, ZENEMY_CHIP_SIZE_Y,
		GHZEnemy01
	);
	//! エネミー02
	LoadDivGraph(ZENEMY_CHIP02, ZENEMY_PATTERN,
		ZENEMY_PATTERN, 1,
		ZENEMY_CHIP_SIZE_X, ZENEMY_CHIP_SIZE_Y,
		GHZEnemy02
	);
	//! エネミー03
	LoadDivGraph(ZENEMY_CHIP03, ZENEMY_PATTERN,
		ZENEMY_PATTERN, 1,
		ZENEMY_CHIP_SIZE_X, ZENEMY_CHIP_SIZE_Y,
		GHZEnemy03
	);
	//! エネミー04
	LoadDivGraph(ZENEMY_CHIP04, ZENEMY_PATTERN,
		ZENEMY_PATTERN, 1,
		ZENEMY_CHIP_SIZE_X, ZENEMY_CHIP_SIZE_Y,
		GHZEnemy04
	);
	//! Bullet
	LoadDivGraph(BULLET_CHIP, BULLET_PATTERN,
		BULLET_PATTERN, 1,
		BULLET_CHIP_SIZE_X, BULLET_CHIP_SIZE_Y,
		GHBullet
	);
	//! Metar
	LoadDivGraph(METAR_CHIP, METAR_PATTERN,
		METAR_PATTERN, 1,
		METAR_CHIP_SIZE_X, METAR_CHIP_SIZE_Y,
		GHMetar
	);
	LoadDivGraph(ARROW_CHIP, ARROW_PATTERN,
		ARROW_PATTERN, 1,
		ARROW_SIZE_X, ARROW_SIZE_Y,
		GHArrow
	);
	LoadDivGraph(PCRASH_CHIP, PCRASH_PATTERN,
		PCRASH_PATTERN, 1,
		PCRASH_CHIP_SIZE, PCRASH_CHIP_SIZE,
		GHPCrash
	);
	LoadDivGraph(ECRASH_CHIP, ECRASH_PATTERN,
		ECRASH_PATTERN, 1,
		ECRASH_CHIP_SIZE, ECRASH_CHIP_SIZE,
		GHECrash
	);
	LoadDivGraph(PORTAL_EFFECT_CHIP, PORTAL_EFFECT_PATTERN,
		PORTAL_EFFECT_PATTERN, 1,
		PORTAL_EFFECT_SIZE, PORTAL_EFFECT_SIZE,
		GHPortalEffect
	);
	//! ノーマルフェード
	LoadDivGraph(FADEBG, 1,
		1, 1,
		FADE_SIZE_X, FADE_SIZE_Y,
		&GHNFade
	);
	//! スペシャルフェード
	LoadDivGraph(FADEBG, 1,
		1, 1,
		FADE_SIZE_XY, FADE_SIZE_XY,
		&GHSFade
	);

	//! サウンドハンドルの初期化

	// スクリプト
	//Script[0] = new CLoadScript("Res\\StagePromoScript.txt");
	Script[0] = new CLoadScript("res\\Stage01Script.txt");
	Script[1] = new CLoadScript("res\\Stage02Script.txt");
	Script[2] = new CLoadScript("res\\Stage03Script.txt");
	Script[3] = new CLoadScript("res\\Stage04Script.txt");
	Script[4] = new CLoadScript("res\\Stage05Script.txt");

}

//! デストラクタ
CShoutingHockey::~CShoutingHockey()
{
	DxLib_End();
}

void CShoutingHockey::Run() {
	while (!ProcessMessage()) {
		ClearDrawScreen();

		//! 長押しの処理
		char cTmpKey[256];
		GetHitKeyStateAll(cTmpKey);
		for (int i = 0; i < 256; i++) {
			if (cTmpKey[i] != 0) {
				Key[i]++;
			}
			else {
				Key[i] = 0;
			}
		}

		if (Key[KEY_INPUT_ESCAPE])
			break;

		if (Key[KEY_INPUT_P] == 1)
			Pause = !Pause;

		SH->Move();
		SH->Draw();

		ScreenFlip();
	}
}

/***************************************************************
* @brief 移動
***************************************************************/
void CShoutingHockey::Move() {
	if (Pause)
		return;

	MoveTask(SceneList);
	MoveTask(TTextList);
	MoveTask(WaitList);
	MoveTask(BGList);
	MoveTask(ArrowList);
	if (!bMoveFlag) {
		MoveTask(BumperList);
		MoveTask(PortalList);
		MoveTask(BulletList);
		MoveTask(PlayerList);
		MoveTask(Enemy01List);
		MoveTask(Enemy02List);
		MoveTask(Enemy03List);
		MoveTask(Enemy04List);
	}
	MoveTask(EffectList);
	MoveTask(NFadeList);
	MoveTask(SFadeList);
}

/***************************************************************
* @brief 描画
***************************************************************/
void CShoutingHockey::Draw() {
	DrawTask(SceneList);
	DrawTask(TTextList);
	DrawTask(BGList);
	DrawTask(ArrowList);
	DrawTask(BumperList);
	DrawTask(PortalList);
	DrawTask(BulletList);
	DrawTask(PlayerList);
	DrawTask(Enemy01List);
	DrawTask(Enemy02List);
	DrawTask(Enemy03List);
	DrawTask(Enemy04List);
	DrawTask(UiList);
	DrawTask(EffectList);
	DrawTask(NFadeList);
	DrawTask(SFadeList);
}

/****************************************************************
* @brief タスクの動作
*****************************************************************/
void CShoutingHockey::MoveTask(CRemTaskList* list) {
	for (CRemTaskIter i(list); i.HasNext(); ) {
		CMover* mover = (CMover*)i.Next();
		if (!mover->Move()) i.Remove();
	}
}


/****************************************************************
* タスクの描画
*****************************************************************/
void CShoutingHockey::DrawTask(CRemTaskList* list) {
	for (CRemTaskIter i(list); i.HasNext(); ) {
		((CMover*)i.Next())->Draw();
	}
}

//=============================================================
// メインルーチン
//=============================================================
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int)
{
	SH = new CShoutingHockey();
	new CTitle();
	new CNFade(FADEIN);

	//! ゲームの実行
	SH->Run();
	//delete SH;
	return 0;
}