#include "stdafx.h"
#include "BelialDie.h"

HRESULT BelialDie::init(int id, string name, OBJECTTYPE type, vector<string> imgNames)
{
	Object::init(id, name, type, imgNames);

	return S_OK;
}

HRESULT BelialDie::init(float x, float y)
{
	_id = 5000;
	_name = "보스시체";
	_type = OBJECTTYPE::OT_DEATH;

	_x2 = _x = x;
	_y2 = _y = y;
	_spawnTime = 0;
	_frameX = 0;
	_frameY = 0;
	_useImage = 0;
	_frameTimer = 0;
	_body = RECT{ 0,0,0,0 };
	_isDead = false;
	_renderOrder = 1;
	_upIg = IMAGEMANAGER->findImage("SkellBossDead");
	_downIg = IMAGEMANAGER->findImage("SkellBossDead0");
	
	_CenterX = _x+_upIg->getFrameWidth()/2 - 30;
	_CenterY = _y + (_upIg->getFrameHeight()+_downIg->getFrameHeight()) / 2;
	_angle = 0;
	_downSpeed = 1;
	_gravity = 0.05f;
	_effectCount = 0;
	_effectCount2 = 0;
	_isEffect1 = true;
	_isEffect2 = false;
	_downBoss = false;
	_shakeHead = false;
	_leftPlus = true;
	_rightPlus = false;
	_EffectRange = 0;
	_plusCount = 0;
	_plusAngle = 0.01f;
	return S_OK;
}

void BelialDie::update()
{
	if (_isEffect1)
	{
		_effectCount++;
		if (_effectCount % 20== 0)
		{
			SOUNDMANAGER->play("몬스터_사망");
			for (int i = 0; i < 7; i++)
			{
				EFFECTMANAGER->AddEffect(RANDOM->range(_x - 130, _x + _upIg->getFrameWidth()), RANDOM->range(_y-100, _y + _upIg->getFrameHeight()), "DieEffect",
					6, 0, 0, false, 255, 0, 1, 1, false, false, true);
			}
		}
		if (_effectCount == 200)
		{
			
			_isEffect1 = false;
			_isEffect2 = true;
			_downBoss = true;
		}
	}
	if (_isEffect2)
	{
		_effectCount2++;

		if (_effectCount2 % 10 == 0)
		{
			SOUNDMANAGER->play("몬스터_사망");
			_EffectRange += 60;
			for (int i = -2; i < 3; i++)
			{

				_X[i + 2] = _CenterX+ cosf(PI / 2 + i * PI / 6)*_EffectRange;
				_Y[i + 2] = _CenterY -sinf(PI / 2 + i * PI / 6)*_EffectRange;

				_X2[i + 2] = _CenterX -cosf(PI / 2 + i * PI / 6)*_EffectRange;
				_Y2[i + 2] = _CenterY +sinf(PI / 2 + i * PI / 6)*_EffectRange;
				EFFECTMANAGER->AddEffect(_X[i + 2], _Y[i + 2], "DieEffect" , 4,0,0, false, 255, 0, 1, 1, false, false, true);
				EFFECTMANAGER->AddEffect(_X2[i + 2], _Y2[i + 2], "DieEffect" , 4,0,0, false, 255, 0, 1, 1, false, false, true);
			}
		}
		
		if (_effectCount2 > 61)
		{
			_isEffect2 = false;
		}
	}
	if (_downBoss)
	{
		_y += _downSpeed;
		_y2 += _downSpeed;

		_downSpeed += _gravity;
		if (_downSpeed > 5)
		{
			_downSpeed = 5;
		}
		
	}
	if (_shakeHead)
	{
		_plusCount++;
		if (_leftPlus)
		{
			_angle -= _plusAngle;

			if (_plusCount == 30)
			{
				_plusCount = 0;
				_plusAngle = _plusAngle / 2;
				_rightPlus = true;
				_leftPlus = false;
			}
		}
		if (_rightPlus)
		{
			_angle += _plusAngle;

			if (_plusCount == 30)
			{
				_plusCount = 0;
				_plusAngle = _plusAngle / 2;
				_rightPlus = false;
				_leftPlus = true;
			}
		}

	}
	pixelCollision();
}

void BelialDie::release()
{
}

void BelialDie::render(HDC hdc)
{
	CAMERAMANAGER->Render(hdc, _downIg, _x2+60, _y2 + _upIg->getFrameHeight(), 0);
	
	CAMERAMANAGER->Render(hdc, _upIg, _x, _y, _angle);
}

void BelialDie::pixelCollision()
{

	bool collision1 = false;
	bool collision2 = false;
	

	image* pixelMapIg = IMAGEMANAGER->findImage("PixelMapIg");
	

	float _probeBottom = _y + _upIg->getFrameHeight();

	for (int i = _probeBottom - 6; i < _probeBottom + 2; i++)
	{
		COLORREF color = GetFastPixel(MAPMANAGER->GetPixelGetter(), _x + _upIg->getFrameWidth() / 2, i);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (r == 255 && g == 0 && b == 0 || (r == 0 && g == 0 && b == 255))
		{
			collision1 = true;
			_y = i -_upIg->getFrameHeight();
			
			break;
		}
	}

	float _probeBottom2 = _y2 + _upIg->getFrameHeight()+ _downIg->getFrameHeight();

	for (int i = _probeBottom2 - 6; i < _probeBottom2 + 2; i++)
	{
		COLORREF color = GetFastPixel(MAPMANAGER->GetPixelGetter(), _x + _upIg->getFrameWidth() / 2, i);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (r == 255 && g == 0 && b == 0 || (r == 0 && g == 0 && b == 255))
		{
			collision2 = true;
			_y2 = i - _upIg->getFrameHeight() - _downIg->getFrameHeight();
			
			break;
		}
	}
	if (collision1 && collision2)
	{
		_downBoss = false;
		_shakeHead = true;
	}
}
