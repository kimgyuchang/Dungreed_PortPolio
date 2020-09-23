#include "stdafx.h"
#include "uibrushTool.h"
#include "mapScene.h"

HRESULT uibrushTool::init()
{
	_page = 0;
	
	_vUiBrushGrid.push_back(vector<Grid*>());
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			Grid* grid = new Grid();
			grid->_img = IMAGEMANAGER->findImage("Tile" + to_string(i*5 +j));
			grid->_x = i * 50 + WINSIZEX / 2 + 200;
			grid->_y = j * 50 + 300;
			grid->_rc = RectMake(grid->_x, grid->_y, 50, 50);

			_vUiBrushGrid[0].push_back(grid);
		}
	}

	_vUiBrushObject.push_back(vector<Object*>());
	_isOn = false;
	_isObject = true;
	_xPos = 1400;
	return S_OK;
}

void uibrushTool::UIInit()
{
	UIFrame* brushToolFrame = new UIFrame();
	brushToolFrame->init("brushTool", _xPos, 180, 222, 189, "Base", 1.7f, 2.5f);
	UIMANAGER->GetGameFrame()->AddFrame(brushToolFrame);
	brushToolFrame->SetChildFirst(true);

	UIFrame* brushGridButton = new UIFrame();
	brushGridButton->init("gridBtn", -50, 20, 222, 189, "Base", 0.5f, 1.0f);
	brushToolFrame->AddFrame(brushGridButton);

	UIText* brushText = new UIText();
	brushText->init("Text", 10, 20, 30, 170, "   그리드   ", FONT::PIX, WORDSIZE::WS_MIDDLE, WORDSORT::WSORT_MIDDLE, RGB(255, 255, 255));
	brushGridButton->AddFrame(brushText);

	UIFrame* brushObjectButton = new UIFrame();
	brushObjectButton->init("objBtn", -50, 220, 222, 189, "Base", 0.5f, 1.0f);
	brushToolFrame->AddFrame(brushObjectButton);

	brushText = new UIText();
	brushText->init("Text", 10, 0, 30, 170, "  오브젝트  ", FONT::PIX, WORDSIZE::WS_MIDDLE, WORDSORT::WSORT_MIDDLE, RGB(255, 255, 255));
	brushObjectButton->AddFrame(brushText);

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
	for (int i = 0; i < _vUiBrushGrid[_page].size(); i++)
	{
		Grid* grid = _vUiBrushGrid[_page][i];
		Rectangle(getMemDC(), grid->_rc);
		if(grid->_img) grid->_img->render(getMemDC(), grid->_x, grid->_y);
	}

	for (int i = 0; i < _vUiBrushObject[_page].size(); i++)
	{
		Object* obj = _vUiBrushObject[_page][i];
		obj->GetImage(0)->render(getMemDC(), obj->GetX(), obj->GetY());
	}
}

void uibrushTool::mouseCollisionCheck()
{
	for (int i = 0; i < _vUiBrushGrid[_page].size(); i++)
	{
		if (PtInRect(&_vUiBrushGrid[_page][i]->_rc, _ptMouse))
		{
			_mapScene->SetTargetImage(_vUiBrushGrid[_page][i]->_img);
			return;
		}
	}
}