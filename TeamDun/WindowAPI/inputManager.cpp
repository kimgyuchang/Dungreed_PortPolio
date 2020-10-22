#include "stdafx.h"
#include "inputManager.h"

HRESULT inputManager::init()
{
	//키값을 전부 눌려있지 않은 상태로 초기화
	for (int i = 0; i < KEYMAX; i++)
	{
		_keyUp[i] = false;
		_keyDown[i] = false;
	}

	_clickTimer = 0;
	_isOnceClicked = false;
	_isLButtonClicked = false;
	_isRButtonClicked = false;
	return S_OK;
}

void inputManager::update()
{
	_isLButtonClicked = false;
	_isRButtonClicked = false;
	_isLButtonUp = false;

	if (GetKeyDown(VK_LBUTTON)) _isLButtonClicked = true;
	if (GetKeyDown(VK_RBUTTON)) _isRButtonClicked = true;
	if (GetKeyUp(VK_LBUTTON)) _isLButtonUp = true;
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

void inputManager::release()
{
}

bool inputManager::GetKey(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
	{
		return true;
	}
	return false;
}

bool inputManager::GetKeyDown(int key)
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

bool inputManager::GetKeyUp(int key)
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

bool inputManager::GetToggleKey(int key)
{
	if (GetKeyState(key) & 0x0001)
	{
		return true;
	}
	return false;
}
