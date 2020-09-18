#include "stdafx.h"
#include "Grid.h"

HRESULT Grid::init()
{
	return S_OK;
}

void Grid::release()
{
}

void Grid::update()
{
}

void Grid::render(HDC hdc)
{
	Rectangle(hdc, _rc);
	if(_ig) _ig->render(hdc, _x + 1, _y + 1);
}
