#pragma once
#include "UIFrame.h"

class UIProgressBar : public UIFrame
{
private:
	image*	_backImg;		// 백그라운드 이미지
	float	_fillPercent;	// 채워진 정도 (%)
	float   _imgFillX;		// 채워진 정도 (수치)

public:
	// 기본 //
	virtual HRESULT init(string name, float x, float y, float sizeX, float sizeY, string imageName, string backImgName);
	virtual void render(HDC hdc);
	virtual void update();
	
	void FillCheck(float initX, float fillX);
};

