#include "stdafx.h"
#include "gameScene.h"

HRESULT gameScene::init()
{
	MAPMANAGER->init();
	UIMANAGER->init();
	_p = new Player();
	_p->init();

	ENTITYMANAGER->init();
	ENTITYMANAGER->setPlayer(_p);

	EFFECTMANAGER->init();

	_pivX = WINSIZEX / 2;
	_pivY = WINSIZEY / 2;

	CAMERAMANAGER->init(0,0,15000,15000,-500,-500,WINSIZEX/2, WINSIZEY/2);
	MAPMANAGER->ChangeMap(RANDOM->range((int)MAPMANAGER->GetMaps().size()));


	return S_OK;
}

void gameScene::release()
{
	ENTITYMANAGER->release();
	ENTITYMANAGER->releaseSingleton();
	MAPMANAGER->release();
	MAPMANAGER->releaseSingleton();
	EFFECTMANAGER->release();
	EFFECTMANAGER->releaseSingleton();
}

void gameScene::update()
{
	if (INPUT->GetKeyDown(VK_BACK))
	{
		UIMANAGER->_GameFrame->GetVChildFrames().clear();
		SCENEMANAGER->loadScene("시작화면");
	}

	if (INPUT->GetKeyDown(VK_F2))
	{
		MAPMANAGER->ChangeMap(RANDOM->range((int)MAPMANAGER->GetMaps().size()));
		ENTITYMANAGER->getPlayer()->SetX(30);
		ENTITYMANAGER->getPlayer()->SetY(30);
	}

	MAPMANAGER->GetMaps()[MAPMANAGER->GetCurrentMap()]->update();
	CAMERAMANAGER->MovePivotLerp(ENTITYMANAGER->getPlayer()->GetX(), ENTITYMANAGER->getPlayer()->GetY(), 5.f);
	ENTITYMANAGER->update();
	EFFECTMANAGER->update();
}

void gameScene::render()
{
	MAPMANAGER->GetMaps()[MAPMANAGER->GetCurrentMap()]->render(getMemDC());
	UIMANAGER->render(getMemDC());

	TextOut(getMemDC(), 0, 0, "EXIT : VK_BACK", strlen("EXIT : VK_BACK"));
	TextOut(getMemDC(), 0, 30, MAPMANAGER->GetMaps()[MAPMANAGER->GetCurrentMap()]->GetFileName().c_str(), MAPMANAGER->GetMaps()[MAPMANAGER->GetCurrentMap()]->GetFileName().size());

	IMAGEMANAGER->findImage("BasicCursor")->render(getMemDC(), _ptMouse.x, _ptMouse.y);
}
