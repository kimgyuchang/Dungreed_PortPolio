#include "stdafx.h"
#include "uibrushTool.h"
#include "mapScene.h"

HRESULT uibrushTool::init()
{
	DATAMANAGER->GetUIBrushToolData();

	_page = 0;
	_vUiBrushObject.push_back(vector<Object*>());
	_isOn = false;
	_isObject = true;
	_xPos = 1400;
	return S_OK;
}

void uibrushTool::UIInit()
{
	UIFrame* brushToolFrame = new UIFrame();
	brushToolFrame->init("brushTool", _xPos, 10, 222, 189, "Base", 1.7f, 4.1f);
	UIMANAGER->GetGameFrame()->AddFrame(brushToolFrame);

	UIFrame* brushGridButton = new UIFrame();
	brushGridButton->init("gridBtn", -50, 20, 222, 189, "Base", 0.5f, 1.0f);
	brushToolFrame->AddFrame(brushGridButton);
	brushGridButton->SetRenderBeforeParent(true);

	UIText* brushText = new UIText();
	brushText->init("Text", 10, 20, 30, 170, "   그리드   ", FONT::PIX, WORDSIZE::WS_MIDDLE, WORDSORT::WSORT_MIDDLE, RGB(255, 255, 255));
	brushGridButton->AddFrame(brushText);

	UIFrame* brushObjectButton = new UIFrame();
	brushObjectButton->init("objBtn", -50, 220, 222, 189, "Base", 0.5f, 1.0f);
	brushToolFrame->AddFrame(brushObjectButton);
	brushObjectButton->SetRenderBeforeParent(true);

	brushText = new UIText();
	brushText->init("Text", 10, 0, 30, 170, "  오브젝트  ", FONT::PIX, WORDSIZE::WS_MIDDLE, WORDSORT::WSORT_MIDDLE, RGB(255, 255, 255));
	brushObjectButton->AddFrame(brushText);

	UIImage* arrow = new UIImage();
	arrow->init("arrowLeft", 30, 670, IMAGEMANAGER->findImage("OptionArrow1")->getWidth(), IMAGEMANAGER->findImage("OptionArrow1")->getHeight(), "OptionArrow1", false, 0, 0);
	brushToolFrame->AddFrame(arrow);

	arrow = new UIImage();
	arrow->init("arrowRight", 240, 670, IMAGEMANAGER->findImage("OptionArrow0")->getWidth(), IMAGEMANAGER->findImage("OptionArrow0")->getHeight(), "OptionArrow0", false,0,0);
	brushToolFrame->AddFrame(arrow);
	
	map<int, GridData*> dataSet = DATAMANAGER->GetGridData();
	for (auto it = dataSet.begin(); it != dataSet.end(); it++)
	{
		GridData* data = it->second;
		UIImage* image = new UIImage();
		image->init(data->_name, data->_x, data->_y, 48, 48, data->_name, false, 0, 0);
		brushToolFrame->AddFrame(image);

		while (_vUiBrushGrid.size() <= data->_page) _vUiBrushGrid.push_back(vector<UIImage*>());
		_vUiBrushGrid[data->_page].push_back(image);

		if (data->_page != _page) image->SetIsViewing(false);
	}
}

void uibrushTool::PageViewChange()
{
	for (int i = 0; i < _vUiBrushGrid.size(); i++)
	{
		for (int j = 0; j < _vUiBrushGrid[i].size(); j++)
		{
			if (i == _page) _vUiBrushGrid[i][j]->SetIsViewing(true);
			else _vUiBrushGrid[i][j]->SetIsViewing(false);
		}
	}
}

void uibrushTool::release()
{
}

void uibrushTool::update() 
{
	MoveBrushTool();
}

void uibrushTool::MoveBrushTool()
{
	UIFrame* frame = UIMANAGER->GetGameFrame()->GetChild("brushTool");

	if (_isOn && frame->GetX() > 1100)
	{
		UIMANAGER->GetGameFrame()->GetChild("brushTool")->MoveFrame(-15, 0);
	}

	if (!_isOn && frame->GetX() < 1400)
	{
		UIMANAGER->GetGameFrame()->GetChild("brushTool")->MoveFrame(15, 0);
	}
}

void uibrushTool::MenuCollisionCheck()
{
	UIFrame* frame = UIMANAGER->GetGameFrame()->GetChild("brushTool");
	if (PtInRect(&frame->GetChild("gridBtn")->GetRect(), _ptMouse))
	{
		if (_isOn)
		{
			if (_isObject)
			{
				_isObject = false;
				
			}

			else
			{
				_isOn = false;
			}
		}

		else
		{
			_isObject = false;
			_isOn = true;
		}
	}

	else if (PtInRect(&frame->GetChild("objBtn")->GetRect(), _ptMouse))
	{
		if (_isOn)
		{
			if (_isObject)
			{
				_isOn = false;
			}

			else
			{
				_isObject = true;
			}
		}

		else
		{
			_isObject = true;
			_isOn = true;
		}
	}
}

void uibrushTool::render()
{
}

void uibrushTool::mouseCollisionCheck()
{
	for (int i = 0; i < _vUiBrushGrid[_page].size(); i++)
	{
		if (PtInRect(&_vUiBrushGrid[_page][i]->GetRect(), _ptMouse))
		{
			_mapScene->SetTargetImage(_vUiBrushGrid[_page][i]->GetImage());
			return;
		}
	}
}
