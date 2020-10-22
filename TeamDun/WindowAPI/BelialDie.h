#pragma once
#include "Object.h"
class BelialDie : public Object
{
private:

	float _x;
	float _y;
	float _x2;
	float _y2;
	float _CenterX;
	float _CenterY;
	float _angle;
	float _angle2;
	float _EffectRange;
	float _downSpeed;
	float _gravity;
	float _plusAngle;

	image* _upIg;
	image* _downIg;
	
	int _effectCount;
	int _effectCount2;
	
	float _X[6]{ 0.0f, };
	float _Y[6]{ 0.0f, };

	float _X2[6]{ 0.0f, };
	float _Y2[6]{ 0.0f, };
	
	bool _isEffect1;
	bool _isEffect2;
	bool _downBoss;
	bool _shakeHead;
	bool _leftPlus;
	bool _rightPlus;
	int _plusCount;


public:
	virtual HRESULT init(int id, string name, OBJECTTYPE type, vector<string> imgNames);
	HRESULT init(float x, float y);
	virtual void	update();
	virtual	void	release();
	virtual void	render(HDC hdc);
	void pixelCollision();
};
