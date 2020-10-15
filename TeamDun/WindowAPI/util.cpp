#include "stdafx.h"
#include "util.h"
#include "image.h"
#include "MapManager.h"

float UTIL::getDistance(float startX, float startY, float endX, float endY)
{
	float x = endX - startX;
	float y = endY - startY;

	return sqrtf(x * x + y * y);
}

float UTIL::getAngle(float startX, float startY, float endX, float endY)
{
	float x = endX - startX;
	float y = endY - startY;
	float distance = sqrtf(x * x + y * y);
	float angle = acosf(x / distance);
	if (endY > startY)
	{
		angle = PI2 - angle;
	}
	return angle;
}

float UTIL::getLerpByAmount(float start, float end, float amount)
{
	return start + (end - start) * amount;
}

float UTIL::getLerpByAlpha(float start, float end, float alpha, LERPTYPE lerpType)
{
	switch (lerpType)
	{
	case LPT_LINEAR:
		alpha = alpha;
		break;
	case LPT_SMOOTH:
		alpha = alpha * alpha * (3 - 2 * (alpha));
		break;
	case LPT_SMOOTHER:
		alpha = alpha * alpha * alpha * (alpha * (alpha * 6 - 15) + 10);
		break;
	case LPT_SMOOTHERX3:
		alpha = pow(alpha * alpha * (3 - 2 * (alpha)), 3);
		break;
	default:
		break;
	}

	return start * (1 - alpha) + end * alpha;
}

bool UTIL::IsPointInCircle(POINT center, float radius, POINT pt)
{
	float deltaX = center.x - pt.x;
	float deltaY = center.y - pt.y;

	float length = sqrt(deltaX * deltaX + deltaY * deltaY);

	if (length > radius)
		return false;

	return true;
}

float UTIL::SetAngleInBoundary(float& angle)
{
	while (angle < 0) angle += 2 * PI;
	while (angle >= 2 * PI) angle -= 2 * PI;
	return angle;
}

bool UTIL::interactRectArc(RECT& rect, POINT center, float radius, float minAngle, float maxAngle, float checkDistance, bool useCout)
{
	SetAngleInBoundary(maxAngle);
	SetAngleInBoundary(minAngle);


	if (checkDistance > radius / 2)
	{
		checkDistance = radius / 2;
	}
	if(useCout) cout << minAngle << " " << maxAngle << endl;
	POINT rectPoints[4] = { POINT{rect.left, rect.top}, POINT{rect.left, rect.bottom}, POINT{rect.right, rect.top}, POINT{rect.right, rect.bottom} };
	
	vector<POINT> vPoint;
	
	for (int i = 0; i < 4; i++)
	{
		float distance = abs(getDistance(rectPoints[i].x, rectPoints[i].y, center.x, center.y));
		if (distance > radius) continue;

		else
		{
			float angle = getAngle(center.x, center.y, rectPoints[i].x, rectPoints[i].y);
			SetAngleInBoundary(angle);

			if (minAngle <= maxAngle)
			{
				if (angle >= minAngle && angle <= maxAngle)
				{
					return true;
				}
			}

			else
			{
				if (angle <= maxAngle || angle >= minAngle)
				{
					return true;
				}
			}
		}
	}
	
	for (int i = rect.left; i < rect.right+ checkDistance; i += checkDistance)
	{
		if (i > rect.right)
		{
			i = rect.right;
		}
		for (int j = rect.top; j < rect.bottom+ checkDistance; j += checkDistance)
		{
			if (j > rect.bottom)
			{
				j = rect.bottom;
			}
			float distance = abs(getDistance(i, j, center.x, center.y));
			if (distance > radius) continue;

			else
			{
				float angle = getAngle(center.x, center.y, i, j);
				SetAngleInBoundary(angle);

				if (minAngle <= maxAngle)
				{
					if (angle >= minAngle && angle <= maxAngle)
					{
						return true;
					}
				}

				else
				{
					if (angle <= maxAngle  ||angle >= minAngle)
					{
						return true;
					}
				}
			}
		}
	}
	return false;
}

bool UTIL::interactRectCircle(RECT& rect, POINT center, float radius)
{
	if ((rect.left <= center.x && center.x <= rect.right) ||
		rect.top <= center.y && center.y <= rect.bottom)
	{
		RECT rcEx = {
			rect.left - radius,
			rect.top - radius,
			rect.right + radius,
			rect.bottom + radius
		};

		if (rcEx.left < center.x && rcEx.right > center.x &&
			rcEx.top < center.y && rcEx.bottom > center.y)
		{
			return true;
		}
	}

	else
	{
		if (IsPointInCircle(center, radius, POINT{ rect.left, rect.top })) return true;
		if (IsPointInCircle(center, radius, POINT{ rect.left, rect.bottom })) return true;
		if (IsPointInCircle(center, radius, POINT{ rect.right, rect.top })) return true;
		if (IsPointInCircle(center, radius, POINT{ rect.right, rect.bottom })) return true;
	}

	return false;
}

string UTIL::to_string_with_precision(const float a_value, const int n = 6)
{
	std::ostringstream out;
	out.precision(n);
	out << std::fixed << a_value;
	return out.str();
}

void UTIL::SetFastPixel(image* img, PixelGetter* getter)
{
	HBITMAP bm = img->getHBitMap(); 
	::GetObject(bm, sizeof(BITMAP), &getter->bmInfo);
	delete(getter->pData);
	getter->pData = new BYTE[getter->bmInfo.bmWidthBytes * getter->bmInfo.bmHeight];
	GetBitmapBits(bm, getter->bmInfo.bmWidthBytes * getter->bmInfo.bmHeight, getter->pData);
	getter->mapSize = getter->bmInfo.bmWidthBytes * getter->bmInfo.bmHeight;
	getter->byteSize = getter->bmInfo.bmWidthBytes / getter->bmInfo.bmWidth;
}

COLORREF UTIL::GetFastPixel(PixelGetter* getter, int x, int y)
{
	RGBQUAD* pRgb = (RGBQUAD*)getter->pData;

	float pos = x + (y * getter->bmInfo.bmWidth);
	if (pos * getter->byteSize >= getter->mapSize || pos < 0) return RGB(255, 255, 255);

  	BYTE r = pRgb[(int)pos].rgbRed;
	BYTE g = pRgb[(int)pos].rgbGreen;
	BYTE b = pRgb[(int)pos].rgbBlue;
	
	return RGB(r, g, b);
}