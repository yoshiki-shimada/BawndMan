/*******************************************************************
* @file		SH.h
* @brief	Mainclass.h
* @author	yshimada
* @data		20191215
*******************************************************************/

#pragma once

#include "RemTask.h"

class CLoadScript;

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
enum BGPhase {
	Run,
	End,
	State
};

#define BGSTAGEFLOOR	"res\\Game_BG_Chip.png"
#define BGSTAGE1_SIZE_X  864
#define BGSTAGE1_SIZE_Y  864
#define RLWALL_AND_PLAYER 56
#define TBWALL_AND_PLAYER 55
#define BG_PATTERN 3

//! バンパー	230x13
#define BUMPER	"res\\Bumper.png"
#define BUMPER_SIZE_X  230
#define BUMPER_SIZE_Y  13

//! プレイヤー
#define PLAYER_CHIP	"res\\Player.png"
#define PLAYER_PATTERN 4
#define PLAYER_SIZE 71
#define PLAYER_SIZE_HARF 35.5

//! リング
#define PORTAL "res\\PortalChip.png"
#define PORTAL_SIZE 171
#define PORTAL_SIZE_HARF 85.5
// 当たり判定用
#define PORTAL_SIZE_HARFCOLLI 55
#define PORTAL_PATTERN 5

#define ZENEMY_CHIP	"res\\ZEnemy1.png"
#define ZENEMY_PATTERN 4
#define ZENEMY_CHIP_SIZE_X 69
#define ZENEMY_CHIP_SIZE_Y 85
#define ZENEMY_CHIP_HARF 35
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

enum CreateLine {
	TOP,
	RIGHT,
	BOTTOM,
	LEFT
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
	// ステージ移動時の背景用
	BGPhase m_ePhase;

	//! グラフィックハンドル
	int GHTitle = 0;
	int GHNFade = 0;
	int GHSFade = 0;
	int GHStageFloor[BG_PATTERN] = { 0 };
	int GHBumper = 0;
	int GHPlayer[PLAYER_PATTERN] = { 0 };
	int GHZEnemy[ZENEMY_PATTERN] = { 0 };
	int GHBullet[BULLET_PATTERN] = { 0 };
	int GHPortal[PORTAL_PATTERN] = { 0 };

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
	CRemTaskList *SceneList, *NFadeList, *SFadeList, *BGList, *BumperList, *PlayerList, *EnemyList, *BulletList, *PortalList;
	void MoveTask(CRemTaskList* list);
	void DrawTask(CRemTaskList* list);

	// スクリプト
	CLoadScript* Script[];
};

extern CShoutingHockey* SH;