#include "stdafx.h"
#include "mainGame.h"

//=============================================================
//	## 초기화 ## init()
//=============================================================
HRESULT mainGame::init()
{
	gameNode::init();

	SCENEMANAGER->addScene("로딩화면", new loadingScene());
	SCENEMANAGER->addScene("맵씬", new mapScene());
	SCENEMANAGER->loadScene("로딩화면");

	return S_OK;
}

//=============================================================
//	## 해제 ## release()
//=============================================================
void mainGame::release()
{
	gameNode::release();
}

//=============================================================
//	## 업데이트 ## update()
//=============================================================
void mainGame::update()
{
	gameNode::update();
	
	SCENEMANAGER->update();
	SOUNDMANAGER->update();
}

//=============================================================
//	## 렌더 ## render()
//=============================================================
void mainGame::render()
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
	SetBkMode(getMemDC(), TRANSPARENT);
	// ============================================= //
	
	SCENEMANAGER->render();
	// ============================================= //
	this->getBackBuffer()->render(getHDC());
}
