#include "stdafx.h"
#include "startScene.h"


HRESULT startScene::init()
{
	//렉트 위치 초기화
	_rc = RectMakeCenter(WINSIZEX / 2, WINSIZEY - 300, 158, 47);
	_rc2 = RectMakeCenter(WINSIZEX / 2, WINSIZEY - 240, 158, 47);
	_rc3 = RectMakeCenter(WINSIZEX / 2, WINSIZEY - 180, 158, 47);
	ShowCursor(false);
	_img = IMAGEMANAGER->findImage("DemensionVault1");
	_img2 = IMAGEMANAGER->findImage("DemensionVault1_test2");
	_StartIg = IMAGEMANAGER->findImage("gameStart1");
	_MaptoolIg = IMAGEMANAGER->findImage("mapTool2");
	_QuitIg = IMAGEMANAGER->findImage("quit2");
	
	_angle = 0;
	_alpha = 0;
	_xFrame = 0;
	_yFrame = 0;
	_count = 0;
	_backLoopX = 0;
	_midLoopX =0 ;
	_frontLoopX =0;
	_loopCount = 0;

	_backGround = IMAGEMANAGER->findImage("BackCloud");
	_midCloud = IMAGEMANAGER->findImage("MidCloud0");
	_FrontGround = IMAGEMANAGER->findImage("FrontCloud"); 
	return S_OK;
}

void startScene::release()
{
	
}

void startScene::update()
{
	_loopCount++;
	if (_loopCount > 1)
	{
		_loopCount = 0;
		_backLoopX++;

	}
	_midLoopX += 1;
	_frontLoopX += 2;

	if (PtInRect(&_rc, _ptMouse))
	{
		_StartIg = IMAGEMANAGER->findImage("gameStart0");
		if (INPUT->GetKeyDown(VK_LBUTTON))
		{
			SCENEMANAGER->loadScene("게임화면");
		}
	}
	else
	{
		_StartIg = IMAGEMANAGER->findImage("gameStart1");
	}

	if (PtInRect(&_rc2, _ptMouse))
	{
		_MaptoolIg = IMAGEMANAGER->findImage("mapTool");
		if (INPUT->GetKeyDown(VK_LBUTTON))
		{
			SCENEMANAGER->loadScene("맵씬");
		}
	}
	else
	{
		_MaptoolIg = IMAGEMANAGER->findImage("mapTool2");
	}

	if (PtInRect(&_rc3, _ptMouse))
	{
		_QuitIg = IMAGEMANAGER->findImage("quit");
		if (INPUT->GetKeyDown(VK_LBUTTON))
		{
			PostQuitMessage(0);
		}
	}
	else
	{
		_QuitIg = IMAGEMANAGER->findImage("quit2");
	}

	

	_alpha += 5;
	if (_alpha > 255) _alpha = 0;
	_angle += PI/32;
	if (_angle > 2 * PI) _angle -= 2 * PI;
	
	_count++;
	if (_count == 2)
	{
		_count = 0;
		_xFrame += 1;
		if (_xFrame > 7)
		{
			_xFrame = 0;
			_yFrame++;

			if (_yFrame > 7)
			{
				_yFrame = 0;
			}
		}
	}
}

void startScene::render()
{
	RECT rc = RectMake(0, 0, WINSIZEX, WINSIZEY);
	IMAGEMANAGER->loopRender("BackCloud", getMemDC(), &rc, _backLoopX, 0);
	IMAGEMANAGER->loopRender("MidCloud0", getMemDC(), &rc, _midLoopX, 0);
	IMAGEMANAGER->loopRender("FrontCloud", getMemDC(), &rc, _frontLoopX, 0);
	IMAGEMANAGER->findImage("MainLogo")->render(getMemDC(), 500, 200);

	
	_StartIg->render(getMemDC(), _rc.left, _rc.top);
	_MaptoolIg->render(getMemDC(), _rc2.left, _rc2.top);
	_QuitIg->render(getMemDC(), _rc3.left, _rc3.top);
	IMAGEMANAGER->findImage("BasicCursor")->render(getMemDC(), _ptMouse.x, _ptMouse.y);

	/*_img->render(getMemDC(), 100, 0, _angle);
	_img->alphaRender(getMemDC(), 200, 0, _alpha, _angle);
	_img->stretchRender(getMemDC(), 300, 0, 1.5f, 1.5f, _angle);
	_img->stretchRender(getMemDC(), 450, 0, 0.5f, 0.5f, _angle);
	_img->stretchAlphaRender(getMemDC(), 500, 0, 1.5f, 1.5f, _alpha, _angle);
	_img->stretchAlphaRender(getMemDC(), 650, 0, 0.5f, 0.5f, _alpha, _angle);
	_img2->frameRender(getMemDC(), 200, 200, _xFrame, _yFrame, _angle);
	_img2->frameAlphaRender(getMemDC(), 300, 200, _xFrame, _yFrame,_alpha, _angle);
	_img2->frameStretchRender(getMemDC(), 400, 200, _xFrame, _yFrame,1.5,1.5, _angle);
	_img2->frameStretchAlphaRender(getMemDC(), 200, 500, _xFrame, _yFrame,1.5,1.5,_alpha, _angle);*/
}
