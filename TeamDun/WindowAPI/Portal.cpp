#include "stdafx.h"
#include "Portal.h"

HRESULT Portal::init(int id, string name, OBJECTTYPE type, vector<string> imgNames)
{
	NPC::init(id, name, type, imgNames);
	_isOn = false;
	_isUp = false;
	_destination = -1;
	return S_OK;
}

void Portal::update()
{
	NPC::update();
}

void Portal::release()
{
	NPC::release();
}

void Portal::render(HDC hdc)
{
	if (_vImages[_useImage]->getMaxFrameX() == 0) CAMERAMANAGER->Render(hdc, _vImages[_useImage], _x, _y);
	else CAMERAMANAGER->FrameRender(hdc, _vImages[_useImage], _x, _y, _frameX, _frameY);

	if (_isInteracting)
	{
		CAMERAMANAGER->Render(hdc, _interactionImage, _x + _vImages[_useImage]->getFrameWidth() / 2, _y - 50);
	}
}

void Portal::MoveMap(int stage)
{
	_useImage = 2;
	_frameX = 0;
	_frameTimer = 0;
	_destination = stage;
	EFFECTMANAGER->AddEffect(_x - 10, _y, "DieEffect", 7, 0, 0);
}

void Portal::initSecond()
{
	NPC::initSecond();
}

void Portal::Animation()
{
	_frameTimer++;

	if (_useImage == 0)
	{
		if (_frameTimer > 5)
		{
			_frameTimer = 0;
			_frameX++;

			if (_frameX >= _vImages[_useImage]->getMaxFrameX()) _frameX = 0;
		}
	}

	else
	{
		if (_isUp)
		{
			if (_frameTimer == 1 && _frameX == 3)
			{
				EFFECTMANAGER->AddEffect(_x - 10, _y, "DieEffect", 7, 0, 0);
			}

			if (_frameTimer > 7)
			{
				_frameTimer = 0;
				_frameX--;

				if (_frameX < 0)
				{
					_useImage = 0;
					_destination = -1;
					_frameX = 0;
					_isUp = false;
					MAPMANAGER->SetPortalAnimOn(false);
				}
			}
		}
	
		else
		{
			if (_frameTimer > 7)
			{
				_frameTimer = 0;
				_frameX++;

				if (_frameX >= _vImages[_useImage]->getMaxFrameX())
				{
					_useImage = 0;
					_frameX = 0;
					_isUp = false;
					MAPMANAGER->ChangeMap(_destination);
					ENTITYMANAGER->getPlayer()->SetX(MAPMANAGER->GetPlayMap()->GetPortal()->GetX());
					ENTITYMANAGER->getPlayer()->SetY(MAPMANAGER->GetPlayMap()->GetPortal()->GetY());
					MAPMANAGER->GetPlayMap()->GetPortal()->SetIsUp(true);
					MAPMANAGER->GetPlayMap()->GetPortal()->SetUseImage(2);
					MAPMANAGER->GetPlayMap()->GetPortal()->SetFrameX(_vImages[_useImage]->getMaxFrameX()-1);
					MAPMANAGER->GetPlayMap()->GetPortal()->SetFrameTimer(0);
					SOUNDMANAGER->play("게임_던전나가기");

					_destination = -1;
				}
			}
		}
	}
}

void Portal::Activate()
{
	if (!MAPMANAGER->GetPortalAnimOn())
	{
		UIMANAGER->GetGameFrame()->GetChild("allMapFrame")->ToggleIsViewing();
		MAPMANAGER->ReNewMapUI();
		MAPMANAGER->SetPortalOn(UIMANAGER->GetGameFrame()->GetChild("allMapFrame")->GetIsViewing());
		MAPMANAGER->SetCurrentPortal(this);
	}
}
