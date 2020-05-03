/*******************************************************************
* @file		SH.h
* @brief	Mainclass.h
* @author	yshimada
* @data		20191215
*******************************************************************/

#pragma once

#include "RemTask.h"

//! スクリーンサイズ
#define SCREEN_WIDTH	864
#define SCREEN_HEIGHT	864
//! 一応色
#define SCREEN_COLOR	32

//! 斜め移動のための変換計算数値
#define PI        3.14159265f
#define PI_HARF	  PI * 0.5f
#define RadToDeg  57.29577951f
#define DegToRad  0.017453293f

//! フェード演出用
#define FADEBG "res\\BlacBox.png"
#define FADE_SIZE_X 1920
#define FADE_SIZE_Y 1080
#define FADE_SIZE_XY 36

//--------------------------------------------------------
//! タイトル	864x864
#define TITLEBG	"res\\TitleBG.png"
#define TITLE_SIZE_X  864
#define TITLE_SIZE_Y  864

//--------------------------------------------------------

//! ゲーム背景	908x864
//! 両サイドのはみだし画像サイズ　22
#define BGSTAGEFLOOR	"res\\GameBG1.png"
#define BGSTAGEWALL		"res\\Wall.png"
#define BGSTAGE1_SIZE_X  908
#define BGSTAGE1_SIZE_Y  864
#define RLWALL_AND_PLAYER 56
#define TBWALL_AND_PLAYER 55

//! バンパー	230x13
#define BUMPER	"res\\Bumper.png"
#define BUMPER_SIZE_X  230
#define BUMPER_SIZE_Y  13

//! プレイヤー
#define PLAYER_CHIP	"res\\Player.png"
#define PLAYER_PATTERN 4
#define PLAYER_SIZE 34
#define PLAYER_SIZE_HARF 17

enum {
	MOVE_DIR_NORMAL,
	MOVE_DIR_LV2,
	MOVE_DIR_LV3,
	MOVE_DIR_MAX
};

#define PORTAL "res\\Portal.png"
#define PORTAL_SIZE 105
#define PORTAL_SIZE_HARF 52.5

#define ZENEMY_CHIP	"res\\ZEnemy1.png"
#define ZENEMY_PATTERN 4
#define ZENEMY_CHIP_SIZE_X 58
#define ZENEMY_CHIP_SIZE_Y 58
#define ZENEMY_CHIP_HARF 29
//#define ZENEMY_SE "res\\SE_Crash.wav"

#define BULLET_CHIP	"Res\\Bullet.png"
#define BULLET_PATTERN 4
#define BULLET_CHIP_SIZE_X 8
#define BULLET_CHIP_SIZE_Y 8
#define BULLET_SE "Res\\SE_Bullet.wav"

enum FadePhase {
	FADEIN = 0,
	FADEOUT = 1
};

/*
* @brief MainClass
*/
class CShoutingHockey
{
public:
	//! 敵の数を数えるため
	int ECount;
	//! プレイヤーのレベル
	//! Move等の関係でここに定義します。
	int Count;
	//! キー入力されているフレームを記録する
	int Key[256] = { 0 };
	//! 一時停止
	bool Pause = false;
	//! ステージ上の動きを止める
	// falseで動く
	bool bMoveFlag;
	//! タイム
	int time = 0;
	//! fadeが終了したかの判定用
	bool bSceneFlag;

	//! グラフィックハンドル
	int GHTitle = 0;
	int GHNFade = 0;
	int GHSFade = 0;
	int GHStageFloor = 0;
	int GHStageWall = 0;
	int GHBumper = 0;
	int GHPlayer[MOVE_DIR_MAX * PLAYER_PATTERN] = { 0 };
	int GHZEnemy[ZENEMY_PATTERN] = { 0 };
	int GHBullet[BULLET_PATTERN] = { 0 };
	int GHPortal = 0;

	//! サウンドハンドル

	//　コンストラクタ
	CShoutingHockey();
	//　デストラクタ
	~CShoutingHockey();

	//! Run
	void Run();

	//! 移動
	virtual void Move();
	//! 描画
	virtual void Draw();

	//! タスクリスト
	CRemTaskList *TitleList, *NFadeList,*SFadeList, *BGList, *BumperList, *PlayerList, *EnemyList, *BulletList, *PortalList;
	void MoveTask(CRemTaskList* list);
	void DrawTask(CRemTaskList* list);
};

extern CShoutingHockey* SH;