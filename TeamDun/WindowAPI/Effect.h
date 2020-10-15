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
	int		_alpha;
	float	_angle;
	float	_scaleX;
	float	_scaleY;
	bool	_isAlpha;
	bool	_useCamera;
public :
	HRESULT init(float x, float y, string imgName, int animSpeed, int frameX = 0, int frameY = 0, bool isLoop = false, int alpha = 255, float angle = 0, float scaleX = 1, float scaleY = 1 ,bool isAlpha = false, bool useCamera = false);
	void update();
	void release();
	void render(HDC hdc);
	void Animation();
	void DeleteEffect();
	void AlphaDeleteEffect();

	// GETSET //
	bool GetIsDead() { return _isDead; }
	float GetX() { return _x; }
	float GetY() { return _y; }
	int GetFrameX() { return _frameX; }
	int GetAnimTimer() { return _animTimer; }
};

