#include "stdafx.h"
#include "loadingScene.h"

HRESULT loadingScene::init()
{
	//로딩클래스 초기화

	_loading = new loading();
	_loading->init();
	//SOUNDMANAGER->addSound("PuzzleBubbleSound", "PuzzleBubbleSound.wav", true, true);
	//SOUNDMANAGER->play("PuzzleBubbleSound",0.1);

	this->loadingImage();
	this->loadingSound();

	return S_OK;
}

void loadingScene::release()
{
	_loading->release();
	SAFE_DELETE(_loading);
}

void loadingScene::update()
{
	_loading->update();
	
	//로딩완료후 화면 변경
	if (_loading->loadingDone())
	{
	//	SOUNDMANAGER->stop("PuzzleBubbleSound");
		SCENEMANAGER->loadScene("맵씬");
	}
}

void loadingScene::render()
{
	_loading->render();

	textOut(getMemDC(), 10, 10, "로딩화면");

	IMAGEMANAGER->frameRender("number", getMemDC(), 680, 500,(int)((float)_loading->getCurrentGauge() /(float)_loading->getLoadItem().size()*100) % 10, 0);
	if ((int)((float)_loading->getCurrentGauge()*(100 / (float)_loading->getLoadItem().size()) / 10) > 0)
	IMAGEMANAGER->frameRender("number", getMemDC(), 660, 500, (float)_loading->getCurrentGauge()*(100/(float)_loading->getLoadItem().size()) / 10, 0);
}

void loadingScene::loadingImage()
{
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
	_loading->loadImage("UIBaseBig", "Images/UI/Base.bmp", 222*5, 189*3 , true ,RGB(255,0,255));
	_loading->loadImage("UIBaseMiddle", "Images/UI/Base.bmp", 222*2, 189*2 , true ,RGB(255,0,255));
	_loading->loadImage("UIBaseSmall", "Images/UI/Base.bmp", 222, 189 , true ,RGB(255,0,255));
	//임시용
	_loading->loadImage("UpButton", "Images/UI/FullWindowExitButton_Selected.bmp", 66, 57 , true ,RGB(255,0,255));
	_loading->loadImage("RightButton", "Images/UI/FullWindowExitButton_Selected.bmp", 66, 57 , true ,RGB(255,0,255));
	_loading->loadImage("DownButton", "Images/UI/FullWindowExitButton.bmp", 66, 57 , true ,RGB(255,0,255));
	_loading->loadImage("LeftButton", "Images/UI/FullWindowExitButton.bmp", 66, 57 , true ,RGB(255,0,255));
	_loading->loadImage("mapWidthBox", "Images/UI/AbilityTextBar.bmp", 66*3, 108 , true ,RGB(255,0,255));
	_loading->loadImage("mapHeightBox", "Images/UI/AbilityTextBar.bmp", 66*3, 108 , true ,RGB(255,0,255));
	_loading->loadFrameImage("Word", "Images/number.bmp", 220, 28 ,10,1, true ,RGB(255,0,255));
}

void loadingScene::loadingSound()
{
}
