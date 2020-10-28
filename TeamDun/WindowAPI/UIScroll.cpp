#include "stdafx.h"
#include "UIScroll.h"

/// <summary>
/// 초기화
/// </summary>
HRESULT UIScroll::init(string name, float x, float y, float sizeX, float sizeY, string imageName)
{
	UIFrame::init(name, x, y, sizeX, sizeY, imageName);

	_target = nullptr;
	_scrollPercent = 0.f;
	_isVertical = true;

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

/// <summary>
/// 스크롤바를 이동시킨다
/// </summary>
void UIScroll::MoveScrollBar()
{
	if (_isVertical) // 세로 케이스
	{
		if (PtInRect(&_parent->GetRect(), _ptMouse)) // 부모 UI와 마우스가 겹친 상태에서
		{
			float prevY = _y;
			if (_mouseWheel == 1) // 마우스 휠을 올리면
			{
				_y = _y - (_parent->GetSizeY() * 0.03f); // 스크롤을 전체 사이즈의 0.03만큼 올린다
				if (_y < _parent->GetY())
				{
					_y = _parent->GetY();
				} // 범위 제약

				SetIntersectRect();
				CalculateScrollBarPercent();
			}

			else if (_mouseWheel == -1) // 마우스 휠을 내리면
			{
				_y = _y + (_parent->GetSizeY() * 0.03f); // 스크롤을 전체 사이즈의 0.03만큼 내린다
				if (_y + _image->getHeight() > _parent->GetSizeY() + _parent->GetY())
				{
					_y = _parent->GetSizeY() + _parent->GetY() - _image->getHeight();
				} // 범위 제약

				SetIntersectRect();
				CalculateScrollBarPercent();
			}

			if (prevY != _y) // 만약 스크롤이 움직였다면
			{
				for (int i = 0; i < _vChildFrames.size(); i++)
				{
					MoveFrameChild(0, _y - prevY); // 자식들도 움직인다
				}
			}
		}
	}
	
	else // 가로 케이스
	{
		if (PtInRect(&_parent->GetRect(), _ptMouse)) // 부모 UI와 마우스가 겹친 상태에서
		{
			float prevX = _x;
			if (_mouseWheel == 1) // 마우스 휠을 올리면
			{
				_x = _x - (_parent->GetSizeX() * 0.03f); // 스크롤을 전체 사이즈의 0.03만큼 올린다

				if (_x < _parent->GetX())
				{
					_x = _parent->GetX();
				} // 범위 제약

				SetIntersectRect();
				CalculateScrollBarPercent();
			}

			else if (_mouseWheel == -1) // 마우스 휠을 내리면
			{
				_x = _x + (_parent->GetSizeX() * 0.03f); // 스크롤을 전체 사이즈의 0.03만큼 내린다
				if (_x + _image->getWidth() > _parent->GetSizeX() + _parent->GetX())
				{
					_x = _parent->GetSizeX() + _parent->GetX() - _image->getWidth();
				} // 범위 제약
				SetIntersectRect();
				CalculateScrollBarPercent();
			}

			if (prevX != _x) // 만약 스크롤이 움직였다면
			{
				for (int i = 0; i < _vChildFrames.size(); i++)
				{
					MoveFrameChild(_x - prevX, 0); // 자식들도 움직인다
				}
			}
		}
	}
}

/// <summary>
/// 현재 스크롤의 위치에 따라 타겟의 자식들 역시 움직인다
/// </summary>
void UIScroll::CalculateScrollBarPercent()
{
	if (_isVertical)  // 세로 케이스
	{
		float _prevScrollPercent = _scrollPercent;
		_scrollPercent = (_y - _parent->GetY()) / (_parent->GetSizeY() - _image->getHeight()); // 비율 계산

		float maxY = INT_MIN;
		float minY = INT_MAX;
		for (int i = 0; i < _target->GetVChildFrames().size(); i++)
		{

			if (_target->GetVChildFrames()[i] == this) continue; // 예외처리

			UIFrame* tempFrame = _target->GetVChildFrames()[i];
			if (tempFrame->GetY() > maxY) maxY = tempFrame->GetY(); // 가장 아래 위치의 UI
			if (tempFrame->GetY() < minY) minY = tempFrame->GetY(); // 가장 위 위치의 UI
		}

		// maxY - minY = 자식 UI의 총 거리
		float moveY = _scrollPercent * (maxY - minY) - _prevScrollPercent * (maxY - minY); // 이전의 스크롤 위치와 현재 스크롤 위치를 계산해서 얼마만큼 target의 자식들을 이동시켜야 하는지 결정한다.

		for (int i = 0; i < _target->GetVChildFrames().size() - 1; i++) // 여기 -1은 왜 있는지 기억안남 (문제 없으면 지울 예정)
		{
			if (_target->GetVChildFrames()[i] == this) continue; // 예외처리
			_target->GetVChildFrames()[i]->MoveFrameChild(0, -moveY); // 이동거리만큼 반대방향으로 자식들을 움직임 (스크롤 내림 -> 자식 올라감)
		}
	}
	
	else // 가로 케이스
	{
		float _prevScrollPercent = _scrollPercent;
		_scrollPercent = (_x - _parent->GetX()) / (_parent->GetSizeX() - _image->getWidth());

		float maxX = INT_MIN;
		float minX = INT_MAX;
		for (int i = 0; i < _target->GetVChildFrames().size(); i++)
		{
			if (_target->GetVChildFrames()[i] == this) continue;

			UIFrame* tempFrame = _target->GetVChildFrames()[i];
			if (tempFrame->GetX() > maxX) maxX = tempFrame->GetX();
			if (tempFrame->GetX() < minX) minX = tempFrame->GetX();
		}

		float moveX = _scrollPercent * (maxX - minX) - _prevScrollPercent * (maxX - minX);

		for (int i = 0; i < _target->GetVChildFrames().size() - 1; i++)
		{
			if (_target->GetVChildFrames()[i] == this) continue; 
			_target->GetVChildFrames()[i]->MoveFrameChild(-moveX, 0);
		}
	}
}

