#pragma once
#include "DropObjs.h"
class DropItem : public DropObjs
{
private:
	Item* _item;
public:
	HRESULT init();
	virtual void	update();
	virtual	void	release();
	virtual void	render(HDC hdc);
	void SetItem(float x, float y, float speedX, float speedY, Item* item);
	virtual void CheckCollision();
	void PixelCollision();
};

