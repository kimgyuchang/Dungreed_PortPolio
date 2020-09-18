#pragma once
#include "UIManager.h"
#include "UIFrame.h"

enum WORDSIZE
{
	WS_BIG, WS_MIDDLE, WS_SMALL
};

enum WORDANIMATIONSPEED
{
	WAS_FAST, WAS_MIDDLE, WAS_SLOW
};

enum WORDSORT
{
	WSORT_LEFT, WSORT_MIDDLE, WSORT_RIGHT
};

enum FONT
{
	PIX
};

class UIText : public UIFrame
{
private:
	string				_text;
	WORDSIZE			_wordSize;
	WORDSORT			_wordSort;
	FONT				_font;
	int					_space;
	bool				_isAnimation;
	WORDANIMATIONSPEED	_animationSpeed;
public:
	string GetText() { return _text; }
	bool GetIsAnimation() { return _isAnimation; }
	WORDSIZE GetWordSize() { return _wordSize; }

	void SetText(string text) { _text = text; }

	virtual void init(string name, float x, float y, string text, FONT font, WORDSIZE size, WORDSORT sort = WORDSORT::WSORT_LEFT, int space = 0, bool isAnimation = false, WORDANIMATIONSPEED speed = WORDANIMATIONSPEED::WAS_MIDDLE);
	virtual void render(HDC hdc);
};
