#include "stdafx.h"
#include "Item.h"

HRESULT Item::init(int id, ITEMTYPE itemType, WEAPONTYPE weaponType, Skill* skill,
	string name, string description, ITEMCLASS itemClass, float minAtk, float maxAtk, float atkSpeed,
	int defence, bool useAtkSpeed, int numOfBullet, float reloadTime, Bullet* bullet, float accuracy,
	int buyPrice, bool isBulletInfinite, vector<string> imageNames, string invenImage)
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

	_invenImage = IMAGEMANAGER->findImage(invenImage);
	_currentImage = 0;
	_chargePercent = 0;
	_xFrame = 0;
	_yFrame = 0;
	_renderAngle = _angle = 0;
	_angleCheckPosX = _angleCheckPosY = 0;
	_renderPosX = _renderPosY = 0;
	_isAttacking = false;
	_isRenderFirst = false;
	return S_OK;
}

void Item::AddSubOption(SubOption* option)
{
	_vSubOption.push_back(option);
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

void Item::Activate()
{
}

void Item::EquipUnEquipItem(bool isEquip)
{
	Player* p = ENTITYMANAGER->getPlayer();
	int statusChanger = isEquip ? 1 : -1;
	p->SetMinDamage(p->GetMinDamage() + statusChanger * _minAtk);
	p->SetMaxDamage(p->GetMaxDamage() + statusChanger * _maxAtk);
	p->SetAtkSpeed(p->GetAtkSpeed() + statusChanger * _atkSpeed);
	p->SetDefence(p->GetDefence() + statusChanger * _defence);

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
		p->SetAtkSpeed(p->GetAtkSpeed() + value);
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
		p->SetMaxHp(p->GetMaxHp() + value);
		break;
	case MAXHPPERCENT:
		p->SetMaxHpPer(p->GetMaxHpPer() + value);
		break;
	case EVADE:
		p->SetEvasion(p->GetEvasion() + value);
		break;
	case MOVESPEED:
		p->SetMoveSpeed(p->GetMoveSpeed() + value);
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
		p->SetDashCount(p->GetDashCount() + value);
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
	case ETC:
		// 이런저런 ~~ 저런저런 ~~
		break;
	default:
		break;
	}
}

void Item::SetBaseRenderPos()
{
	bool playerIsLeft = ENTITYMANAGER->getPlayer()->GetIsLeft();
	_yFrame = playerIsLeft ? 0 : 1;

	_angleCheckPosX = ENTITYMANAGER->getPlayer()->GetX() + (playerIsLeft ? 40 : 20);
	_angleCheckPosY = ENTITYMANAGER->getPlayer()->GetY() + 45;
	_renderPosX = _angleCheckPosX - _vImages[_currentImage]->getFrameWidth() / 2;
	_renderPosY = _angleCheckPosY - _vImages[_currentImage]->getFrameHeight() / 2;
	if (!_isAttacking)
	{
		_angle = -getAngle(CAMERAMANAGER->GetAbsoluteX(_ptMouse.x), CAMERAMANAGER->GetAbsoluteY(_ptMouse.y), _angleCheckPosX, _angleCheckPosY);
		if (_angle > PI * 2) _angle -= PI * 2;
		if (_angle < 0) _angle += PI * 2;
	}
}
