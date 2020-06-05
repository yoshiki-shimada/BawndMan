#pragma once

#include <vector>
#include <string>
#include "DxLib.h"
#include "ShoutingHockey.h"
#include "Enemy.h"
#include "Portal.h"
#include "Bumper.h"

using namespace std;

/*
* @brief コマンドクラス
*/
class CCommand {
public:
	// 純粋仮想に
	virtual void Run() = 0;

};

/*
* @brief スクリプトクラス
*/
class CLoadScript
{
	// コマンドを保持する配列
	vector<CCommand*> Command;

	// 実行コマンド番号
	int nCommandIndex;

public:
	// コンストラクタ
	CLoadScript(string file);

	// 実行開始、実行の設定
	void Init();
	void Run();


};


// 敵生成用関数へのポインタ
typedef CEnemy* (*NEW_ENEMY_FUNC)(float x, float y);

/*
* @brief 敵生成コマンドクラス
*/
class CEnemyCommand : public CCommand {

	NEW_ENEMY_FUNC Func;
	float X, Y;

public:
	CEnemyCommand(NEW_ENEMY_FUNC func, float x, float y)
		: Func(func), X(x), Y(y)
	{}
	virtual void Run() { Func(X, Y); }

};

typedef CPortal* (*NEW_PORTAL_FUNC)(float x, float y, float dir);

class CPortalCommand :public CCommand {
	NEW_PORTAL_FUNC Func;
	float X, Y, DIR;

public:
	CPortalCommand(NEW_PORTAL_FUNC func, float x, float y, float dir)
		: Func(func), X(x), Y(y), DIR(dir)
	{}
	virtual void Run() { Func(X, Y, DIR); }

};