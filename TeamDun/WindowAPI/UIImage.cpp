#include "stdafx.h"
#include "UIImage.h"

HRESULT UIImage::init(string name, float x, float y, float sizeX, float sizeY, string imageName, bool useFrameImage, int frameX, int frameY)
{
	UIFrame::init(name, x, y, sizeX, sizeY, imageName);
	
	_useFrameImage = useFrameImage;
	_frameX = frameX;
	_frameY = frameY;
	
	return S_OK;
}

void UIImage::render(HDC hdc)
{
	if (_isViewing)
	{
		if (_isChild)
		{
			if (_useOutsideLimit && _isOutside) {}
			else
			{
				if (_image != nullptr)
				{
					if (_useFrameImage)
					{
						_image->frameRender(hdc, _x, _y, _frameX, _frameY);
					}

					else
					{
						_image->render(hdc, _x, _y);
					}
				}
				if (INPUT->GetKey('P')) Rectangle(hdc, _interactRect);

				for (int i = 0; i < _vChildFrames.size(); i++)
				{
					_vChildFrames[i]->render(hdc);
				}
			}
		}

		else
		{
			if (_image != nullptr)
			{
				if (_useFrameImage)
				{
					_image->frameRender(hdc, _x, _y, _frameX, _frameY);
				}

				else
				{
					_image->render(hdc, _x, _y);
				}
			}
			if (INPUT->GetKey('P')) Rectangle(hdc, _interactRect);

			for (int i = 0; i < _vChildFrames.size(); i++)
			{
				_vChildFrames[i]->render(hdc);
			}
		}
	}
}
