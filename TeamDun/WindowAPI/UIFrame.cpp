#include "stdafx.h"
#include "UIFrame.h"

/// <summary>
/// 초기화 
/// </summary>
/// <param name="name">UI의 이름</param>
/// <param name="x">UI의 위치 X (자식이라면 부모에 대한 상대좌표)</param>
/// <param name="y">UI의 위치 Y (자식이라면 부모에 대한 상대좌표)</param>
/// <param name="sizeX"UI의 크기 X></param>
/// <param name="sizeY">UI의 크기 Y</param>
/// <param name="imageName">이미지 이름</param>
/// <returns></returns>
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

	for (int i = 0; i < _vChildFrames.size(); i++) // 자식 프레임들도 모두 업데이트 시킨다.
	{
		_vChildFrames[i]->update();
	}

	CheckIsOutside();
}

/// <summary>
/// UI가 렌더될지 안될지를 Toggle형식으로 처리한다.
/// </summary>
void UIFrame::ToggleIsViewing()
{
	_isViewing = !_isViewing;

	for (int i = 0; i < _vChildFrames.size(); i++) // 자식 프레임들도 모두 Viewing 속성을 Toggle시킨다.
	{
		_vChildFrames[i]->ToggleIsViewing();
	}
}

/// <summary>
/// UI가 렌더될지 안될지를 Set한다.
/// </summary>
/// <param name="isViewing"></param>
/// <param name="withChild"></param>
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

/// <summary>
/// 이 UI에 자식을 추가한다
/// </summary>
/// <param name="frame">추가할 자식 UI</param>
void UIFrame::AddFrame(UIFrame* frame)
{
	frame->_isChild = true;			
	frame->_isViewing = _isViewing;	// isViewing을 통일시킨다 (부모가 안보이면 자식도 안보이게, 보이면 보이게)
	frame->_parent = this;

	// 상대좌표 (부모 X Y를 기준으로, 자식의 X Y가 결정된다 ex) 부모 좌표 : (100, 200), 자식 좌표 : (50, 50) -> 자식 좌표 최종 (150, 250) 
 	frame->SetX(_x + frame->GetX());	// 부모 X + 자식 X
	frame->SetY(_y + frame->GetY());	// 부모 Y + 자식 Y
	frame->SetIntersectRect();			

	AddChildMap(frame->GetName(), frame);	// ChildMap에 Key : 이름, Value : 자식이 될 프레임을 넣는다.
	_vChildFrames.push_back(frame);			// vector에도 넣어준다.
}
 
/// <summary>
/// UI를 자식과 함께 이동시킨다
/// </summary>
void UIFrame::MoveFrame()
{
	if (!_isChild && _isViewing && _isMoveToDrag) // 보이는 상태이며 드래그로 이동하는것이 가능하고 이것이 제일 상위일때
	{
		if (PtInRect(&_interactRect, _ptMouse) && INPUT->GetKey(VK_LBUTTON)) // 선택하고
		{
			_selectTimer++;

			if (_selectTimer == 10) // 시간이 10 지나면
			{
				_moveStartX = _ptMouse.x;
				_moveStartY = _ptMouse.y;
				_savedX = _x;
				_savedY = _y;
				_isSelected = true; // 이 UI를 움직이도록 설정합니다
			}
		}

		if (_isSelected) // 움직이도록 설정된 UI에 대해서
		{
			// (현재 마우스 위치 - 처음의 마우스 위치) = 얼마나 이동했는지
			// _saved = 처음 UI의 위치
			int newX = _savedX + (_ptMouse.x - _moveStartX); // 처음 UI의 위치 + 마우스 이동거리
			int newY = _savedY + (_ptMouse.y - _moveStartY);

			for (int i = 0; i < _vChildFrames.size(); i++) // 자식들 역시 이동시킨다
			{
				MoveFrameChild(newX - _x, newY - _y);
			}

			_x = newX;
			_y = newY;
			_interactRect = RectMake(_x, _y, _sizeX, _sizeY);
		}

		if (!INPUT->GetKey(VK_LBUTTON)) // 마우스를 떼면
		{
			_isSelected = false; // 선택을 해제
			_selectTimer = 0;
		}
	}
}

/// <summary>
/// 부모가 움직였을때 자식도 그에 상응하여 같은 거리만큼 이동하게 한다
/// </summary>
void UIFrame::MoveFrameChild(float x, float y)
{
	_x += x;
	_y += y;
	_interactRect = RectMake(_x, _y, _sizeX, _sizeY);

	for (int i = 0; i < _vChildFrames.size(); i++) // 자식의 자식도 마찬가지로 이동한다
	{
		_vChildFrames[i]->MoveFrameChild(x, y);
	}
}

/// <summary>
/// 자식이 부모의 밖으로 나갔는지 테스트
/// </summary>
void UIFrame::CheckIsOutside()
{
	if (_isChild) // 자식이라면
	{
		if (_x < _parent->GetX() || _y < _parent->GetY() ||
			_x + _sizeX > _parent->GetX() + _parent->GetSizeX() ||
			_y + _sizeY > _parent->GetY() + _parent->GetSizeY()) // 자식의 위치가 부모의 위치를 넘어섰을때
		{
			_isOutside = true; // 외부로 나갔다고 설정
		}

		else
		{
			_isOutside = false; // 내부에 존재한다 설정
		}
	}
}

void UIFrame::render(HDC hdc)
{
	if (_isViewing) // 보이는 상태이며
	{
		if (_isChild && _useOutsideLimit && _isOutside) {} // 자식이며, 범위제한을 사용했고 부모의 범위를 넘었다면 그리지 않음.

		else // 그게 아니라면
		{
			if (_image != nullptr) _image->render(hdc, _x, _y); // 그린다
			if (INPUT->GetKey('P')) Rectangle(hdc, _interactRect); // P를 누른 상태라면 충돌 범위도 그린다

			for (int i = 0; i < _vChildFrames.size(); i++) // 자식 역시 그린다
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
