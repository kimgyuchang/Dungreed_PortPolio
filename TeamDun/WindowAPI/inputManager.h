#pragma once
#include "singletonBase.h"
//=============================================================
//	## input ## 입력매니져 (키보드, 마우스버튼)
//=============================================================

#define KEYMAX 256
class inputManager : public singletonBase <inputManager>
{
private:
	bool	_keyUp[KEYMAX];
	bool	_keyDown[KEYMAX];

	bool	_isOnceClicked;
	int		_clickTimer;
	int		_prevMouseWheel;

	// 이번 프레임의 INPUT 목록 //
	bool	_isLButtonClicked;
	bool	_isRButtonClicked;
	bool	_isLButtonUp;
	bool	_isEscapePressed;

	// 프레임 키 체커 //
	void FrameKeyInputChecker();

public:
	// 기본 //
	inputManager() {}
	~inputManager() {}
	HRESULT init();
	void update();
	void release();

	// 키 입력 관련 //
	bool GetKey(int key);
	bool GetKeyDown(int key);
	bool GetKeyUp(int key);
	bool GetToggleKey(int key);

	// GETSET //
	bool	GetIsLButtonUp()						{ return _isLButtonUp; }
	bool	GetIsOnceClicked()						{ return _isOnceClicked; }
	int		GetClickTimer()							{ return _clickTimer; }
	bool	GetIsLButtonClicked()					{ return _isLButtonClicked; }
	bool	GetIsRButtonClicked()					{ return _isRButtonClicked; }
	bool	GetIsEscapeKeyPressed()					{ return _isEscapePressed; }
	
	void	SetIsOnceClicked(bool isOnceClicked)	{ _isOnceClicked = isOnceClicked; }
	void	SetClickTimer(int clickTimer)			{ _clickTimer = clickTimer; }
};