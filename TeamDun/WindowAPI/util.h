#pragma once
//=============================================================
//	## namespace ## MY_UTIL
//=============================================================

#define PI 3.1415926f
#define PI2 (PI * 2)

//나중에 이미지 회전시 사용할 값
#define PI_2 (PI / 2) //90도
#define PI_4 (PI / 4) //45도
#define PI_8 (PI / 8) //22.5도

class image;
class PixelGetter;

enum LERPTYPE
{
	LPT_LINEAR, LPT_SMOOTH, LPT_SMOOTHER, LPT_SMOOTHERX3
};

namespace UTIL
{
	//두점 사이의 거리
	float getDistance(float startX, float startY, float endX, float endY);
	
	//두점 사이의 각도
	float getAngle(float startX, float startY, float endX, float endY);
	float getLerpByAmount(float start, float end, float amount);
	float getLerpByAlpha(float start, float end, float alpha, LERPTYPE lerpType);
	bool IsPointInCircle(POINT center, float radius, POINT pt);
	float SetAngleInBoundary(float& angle);
	bool interactRectArc(RECT& rect, POINT center, float radius, float minAngle, float maxAngle , float checkDistance, bool useCout = false);
	bool interactRectCircle(RECT& rect, POINT pt, float distance);
	string to_string_with_precision(const float a_value, const int n);
	void SetFastPixel(image* img, PixelGetter* getter);
	COLORREF GetFastPixel(PixelGetter* getter, int x, int y);
};

