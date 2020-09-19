#pragma once
#include "singletonBase.h"
#include "UIText.h"
#include "UIImage.h"
#include "UIScroll.h" 

/// <summary>
/// UI전체를 관리하는 매니저이다.
/// </summary>
class UIManager : public singletonBase<UIManager>
{

public :
	UIFrame*			_GameFrame;		// 예시용

public :
	HRESULT init();
	void update();
	void render(HDC hdc);
	void release();

	UIFrame* GetGameFrame()		{ return _GameFrame; }
};

