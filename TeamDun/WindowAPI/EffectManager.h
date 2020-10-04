#pragma once
#include "singletonBase.h"
#include "Effect.h"
class EffectManager : public singletonBase<EffectManager>
{
private :
	vector<Effect*> _vEffect;

public :
	HRESULT init();
	void update();
	void release();
	void render(HDC hdc);
	Effect* AddEffect(float x, float y, string imgName, int animSpeed, int frameX = 0, int frameY = 0, bool isLoop = false , int alpha= 255);
	void DeleteEffect();
	
	vector<Effect*>& GetVEffect() { return _vEffect; }
};

