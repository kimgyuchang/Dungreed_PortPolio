#pragma once
#include "UIFrame.h"

/// <summary>
/// UIImage는 이미지 표현에 특화된 UI이다.
/// </summary>
class UIImage : public UIFrame // UIFrame을 상속받아 UIFrame의 기능을 모두 이용할 수 있다.
{
private:
	bool	_useFrameImage;	// FrameImage 사용 여부
	int		_frameX;		// FrameX
	int		_frameY;		// FrameY

	// 안녕하세요
public:
	HRESULT init(string name, float x, float y, float sizeX, float sizeY, string imageName, bool useFrameImage, int frameX, int frameY, float scaleX = 1, float scaleY = 1);
	virtual void render(HDC hdc);

	void SetFrameX(int x) { _frameX = x; }
	void SetFrameY(int y) { _frameY = y; }
};
