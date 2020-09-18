#include "stdafx.h"
#include "UIText.h"

void UIText::init(string name, float x, float y, string text, FONT font, WORDSIZE size, WORDSORT sort, int space, bool isAnimation, WORDANIMATIONSPEED speed)
{
	UIFrame::init(name, x, y, 0, 0, "");
	_text = text;
	_wordSize = size;
	_wordSort = sort;
	_font = font;
	_isAnimation = isAnimation;
	_animationSpeed = speed;
	_space = space;
}

void UIText::render(HDC hdc)
{
	if (_isViewing)
	{
		string fontName = "Word_Pix_Large";
		POINT framePt;
		switch (_font)
		{
		case PIX:
			switch (_wordSize)
			{
			case WS_BIG: fontName = "Font_Word_Pix_Big"; break;
			case WS_MIDDLE: fontName = "Font_Word_Pix_Middle"; break;
			case WS_SMALL: fontName = "Font_Word_Pix_Small"; break;
			}
			break;
		}

		float curX = _x;

		switch (_wordSort)
		{
		case WSORT_LEFT:
			for (int i = 0; i < _text.length(); i++)
			{
				framePt = UIMANAGER->GetWordFramePosition(_text[i]);
				IMAGEMANAGER->findImage(fontName)->frameRender(hdc, curX, _y, framePt.x, framePt.y);
				curX += IMAGEMANAGER->findImage(fontName)->getFrameWidth() - _space;
			}
			break;

		case WSORT_MIDDLE: // ¹Ì±¸Çö
			break;

		case WSORT_RIGHT:
			for (int i = _text.length()-1; i >= 0; i--)
			{
				framePt = UIMANAGER->GetWordFramePosition(_text[i]);
				IMAGEMANAGER->findImage(fontName)->frameRender(hdc, curX, _y, framePt.x, framePt.y);
				curX -= IMAGEMANAGER->findImage(fontName)->getFrameWidth() + _space;
			}
			break;
		}

		if (INPUT->GetKey('P')) Rectangle(hdc, _interactRect);
	}
}
