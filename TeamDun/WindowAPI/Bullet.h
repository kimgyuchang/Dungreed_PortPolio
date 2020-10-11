#pragma once

enum BULLETTYPE
{
	BT_NOMAL,
	BT_NOCOL,
	BT_PLAYER,
	BT_PLAYERNOCOL
};
class Bullet
{
private :
	BULLETTYPE	_type;
	image*		_ig;
	string		_effectIgName;
	RECT		_rc;
	float		_x;
	float		_y;
	float		_startX;
	float		_startY;
	float		_angle;
	float		_speed;
	float		_igAngle;
	int			_frameX;
	int			_frameY;
	int			_frameTimer;
	float		_distance;
	float		_maxDistance;

	bool		_isFrame;
	bool		_isDead;

public :
	virtual HRESULT init();
	virtual void	update();
	virtual	void	release();
	virtual void	render(HDC hdc);
	void makeBullet(const char* imageName,string effectIgName, BULLETTYPE type, float x, float y, float angle, float speed, float maxDis, bool isFrame ,float igAngle =0);

	void moveBullet();
	void Animation();
	

	////GetSet
	BULLETTYPE getType() { return _type; }
	image* getIg() { return _ig; }
	string getEffectIgName(){return _effectIgName;}
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
	bool getIsDead() { return _isDead; }

	void SetType(BULLETTYPE type) {  _type = type; }
	void SetIg(image* ig) { _ig = ig; }
	void SetEffectIgName(string effectname) { _effectIgName = effectname; }
	void SetRc(RECT rc){ _rc = rc; }
	void SetX(float x) {  _x = x; }
	void SetY(float y) {  _y = y; }
	void SetStartX(float startX) {  _startX= startX; }
	void SetStartY(float startY) {  _startY = startY; }
	void SetAngle(float angle){ _angle = angle; }
	void SetSpeed(float speed) {  _speed = speed; }
	void SetFrameX(int frameX) { _frameX = frameX; }
	void SetFrameY(int frameY) {  _frameY = frameY; }
	void SetFrameTimer( int frameTimer) { _frameTimer = frameTimer; }
	void SetDis(float distance) { _distance= distance; }
	void SetMaxDis(float maxDistance) {  _maxDistance = maxDistance; }
	void SetIsDead(bool isDead) { _isDead = isDead; }
};
