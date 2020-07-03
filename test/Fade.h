/*******************************************************************
* @file		Fade.h
* @brief	フェード用.h
* @author	yshimada
* @data		20191220
*******************************************************************/

#pragma once

#include "Mover.h"


/************************
* @brief フェードクラス
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

///************************
//* @brief フェード描画クラス
//************************/
//class CSFade : public CMover
//{
//public:
//	CSFade(int x, int y, int ID);
//
//	void* operator new(size_t t) {
//		return operator_new(t, SH->SFadeList);
//	}
//	void operator delete(void* p) {
//		operator_delete(p, SH->SFadeList);
//	}
//
//	virtual bool Move();
//	virtual void Draw();
//
//private:
//	float X;
//	float Y;
//	int nID;
//
//	FadePhase m_ePhase;
//
//};