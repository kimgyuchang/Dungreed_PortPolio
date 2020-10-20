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
	int		_alpha;			// alpha
	int		_frameTimer;	// timer

public:
	HRESULT init(string name, float x, float y, float sizeX, float sizeY, string imageName, bool useFrameImage, int frameX, int frameY, float scaleX = 1, float scaleY = 1, int alpha = 255);
	virtual void update();
	void Animation();
	virtual void render(HDC hdc);
	
	int GetAlpha() { return _alpha; }

	void SetFrameX(int x) { _frameX = x; }
	void SetFrameY(int y) { _frameY = y; }
	void SetAlpha(int alpha) { _alpha = alpha; }
};
