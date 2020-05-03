#pragma once

#include "Mover.h"

//�t�F�[�h�̔z��J�E���g�p
#define FADE_MAX 24

/************************
* @brief �t�F�[�h�N���X
************************/
class CNFade : public CMover
{
public:
	CNFade(FadePhase m_Phase);

	void* operator new(size_t t) {
		return operator_new(t, SH->NFadeList);
	}
	void operator delete(void* p) {
		operator_delete(p, SH->NFadeList);
	}

	virtual bool Move();
	virtual void Draw();

private:
	int nAlpha;
	int nAlphaCount;
	
	FadePhase m_ePhase;

};

/************************
* @brief �t�F�[�h�`��N���X
************************/
class CSFade : public CMover
{
public:
	CSFade(FadePhase m_Phase, int x, int y);

	void* operator new(size_t t) {
		return operator_new(t, SH->SFadeList);
	}
	void operator delete(void* p) {
		operator_delete(p, SH->SFadeList);
	}

	virtual bool Move();
	virtual void Draw();

private:
	int nFadeCount[FADE_MAX][FADE_MAX];
	int nCount;

	FadePhase m_ePhase;

};