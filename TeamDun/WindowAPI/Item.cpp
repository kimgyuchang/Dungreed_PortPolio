#include "stdafx.h"
#include "Item.h"

HRESULT Item::init()
{
	return E_NOTIMPL;
}

void Item::update()
{
}

void Item::render(HDC hdc)
{
}

void Item::release()
{
}

void Item::EquipUnEquip(SubOption subOption, bool isEquip)
{
	Player* p = ENTITYMANAGER->getPlayer();

	switch (subOption._optionId)
	{
	case POWER : 
		break;
	case ATKSPEED:
		break;
	case DASHATK:
		break;
	case DEFENCE:
		break;
	case BLOCK:
		break;
	case CRITICALPERCENT:
		break;
	case CRITICALDAMAGE:
		break;
	case MINDAMAGE:
		break;
	case MAXDAMAGE:
		break;
	case FINALDAMAGEPERCENT:
		break;
	case FINALDAMAGE:
		break;
	case TOUGHNESS:
		break;
	case TRUEDAMAGE:
		break;
	case MAXHP:
		break;
	case MAXHPPERCENT:
		break;
	case EVADE:
		break;
	case MOVESPEED:
		break;
	case JUMPPOWER:
		break;
	case GOLDDROP:
		break;
	case RELOADSPEED:
		break;
	case DASHCOUNT:
		break;
	case ACCURACY:
		break;
	case IMMUNEFIRE:
		break;
	case IMMUNEICE:
		break;
	case IMMUNEELEC:
		break;
	case IMMUNEPOSION:
		break;
	case TOFIRE:
		break;
	case TOICE:
		break;
	case TOELEC:
		break;
	case TOPOSION:
		break;
	case FIREDAMAGE:
		break;
	case ICEDAMAGE:
		break;
	case ELECDAMAGE:
		break;
	case POSIONDAMAGE:
		break;
	case ETC:
		break;
	default:
		break;
	}
}