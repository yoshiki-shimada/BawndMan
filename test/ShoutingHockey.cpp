/*******************************************************************
* @file		SH.h
* @brief	MainClass.cpp
* @author	yshimada
* @data		20191215
*******************************************************************/

#include "DxLib.h"
#include "ShoutingHockey.h"
#include "Selector.h"
#include "BG.h"
#include "Bumper.h"
#include "Portal.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Fade.h"
#include "LoadScript.h"


CShoutingHockey *SH;

//! �R���X�g���N�^
CShoutingHockey::CShoutingHockey() : ECount(0), Count(0), bMoveFlag(false)
{
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_COLOR);
	ChangeWindowMode(TRUE);
	DxLib_Init();
	SetDrawScreen(DX_SCREEN_BACK);

	// �^�X�N���X�g�̏�����
	SceneList = new CRemTaskList(sizeof(CStage), 100);
	BGList = new CRemTaskList(sizeof(CBGStage1), 10);
	BumperList = new CRemTaskList(sizeof(CBumper), 10);
	PortalList = new CRemTaskList(sizeof(CPortal), 100);
	EnemyList = new CRemTaskList(sizeof(CZakoEnemy1), 100);
	BulletList = new CRemTaskList(sizeof(CBullet), 100);
	PlayerList = new CRemTaskList(sizeof(CNormalPlayer), 10);
	NFadeList = new CRemTaskList(sizeof(CNFade), 10);
	SFadeList = new CRemTaskList(sizeof(CSFade), 100);


	// �O���t�B�b�N�n���h���̏�����
	//! �^�C�g��
	LoadDivGraph(TITLEBG, 1,
		1, 1,
		TITLE_SIZE_X, TITLE_SIZE_Y,
		&GHTitle
	);
	//! �X�e�[�W�̏�
	LoadDivGraph(BGSTAGEFLOOR, BG_PATTERN,
		BG_PATTERN, 1,
		BGSTAGE1_SIZE_X, BGSTAGE1_SIZE_Y,
		GHStageFloor
	);
	//! �o���p�[
	LoadDivGraph(BUMPER, 1,
		1, 1,
		BUMPER_SIZE_X, BUMPER_SIZE_Y,
		&GHBumper
	);
	//! �|�[�^��
	LoadDivGraph(PORTAL, PORTAL_PATTERN,
		PORTAL_PATTERN, 1,
		PORTAL_SIZE, PORTAL_SIZE,
		GHPortal
	);
	//! �v���C���[
	LoadDivGraph(PLAYER_CHIP, PLAYER_PATTERN,
		PLAYER_PATTERN, 1,
		PLAYER_SIZE, PLAYER_SIZE,
		GHPlayer
	);
	//! �G�l�~�[
	LoadDivGraph(ZENEMY_CHIP, ZENEMY_PATTERN,
		ZENEMY_PATTERN, 1,
		ZENEMY_CHIP_SIZE_X, ZENEMY_CHIP_SIZE_Y,
		GHZEnemy
	);
	LoadDivGraph(BULLET_CHIP, BULLET_PATTERN,
		BULLET_PATTERN, 1,
		BULLET_CHIP_SIZE_X, BULLET_CHIP_SIZE_Y,
		GHBullet
	);
	//! �m�[�}���t�F�[�h
	LoadDivGraph(FADEBG, 1,
		1, 1,
		FADE_SIZE_X, FADE_SIZE_Y,
		&GHNFade
	);
	//! �X�y�V�����t�F�[�h
	LoadDivGraph(FADEBG, 1,
		1, 1,
		FADE_SIZE_XY, FADE_SIZE_XY,
		&GHSFade
	);

	//! �T�E���h�n���h���̏�����

	// �X�N���v�g
	Script[5] = {
		new CLoadScript("Res\\Stage01Script.txt") 

	};
}

//! �f�X�g���N�^
CShoutingHockey::~CShoutingHockey()
{
	DxLib_End();
}

void CShoutingHockey::Run() {
	while (!ProcessMessage()) {
		ClearDrawScreen();

		//! �������̏���
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
* @brief �ړ�
***************************************************************/
void CShoutingHockey::Move() {
	if (Pause)
		return;

	MoveTask(SceneList);
	MoveTask(BGList);
	if (!bMoveFlag) {
		MoveTask(BumperList);
		MoveTask(PortalList);
		MoveTask(BulletList);
		MoveTask(PlayerList);
		MoveTask(EnemyList);
	}
	MoveTask(NFadeList);
	MoveTask(SFadeList);
}

/***************************************************************
* @brief �`��
***************************************************************/
void CShoutingHockey::Draw() {
	DrawTask(SceneList);
	DrawTask(BGList);
	DrawTask(BumperList);
	DrawTask(PortalList);
	DrawTask(BulletList);
	DrawTask(PlayerList);
	DrawTask(EnemyList);
	DrawTask(NFadeList);
	DrawTask(SFadeList);
}

/****************************************************************
* @brief �^�X�N�̓���
*****************************************************************/
void CShoutingHockey::MoveTask(CRemTaskList* list) {
	for (CRemTaskIter i(list); i.HasNext(); ) {
		CMover* mover = (CMover*)i.Next();
		if (!mover->Move()) i.Remove();
	}
}


/****************************************************************
* �^�X�N�̕`��
*****************************************************************/
void CShoutingHockey::DrawTask(CRemTaskList* list) {
	for (CRemTaskIter i(list); i.HasNext(); ) {
		((CMover*)i.Next())->Draw();
	}
}

//=============================================================
// ���C�����[�`��
//=============================================================
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int)
{
	SH = new CShoutingHockey();
	new CTitle();
	new CNFade(FADEIN);

	//! �Q�[���̎��s
	SH->Run();
	delete SH;
	return 0;
}