#include "stdafx.h"
#include "EntityManager.h"

HRESULT EntityManager::init()
{
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
}
