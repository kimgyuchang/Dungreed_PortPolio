#pragma once
class Effect
{
private :
	float	_x;
	float	_y;
	image*	_image;
	int		_frameX;
	int		_frameY;
	int		_animTimer;
	int		_initAnimTimer;
	RECT	_body;
	bool	_isLoop;
	bool	_isDead;

public :
	
	HRESULT init(float x, float y, string imgName, int animSpeed, int frameX = 0, int frameY = 0, bool isLoop = false);
	void update();
	void release();
	void render(HDC hdc);
	void Animation();
	void DeleteEffect();

	// GETSET //
	bool GetIsDead() { return _isDead; }
};

