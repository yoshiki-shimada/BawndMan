/*******************************************************************
* @file		Selector.h
* @brief	シーン管理用.h
* @author	yshimada
* @data		20191215
*******************************************************************/

#pragma once
//-------------------------------------------------------
#include "Mover.h"
//-------------------------------------------------------

//#define SCRIPT_LENGTH(array) (sizeof(*SH->Script) / sizeof(SH->Script[0]))

class CSelector : public CMover
{
public:
	// ステージ番号
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
	//bool bFade;
	// クリックしたかの判定
	bool bClick;

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
	// フェードに入っているかの判定
	int bFadeFlag;

public:
	// コンストラクタ
	CStage(int Num);

	// 移動、描画
	virtual bool Move();

	//// SFade用ID
	//int nAlphaID;

private:
	// SFade用配列
	int nFadeCount[FADE_MAX][FADE_MAX];
	// SFade用IDNumber
	int nIDCount;

	// CreateSFade関数
	//void CreateSFade();
	//void FadeIn();
	//void FadeOut();

	CreateLine m_eLine;
};
extern CStage *CS;


//==============================================================
// @brief Stage遷移時の準備クラス
// Waitはタスクを非共有
//==============================================================
class CWait : public CMover {
private:
	// ステージ番号受け取り用
	int nNum;
	// WaitTime
	int nCount;

public:
	// コンストラクタ
	CWait(int Num);

	void* operator new(size_t t) {
		return operator_new(t, SH->WaitList);
	}
	void operator delete(void* p) {
		operator_delete(p, SH->WaitList);
	}

	// 移動処理
	virtual bool Move();

};


//class CCG : CMover {
//public:
//	CCG() : CMover(SH->ClearOverList, 0, 0) {}
//
//	void* operator new(size_t t) {
//		return operator_new(t, SH->ClearOverList);
//	}
//	void operator delete(void* p) {
//		operator_delete(p, SH->ClearOverList);
//	}
//};

//=============================================================
//  @brief ゲームオーバークラス
//=============================================================
class CGOver : public CSelector {
private:
	// フェードに入っているかの判定
	int bFadeFlag;

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
private:
	// フェードに入っているかの判定
	int bFadeFlag;

public:
	// メニュー項目の選択位置
	int MenuPos;

	// コンストラクタ
	CGCreal();

	// 移動、描画
	virtual bool Move();
	virtual void Draw();
};