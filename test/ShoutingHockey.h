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
//! スクリーンの横幅は黒い部分を設けるのでこれを引数に
#define SCREEN_WIDTH_ANDUI	1158
//! 一応色
#define SCREEN_COLOR	32

//! 斜め移動のための変換計算数値
#define PI        3.14159265f
#define PI_HARF	  PI * 0.5f
#define RadToDeg  57.29577951f
#define DegToRad  0.017453293f

//! フェード演出用
#define FADEBG "res\\BlackBox.png"
#define FADE_SIZE_X 1920
#define FADE_SIZE_Y 1080
#define FADE_SIZE_XY 36

//------------------------タイトル画面----------------------
//! タイトル	864x864
#define TITLEBG	"res\\TitleBG.png"
#define TITLE_SIZE_X  864
#define TITLE_SIZE_Y  864

//! Text,yaji
#define TITLE_TEXT01 "res\\START.png"
#define TITLE_TEXT02 "res\\EXIT.png"
#define TEXT_POS_Y_0 550
#define TEXT_POS_Y_1 700
#define TEXT01_SIZE_X 396
#define TEXT01_SIZE_Y 119
#define TEXT02_SIZE_X 293
#define TEXT02_SIZE_Y 116
#define TEXT_HARFHARF_Y 28.5

#define TITLE_YAJI "res\\yaji.png"
#define YAJI_SIZE_X 59
#define YAJI_SIZE_Y 67


//------------------------ゲーム画面--------------------------

//! ゲーム背景	908x864
//! 両サイドのはみだし画像サイズ　22
enum BGPhase {
	Run,
	End
};

#define BGSTAGEFLOOR	"res\\Game_BG_Chip.png"
#define BGSTAGE1_SIZE_X  864
#define BGSTAGE1_SIZE_Y  864
#define RLWALL_AND_PLAYER 56
#define TBWALL_AND_PLAYER 55
#define BG_PATTERN 3

//! Arrow
#define ARROW_CHIP "res\\arrow.png"
#define ARROW_SIZE_X 93
#define ARROW_SIZE_Y 96
#define ARROW_SIZE_HARF 48
#define ARROW_PATTERN 3

//! バンパー	230x13
#define BUMPER	"res\\Bumper.png"
#define BUMPER_SIZE_X  246
#define BUMPER_SIZE_Y  36
#define BUMPER_PATTERN 3

//! プレイヤー
#define PLAYER_CHIP	"res\\Player.png"
#define PLAYER_PATTERN 5
#define PLAYER_SIZE 55
#define PLAYER_SIZE_HARF 27.5

//! リング
#define PORTAL "res\\PortalChip.png"
#define PORTAL_SIZE 136
#define PORTAL_SIZE_HARF 68
// 当たり判定用
#define PORTAL_SIZE_HARFCOLLI 50
#define PORTAL_PATTERN 10
#define PORTAL_PATTERN_X 5
#define PORTAL_PATTERN_Y 2

//! エネミー
#define ZENEMY_CHIP01	"res\\ZEnemy1.png"
#define ZENEMY_CHIP02	"res\\ZEnemy2.png"
#define ZENEMY_CHIP03	"res\\ZEnemy3.png"
#define ZENEMY_CHIP04	"res\\ZEnemy4.png"
#define ZENEMY_PATTERN 4
#define ZENEMY_CHIP_SIZE_X 53
#define ZENEMY_CHIP_SIZE_Y 65
#define ZENEMY_CHIP_HARF_Y 32.5
#define ZENEMY_CHIP_HARF_X 26.5

//! バレット
#define BULLET_CHIP	"res\\Bullet.png"
#define BULLET_PATTERN 8
#define BULLET_CHIP_SIZE_X 8
#define BULLET_CHIP_SIZE_Y 8
#define BULLET_CHIP_SIZE_HARF 4
#define BULLET_SE "Res\\SE_Bullet.wav"

//! メーターUI
#define METAR_CHIP "res\\MeterChip.png"
#define METAR_PATTERN 5
#define METAR_CHIP_SIZE_X 199
#define METAR_CHIP_SIZE_Y 253

//! ルールテキストUI
#define RULE "res\\Rule.png"
#define RULE_SIZE 294


