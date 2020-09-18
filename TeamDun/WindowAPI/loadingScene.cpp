#include "stdafx.h"
#include "loadingScene.h"

HRESULT loadingScene::init()
{
	//로딩클래스 초기화
	_loading = new loading;
	_loading->init();
	SOUNDMANAGER->addSound("BB7INTR", "BB7INTR.wav", true, true);
	SOUNDMANAGER->play("BB7INTR",0.1);

	//로딩 이미지 및 사운드 초기화
	this->loadingImage();
	this->loadingSound();

	return S_OK;
}

void loadingScene::release()
{
	//로딩클래스 해제
	_loading->release();
	SAFE_DELETE(_loading);
}

void loadingScene::update()
{
	//로딩클래스 업데이트
	_loading->update();
	
	//로딩완료후 화면 변경
	if (_loading->loadingDone())
	{
		SOUNDMANAGER->stop("BB7INTR");
		SCENEMANAGER->loadScene("맵씬");
	}

}

void loadingScene::render()
{
	//로딩클래스 렌더
	_loading->render();

	textOut(getMemDC(), 10, 10, "로딩화면");

	IMAGEMANAGER->frameRender("number", getMemDC(), 680, 500,(int)((float)_loading->getCurrentGauge() /(float)_loading->getLoadItem().size()*100) % 10, 0);
	if ((int)((float)_loading->getCurrentGauge()*(100 / (float)_loading->getLoadItem().size()) / 10) > 0)
	IMAGEMANAGER->frameRender("number", getMemDC(), 660, 500, (float)_loading->getCurrentGauge()*(100/(float)_loading->getLoadItem().size()) / 10, 0);
	
}

void loadingScene::loadingImage()
{
	//로딩이 너무 빠르게 진행되서 천천히 돌아가도록 테스트용으로 만들기
	//for (int i = 0; i < 0; i++)
	//{
	//	_loading->loadImage("Test",("test"+to_string(i)).c_str(), WINSIZEX, WINSIZEY);
	//}	

	_loading->loadImage("Tile0", "Images/Tile (1).bmp", 48, 48);
	_loading->loadImage("Tile1", "Images/Tile (2).bmp", 48, 48);
	_loading->loadImage("Tile2", "Images/Tile (3).bmp", 48, 48);
	_loading->loadImage("Tile3", "Images/Tile (4).bmp", 48, 48);
	_loading->loadImage("Tile4", "Images/Tile (5).bmp", 48, 48);
	_loading->loadImage("Tile5", "Images/Tile (6).bmp", 48, 48);
	_loading->loadImage("Tile6", "Images/Tile (7).bmp", 48, 48);
	_loading->loadImage("Tile7", "Images/Tile (8).bmp", 48, 48);
	_loading->loadImage("Tile8", "Images/Tile (9).bmp", 48, 48);
	_loading->loadImage("Tile9", "Images/Tile (10).bmp", 48, 48);
	_loading->loadImage("Tile10", "Images/Tile (11).bmp", 48, 48);
	_loading->loadImage("Tile11", "Images/Tile (12).bmp", 48, 48);
	_loading->loadImage("Tile12", "Images/Tile (13).bmp", 48, 48);
	_loading->loadImage("Tile13", "Images/Tile (14).bmp", 48, 48);
	_loading->loadImage("Tile14", "Images/Tile (15).bmp", 48, 48);

	_loading->loadImage("mountain", "Images/mountain.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	_loading->loadImage("ball", "Images/ball.bmp", 60, 60, true, RGB(255, 0, 255));
}

void loadingScene::loadingSound()
{
	/*for (int i = 0; i < 500; i++)
	{
		_loading->loadSound("testSound", "testSound", true, true);
		
	}*/
}
