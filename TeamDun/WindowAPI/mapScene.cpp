#include "stdafx.h"
#include "mapScene.h"

HRESULT mapScene::init()
{
	UIMANAGER->init();

	_heightNum = 0;
	_widthNum = 0;
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

	/*UIImage* setHeightNumFrame = new UIImage();
	setHeightNumFrame->init("Word", 110, 40, IMAGEMANAGER->findImage("Word")->getWidth(), IMAGEMANAGER->findImage("Word")->getHeight(), "Word", true, _heightNum, 0);
	setHeightBoxFrame->AddFrame(setHeightNumFrame);

	UIImage* setHeightNumFrame2 = new UIImage();
	setHeightNumFrame2->init("Word2", 70, 40, IMAGEMANAGER->findImage("Word")->getWidth(), IMAGEMANAGER->findImage("Word")->getHeight(), "Word", true,0, 0);
	setHeightBoxFrame->AddFrame(setHeightNumFrame2);

	UIImage* setWidthNumFrame = new UIImage();
	setWidthNumFrame->init("Word", 110, 40, IMAGEMANAGER->findImage("Word")->getWidth(), IMAGEMANAGER->findImage("Word")->getHeight(), "Word", true, 0, 0);
	setWidthBoxFrame->AddFrame(setWidthNumFrame);

	UIImage* setWidthNumFrame2 = new UIImage();
	setWidthNumFrame2->init("Word2", 70, 40, IMAGEMANAGER->findImage("Word")->getWidth(), IMAGEMANAGER->findImage("Word")->getHeight(), "Word", true, 0, 0);
	setWidthBoxFrame->AddFrame(setWidthNumFrame2);
	*/

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
	

		if (PtInRect(&UIMANAGER->GetGameFrame()->GetChild("sizeFrame")->GetChild("UpButtonFrame")->GetRect(), _ptMouse)&&INPUT->GetKeyDown(VK_LBUTTON))
		{
			_heightNum++;
		}
		if (PtInRect(&UIMANAGER->GetGameFrame()->GetChild("sizeFrame")->GetChild("DownButtonFrame")->GetRect(), _ptMouse) && INPUT->GetKeyDown(VK_LBUTTON))
		{
			_heightNum--;
		}
		if (PtInRect(&UIMANAGER->GetGameFrame()->GetChild("sizeFrame")->GetChild("RightButtonFrame")->GetRect(), _ptMouse) && INPUT->GetKeyDown(VK_LBUTTON))
		{
			_widthNum++;
		}
		if (PtInRect(&UIMANAGER->GetGameFrame()->GetChild("sizeFrame")->GetChild("LeftButtonFrame")->GetRect(), _ptMouse) && INPUT->GetKeyDown(VK_LBUTTON))
		{
			_widthNum--;
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

		if (_targetImage != nullptr && INPUT->GetKeyDown(VK_SPACE))
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