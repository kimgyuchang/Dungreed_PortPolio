#include "stdafx.h"
#include "input.h"

HRESULT input::init()
{
	//키값을 전부 눌려있지 않은 상태로 초기화
	for (int i = 0; i < KEYMAX; i++)
	{
		_keyUp[i] = false;
		_keyDown[i] = false;
	}

	_clickTimer = 0;
	_isOnceClicked = false;

	return S_OK;
}

void input::update()
{
	if (_isOnceClicked)
	{
		_clickTimer++;
		if (_clickTimer > 30)
		{
			_clickTimer = 0;
			_isOnceClicked = false;
		}
	}

	if (_mouseWheel == _prevMouseWheel)
	{
		_mouseWheel = 0;
	}
	_prevMouseWheel = _mouseWheel;
}

void input::release()
{
}

bool input::GetKey(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
	{
		return true;
	}
	return false;
}

bool input::GetKeyDown(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
	{
		if (!_keyDown[key])
		{
			_keyDown[key] = true;
			return true;
		}
	}
	else
	{
		_keyDown[key] = false;
	}

	return false;
}

bool input::GetKeyUp(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
	{
		_keyUp[key] = true;
	}
	else
	{
		if (_keyUp[key])
		{
			_keyUp[key] = false;
			return true;
		}
	}

	return false;
}

bool input::GetToggleKey(int key)
{
	if (GetKeyState(key) & 0x0001)
	{
		return true;
	}
	return false;
}

int input::GetMouseWheel()
{

	return 0;
}
