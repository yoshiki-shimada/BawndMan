#pragma once

#include <vector>
#include <string>
#include "DxLib.h"
#include "ShoutingHockey.h"
#include "Enemy.h"
#include "Enemy02.h"
#include "Enemy03.h"
#include "Enemy04.h"
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


// Blue敵生成用関数へのポインタ
typedef CEnemy* (*NEW_ENEMY_FUNC01)(float x, float y);

/*
* @brief Blue敵生成コマンドクラス
*/
class CEnemyCommand01 : public CCommand {

	NEW_ENEMY_FUNC01 Func;
	float X, Y;

public:
	CEnemyCommand01(NEW_ENEMY_FUNC01 func, float x, float y)
		: Func(func), X(x), Y(y)
	{}
	virtual void Run() { Func(X, Y); }

};

// Green敵生成用関数へのポインタ
typedef CEnemy02* (*NEW_ENEMY_FUNC02)(float x, float y);

/*
* @brief Green敵生成コマンドクラス
*/
class CEnemyCommand02 : public CCommand {

	NEW_ENEMY_FUNC02 Func;
	float X, Y;

public:
	CEnemyCommand02(NEW_ENEMY_FUNC02 func, float x, float y)
		: Func(func), X(x), Y(y)
	{}
	virtual void Run() { Func(X, Y); }

};

// Yellow敵生成用関数へのポインタ
typedef CEnemy03* (*NEW_ENEMY_FUNC03)(float x, float y);

/*
* @brief Yellow敵生成コマンドクラス
*/
class CEnemyCommand03 : public CCommand {

	NEW_ENEMY_FUNC03 Func;
	float X, Y;

public:
	CEnemyCommand03(NEW_ENEMY_FUNC03 func, float x, float y)
		: Func(func), X(x), Y(y)
	{}
	virtual void Run() { Func(X, Y); }

};

// Red敵生成用関数へのポインタ
typedef CEnemy04* (*NEW_ENEMY_FUNC04)(float x, float y);

/*
* @brief Red敵生成コマンドクラス
*/
class CEnemyCommand04 : public CCommand {

	NEW_ENEMY_FUNC04 Func;
	float X, Y;

public:
	CEnemyCommand04(NEW_ENEMY_FUNC04 func, float x, float y)
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