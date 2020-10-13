#include "stdafx.h"
#include "cameraText.h"



HRESULT cameraText::init(float x, float y, float xSize, float ySize, string text, FONT font, WORDSIZE size, WORDSORT sort, COLORREF color)
{
	_x = x;
	_y = y; 
	_xSize = xSize;
	_ySize = ySize; 
	_text = text;
	_font = font;
	_size = size;
	_sort = sort;
	_color = color;
	_isDead = false;
	_count = 0;

	return S_OK;
}

void cameraText::update()
{
	deleteText();
}

void cameraText::release()
{
}

void cameraText::render(HDC hdc)
{
	CAMERAMANAGER->TextInit(hdc, _x, _y, _xSize, _ySize, _text, _font, _size, _sort, _color);
}

void cameraText::deleteText()
{
	_count++;
	_y--;
	if (_count > 50)
	{
		_count = 0;
		_isDead = true;
	}
}



