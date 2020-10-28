#include "stdafx.h"
#include "StageChanger.h"

HRESULT StageChanger::init()
{
	_isChangingStage = false;
	_changerAlpha = 0;
	_coverImage = IMAGEMANAGER->findImage("ScreenCover");
	_soundVolume = 1.0f;
	_stage = 0;
	_updown = 1;
	_waitTime = 0;
	return S_OK;
}

void StageChanger::render(HDC hdc)
{
	if (_isChangingStage) _coverImage->stretchAlphaRender(hdc, 0, 0, 8, 4, _changerAlpha, 0);
}

void StageChanger::release()
{
}

void StageChanger::update()
{
	fadeInOut();
}

void StageChanger::MoveStage(int stage)
{
	_isChangingStage = true;
	_stage = stage;
}

void StageChanger::fadeInOut()
{
	if (_isChangingStage)
	{
		if (_waitTime == 0)
		{
			_changerAlpha += _updown * 5.1f;

			if (_changerAlpha >= 255)
			{
				_changerAlpha = 255;
				_waitTime = 50;
				_updown = -_updown;
				MAPMANAGER->MoveStage(_stage);
				MAPMANAGER->ChangeMap(0);
				MAPMANAGER->GetPlayMap()->ChangePlayerByDirection(DIRECTION::DIR_RIGHT);
				
			}

			if (_changerAlpha <= 0)
			{
				_updown = -_updown;
				_isChangingStage = false;
				ENTITYMANAGER->GetWormVillage()->SetRenderPlayer(true);
			}
		}

		else
		{
			_waitTime--;
		}
	}
}
