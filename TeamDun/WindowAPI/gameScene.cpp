#include "stdafx.h"
#include "gameScene.h"

HRESULT gameScene::init()
{
	UIMANAGER->init();

	return S_OK;
}

void gameScene::release()
{
}

void gameScene::update()
{
	if (INPUT->GetKeyDown(VK_BACK))
	{
		UIMANAGER->_GameFrame->GetVChildFrames().clear();
		SCENEMANAGER->loadScene("시작화면");
	}
}

void gameScene::render()
{
	IMAGEMANAGER->findImage("BasicCursor")->render(getMemDC(), _ptMouse.x, _ptMouse.y);
	TextOut(getMemDC(), 0, 0, "EXIT : VK_BACK", strlen("EXIT : VK_BACK"));
}
