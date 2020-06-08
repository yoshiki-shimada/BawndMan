/*******************************************************************
* @file		Selector.h
* @brief	セレクター.h
* @author	yshimada
* @data		20191215
*******************************************************************/

#pragma once
//-------------------------------------------------------
#include "Mover.h"
//-------------------------------------------------------

class CSelector : public CMover
{
protected:

public:
	int nStageNum;

	//　コンストラクタ
	CSelector() : CMover(SH->SceneList, 0, 0), nStageNum(0) {}

	void* operator new(size_t t) {
		return operator_new(t, SH->SceneList);
	}
	void operator delete(void* p) {
		operator_delete(p, SH->SceneList);
	}

};

//-------------------------------------------------------------
// @brief 定数
//-------------------------------------------------------------
enum {
	MENU_FIRST,
	MENU_SECOND,
	MENU_MAX
};

//=============================================================
// @brief タイトルのクラス
//=============================================================
class CTitle : public CSelector {
private:
	int nCount;
	bool bFade;

public:

	// コンストラクタ
	CTitle();

	// 移動、描画
	virtual bool Move();
	//virtual void Draw();
};

//=============================================================
//  @brief ステージクラス
//=============================================================

//フェードの配列カウント用
#define FADE_MAX 24

class CStage : public CSelector {

protected:
	// タイマー
	int Time;

public:
	// コンストラクタ
	CStage(int Num);

	// 移動、描画
	virtual bool Move();

	int nAlphaID;

private:
	// SFade用配列
	int nFadeCount[FADE_MAX][FADE_MAX];
	// SFade用IDNumber
	int nIDCount;

	// CreateSFade関数
	void CreateSFade();
	void FadeIn();
	void FadeOut();

	CreateLine m_eLine;
};
extern CStage *CS;

//==============================================================
// @brief Stage遷移時の準備クラス
// Waitはタスクを非共有
//==============================================================
class CWait : public CMover {
private:
	int nNum;
	int nCount;

public:
	CWait(int Num);

	void* operator new(size_t t) {
		return operator_new(t, SH->WaitList);
	}
	void operator delete(void* p) {
		operator_delete(p, SH->WaitList);
	}

	virtual bool Move();

};


//=============================================================
//  @brief ゲームオーバークラス
//=============================================================
class CGOver : public CSelector {

public:
	// メニュー項目の選択位置
	int MenuPos;

	// コンストラクタ
	CGOver();

	// 移動、描画
	virtual bool Move();
	virtual void Draw();
};

//=============================================================
//  @brief ゲームクリアクラス
//=============================================================
class CGCreal : public CSelector {

public:
	// メニュー項目の選択位置
	int MenuPos;

	// コンストラクタ
	CGCreal();

	// 移動、描画
	virtual bool Move();
	virtual void Draw();
};