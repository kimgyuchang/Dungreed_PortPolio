#include "stdafx.h"
#include "gameScene.h"

HRESULT gameScene::init()
{
	UIMANAGER->init();
	_p = new Player();
	_p->init();

	ENTITYMANAGER->init();
	ENTITYMANAGER->setPlayer(_p);

	_pivX = WINSIZEX / 2;
	_pivY = WINSIZEY / 2;

	CAMERAMANAGER->init(0,0,15000,15000,-500,-500,WINSIZEX/2, WINSIZEY/2);

	
	FieldMap* map = new FieldMap();
	map->init("Stage1_longY");
	_maps.push_back(map);
	_currentMap = 0;
	return S_OK;
}

void gameScene::release()
{
	ENTITYMANAGER->release();
}

void gameScene::update()
{
	if (INPUT->GetKeyDown(VK_BACK))
	{
		UIMANAGER->_GameFrame->GetVChildFrames().clear();
		SCENEMANAGER->loadScene("시작화면");
	}
	_maps[_currentMap]->update();
	CAMERAMANAGER->MovePivotLerp(ENTITYMANAGER->getPlayer()->GetX(), ENTITYMANAGER->getPlayer()->GetY(), 5.f);
	ENTITYMANAGER->update();
}

void gameScene::render()
{
	IMAGEMANAGER->findImage("BasicCursor")->render(getMemDC(), _ptMouse.x, _ptMouse.y);
	TextOut(getMemDC(), 0, 0, "EXIT : VK_BACK", strlen("EXIT : VK_BACK"));

	_maps[_currentMap]->render(getMemDC());
	ENTITYMANAGER->render(getMemDC());
	UIMANAGER->render(getMemDC());
}
