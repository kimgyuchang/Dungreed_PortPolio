#include "stdafx.h"
#include "NPC.h"

HRESULT NPC::init(int id, string name, OBJECTTYPE type, vector<string> imgNames)
{
	Object::init(id, name, type, imgNames);
	_isInteracting = false;
	_interactionImage = IMAGEMANAGER->findImage("Keyboard_F");
	
	return S_OK;
}

void NPC::update()
{
	CollisionInteraction();
	PressActivateKey();
	Animation();
}

void NPC::CollisionInteraction()
{
	_interactRect = RectMake(_x - 50, _y - 50, _vImages[_useImage]->getFrameWidth() + 100, _vImages[_useImage]->getFrameHeight() + 100);

	RECT temp;
	if (IntersectRect(&temp, &_interactRect, &ENTITYMANAGER->getPlayer()->GetBody()))
	{
		_isInteracting = true;
	}

	else
	{
		_isInteracting = false;
	}
}

void NPC::PressActivateKey()
{
	if (_isInteracting && INPUT->GetKeyDown('F'))
	{
		Activate();
	}
}

void NPC::release()
{
}

void NPC::render(HDC hdc)
{
	Object::render(hdc);

	if (_isInteracting)
	{
		CAMERAMANAGER->Render(hdc, _interactionImage, _x + _vImages[_useImage]->getFrameWidth() / 2, _y - 50);
	}
}

void NPC::Animation()
{
	_frameTimer++;

	if (_frameTimer > 5)
	{
		_frameTimer = 0;
		_frameX++;

		if (_frameX >= _vImages[_useImage]->getMaxFrameX()) _frameX = 0;
	}
}

void NPC::Activate()
{
}
