#include "stdafx.h"
#include "UIProgressBar.h"

HRESULT UIProgressBar::init(string name, float x, float y, float sizeX, float sizeY, string imageName, string imageName2)
{
	UIFrame::init(name, x, y, sizeX, sizeY, imageName, 1, 1);

	_backImg = IMAGEMANAGER->findImage(imageName2);
	_fillPercent = 0;
	_imgFillX = 0;
	return S_OK;
}

void UIProgressBar::render(HDC hdc)
{
	if (_isViewing) // 보이는 상태이며
	{
		if (_isChild && _useOutsideLimit && _isOutside) {} // 자식이며, 범위제한을 사용했고 부모의 범위를 넘었다면 그리지 않음.

		else // 그게 아니라면
		{
			for (int i = 0; i < _vChildFrames.size(); i++)
			{
				if (_vChildFrames[i]->GetRenderBeforeParent()) // 부모 렌더 전에 렌더되는 자식이라면
					_vChildFrames[i]->render(hdc);
			}

			if (_image != nullptr)
			{
				_backImg->render(hdc, _x, _y);
				_image->render(hdc, _x, _y, 0, 0, _imgFillX, _backImg->getHeight()); // 그린다
			}

			if (INPUT->GetKey(VK_F3)) Rectangle(hdc, _interactRect); // P를 누른 상태라면 충돌 범위도 그린다

			for (int i = 0; i < _vChildFrames.size(); i++) // 자식 역시 그린다
			{
				if (!_vChildFrames[i]->GetRenderBeforeParent()) // 부모 렌더 후에 렌더되는 자식이라면
					_vChildFrames[i]->render(hdc);
			}
		}
	}
}

void UIProgressBar::update()
{
	UIFrame::update();
}

void UIProgressBar::FillCheck(float initX, float fillX)
{
	_fillPercent = fillX / initX;
	_imgFillX = _fillPercent * _backImg->getWidth();
}