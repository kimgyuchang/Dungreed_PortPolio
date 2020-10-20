#include "stdafx.h"
#include "HpPixie.h"

HRESULT HpPixie::init(int id, string name, OBJECTTYPE type, vector<string> imgNames)
{
	DropObjs::init(id, name, type, imgNames);
	return S_OK;
}

void HpPixie::update()
{
	DropObjs::update();

	_body = RectMake(_x, _y, _vImages[_useImage]->getFrameWidth(), _vImages[_useImage]->getFrameHeight());
	CheckCollision();
}

void HpPixie::release()
{
	DropObjs::release();
}

void HpPixie::render(HDC hdc)
{
	DropObjs::render(hdc);
}

void HpPixie::Animation()
{
	DropObjs::Animation();
}

/// <summary>
/// 충돌하여 HP를 회복하게함
/// </summary>
void HpPixie::CheckCollision()
{
	_droppedTimer++;

	if (_droppedTimer > 20)
	{
		RECT temp;

		int hp = 0;
		if (IntersectRect(&temp, &ENTITYMANAGER->getPlayer()->GetBody(), &_body))
		{
			if (ENTITYMANAGER->getPlayer()->GetHP() != ENTITYMANAGER->getPlayer()->GetInitHp())
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
					break;
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
				_droppedTimer = 0;
			}
		}
	}
}
