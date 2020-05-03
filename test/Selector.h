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
	//　コンストラクタ
	CSelector() : CMover(SH->TitleList, 0, 0) {}

	void* operator new(size_t t) {
		return operator_new(t, SH->TitleList);
	}
	void operator delete(void* p) {
		operator_delete(p, SH->TitleList);
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
	// メニュー項目の選択位置
	int MenuPos;

	// コンストラクタ
	CTitle();

	// 移動、描画
	virtual bool Move();
	virtual void Draw();
};

//=============================================================
//  @brief ステージクラス
//=============================================================
class CStage : public CSelector {

protected:
	// タイマー
	int Time;

public:
	// コンストラクタ
	CStage();

	// 移動、描画
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