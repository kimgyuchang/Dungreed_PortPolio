#pragma once
#include "UIFrame.h"

class UIImage : public UIFrame
{
private:
	bool _useFrameImage;
	int _frameX;
	int _frameY;

public:
	virtual	HRESULT init(string name, float x, float y, float sizeX, float sizeY, string imageName, bool useFrameImage, int frameX, int frameY);
	virtual void render(HDC hdc);

	void SetFrameX(int x) { _frameX = x; }
	void SetFrameY(int y) { _frameY = y; }
};
