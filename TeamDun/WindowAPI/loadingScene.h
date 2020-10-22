#pragma once
#include "gameNode.h"
#include "loading.h"

class loadingScene : public gameNode
{
private:
	Loading*	_loading;

	// 연출 관련 //
	progressBar*	_loadingBar;		// 로딩바
	int				_currentGauge;		// 로딩바 게이지 값
	int				_animationCount;	// 로딩시 이미지 애니메이션 재생
	int				_animationFrame;	// 로딩시 이미지 프레임
	image*			_background;		// 백그라운드 이미지
	string			_text[11];
public:
	HRESULT init();
	void	release();
	void	update();
	void	render();

	void LoadData();

	void animation();

	void loadingFont();
	void loadingImage();
	void loadingSound();

	// GETSET //
	int getCurrentGauge() { return _currentGauge; }
};

