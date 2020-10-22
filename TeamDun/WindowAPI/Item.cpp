#include "stdafx.h"
#include "Item.h"

HRESULT Item::init(int id, ITEMTYPE itemType, WEAPONTYPE weaponType, Skill* skill,
	string name, string description, ITEMCLASS itemClass, float minAtk, float maxAtk, float atkSpeed,
	int defence, bool useAtkSpeed, int numOfBullet, float reloadTime, Bullet* bullet, float accuracy,
	int buyPrice, bool isBulletInfinite, vector<string> imageNames, string invenImage, string dropImage)
{
	_renderPosX = _renderPosY = 0;

	_id = id;
	_itemType = itemType;
	_weaponType = weaponType;
	_skill = skill;
	_name = name;
	_description = description;
	_itemClass = itemClass;
	_minAtk = minAtk;
	_maxAtk = maxAtk;
	_atkSpeed = atkSpeed;
	_defence = defence;
	_useAtkSpeed = useAtkSpeed;
	_initNumOfBullet = _curNumOfBullet = numOfBullet;
	_reloadTime = reloadTime;
	_bullet = bullet;
	_accuracy = accuracy;
	_buyPrice = buyPrice;
	_isBulletInfinite = isBulletInfinite;

	for (int i = 0; i < imageNames.size(); i++)
	{
		if (imageNames[i] != ".")
		{
			_vImages.push_back(IMAGEMANAGER->findImage(imageNames[i]));
			_vImageNames.push_back(imageNames[i]);
		}
	}

	_invenImageName = invenImage;
	_invenImage = IMAGEMANAGER->findImage(invenImage);
	
	_dropImageName = dropImage;
	_dropImage = IMAGEMANAGER->findImage(dropImage);

	_currentImage = 0;
	_chargePercent = 0;
	_xFrame = 0;
	_yFrame = 0;
	_renderAngle = _angle = 0;
	_angleCheckPosX = _angleCheckPosY = 0;
	_renderPosX = _renderPosY = 0;
	_isAttacking = false;
	_renderScale = 1.f;

	if (_itemType == ITEMTYPE::IT_SUBWEAPON)
		_isRenderFirst = false;
	else
		_isRenderFirst = true;

	return S_OK;
}

void Item::AddSubOption(SubOption* option)
{
	_vSubOption.push_back(option);
}

void Item::update()
{
	SetBaseRenderPos();
}

void Item::render(HDC hdc)
{
	if (_itemType != ITEMTYPE::IT_NOTHING && _itemType != ITEMTYPE::IT_ACCESORRY)
	{
		if (_renderScale == 1)
		{
			CAMERAMANAGER->FrameRender(hdc, _vImages[_currentImage], _renderPosX, _renderPosY, _xFrame, _yFrame, _angle);
		}

		else
		{
			CAMERAMANAGER->FrameStretchRender(hdc, _vImages[_currentImage], _renderPosX, _renderPosY, _xFrame, _yFrame, _renderScale, _renderScale, _angle);
		}
	}
}

void Item::release()
{
}

void Item::Activate()
{
}

void Item::EquipUnEquipStatus(bool isEquip)
{
	Player* p = ENTITYMANAGER->getPlayer();
	
	int statusChanger = isEquip ? 1 : -1;
	p->SetMinDamage(p->GetMinDamage() + statusChanger * _minAtk);
	p->SetMaxDamage(p->GetMaxDamage() + statusChanger * _maxAtk);
	p->SetAtkSpeed(p->GetAtkSpeed() + statusChanger * _atkSpeed);
	p->SetDefence(p->GetDefence() + statusChanger * _defence);
	
	if (_initNumOfBullet != 0)
	{
		p->SetMaxBullet(p->GetMaxBullet() + statusChanger* _initNumOfBullet);
		p->SetReloadSpeed(p->GetReloadSpeed() +statusChanger * _reloadTime/100);
	}

	for (int i = 0; i < _vSubOption.size(); i++)
	{
		AdaptSubOption(_vSubOption[i], isEquip);
	}
}

