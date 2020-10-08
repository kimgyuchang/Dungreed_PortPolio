#pragma once
#include "UIFrame.h"

/// <summary>
/// UIScroll은 스크롤 바에 특화된 UI이다.
/// </summary>
class UIScroll : public UIFrame // UIFrame을 상속받아 UIFrame의 기능들도 모두 이용할 수 있다.
{
private :
	UIFrame*	_target;		// Scroll이 움직일 타겟 UI
	float		_scrollPercent;	// Scroll이 얼마만큼 내려왔는지 비율
	bool		_isVertical;	// Scroll이 세로면

	void CalculateScrollBarPercent();
	
public :

	virtual	HRESULT init(string name, float x, float y, float sizeX, float sizeY, string imageName);
	virtual void update();

	UIFrame* GetTarget() { return _target; }
	float GetScrollPercent() { return _scrollPercent; }

	void SetTarget(UIFrame* target) { _target = target; }
	void SetScroll(float percent) { _scrollPercent = percent; }
	void SetIsVertical(bool vertical) { _isVertical = vertical; }
	void MoveScrollBar();
};

