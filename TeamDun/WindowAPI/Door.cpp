#include "stdafx.h"
#include "Door.h"

HRESULT Door::init(int id, string name, OBJECTTYPE type, vector<string> imgNames)
{
	Object::init(id, name, type, imgNames);

	_isActivated = false;
	_isSpawning = false;
	return S_OK;
}

void Door::update()
{
	Object::update();
	Animation();
}

void Door::release()
{
	Object::release();
}

void Door::render(HDC hdc)
{
	if (_isSpawning) CAMERAMANAGER->FrameRender(hdc, _vImages[_useImage], _x, _y, _frameX, _frameY);
}

void Door::Animation()
{
	if (_isActivated) // 활성화된 상태
	{
		_frameTimer++;
		if (_frameTimer > 5)
		{
			_frameTimer = 0;
			_frameX++;
			if (_frameX > 14) _frameX = 7;
		}
	}

	else
	{
		if (_isSpawning) 
		{
			_frameTimer++;
			if (_frameTimer > 5)
			{
				_frameX++;
				if (_frameX <= 6) // 소환 중 -> 소환 완료
				{
					if (_frameX == 6)
					{
						_isActivated = true;
						SetGeneratorIsOff(true);
					}
				}

				else // 소환 완료 -> 사라짐
				{
					if (_frameX >= _vImages[_useImage]->getMaxFrameX())
					{
						_isActivated = false;
						_isSpawning = false;
						_frameX = 0;
						_belongMap->MakeNearTileCollision(this, false);
						SetGeneratorIsOff(false);
					}
				}

				_frameTimer = 0;
			}
		}
	}
}

void Door::SetPGenerator()
{
	_pGenerator = new ParticleGenerator();
	_pGenerator->initGenerator(REGULARGEN, 1000000, 1, 0, 1, vector<string>{"SqaureParticle", "SqaureParticle_2", "SqaureParticle_3", "SqaureParticle_4"});
	_pGenerator->initAlpha(155, 30, 5);
	_pGenerator->initTime(30, 5);
	_pGenerator->initPos(_x + _vImages[_useImage]->getFrameWidth() / 2, _y + _vImages[_useImage]->getFrameHeight() / 2, _vImages[_useImage]->getFrameWidth(), _vImages[_useImage]->getFrameHeight());
	_pGenerator->SetIsOff(false);
	switch (_dir)
	{
	case DIRECTION::DIR_LEFT:
		_pGenerator->initAngle(0, 0, 0);
		_pGenerator->initSpeed(2.0f, 0, 1.5f, 0, 0, 0);
		break;
	case DIRECTION::DIR_RIGHT:
		_pGenerator->initAngle(0, 0, 0);
		_pGenerator->initSpeed(-2.0f, 0, 1.5f, 0, 0, 0);
		break;
	case DIRECTION::DIR_UP:
		_pGenerator->initAngle(PI/2*3, 0, 0);
		_pGenerator->initSpeed(0, 2.0f, 0, 1.5f, 0, 0);
		break;
	case DIRECTION::DIR_DOWN:
		_pGenerator->initAngle(PI/2*3, 0, 0);
		_pGenerator->initSpeed(0, -2.0f, 0, 1.5f, 0, 0);
		break;
	}

	PARTICLEMANAGER->AddGenerator(_pGenerator);
}

void Door::SetGeneratorIsOff(bool isOff)
{
	_pGenerator->SetIsOff(isOff);
}