void Item::AdaptSubOption(SubOption* subOption, bool isEquip)
{
	Player* p = ENTITYMANAGER->getPlayer();
	float value = subOption->_optionPower;
	if (!isEquip) value = -value;

	switch (subOption->_optionId)
	{
	case POWER:
		p->SetPower(p->GetPower() + value);
		break;
	case ATKSPEED:
		p->SetAtkSpeedPer(p->GetAtkSpeedPer() + value);
		break;
	case DASHATK:
		p->SetDashDamage(p->GetDashDamage() + value);
		break;
	case DEFENCE:
		p->SetDefence(p->GetDefence() + value);
		break;
	case BLOCK:
		p->SetBlock(p->GetBlock() + value);
		break;
	case CRITICALPERCENT:
		p->SetCriPer(p->GetCriPer() + value);
		break;
	case CRITICALDAMAGE:
		p->SetCriDamage(p->GetCriDamage() + value);
		break;
	case MINDAMAGE:
		p->SetMinDamage(p->GetMinDamage() + value);
		break;
	case MAXDAMAGE:
		p->SetMaxDamage(p->GetMaxDamage() + value);
		break;
	case FINALDAMAGEPERCENT:
		p->SetFinalDamagePer(p->GetFinalDamagePer() + value);
		break;
	case FINALDAMAGE:
		p->SetFinalDamage(p->GetFinalDamage() + value);
		break;
	case TOUGHNESS:
		p->SetToughness(p->GetToughness() + value);
		break;
	case TRUEDAMAGE:
		p->SetTrueDamage(p->GetTrueDamage() + value);
		break;
	case MAXHP:
		p->SetInitHp(p->GetInitHp() + value);
		break;
	case MAXHPPERCENT:
		p->SetMaxHpPer(p->GetMaxHpPer() + value);
		break;
	case EVADE:
		p->SetEvasion(p->GetEvasion() + value);
		break;
	case MOVESPEED:
		p->SetMoveSpeedPer(p->GetMoveSpeedPer() + value);
		break;
	case JUMPPOWER:
		p->SetJumpPower(p->GetJumpPower() + value);
		break;
	case GOLDDROP:
		p->SetGoldDrop(p->GetGoldDrop() + value);
		break;
	case RELOADSPEED:
		p->SetReloadSpeed(p->GetReloadSpeed() + value);
		break;
	case DASHCOUNT:
		for (int i = 0; i < abs(value); i++) (value > 0 ? p->AddMaxDash() : p->SubMaxDash());
		break;
	case ACCURACY:
		p->SetFireAccuracy(p->GetFireAccuracy() + value);
		break;
	case IMMUNEFIRE:
		p->SetImmuneFire(value == 1 ? true : false);
		break;
	case IMMUNEICE:
		p->SetImmuneIce(value == 1 ? true : false);
		break;
	case IMMUNEELEC:
		p->SetImmuneElec(value == 1 ? true : false);
		break;
	case IMMUNEPOSION:
		p->SetImmunePosion(value == 1 ? true : false);
		break;
	case IMMUNESTUN:
		p->SetImmuneStun(value == 1 ? true : false);
	case TOFIRE:
		p->SetToFire(p->GetToFire() + value);
		break;
	case TOICE:
		p->SetToIce(p->GetToIce() + value);
		break;
	case TOELEC:
		p->SetToElec(p->GetToElec() + value);
		break;
	case TOPOSION:
		p->SetToPosion(p->GetToPosion() + value);
		break;
	case TOSTUN:
		p->SetToStun(p->GetToStun() + value);
		break;
	case FIREDAMAGE:
		p->SetFireDamage(p->GetFireDamage() + value);
		break;
	case ICEDAMAGE:
		p->SetIceDamage(p->GetIceDamage() + value);
		break;
	case ELECDAMAGE:
		p->SetElecDamage(p->GetElecDamage() + value);
		break;
	case POSIONDAMAGE:
		p->SetPosionDamage(p->GetPosionDamage() + value);
		break;
	case STUNDAMAGE:
		p->SetStunDamage(p->GetStunDamage() + value);
	case ETC:
		// 이런저런 ~~ 저런저런 ~~
		break;
	default:
		break;
	}
}

void Item::ActivateAlways()
{
}

void Item::SetBaseRenderPos()
{
	bool playerIsLeft = ENTITYMANAGER->getPlayer()->GetIsLeft();	//플레이어 왼쪽인지
	_yFrame = playerIsLeft ? 0 : 1;									

	if(_itemType == ITEMTYPE::IT_WEAPON_ONEHAND) _angleCheckPosX = ENTITYMANAGER->getPlayer()->GetX() + (playerIsLeft ? 10 : 70);	//아이템 타입이 한손일때,각도체크용 중점에 플레이어의 x좌표+ 왼쪽인지 여부에따라 맞으면 +20,아니면 +40
	else if(_itemType == ITEMTYPE::IT_SUBWEAPON) _angleCheckPosX = ENTITYMANAGER->getPlayer()->GetX() + (playerIsLeft ? 60 : 20);	
	else _angleCheckPosX = ENTITYMANAGER->getPlayer()->GetX() + (playerIsLeft ? 40 : 20);

	_angleCheckPosY = ENTITYMANAGER->getPlayer()->GetY() + 45;	//각도 체크용 중점에 플레이어의 Y좌표를 받아와서  +45만큼
	_renderPosX = _angleCheckPosX - _vImages[_currentImage]->getFrameWidth() / 2;
	_renderPosY = _angleCheckPosY - _vImages[_currentImage]->getFrameHeight() / 2;
	if (!_isAttacking)	//공격중이 아니면
	{
		_angle = getAngle(_angleCheckPosX, _angleCheckPosY, CAMERAMANAGER->GetAbsoluteX(_ptMouse.x), CAMERAMANAGER->GetAbsoluteY(_ptMouse.y)); 
		if (_angle > PI * 2) _angle -= PI * 2;
		if (_angle < 0) _angle += PI * 2;
	}
}

void Item::ChangeMap()
{
}