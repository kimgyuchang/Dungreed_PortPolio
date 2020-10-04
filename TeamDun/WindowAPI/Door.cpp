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
					}
				}

				_frameTimer = 0;
			}
		}
	}
}
