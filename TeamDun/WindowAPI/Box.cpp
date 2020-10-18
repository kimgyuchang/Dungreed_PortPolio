#include "stdafx.h"
#include "Box.h"

HRESULT Box::init(int id, string name, OBJECTTYPE type, vector<string> imgNames)
{
	Object::init(id, name, type, imgNames);
	return S_OK;
}

void Box::SetParticle()
{
	switch (_boxType)
	{
	case BOX_SMALLBOX:
		_vParticles.push_back(IMAGEMANAGER->findImage("BigBoxParticle0_0"));
		_vParticles.push_back(IMAGEMANAGER->findImage("BigBoxParticle0_1"));
		_vParticles.push_back(IMAGEMANAGER->findImage("BigBoxParticle0_2"));
		_vParticles.push_back(IMAGEMANAGER->findImage("BigBoxParticle0_3"));
		_vParticles.push_back(IMAGEMANAGER->findImage("BigBoxParticle0_4"));
		_vParticles.push_back(IMAGEMANAGER->findImage("BigBoxParticle0_5"));
		break;

	case BOX_BIGBOX:
		_vParticles.push_back(IMAGEMANAGER->findImage("BoxParticle0_0"));
		_vParticles.push_back(IMAGEMANAGER->findImage("BoxParticle0_1"));
		_vParticles.push_back(IMAGEMANAGER->findImage("BoxParticle0_2"));
		_vParticles.push_back(IMAGEMANAGER->findImage("BoxParticle0_3"));
		_vParticles.push_back(IMAGEMANAGER->findImage("BoxParticle0_4"));
		_vParticles.push_back(IMAGEMANAGER->findImage("BoxParticle0_5"));
		_vParticles.push_back(IMAGEMANAGER->findImage("BoxParticle0_6"));
		break;

	case BOX_ORC:
		_vParticles.push_back(IMAGEMANAGER->findImage("OakDrumParticle0_0"));
		_vParticles.push_back(IMAGEMANAGER->findImage("OakDrumParticle0_1"));
		_vParticles.push_back(IMAGEMANAGER->findImage("OakDrumParticle0_2"));
		_vParticles.push_back(IMAGEMANAGER->findImage("OakDrumParticle0_3"));
		_vParticles.push_back(IMAGEMANAGER->findImage("OakDrumParticle0_4"));
		break;
	}
}

void Box::update()
{
	Object::update();
}

void Box::release()
{
	Object::update();
}

void Box::render(HDC hdc)
{
	Object::render(hdc);
}

void Box::GetDamage()
{
	switch (_boxType)
	{
		case BOX_BIGBOX:	SOUNDMANAGER->play("오브젝트_통부숨 (2)"); break;
		case BOX_SMALLBOX:	SOUNDMANAGER->play("오브젝트_통부숨 (2)"); break;
		case BOX_ORC:		SOUNDMANAGER->play("오브젝트_통부숨 (1)"); break;
	}

	int particleCount = RANDOM->range(1,3);
	for (int i = 0; i < particleCount; i++)
	{
		BoxParticle* boxParticle = new BoxParticle();
		boxParticle->init(_x + _vImages[_useImage]->getWidth() / 2, _y - 10, RANDOM->range(-5.f, 5.f), RANDOM->range(3, 5), _vParticles[RANDOM->range((int)_vParticles.size())]);
		MAPMANAGER->GetPlayMap()->GetObjects().push_back(boxParticle);
	}

	if (RANDOM->range(10) < 200)
	{
		int pixieCase = RANDOM->range(13, 17);
		HpPixie* pixie = new HpPixie(*dynamic_cast<HpPixie*>(DATAMANAGER->GetObjectById(pixieCase)));
		pixie->SetX(_x + (_vImages[_useImage]->getWidth() / 2) - pixie->GetImage(_useImage)->getFrameWidth() / 2);
		pixie->SetY(_y);
		MAPMANAGER->GetPlayMap()->GetObjects().push_back(pixie);
	}
	
	int coinNumber = RANDOM->range(0, 4);
	for (int i = 0; i < coinNumber; i++)
	{
		Coin* coin = new Coin(*dynamic_cast<Coin*>(DATAMANAGER->GetObjectById(524)));
		coin->SetUseImage(1);
		coin->SetCoin(_x, _y - 30, RANDOM->range(-5.f, 5.f), RANDOM->range(4.f, 6.f));
		MAPMANAGER->GetPlayMap()->GetObjects().push_back(coin);
	}

	_isDead = true;
}