//! エフェクト
#define ECRASH_CHIP	"Res\\ZEnemyExpl.png"
#define ECRASH_PATTERN 6
#define ECRASH_CHIP_SIZE 64
#define PCRASH_CHIP	"Res\\CharaEffect.png"
#define PCRASH_PATTERN 5
#define PCRASH_CHIP_SIZE 72
#define PORTAL_EFFECT_CHIP "Res\\RingEffect.png"
#define PORTAL_EFFECT_PATTERN 7
#define PORTAL_EFFECT_SIZE 72


//-----------------------クリア画面----------------------------
#define CLEARBG "res\\ClearBG.png"

#define CLEAR_ROGO "res\\ClearRogo.png"
#define CLEAR_ROGO_SIZE_X 782
#define CLEAR_ROGO_SIZE_Y 114

#define CLEAR_CHARA "res\\CharaRot.png"

//-----------------------ゲームオーバー画面---------------------
#define OVER_BG "res\\GameOverBG.png"

//-----------------------構造体---------------------------------
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

enum StagePhase {
	RunStage,
	GameOver,
	NextStage,
	StageClear,
	GameClear
};

//--------------------------サウンド-----------------------
//! BGM
#define TITLEBG_SE ("res\\STitleBG.mp3")
#define STAGE_SE ("res\\SStageBG.mp3")
#define OVER_SE ("res\\SGameOverBG.mp3")
#define CLEAR_SE ("res\\SClearBG.mp3")

//! SE
#define SHOT_SE ("res\\SShot.wav")
#define BULLET_SE ("res\\SBullet.wav")
#define REF_SE ("res\\SRef.wav")
#define DAMAGE_SE ("res\\SDamage.wav")
#define UP_SE ("res\\SPowerup.wav")
#define NEXTSTAGE_SE ("res\\SNextStage.wav")
#define CLICK_SE ("res\\SClick.wav")
#define CRASH_SE ("res\\SCrash.wav")
#define SDOWN_SE ("res\\SSpeedDown.wav")

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
	// メニュー項目の選択位置
	int TitleMenuPos;

	StagePhase m_eStagePhase;

	//! グラフィックハンドル
	int GHTitle = 0;
	int GHText01 = 0;
	int GHText02 = 0;
	int GHYaji = 0;
	int GHNFade = 0;
	int GHSFade = 0;
	int GHStageFloor[BG_PATTERN] = { 0 };
	int GHBumper[BUMPER_PATTERN] = { 0 };
	int GHPlayer[PLAYER_PATTERN] = { 0 };
	int GHZEnemy01[ZENEMY_PATTERN] = { 0 };
	int GHZEnemy02[ZENEMY_PATTERN] = { 0 };
	int GHZEnemy03[ZENEMY_PATTERN] = { 0 };
	int GHZEnemy04[ZENEMY_PATTERN] = { 0 };
	int GHBullet[BULLET_PATTERN] = { 0 };
	int GHPortal[PORTAL_PATTERN] = { 0 };
	int GHMetar[METAR_PATTERN] = { 0 };
	int GHArrow[ARROW_PATTERN] = { 0 };
	int GHPCrash[PCRASH_PATTERN] = { 0 };
	int GHECrash[ECRASH_PATTERN] = { 0 };
	int GHRule = 0;
	int GHPortalEffect[PORTAL_EFFECT_PATTERN] = { 0 };
	int GHClearBG = 0;
	int GHClearRogo = 0;
	int GHOverBG = 0;

	//! サウンドハンドル BG以外
	int SHClick;
	int SHCrash;
	int SHRef;
	int SHShot;
	int SHBullet;
	int SHDamage;
	int SHLeverUP;
	int SHNextStage;
	int SHSDown;

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
	CRemTaskList *SceneList, *WaitList, *NFadeList, /**SFadeList,*/ *BGList,
		*BumperList, *PlayerList, *Enemy01List, *Enemy02List,
		*Enemy03List, *Enemy04List, *BulletList, *PortalList, *UiList,
		*TTextList, *EffectList, *ArrowList/*, *ClearOverList*/;
	void MoveTask(CRemTaskList* list);
	void DrawTask(CRemTaskList* list);

	// スクリプト
	CLoadScript* Script[];
};

extern CShoutingHockey* SH;