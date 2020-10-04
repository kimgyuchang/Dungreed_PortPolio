#include "stdafx.h"
#include "EntityManager.h"

HRESULT EntityManager::init()
{
	for (int i = 0; i < _vBullets.size(); i++)
	{
		_vBullets[i]->init();
	}
	return S_OK;
}

void EntityManager::update()
{
	for (int i = 0; i < _vObjs.size(); i++)
	{
		_vObjs[i]->update();
	}
	
	for (int i = 0; i < _vBullets.size(); i++)
	{
		_vBullets[i]->update();
	}
	eraseBullet();
	_p->update();
}

void EntityManager::render(HDC hdc)
{
	for (int i = 0; i < _vObjs.size(); i++)
	{
		_vObjs[i]->render(hdc);
	}

	for (int i = 0; i < _vBullets.size(); i++)
	{
		_vBullets[i]->render(hdc);
	}

	_p->render(hdc);
}

void EntityManager::release()
{
	for (int i = 0; i < _vObjs.size(); i++)		
	{
		_vObjs[i]->release();
	}

	for (int i = 0; i < _vBullets.size(); i++)
	{
		_vBullets[i]->release();
	}

	_p->release();
}

void EntityManager::makeBullet(const char * imageName, float x, float y, float angle, float speed, float maxDis, bool isFrame)
{
	Bullet* _bullet = new Bullet;
	_bullet->makeBullet(imageName, x, y, angle, speed, maxDis, isFrame);
	_vBullets.push_back(_bullet);

}

void EntityManager::eraseBullet()
{
	for (int i = 0; i < _vBullets.size(); i++)
	{
		if (_vBullets[i]->getDis() >= _vBullets[i]->getMaxDis())
		{
			_vBullets.erase(_vBullets.begin() + i);
			break;
		}

	}
	for (int i = 0; i < _vBullets.size(); i++)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("PixelMapIg")->getMemDC(), _vBullets[i]->getX(), _vBullets[i]->getY());
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if ((r == 255 && g == 0 && b == 0))
		{

			_vBullets.erase(_vBullets.begin() + i);
			break;
		}
	}
	
}
