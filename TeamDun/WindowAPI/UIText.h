#pragma once
#include "UIManager.h"
#include "UIFrame.h"

// 글자의 크기
enum WORDSIZE
{
	WS_BIG, WS_MIDDLE, WS_SMALL
};

// 글자가 애니메이션으로 나오는 속도
enum WORDANIMATIONSPEED
{
	WAS_FAST, WAS_MIDDLE, WAS_SLOW
};

// 글자가 어떤 정렬을 하고 있는지
enum WORDSORT
{
	WSORT_LEFT, WSORT_MIDDLE, WSORT_RIGHT
};

// 폰트 종류
enum FONT
{
	PIX
};


// ttf 적용 테스트 후 수정 예정
/// <summary>
/// UIText는 UIFrame을 상속하여 UIFrame의 기능도 사용하며, Text를 위한 기능 역시 존재한다.
/// </summary>
class UIText : public UIFrame 
{
private:
	string				_text;				// 이 TextUI의 내용
	WORDSIZE			_wordSize;			// 이 TextUI의 크기
	WORDSORT			_wordSort;			// 이 TextUI의 정렬 방식
	FONT				_font;				// 이 TextUI가 사용할 폰트
	int					_space;				// 이 TextUI의 자간
	bool				_isAnimation;		// 이 TextUI가 Animation을 사용하는지
	WORDANIMATIONSPEED	_animationSpeed;	// 이 TextUI의 Animation 속도

public:
	string GetText() { return _text; }
	bool GetIsAnimation() { return _isAnimation; }
	WORDSIZE GetWordSize() { return _wordSize; }

	void SetText(string text) { _text = text; }

	virtual void init(string name, float x, float y, string text, FONT font, WORDSIZE size, WORDSORT sort = WORDSORT::WSORT_LEFT, int space = 0, bool isAnimation = false, WORDANIMATIONSPEED speed = WORDANIMATIONSPEED::WAS_MIDDLE);
	virtual void render(HDC hdc);
	POINT GetWordFramePosition(char ch);
};
