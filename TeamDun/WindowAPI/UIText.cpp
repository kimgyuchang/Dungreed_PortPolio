#include "stdafx.h"
#include "UIText.h"

/// <summary>
/// 초기화
/// </summary>
/// <param name="text">텍스트 내용</param>
/// <param name="font">글씨체</param>
/// <param name="size">크기</param>
/// <param name="sort">정렬 방식</param>
/// <param name="space">자간</param>
/// <param name="isAnimation">애니메이션 유무</param>
/// <param name="speed">애니메이션 속도</param>
void UIText::init(string name, float x, float y, float xSize, float ySize, string text, FONT font, WORDSIZE size, WORDSORT sort, COLORREF color, bool isAnimation, WORDANIMATIONSPEED speed)
{
	UIFrame::init(name, x, y, xSize, ySize, "");
	_text = text;
	_wordSize = size;
	_wordSort = sort;
	_font = font;
	_isAnimation = isAnimation;
	_animationSpeed = speed;
	_color = color;
	
	switch (speed) // 애니메이션 속도에 따른 애니메이션 타이머 설정
	{
	case WORDANIMATIONSPEED::WAS_FAST:
		_initAnimationTimer = _animationTimer = 1;
		break;

	case WORDANIMATIONSPEED::WAS_MIDDLE:
		_initAnimationTimer = _animationTimer = 3;
		break;

	case WORDANIMATIONSPEED::WAS_SLOW:
		_initAnimationTimer = _animationTimer = 5;
		break;
	}
}

void UIText::render(HDC hdc)
{

	HFONT hFont;
	HFONT OldFont;

	if (_isViewing) // 보이는 상태라면
	{
		string fontName = "";
		POINT framePt;
		switch (_font) // 폰트 종류에 따라
		{
		case PIX:
			switch (_wordSize) // 폰트 크기에 따라
			{
			case WS_BIG: 
				hFont = CreateFont(40, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0,
					VARIABLE_PITCH | FF_ROMAN, "Neo둥근모"); 
				break;
			case WS_MIDDLE: 
				hFont = CreateFont(30, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0,
					VARIABLE_PITCH | FF_ROMAN, "Neo둥근모"); 
				break;
			case WS_SMALL: 
				hFont = CreateFont(20, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0,
					VARIABLE_PITCH | FF_ROMAN, "Neo둥근모"); 
				break;
			case WS_SMALLEST:
				hFont = CreateFont(10, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0,
					VARIABLE_PITCH | FF_ROMAN, "Neo둥근모");
			} // 폰트를 결정
			break;
		}

		float curX = _x;
		SetTextColor(hdc, _color);
		OldFont = (HFONT)SelectObject(hdc, hFont);

		if (!_isAnimation) _cntPos = _text.length(); // 애니메이션이 아니면 언제나 모두 출력되게

		switch (_wordSort) // 정렬 방식에 따라
		{
		case WSORT_LEFT: // 좌측 정렬
			DrawText(hdc, _text.substr(0, _cntPos).c_str(), -1, &_interactRect, DT_LEFT | DT_WORDBREAK ); // 좌측정렬 & 멀티라인
			break;

		case WSORT_MIDDLE: // 가운데 정렬
			DrawText(hdc, _text.substr(0, _cntPos).c_str(), -1, &_interactRect, DT_CENTER | DT_WORDBREAK); // 가운데정렬 & 멀티라인
			break;

		case WSORT_RIGHT: // 우측 정렬
			DrawText(hdc, _text.substr(0, _cntPos).c_str(), -1, &_interactRect, DT_RIGHT | DT_WORDBREAK); // 우측정렬 & 멀티라인
			break;
		}

		if (_cntPos < _text.length()) // 애니메이션이면 출력 위치를 점점 늘인다.
		{
			_animationTimer--;
			if (_animationTimer == 0) // 애니메이션 속도에 따라 다른 타이머
			{
				_animationTimer = _initAnimationTimer;
				_cntPos++;
			}
		}

		SelectObject(hdc, OldFont);
		DeleteObject(hFont);

		if (INPUT->GetKey('P')) Rectangle(hdc, _interactRect);
	}
}
