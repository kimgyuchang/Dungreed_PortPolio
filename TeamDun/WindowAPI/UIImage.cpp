#include "stdafx.h"
#include "UIImage.h"

/// <summary>
/// 초기화
/// </summary>
/// <param name="useFrameImage">FrameImage 사용 여부</param>
/// <param name="frameX">frame x index</param>
/// <param name="frameY">frame y index</param>
/// <returns></returns>
HRESULT UIImage::init(string name, float x, float y, float sizeX, float sizeY, string imageName, bool useFrameImage, int frameX, int frameY, float scaleX, float scaleY, int alpha)
{
	UIFrame::init(name, x, y, sizeX, sizeY, imageName, scaleX, scaleY);

	_useFrameImage = useFrameImage;
	_frameX = frameX;
	_frameY = frameY;
	_alpha = alpha;

	return S_OK;
}

void UIImage::render(HDC hdc)
{
	if (_isViewing)	// 보이는 상태
	{
		if (_isChild && _useOutsideLimit && _isOutside) {} // 자식이고 부모의 범위를 나갔다면

		else // 렌더하는 케이스
		{
			for (int i = 0; i < _vChildFrames.size(); i++) // 자식들 렌더
			{
				if (_vChildFrames[i]->GetRenderBeforeParent())
					_vChildFrames[i]->render(hdc);
			}
			if (_image != nullptr)
			{
				if (_useFrameImage) // 프레임 이미지 사용시
				{
					if (_alpha == 255)
					{
						if (_scaleX == 1 && _scaleY == 1)
							_image->frameRender(hdc, _x, _y, _frameX, _frameY);
						else
							_image->frameStretchRender(hdc, _x, _y, _frameX, _frameY, _scaleX, _scaleY);
					}

					else
					{
						if (_scaleX == 1 && _scaleY == 1)
							_image->frameAlphaRender(hdc, _x, _y, _frameX, _frameY, _alpha);

						else
							_image->frameStretchAlphaRender(hdc, _x, _y, _frameX, _frameY, _scaleX, _scaleY, _alpha);
					}
				}

				else // 미사용시
				{
					if (_alpha == 255)
					{
						if (_scaleX == 1 && _scaleY == 1)
							_image->render(hdc, _x, _y);
						else
							_image->stretchRender(hdc, _x, _y, _scaleX, _scaleY);
					}

					else
					{
						if (_scaleX == 1 && _scaleY == 1)
							_image->alphaRender(hdc, _x, _y, _alpha);

						else
						{
							_image->stretchAlphaRender(hdc, _x, _y, _scaleX, _scaleY, _alpha);
						}
					}
				}
			}

			if (INPUT->GetKey(VK_F3)) Rectangle(hdc, _interactRect); // P를 통해 상호작용 Rect 출력

			for (int i = 0; i < _vChildFrames.size(); i++) // 자식들 렌더
			{
				if(!_vChildFrames[i]->GetRenderBeforeParent())
					_vChildFrames[i]->render(hdc);
			}
			
		}
	}
}
