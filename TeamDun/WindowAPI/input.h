#pragma once
#include "singletonBase.h"
//=============================================================
//	## input ## 입력매니져 (키보드, 마우스버튼)
//=============================================================

#define KEYMAX 256

class input : public singletonBase <input>
{
private:
	bool _keyUp[KEYMAX];
	bool _keyDown[KEYMAX];

	bool _isOnceClicked;
	int	_clickTimer;
	int _prevMouseWheel;

public:
	//입력매니져 초기화
	HRESULT init();
	//입력매니져 해제
	void update();
	void release();

	//키가 계속 눌려 있냐?
	bool GetKey(int key);
	//키가 한번만 눌렸냐?
	bool GetKeyDown(int key);
	//키가 한번 눌렸다 띄었냐?
	bool GetKeyUp(int key);
	//토글키냐? (참고로 유니티에는 이기능은 없음)
	bool GetToggleKey(int key);

	bool GetIsOnceClicked() { return _isOnceClicked; }
	int GetClickTimer() { return _clickTimer; }
	void SetIsOnceClicked(bool isOnceClicked) { _isOnceClicked = isOnceClicked; }
	void SetClickTimer(int clickTimer) { _clickTimer = clickTimer; }
	int GetMouseWheel();
	input() {}
	~input() {}
};