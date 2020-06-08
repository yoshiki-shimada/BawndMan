/*******************************************************************
* @file		Selector.h
* @brief	�Z���N�^�[.h
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

	//�@�R���X�g���N�^
	CSelector() : CMover(SH->SceneList, 0, 0), nStageNum(0) {}

	void* operator new(size_t t) {
		return operator_new(t, SH->SceneList);
	}
	void operator delete(void* p) {
		operator_delete(p, SH->SceneList);
	}

};

//-------------------------------------------------------------
// @brief �萔
//-------------------------------------------------------------
enum {
	MENU_FIRST,
	MENU_SECOND,
	MENU_MAX
};

//=============================================================
// @brief �^�C�g���̃N���X
//=============================================================
class CTitle : public CSelector {
private:
	int nCount;
	bool bFade;

public:

	// �R���X�g���N�^
	CTitle();

	// �ړ��A�`��
	virtual bool Move();
	//virtual void Draw();
};

//=============================================================
//  @brief �X�e�[�W�N���X
//=============================================================

//�t�F�[�h�̔z��J�E���g�p
#define FADE_MAX 24

class CStage : public CSelector {

protected:
	// �^�C�}�[
	int Time;

public:
	// �R���X�g���N�^
	CStage(int Num);

	// �ړ��A�`��
	virtual bool Move();

	int nAlphaID;

private:
	// SFade�p�z��
	int nFadeCount[FADE_MAX][FADE_MAX];
	// SFade�pIDNumber
	int nIDCount;

	// CreateSFade�֐�
	void CreateSFade();
	void FadeIn();
	void FadeOut();

	CreateLine m_eLine;
};
extern CStage *CS;

//==============================================================
// @brief Stage�J�ڎ��̏����N���X
// Wait�̓^�X�N��񋤗L
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
//  @brief �Q�[���I�[�o�[�N���X
//=============================================================
class CGOver : public CSelector {

public:
	// ���j���[���ڂ̑I���ʒu
	int MenuPos;

	// �R���X�g���N�^
	CGOver();

	// �ړ��A�`��
	virtual bool Move();
	virtual void Draw();
};

//=============================================================
//  @brief �Q�[���N���A�N���X
//=============================================================
class CGCreal : public CSelector {

public:
	// ���j���[���ڂ̑I���ʒu
	int MenuPos;

	// �R���X�g���N�^
	CGCreal();

	// �ړ��A�`��
	virtual bool Move();
	virtual void Draw();
};