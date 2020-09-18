#include "stdafx.h"
#include "UIFrame.h"

HRESULT UIFrame::init(string name, float x, float y, float sizeX, float sizeY, string imageName)
{
	_name = name;
	_x = x;
	_y = y;
	_sizeX = sizeX;
	_sizeY = sizeY;
	_image = IMAGEMANAGER->findImage(imageName);
	_interactRect = RectMake(_x, _y, _sizeX, _sizeY);
	_parent = nullptr;

	_isSelected = false;
	_selectTimer = 0;
	_moveStartX = 0;
	_moveStartY = 0;
	_useOutsideLimit = false;
	_isMoveToDrag = false;
	SetIntersectRect();

	return S_OK;
}

void UIFrame::update()
{
	MoveFrame();

	for (int i = 0; i < _vChildFrames.size(); i++)
	{
		_vChildFrames[i]->update();
	}

	CheckIsOutside();
}

void UIFrame::ToggleIsViewing()
{
	_isViewing = !_isViewing;

	for (int i = 0; i < _vChildFrames.size(); i++)
	{
		_vChildFrames[i]->ToggleIsViewing();
	}
}

void UIFrame::AddFrame(UIFrame* frame)
{
	frame->_isChild = true;
	frame->_isViewing = _isViewing;
	frame->_parent = this;
	

	frame->SetX(_x + frame->GetX());
	frame->SetY(_y + frame->GetY());
	frame->SetIntersectRect();

	AddChildMap(frame->GetName(), frame);
	_vChildFrames.push_back(frame);
}

void UIFrame::SetIsViewing(bool isViewing, bool withChild)
{
	_isViewing = isViewing;

	if (withChild)
	{
		for (int i = 0; i < _vChildFrames.size(); i++)
		{
			_vChildFrames[i]->SetIsViewing(isViewing, withChild);
		}
	}
}

void UIFrame::MoveFrame()
{
	if (!_isChild && _isViewing && _isMoveToDrag)
	{
		if (PtInRect(&_interactRect, _ptMouse) && INPUT->GetKey(VK_LBUTTON))
		{
			_selectTimer++;

			if (_selectTimer == 10)
			{
				_moveStartX = _ptMouse.x;
				_moveStartY = _ptMouse.y;
				_savedX = _x;
				_savedY = _y;
				_isSelected = true;
			}
		}

		if (_isSelected)
		{
			int newX = _savedX + (_ptMouse.x - _moveStartX);
			int newY = _savedY + (_ptMouse.y - _moveStartY);

			for (int i = 0; i < _vChildFrames.size(); i++)
			{
				MoveFrameChild(newX - _x, newY - _y);
			}

			_x = newX;
			_y = newY;
			_interactRect = RectMake(_x, _y, _sizeX, _sizeY);
		}

		if (!INPUT->GetKey(VK_LBUTTON))
		{
			_isSelected = false;
			_selectTimer = 0;
		}
	}
}

void UIFrame::MoveFrameChild(float x, float y)
{
	_x += x;
	_y += y;
	_interactRect = RectMake(_x, _y, _sizeX, _sizeY);

	for (int i = 0; i < _vChildFrames.size(); i++)
	{
		_vChildFrames[i]->MoveFrameChild(x, y);
	}
}

void UIFrame::CheckIsOutside()
{
	if (_isChild)
	{
		if (_x < _parent->GetX() || _y < _parent->GetY() ||
			_x + _sizeX > _parent->GetX() + _parent->GetSizeX() ||
			_y + _sizeY > _parent->GetY() + _parent->GetSizeY())
		{
			_isOutside = true;
		}

		else
		{
			_isOutside = false;
		}
	}
}

void UIFrame::render(HDC hdc)
{
	if (_isViewing)
	{
		if (_isChild)
		{
			if (_useOutsideLimit && _isOutside) {}
			else
			{
				if(_image != nullptr) _image->render(hdc, _x, _y);
				if(INPUT->GetKey('P')) Rectangle(hdc, _interactRect);

				for (int i = 0; i < _vChildFrames.size(); i++)
				{
					_vChildFrames[i]->render(hdc);
				}
			}
		}

		else
		{
			if(_image != nullptr) _image->render(hdc, _x, _y);
			if (INPUT->GetKey('P')) Rectangle(hdc, _interactRect);

			for (int i = 0; i < _vChildFrames.size(); i++)
			{
				_vChildFrames[i]->render(hdc);
			}
		}
	}
}

void UIFrame::release()
{
	for (int i = 0; i < _vChildFrames.size(); i++)
	{
		_vChildFrames[i]->release();
	}
}
