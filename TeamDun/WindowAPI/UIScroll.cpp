#include "stdafx.h"
#include "UIScroll.h"

HRESULT UIScroll::init(string name, float x, float y, float sizeX, float sizeY, string imageName)
{
	UIFrame::init(name, x, y, sizeX, sizeY, imageName);

	_target = nullptr;
	_scrollPercent = 0.f;

	return S_OK;
}

void UIScroll::update()
{
	MoveFrame();
	MoveScrollBar();

	for (int i = 0; i < _vChildFrames.size(); i++)
	{
		_vChildFrames[i]->update();
	}

	CheckIsOutside();
}

void UIScroll::MoveScrollBar()
{
	if (PtInRect(&_parent->GetRect(), _ptMouse))
	{
		float prevY = _y;
		if (_mouseWheel == 1)
		{
			_y = _y - (_parent->GetSizeY() * 0.03f);
			if (_y < _parent->GetY())
			{
				_y = _parent->GetY();
			}

			SetIntersectRect();
			CalculateScrollBarPercent();
		}

		else if (_mouseWheel == -1)
		{
			_y = _y + (_parent->GetSizeY() * 0.03f);
			if (_y + _image->getHeight() > _parent->GetSizeY() + _parent->GetY())
			{
				_y = _parent->GetSizeY() + _parent->GetY() - _image->getHeight();
			}
			SetIntersectRect();
			CalculateScrollBarPercent();
		}

		if (prevY != _y)
		{
			for (int i = 0; i < _vChildFrames.size(); i++)
			{
				MoveFrameChild(0, _y - prevY);
			}
		}
	}
}

void UIScroll::CalculateScrollBarPercent()
{
	float _prevScrollPercent = _scrollPercent;
	_scrollPercent = (_y - _parent->GetY()) / (_parent->GetSizeY() - _image->getHeight()); // ∫Ò¿≤
	
	float maxY = INT_MIN;
	float minY = INT_MAX;
	for (int i = 0; i < _target->GetVChildFrames().size(); i++)
	{
		if (_target->GetVChildFrames()[i] == this) continue;
		UIFrame* tempFrame = _target->GetVChildFrames()[i];
		if (tempFrame->GetY() > maxY) maxY = tempFrame->GetY();
		if (tempFrame->GetY() < minY) minY = tempFrame->GetY();
	}

	float moveY = _scrollPercent * (maxY - minY) - _prevScrollPercent * (maxY - minY);

	for (int i = 0; i < _target->GetVChildFrames().size() - 1; i++)
	{
		if (_target->GetVChildFrames()[i] == this) continue;
		UIFrame* tempFrame = _target->GetVChildFrames()[i];
		float prevY = tempFrame->GetY();

		tempFrame->MoveFrameChild(0, -moveY);
	}
}

