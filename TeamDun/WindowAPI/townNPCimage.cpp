#include "stdafx.h"
#include "townNPCimage.h"

//상호작용이 필요하지 않은 이미지같은 NPC 전용 클래스 입니다 (타운)

HRESULT townNPCimage::init(int id, string name, OBJECTTYPE type, vector<string> imgNames)
{
	Object::init(id, name, type, imgNames);
	_state = TNS_IDLE;
	_count, _index = 0;
	_isLeft = false;
	return S_OK;
}

void townNPCimage::update()
{
	Object::update();

	switch (_state)
	{
	case TNS_IDLE:
		break;
	case TNS_RUN:
		break;
	default:
		break;
	}
}

void townNPCimage::release()
{
	Object::release();
}

void townNPCimage::render(HDC hdc)
{
	Object::render(hdc);
}

void townNPCimage::Animation()
{
	Object::Animation();

	switch (_state)
	{
	case TNS_IDLE:
		_useImage = 0;
		if (!_isLeft)
		{
			_frameY = 1;
			if (_count > 5)
			{
				_count = 0;
				_frameX--;

				if (_frameX < 0)
				{
					_frameX = _vImages[_useImage]->getMaxFrameX();
				}
			}
		}
		else
		{
			_frameY = 0;
			if (_count > 5)
			{
				_count = 0;
				_frameX++;

				if (_frameX > _vImages[_useImage]->getMaxFrameX())
				{
					_frameX = 0;
				}
			}
		}
		break;
	case TNS_RUN:
		_useImage = 1;
		if (!_isLeft)
		{
			_frameY = 1;
			if (_count > 5)
			{
				_count = 0;
				_frameX--;

				if (_frameX < 0)
				{
					_frameX = _vImages[_useImage]->getMaxFrameX();
				}
			}
		}
		else
		{
			_frameY = 0;
			if (_count > 5)
			{
				_count = 0;
				_frameX++;

				if (_frameX > _vImages[_useImage]->getMaxFrameX())
				{
					_frameX = 0;
				}
			}
		}
		break;
	default:
		break;
	}
}
