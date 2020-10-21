#include "stdafx.h"
#include "EffectManager.h"

HRESULT EffectManager::init()
{
	_vEffect = vector<Effect*>();
	_vCameraText = vector<cameraText*>();

	return S_OK;
}

void EffectManager::update()
{
	for (int i = 0; i < _vEffect.size(); i++)
	{
		_vEffect[i]->update();
	}
	for (int i = 0; i < _vCameraText.size(); i++)
	{
		_vCameraText[i]->update();
	}
	DeleteEffect();
	DeleteText();
}

void EffectManager::release()
{
	for (int i = 0; i < _vEffect.size(); i++)
	{
		_vEffect[i]->release();
	}
	for (int i = 0; i < _vCameraText.size(); i++)
	{
		_vCameraText[i]->release();
	}
}

void EffectManager::render(HDC hdc)
{
	for (int i = 0; i < _vEffect.size(); i++)
	{
		_vEffect[i]->render(hdc);
	}

	for (int i = 0; i < _vCameraText.size(); i++)
	{
		_vCameraText[i]->render(hdc);
	}
}

Effect* EffectManager::AddEffect(float x, float y, string imgName, int animSpeed, int frameX, int frameY, bool isLoop, int alpha, float angle, float scaleX, float scaleY, bool isAlpha,bool useCamera , bool isFirstViewing)
{
	Effect* effect = new Effect();
	effect->init(x, y, imgName, animSpeed, frameX, frameY, isLoop, alpha, angle, scaleX, scaleY ,isAlpha ,useCamera,isFirstViewing);
	_vEffect.push_back(effect);

	return effect;
}

cameraText * EffectManager::AddCameraText(float x, float y, float xSize, float ySize, string text, FONT font, WORDSIZE size, WORDSORT sort, COLORREF color)
{
	cameraText* ctext = new cameraText();
	ctext->init(x, y, xSize, ySize, text, font, size, sort, color);
	_vCameraText.push_back(ctext);
	return ctext;
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

void EffectManager::DeleteText()
{
	for (int i = 0; i < _vCameraText.size(); i++)
	{
		if (_vCameraText[i]->getIsDead())
		{
			_vCameraText.erase(_vCameraText.begin() + i);
			i--;
		}
	}
}
