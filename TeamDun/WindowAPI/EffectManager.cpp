#include "stdafx.h"
#include "EffectManager.h"

HRESULT EffectManager::init()
{
	return S_OK;
}

void EffectManager::update()
{
	for (int i = 0; i < _vEffect.size(); i++)
	{
		_vEffect[i]->update();
	}

	DeleteEffect();
}

void EffectManager::release()
{
	for (int i = 0; i < _vEffect.size(); i++)
	{
		_vEffect[i]->release();
	}
}

void EffectManager::render(HDC hdc)
{
	for (int i = 0; i < _vEffect.size(); i++)
	{
		_vEffect[i]->render(hdc);
	}
}

Effect* EffectManager::AddEffect(float x, float y, string imgName, int animSpeed, int frameX, int frameY, bool isLoop)
{
	Effect* effect = new Effect();
	effect->init(x, y, imgName, animSpeed, frameX, frameY, isLoop);
	_vEffect.push_back(effect);

	return effect;
}

void EffectManager::DeleteEffect()
{
	for (int i = 0; i < _vEffect.size(); i++)
	{
		if (_vEffect[i]->GetIsDead())
		{
			_vEffect.erase(_vEffect.begin() + i);
			i--;
		}
	}
}
