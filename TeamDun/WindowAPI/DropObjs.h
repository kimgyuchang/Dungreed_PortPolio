#pragma once
#include "Object.h"

class DropObjs : public Object
{
protected:
	float _speedX;
	float _speedY;
	float _angle;
	float _gravity;
	int	  _droppedTimer;

public :
	HRESULT init(int id, string name, OBJECTTYPE type, vector<string> imgNames);
	void update();
	void release();
	void render(HDC hdc);
	void Animation();
	void Move();
	void CheckCollision();
	void PixelCollision();
};

