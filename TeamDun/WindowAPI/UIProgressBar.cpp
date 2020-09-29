#include "stdafx.h"
#include "UIProgressBar.h"

HRESULT UIProgressBar::init(string name, float x, float y, float sizeX, float sizeY, string imageName, string imageName2, float scaleX, float scaleY)
{
	UIFrame::init(name, x, y, sizeX, sizeY, imageName, scaleX, scaleY);

	_backImg = IMAGEMANAGER->findImage(imageName2);
	_fillX = 0;
	_initX = 0;
	_fillPercent = 0;
	return S_OK;
}

void UIProgressBar::render(HDC hdc)
{
}

void UIProgressBar::update()
{
	UIFrame::update();
}

void UIProgressBar::FillCheck(float initX, float fillX)
{
	_fillPercent = _fillX / _initX;
	_imgFillX = _fillPercent * _backImg->getWidth();
}