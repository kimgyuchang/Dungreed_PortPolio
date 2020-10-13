#include "stdafx.h"
#include "NPC.h"

HRESULT NPC::init(int id, string name, OBJECTTYPE type, vector<string> imgNames)
{
    Object::init(id, name, type, imgNames);
    _interactRect = RectMake(_x - 50, _y - 50, _vImages[_useImage]->getFrameWidth() + 100, _vImages[_useImage]->getFrameHeight() + 100);
    _isInteracting = false;
    return S_OK;
}

void NPC::update()
{
    CollisionInteraction();
}

void NPC::CollisionInteraction()
{
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

void NPC::release()
{
}

void NPC::render(HDC hdc)
{
    Object::render(hdc);

    if (_isInteracting)
    {
        //CAMERAMANAGER->Render(hdc, image)
    }

}

void NPC::Animation()
{
}
