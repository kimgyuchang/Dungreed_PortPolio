#pragma once
#include "gameNode.h"

class startScene : public gameNode
{
private:
	RECT _rc;
	RECT _rc2;
	RECT _rc3;
	float _angle;
	int _alpha;
	image* _img;
	image* _img2;
	int _count;
	int _xFrame;
	int _yFrame;


	image* _backGround;
	image* _midCloud;
	image* _FrontGround;
	image* _StartIg;
	image* _MaptoolIg;
	image* _QuitIg;
	int	   _backLoopX;
	int	   _midLoopX;
	int	   _frontLoopX;
	int		_loopCount;

public:
	HRESULT init();
	void release();
	void update();
	void render();
};

