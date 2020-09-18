#pragma once
#include "UIFrame.h"
class UIScroll : public UIFrame
{
private :
	UIFrame*	_target;
	float		_scrollPercent;

	void CalculateScrollBarPercent();

public :

	virtual	HRESULT init(string name, float x, float y, float sizeX, float sizeY, string imageName);
	virtual void update();

	UIFrame* GetTarget() { return _target; }
	float GetScrollPercent() { return _scrollPercent; }

	void SetTarget(UIFrame* target) { _target = target; }
	void SetScroll(float percent) { _scrollPercent = percent; }

	void MoveScrollBar();
};

