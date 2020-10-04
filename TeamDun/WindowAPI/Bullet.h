#pragma once

enum BULLETTYPE
{
	BT_NOMAL,BT_NOCOL
};
class Bullet
{
	
private :
	BULLETTYPE	_type;
	image*		_ig;
	RECT		_rc;
	float		_x;
	float		_y;
	float		_startX;
	float		_startY;
	float		_angle;
	float		_speed;
	int			_frameX;
	int			_frameY;
	int			_frameTimer;
	float		_distance;
	float		_maxDistance;

	bool		_isFrame;

public :
	virtual HRESULT init();
	virtual void	update();
	virtual	void	release();
	virtual void	render(HDC hdc);
	void makeBullet(const char* imageName, BULLETTYPE type, float x, float y, float angle, float speed, float maxDis, bool isFrame);

	void moveBullet();
	void Animation();
	

	////GetSet
	BULLETTYPE getType() { return _type; }
	image* getIg() { return _ig; }
	RECT getRc() { return _rc; }
	float getX() { return _x; }
	float getY() { return _y; }
	float getStartX() { return _startX; }
	float getStartY() { return _startY; }
	float getAngle() { return _angle; }
	float getSpeed() { return _speed; }
	int	  getFrameX() { return _frameX; }
	int	  getFrameY() { return _frameY; }
	int	  getFrameTimer() { return _frameTimer; }
	float getDis() { return _distance; }
	float getMaxDis() { return _maxDistance; }
};
