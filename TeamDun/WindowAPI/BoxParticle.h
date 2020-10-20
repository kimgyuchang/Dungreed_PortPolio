#pragma once
#include "DropObjs.h"
class BoxParticle : public DropObjs
{
private:
	int _liveTimer;
public:
	HRESULT init(float x, float y, float xSpeed, float ySpeed, image* img);
	virtual void	update();
	virtual void	render(HDC hdc);
	void CheckLiveTime();
};

