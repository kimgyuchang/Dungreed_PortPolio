#include "stdafx.h"
#include "mapScene.h"

HRESULT mapScene::init()
{
	UIMANAGER->init();

	_heightNum = 1;
	_widthNum = 1;
	_endSetPage = true;

	_uiBrushTool = new uibrushTool();
	_uiBrushTool->init();
	_uiBrushTool->SetMapScene(this);
	
	_mapTool = new MapTool();
	_isCheck = false;

	UIFrame* setSizeFrame = new UIFrame();
	setSizeFrame->init("sizeFrame", 100, 100, IMAGEMANAGER->findImage("UIBaseBig")->getWidth(), IMAGEMANAGER->findImage("UIBaseBig")->getHeight(), "UIBaseBig");
	UIMANAGER->GetGameFrame()->AddFrame(setSizeFrame);

	UIImage* setUpFrame = new UIImage();
	setUpFrame->init("UpButtonFrame", 860, 120, IMAGEMANAGER->findImage("UpButton")->getWidth(), IMAGEMANAGER->findImage("UpButton")->getHeight(), "UpButton", false, 0, 0);
	setSizeFrame->AddFrame(setUpFrame);

	UIImage* setDownFrame = new UIImage();
	setDownFrame->init("DownButtonFrame", 860, 190, IMAGEMANAGER->findImage("DownButton")->getWidth(), IMAGEMANAGER->findImage("DownButton")->getHeight(), "DownButton", false, 0, 0);
	setSizeFrame->AddFrame(setDownFrame);

	UIImage* setLeftFrame = new UIImage();
	setLeftFrame->init("LeftButtonFrame", 860, 450, IMAGEMANAGER->findImage("LeftButton")->getWidth(), IMAGEMANAGER->findImage("LeftButton")->getHeight(), "LeftButton", false, 0, 0);
	setSizeFrame->AddFrame(setLeftFrame);

	UIImage* setRightFrame = new UIImage();
	setRightFrame->init("RightButtonFrame", 860, 380, IMAGEMANAGER->findImage("RightButton")->getWidth(), IMAGEMANAGER->findImage("RightButton")->getHeight(), "RightButton", false, 0, 0);
	setSizeFrame->AddFrame(setRightFrame);

	UIImage* setHeightBoxFrame = new UIImage();
	setHeightBoxFrame->init("HeightBox", 600, 390, IMAGEMANAGER->findImage("mapHeightBox")->getWidth(), IMAGEMANAGER->findImage("mapHeightBox")->getHeight(), "mapHeightBox", false, 0, 0);
	setSizeFrame->AddFrame(setHeightBoxFrame);

	UIImage* setWidthBoxFrame = new UIImage();
	setWidthBoxFrame->init("WidthBox", 600, 130, IMAGEMANAGER->findImage("mapWidthBox")->getWidth(), IMAGEMANAGER->findImage("mapWidthBox")->getHeight(), "mapWidthBox", false, 0, 0);
	setSizeFrame->AddFrame(setWidthBoxFrame);

	UIText* widthText = new UIText();
	widthText->init("Word", -200, 40, 200, 50, "가로", FONT::PIX, WORDSIZE::WS_BIG, WORDSORT::WSORT_MIDDLE, RGB(255, 255, 255));
	setHeightBoxFrame->AddFrame(widthText);

	UIText* heightText = new UIText();
	heightText->init("Word", -200, 40, 200, 50, "세로", FONT::PIX, WORDSIZE::WS_BIG, WORDSORT::WSORT_MIDDLE, RGB(255, 255, 255));
	setWidthBoxFrame->AddFrame(heightText);

	UIText* setHeightNumFrame = new UIText();
	setHeightNumFrame->init("Word", 0, 40, 200, 50, "1", FONT::PIX, WORDSIZE::WS_BIG, WORDSORT::WSORT_MIDDLE, RGB(255,255,255));
	setHeightBoxFrame->AddFrame(setHeightNumFrame);

	UIText* setWidthNumFrame = new UIText();
	setWidthNumFrame->init("Word", 0, 40, 200, 50, "1", FONT::PIX, WORDSIZE::WS_BIG, WORDSORT::WSORT_MIDDLE, RGB(255, 255, 255));
	setWidthBoxFrame->AddFrame(setWidthNumFrame);

	return S_OK;
}

void mapScene::release()
{
}

