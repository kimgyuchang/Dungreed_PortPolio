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
	_isEscapePressed = false;
	return S_OK;
}

void inputManager::update()
{
	FrameKeyInputChecker();

	if (_isOnceClicked)
	{
		_clickTimer++;
		if (_clickTimer > 30)
		{
			_clickTimer = 0;
			_isOnceClicked = false;
		}
	}
}

/// <summary>
/// 매 프레임의 체크해야할 마우스 및 키보드 입력을 업데이트한다.
/// </summary>
void inputManager::FrameKeyInputChecker()
{
	// 초기화
	_isLButtonClicked = false;
	_isRButtonClicked = false;
	_isLButtonUp = false;
	_isEscapePressed = false;

	// 업데이트
	if (GetKeyDown(VK_LBUTTON)) _isLButtonClicked = true;
	if (GetKeyDown(VK_RBUTTON)) _isRButtonClicked = true;
	if (GetKeyDown(VK_ESCAPE)) _isEscapePressed = true;
	if (GetKeyUp(VK_LBUTTON)) _isLButtonUp = true;
	
	if (_mouseWheel == _prevMouseWheel) _mouseWheel = 0; // 마우스 휠이 저번과 같으면 입력되지 않았다 가정
	_prevMouseWheel = _mouseWheel;
}

void inputManager::release()
{
}

/// <summary>
/// 키를 계속 누르고 있는지 체크
/// </summary>
bool inputManager::GetKey(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
	{
		return true;
	}
	return false;
}

/// <summary>
/// 이번 프레임에 키를 누르기 시작했는지 체크
/// </summary>
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

/// <summary>
/// 이번 프레임에 키를 뗏는지 체크
/// </summary>
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

/// <summary>
/// 키 상태가 바뀌었는지 체크
/// </summary>
bool inputManager::GetToggleKey(int key)
{
	if (GetKeyState(key) & 0x0001)
	{
		return true;
	}
	return false;
}
