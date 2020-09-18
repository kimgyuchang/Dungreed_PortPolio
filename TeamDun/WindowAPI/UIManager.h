#pragma once
#include "singletonBase.h"
#include "UIText.h"
#include "UIImage.h"
#include "UIScroll.h" 

class UIManager : public singletonBase<UIManager>
{

public :
	vector<UIImage*> _vItemToBag;
	UIFrame* _GameFrame;
	UIFrame* _PlayerFrame;

public :
	HRESULT init();
	void update();
	void render(HDC hdc);
	void release();
	POINT GetWordFramePosition(char ch);

	UIFrame* GetGameFrame()		{ return _GameFrame; }
	UIFrame* GetPlayerFrame()	{ return _PlayerFrame; }
};