void mapScene::update()
{
	UIMANAGER->update();

	if (_endSetPage)
	{
		if(INPUT->GetKeyDown(VK_TAB))
		{
			_mapTool->init(_widthNum,_heightNum);
			_mapTool->SetMapScene(this); 
			_endSetPage = false;
			UIMANAGER->GetGameFrame()->GetChild("sizeFrame")->SetIsViewing(false);
		}

		//10의자리 숫자 출력 안하게 하는거 예시
		/*UIMANAGER->GetGameFrame()->GetChild("sizeFrame")->GetChild("HeightBox")->GetChild("Word2")->SetIsViewing(false, false);*/
	
		UIFrame* frame = UIMANAGER->GetGameFrame()->GetChild("sizeFrame");
		if (PtInRect(&frame->GetChild("UpButtonFrame")->GetRect(), _ptMouse)&&INPUT->GetKeyDown(VK_LBUTTON))
		{
			_heightNum++;
			dynamic_cast<UIText*>(frame->GetChild("HeightBox")->GetChild("Word"))->SetText(to_string(_heightNum));
		}
		if (PtInRect(&frame->GetChild("DownButtonFrame")->GetRect(), _ptMouse) && INPUT->GetKeyDown(VK_LBUTTON))
		{
			_heightNum--;
			if (_heightNum < 1) _heightNum = 1;
			dynamic_cast<UIText*>(frame->GetChild("HeightBox")->GetChild("Word"))->SetText(to_string(_heightNum));
		}
		if (PtInRect(&frame->GetChild("RightButtonFrame")->GetRect(), _ptMouse) && INPUT->GetKeyDown(VK_LBUTTON))
		{
			_widthNum++;
			dynamic_cast<UIText*>(frame->GetChild("WidthBox")->GetChild("Word"))->SetText(to_string(_widthNum));
		}
		if (PtInRect(&frame->GetChild("LeftButtonFrame")->GetRect(), _ptMouse) && INPUT->GetKeyDown(VK_LBUTTON))
		{
			_widthNum--;
			if (_widthNum < 1) _widthNum = 1;
			dynamic_cast<UIText*>(frame->GetChild("WidthBox")->GetChild("Word"))->SetText(to_string(_widthNum));
		}
	}

	else
	{
		if (INPUT->GetKeyDown(VK_LBUTTON))
		{
			_uiBrushTool->mouseCollisionCheck();
		}

		if (_targetImage != nullptr && INPUT->GetKeyDown('P'))
		{
			Grid* grid = _mapTool->mouseCollisionCheck();
			if (grid)
			{
				_mapTool->fillAll(_targetImage);
			}
		}
		if (_targetImage != nullptr && INPUT->GetKeyDown('O'))
		{
			Grid* grid = _mapTool->mouseCollisionCheck();
			if (grid)
			{
				if (grid->_img != _targetImage)
				{
					_mapTool->fill(grid->_img, grid->_xIndex, grid->_yIndex);
				}
			}
		}

		if (_targetImage != nullptr && INPUT->GetKey(VK_RBUTTON))
		{
			Grid* grid = _mapTool->mouseCollisionCheck();
			if (grid) grid->_img = _targetImage;
		}

		if (_targetImage != nullptr && INPUT->GetKeyDown('A'))
		{
			Grid* grid = _mapTool->mouseCollisionCheck();
			if (grid)
			{

				if (_isCheck == false)
				{
					_clickedPointOne = POINT{ grid->_xIndex, grid->_yIndex };
					_isCheck = true;
				}

				else
				{
					_clickedPointTwo = POINT{ grid->_xIndex, grid->_yIndex };
					_mapTool->GridRange(_clickedPointOne.x, _clickedPointOne.y, _clickedPointTwo.x, _clickedPointTwo.y);
					_isCheck = false;
				}
			}
		}

		if (_targetImage != nullptr && INPUT->GetKey(VK_SPACE))
		{
			Grid* grid = _mapTool->mouseCollisionCheck();
			if (grid)
			{
				grid->_img = nullptr;
			}
		}

		AddMapLine();
		saveData();
		loadData();
	}
}

void mapScene::render()
{
	_uiBrushTool->render();
	_mapTool->render();

	if (_targetImage) _targetImage->alphaRender(getMemDC(), _ptMouse.x, _ptMouse.y, 128);

	UIMANAGER->render(getMemDC());
}

void mapScene::saveData()
{
	if (INPUT->GetKeyDown('S'))
	{
		_mapTool->SaveData();
	}
}

void mapScene::AddMapLine()
{
	if (INPUT->GetKeyDown('T'))
	{
		_mapTool->MapLineAddCol();
	}

	if (INPUT->GetKeyDown('Y'))
	{
		_mapTool->MapLineAddRow();
	}

	if (INPUT->GetKeyDown('G'))
	{
		_mapTool->MapLineRemoveCol();
	}

	if (INPUT->GetKeyDown('H'))
	{
		_mapTool->MapLineRemoveRow();
	}
}

void mapScene::loadData()
{
	if (INPUT->GetKeyDown('L'))
	{
		_mapTool->LoadData();
	}
}