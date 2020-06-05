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
* @brief �R�}���h�N���X
*/
class CCommand {
public:
	// �������z��
	virtual void Run() = 0;

};

/*
* @brief �X�N���v�g�N���X
*/
class CLoadScript
{
	// �R�}���h��ێ�����z��
	vector<CCommand*> Command;

	// ���s�R�}���h�ԍ�
	int nCommandIndex;

public:
	// �R���X�g���N�^
	CLoadScript(string file);

	// ���s�J�n�A���s�̐ݒ�
	void Init();
	void Run();


};


// �G�����p�֐��ւ̃|�C���^
typedef CEnemy* (*NEW_ENEMY_FUNC)(float x, float y);

/*
* @brief �G�����R�}���h�N���X
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