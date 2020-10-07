#pragma once
#include "singletonBase.h"
#include "image.h"

class CameraManager : public singletonBase<CameraManager>
{
private:

	// CAMERAFOLLOW //
	RECT	_cameraRect;		// 현재 카메라의 좌표 (RelativeX, Y를 구할때 사용)
	float	_pivotX;			// 현재 카메라가 중심으로 잡고있는 PIVOT X
	float	_pivotY;			// 현재 카메라가 중심으로 잡고있는 PIVOT Y
	float	_maxX;				// 카메라가 최대한 따라가는 거리 X
	float	_maxY;				// 카메라가 최대한 따라가는 거리 Y
	float	_minX;				// 카메라가 최소한 따라가는 거리 X
	float	_minY;				// 카메라가 최소한 따라가는 거리 X
	float	_distanceX;
	float	_distanceY;
	float	_initDistanceX;		// 보통 WINSIZEX/2를 사용 (pivot 고정할 위치)
	float	_initDistanceY;		// 보통 WINSIZEY/2를 사용 (pivot 고정할 위치)

	// CAMERASHAKE //
	float	_shakeX;			// 쉐이크 X
	float	_shakeY;			// 쉐이크 Y
	float	_tempShakeX;		// 쉐이크 러프용 X
	float	_tempShakeY;		// 쉐이크 러프용 Y
	float	_shakePowerX;		// 흔들 세기 X
	float	_shakePowerY;		// 흔들 세기 Y
	int		_shakeTimer;		// 흔들 시간
	int		_shakeCycleTimer;	// 흔들 사이클 타이머
	int		_shakeCycle;		// 흔들 사이클
	
	void Shaker();

	// ZOOM //
	float	_zoomTargetX;		// 줌의 위치가 될 대상 X
	float	_zoomTargetY;		// 줌의 위치가 될 대상 Y

public:
	CameraManager() {
		_cameraRect = { 0,0,0,0 };
		_pivotX = 0.f;
		_pivotY = 0.f;
		_maxX = 0.f;
		_maxY = 0.f;
		_minX = 0.f;
		_minY = 0.f;
		_distanceX = 0.f;
		_distanceY = 0.f;
		_initDistanceX = 0.f;
		_initDistanceY = 0.f;
	}
	~CameraManager() {}

	HRESULT init(float pivotX, float pivotY, float maxX, float maxY, float minX, float minY, float disX, float disY);
	void update();

	// RENDER //
	void Render(HDC hdc, image* ig, int destX, int destY);
	void AlphaRender(HDC hdc, image * ig, int destX, int destY, BYTE alpha);
	void StretchRender(HDC hdc, image* ig, int destX, int destY, float scaleX, float scaleY);
	void StretchAlphaRender(HDC hdc,image* ig, int destX, int destY, float scaleX, float scaleY, BYTE alpha);
	void FrameRender(HDC hdc, image* ig, int destX, int destY, int frameX, int frameY, float angle = 0);
	void FrameAlphaRender(HDC hdc, image* ig, int destX, int destY, int frameX, int frameY, BYTE alpha, float angle = 0 );
	void FrameStretchRender(HDC hdc, image* ig, int destX, int destY, int frameX, int frameY, float scaleX, float scaleY, float angle = 0);
	void FrameStretchAlphaRender(HDC hdc, image* ig, int destX, int destY, int currentFrameX, int currentFrameY, float scaleX, float scaleY, BYTE alpha, float angle = 0);
	void Rectangle(HDC hdc, RECT rc);
	void RectangleMake(HDC hdc, int left, int top, int width, int height);
	void TextDraw(HDC hdc, int destX, int destY, LPCSTR lpstring, int c, int r = 0, int g = 0, int b = 0);
	
	// 기능 // 
	void MovePivot(float x, float y);
	void MovePivotLerp(float x, float y, float lerpSpeed = 10.f);
	void MovePivotRegular(float x, float y, float moveSpeed);
	void Shake(float shakePowerX, float shakePowerY, int shakeTime, int shakeCycle = 0);
	void ZoomInOut(HDC hdc, int destX, int destY, int sourX, int sourY, float scale);
	
	// 편의성 //
	float	GetRelativeX(float x)				{ return x - _cameraRect.left; }
	float	GetRelativeY(float y)				{ return y - _cameraRect.top; }
	float	GetAbsoluteX(float x)				{ return x + _cameraRect.left; }
	float	GetAbsoluteY(float y)				{ return y + _cameraRect.top; }
	POINT	GetAbsolutePoint(long x, long y)	{ return POINT{ x + _cameraRect.left, y + _cameraRect.top }; }
	
	// GETSET //
	float	GetPivotX()		{ return _pivotX; }
	float	GetPivotY()		{ return _pivotY; }
	float	GetDistanceX()	{ return _distanceX; }
	float	GetDistanceY()	{ return _distanceY; }
	RECT	GetRect()		{ return _cameraRect; }
};