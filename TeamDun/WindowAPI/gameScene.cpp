#include "stdafx.h"
#include "gameScene.h"

HRESULT gameScene::init()
{
	UIMANAGER->init();
	initUI();

	MAPMANAGER->init();
	_p = new Player();
	_p->init();

	ENTITYMANAGER->init();
	ENTITYMANAGER->setPlayer(_p);

	EFFECTMANAGER->init();

	_pivX = WINSIZEX / 2;
	_pivY = WINSIZEY / 2;

	CAMERAMANAGER->init(0,0,15000,15000,-300,-300,WINSIZEX/2, WINSIZEY/2);

	return S_OK;
}

void gameScene::initUI()
{
	// UIFrame

	UIImage* allMapFrame = new UIImage();
	allMapFrame->init("allMapFrame", 0, 0, WINSIZEX, WINSIZEY, "ScreenCover", false, 0, 0, 1, 1, 80);
	UIMANAGER->GetGameFrame()->AddFrame(allMapFrame);

	UIFrame* mapUpperImg = new UIFrame();
	mapUpperImg->init("mapUpperImg", 0, 0, IMAGEMANAGER->findImage("MapBase_1_0")->getWidth(), IMAGEMANAGER->findImage("MapBase_1_0")->getHeight(), "MapBase_1_0", 1.0f, 1.0f);
	allMapFrame->AddFrame(mapUpperImg);

	UIFrame* mapFrame = new UIFrame();
	mapFrame->init("mapFrame", 130, 180, IMAGEMANAGER->findImage("MapBase_1_1")->getWidth(), IMAGEMANAGER->findImage("MapBase_1_1")->getHeight(), "MapBase_1_1", 1.5f, 1.4f);
	mapFrame->SetUseOutsideLimit(true);
	allMapFrame->AddFrame(mapFrame);
	
	allMapFrame->SetIsViewing(false);
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

	/*
	if (INPUT->GetKeyDown(VK_F2))
	{
		MAPMANAGER->ChangeMap(MAPMANAGER->GetCurrentStage(), RANDOM->range((int)MAPMANAGER->GetMaps().size()));
		ENTITYMANAGER->getPlayer()->SetX(30);
		ENTITYMANAGER->getPlayer()->SetY(30);
	}
	*/

	MAPMANAGER->update();
	CAMERAMANAGER->MovePivotLerp(ENTITYMANAGER->getPlayer()->GetX(), ENTITYMANAGER->getPlayer()->GetY(), 5.f);
	ENTITYMANAGER->update();
	EFFECTMANAGER->update();
}

void gameScene::render()
{
	MAPMANAGER->render(getMemDC());
	UIMANAGER->render(getMemDC());

	TextOut(getMemDC(), 0, 0, "EXIT : VK_BACK", strlen("EXIT : VK_BACK"));
	//TextOut(getMemDC(), 0, 30, MAPMANAGER->GetMaps()[MAPMANAGER->GetCurrentMap()]->GetFileName().c_str(), MAPMANAGER->GetMaps()[MAPMANAGER->GetCurrentMap()]->GetFileName().size());

	IMAGEMANAGER->findImage("BasicCursor")->render(getMemDC(), _ptMouse.x, _ptMouse.y);

	string n = to_string((int)CAMERAMANAGER->GetAbsoluteX(_ptMouse.x)) + " " + to_string((int)CAMERAMANAGER->GetAbsoluteY(_ptMouse.y));
	TextOut(getMemDC(), _ptMouse.x, _ptMouse.y, n.c_str(), n.length());
}
