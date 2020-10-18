#include "stdafx.h"
#include "HpPixie.h"

HRESULT HpPixie::init(int id, string name, OBJECTTYPE type, vector<string> imgNames)
{
	Object::init(id, name, type, imgNames);
	return S_OK;
}

void HpPixie::update()
{
	Object::update();

	_body = RectMake(_x, _y, _vImages[_useImage]->getFrameWidth(), _vImages[_useImage]->getFrameHeight());
	CheckCollision();
}

void HpPixie::release()
{
	Object::release();
}

void HpPixie::render(HDC hdc)
{
	Object::render(hdc);
}

void HpPixie::Animation()
{
	Object::Animation();
}

/// <summary>
/// 충돌하여 HP를 회복하게함
/// </summary>
void HpPixie::CheckCollision()
{
	RECT temp;

	int hp = 0;
	if (IntersectRect(&temp, &ENTITYMANAGER->getPlayer()->GetBody(), &_body))
	{
		switch (_pixType)
		{
		case SMALL:
			hp = 10;
			break;
		case MIDDLE:
			hp = 20;
			break;
		case LARGE:
			hp = 40;
			break;
		case XLARGE:
			hp = 60;
			break;
		case GREEN:
			hp = 80;
		}

		EFFECTMANAGER->AddCameraText(_x + _vImages[0]->getFrameWidth() / 2, _y, 100, 100, "+" + to_string(hp), PIX, WS_BIG, WSORT_LEFT, RGB(96, 226, 33));
		int resultHp = ENTITYMANAGER->getPlayer()->GetHP() + hp;
		if (resultHp > ENTITYMANAGER->getPlayer()->GetInitHp())
		{
			resultHp = ENTITYMANAGER->getPlayer()->GetInitHp();
		}
		ENTITYMANAGER->getPlayer()->SetHp(resultHp);
		
		SOUNDMANAGER->play("오브젝트_HP회복");
		_isDead = true;
	}
}
