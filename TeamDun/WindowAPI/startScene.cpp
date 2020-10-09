#include "stdafx.h"
#include "startScene.h"


HRESULT startScene::init()
{
	//렉트 위치 초기화
	_rc = RectMakeCenter(WINSIZEX / 2, WINSIZEY - 500, 200, 100);
	_rc2 = RectMakeCenter(WINSIZEX / 2, WINSIZEY - 300, 200, 100);
	ShowCursor(false);
	_img = IMAGEMANAGER->findImage("DemensionVault1");
	_img2 = IMAGEMANAGER->findImage("DemensionVault1_test2");
	_angle = 0;
	_alpha = 0;
	_xFrame = 0;
	_yFrame = 0;
	_count = 0;
	return S_OK;
}

void startScene::release()
{
	
}

void startScene::update()
{
	if (INPUT->GetKeyDown(VK_LBUTTON))
	{
		if (PtInRect(&_rc, _ptMouse))
		{
			SCENEMANAGER->loadScene("게임화면");
		}

		if (PtInRect(&_rc2, _ptMouse))
		{
			SCENEMANAGER->loadScene("맵씬");
		}
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
	Rectangle(getMemDC(), _rc);
	Rectangle(getMemDC(), _rc2);

	TextOut(getMemDC(), _rc.left + 80, _rc.top + 50, "START", strlen("START"));
	TextOut(getMemDC(), _rc2.left + 80, _rc2.top + 50, "MAPTOOL", strlen("MAPTOOL"));

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
