/*******************************************************************
* @file		SH.h
* @brief	Mainclass.h
* @author	yshimada
* @data		20191215
*******************************************************************/

#pragma once

#include "RemTask.h"

class CLoadScript;

//! �X�N���[���T�C�Y
#define SCREEN_WIDTH	864
#define SCREEN_HEIGHT	864
//! �X�N���[���̉����͍���������݂���̂ł����������
#define SCREEN_WIDTH_ANDUI	1064
//! �ꉞ�F
#define SCREEN_COLOR	32

//! �΂߈ړ��̂��߂̕ϊ��v�Z���l
#define PI        3.14159265f
#define PI_HARF	  PI * 0.5f
#define RadToDeg  57.29577951f
#define DegToRad  0.017453293f

//! �t�F�[�h���o�p
#define FADEBG "res\\BlackBox.png"
#define FADE_SIZE_X 1920
#define FADE_SIZE_Y 1080
#define FADE_SIZE_XY 36

//--------------------------------------------------------
//! �^�C�g��	864x864
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


//--------------------------------------------------------

//! �Q�[���w�i	908x864
//! ���T�C�h�݂̂͂����摜�T�C�Y�@22
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

//! �o���p�[	230x13
#define BUMPER	"res\\Bumper.png"
#define BUMPER_SIZE_X  246
#define BUMPER_SIZE_Y  36
#define BUMPER_PATTERN 3

//! �v���C���[
#define PLAYER_CHIP	"res\\Player.png"
#define PLAYER_PATTERN 4
#define PLAYER_SIZE 55
#define PLAYER_SIZE_HARF 27.5

//! �����O
#define PORTAL "res\\PortalChip.png"
#define PORTAL_SIZE 136
#define PORTAL_SIZE_HARF 68
// �����蔻��p
#define PORTAL_SIZE_HARFCOLLI 50
#define PORTAL_PATTERN 5

#define ZENEMY_CHIP01	"res\\ZEnemy1.png"
#define ZENEMY_CHIP02	"res\\ZEnemy2.png"
#define ZENEMY_CHIP03	"res\\ZEnemy3.png"
#define ZENEMY_CHIP04	"res\\ZEnemy4.png"
#define ZENEMY_PATTERN 4
#define ZENEMY_CHIP_SIZE_X 53
#define ZENEMY_CHIP_SIZE_Y 65
#define ZENEMY_CHIP_HARF 28
//#define ZENEMY_SE "res\\SE_Crash.wav"

#define BULLET_CHIP	"res\\Bullet.png"
#define BULLET_PATTERN 8
#define BULLET_CHIP_SIZE_X 8
#define BULLET_CHIP_SIZE_Y 8
#define BULLET_CHIP_SIZE_HARF 4
#define BULLET_SE "Res\\SE_Bullet.wav"

#define METAR_CHIP "res\\MeterChip.png"
#define METAR_PATTERN 5
#define METAR_CHIP_SIZE_X 199
#define METAR_CHIP_SIZE_Y 253

//-------------------------------------------------------------
#define CRASH_CHIP	"Res\\ZEnemyExpl.png"
//#define CRASH_CHIP	"Res\\.png"
#define CRASH_PATTERN 6
#define CRASH_CHIP_SIZE_X 64
#define CRASH_CHIP_SIZE_Y 64

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
	//! �G�̐��𐔂��邽��
	int ECount;
	//! �v���C���[�̃��x��
	//! Move���̊֌W�ł����ɒ�`���܂��B
	int Count;
	//! �L�[���͂���Ă���t���[�����L�^����
	int Key[256] = { 0 };
	//! �ꎞ��~
	bool Pause = false;
	//! �X�e�[�W��̓������~�߂�
	// false�œ���
	bool bMoveFlag;
	//! �^�C��
	int time = 0;
	//! fade���I���������̔���p
	bool bSceneFlag;
	// �X�e�[�W�ړ����̔w�i�p
	BGPhase m_ePhase;
	// ���j���[���ڂ̑I���ʒu
	int TitleMenuPos;

	//! �O���t�B�b�N�n���h��
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
	int GHPCrash[CRASH_PATTERN] = { 0 };
	int GHECrash[CRASH_PATTERN] = { 0 };

	//! �T�E���h�n���h��

	//�@�R���X�g���N�^
	CShoutingHockey();
	//�@�f�X�g���N�^
	~CShoutingHockey();

	//! Run
	void Run();

	//! �ړ�
	virtual void Move();
	//! �`��
	virtual void Draw();

	//! �^�X�N���X�g
	CRemTaskList *SceneList, *WaitList, *NFadeList, *SFadeList, *BGList,
		*BumperList, *PlayerList, *Enemy01List, *Enemy02List,
		*Enemy03List, *Enemy04List, *BulletList, *PortalList, *UiList,
		*TTextList, *EffectList;
	void MoveTask(CRemTaskList* list);
	void DrawTask(CRemTaskList* list);

	// �X�N���v�g
	CLoadScript* Script[];
};

extern CShoutingHockey* SH;