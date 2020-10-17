#pragma once
class StageChanger
{
private :
	bool	_isChangingStage;
	float	_changerAlpha;
	image*	_coverImage;
	float	_soundVolume;
	int		_stage;
	int		_updown;
	int		_waitTime;

public:
	HRESULT init();
	void	render(HDC hdc);
	void	release();
	void	update();
	void	MoveStage(int stage);
	void	fadeInOut();

	bool	GetIsChangingStage() { return _isChangingStage; }
};

