#include "stdafx.h"
#include "WormVillage.h"

HRESULT WormVillage::init(int id, string name, OBJECTTYPE type, vector<string> imgNames)
{
	Object::init(id, name, type, imgNames);
	_x = -1000;
	_y = -1000;
	_isOn = false;
	_renderPlayer = true;
	return S_OK;
}

void WormVillage::update()
{
	Animation();
}

void WormVillage::release()
{
	Object::release();
}

void WormVillage::render(HDC hdc)
{
	Object::render(hdc);
}

void WormVillage::Animation()
{
	if (_isOn)
	{
		_frameTimer++;
		_frameY = 0;

		if (_frameTimer > 3)
		{
			_frameTimer = 0;
			_frameX++;

			if (_frameX == 8)
			{
				_frameX = 26;
				_renderPlayer = false;
			}

			if (_frameX > _vImages[_useImage]->getMaxFrameX())
			{
				_isOn = false;
				_renderPlayer = true;
				MAPMANAGER->AddStage(1);
				MAPMANAGER->ChangeMap(0);
				MAPMANAGER->GetPlayMap()->ChangePlayerByDirection(DIRECTION::DIR_RIGHT);
			}
		}
	}
}

void WormVillage::Activate()
{
	if (!_isOn)
	{
		_x = ENTITYMANAGER->getPlayer()->GetX() + 30 - _vImages[_useImage]->getFrameWidth()/2;
		_y = ENTITYMANAGER->getPlayer()->GetY() - 48 - _vImages[_useImage]->getFrameHeight()/2;
		_frameX = 0;
		_frameTimer = 0;
		_isOn = true;
	}
}
