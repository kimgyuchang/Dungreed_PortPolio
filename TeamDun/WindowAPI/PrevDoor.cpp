#include "stdafx.h"
#include "PrevDoor.h"

HRESULT PrevDoor::init(int id, string name, OBJECTTYPE type, vector<string> imgNames)
{
	NPC::init(id, name, type, imgNames);
	this->_goPoint = POINT{ 0,0 };

	return S_OK;
}

void PrevDoor::Activate()
{
	ENTITYMANAGER->getPlayer()->SetX(_goPoint.x);
	ENTITYMANAGER->getPlayer()->SetY(_goPoint.y);
}
