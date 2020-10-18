#include "stdafx.h"
#include "DropItem.h"

HRESULT DropItem::init()
{
	_id = 8000;
	_name = "µå¶ø ¾ÆÀÌÅÛ";
	_type = OBJECTTYPE::OT_ETC;

	_x = 0;
	_y = 0;
	_spawnTime = 0;

	_frameX = 0;
	_frameY = 0;
	_useImage = 0;
	_frameTimer = 0;
	_body = RECT{ 0,0,0,0 };
	_isDead = false;
	_renderOrder = 1;

	return S_OK;
}

void DropItem::update()
{
	Object::update();

	Move();
	PixelCollision();
	_body = RectMake(_x, _y, _vImages[_useImage]->getFrameWidth() * _item->GetRenderScale(), _vImages[_useImage]->getFrameHeight() * _item->GetRenderScale());
	CheckCollision();
}

void DropItem::release()
{
	DropObjs::release();
}

void DropItem::render(HDC hdc)
{
	if (_vImages[_useImage]->getMaxFrameX() == 0 && _vImages[_useImage]->getMaxFrameY() == 0) CAMERAMANAGER->StretchRender(hdc, _vImages[_useImage], _x, _y, _item->GetRenderScale(), _item->GetRenderScale());
	else CAMERAMANAGER->FrameStretchRender(hdc, _vImages[_useImage], _x, _y, _frameX, _vImages[_useImage]->getMaxFrameY() > 0 ? 1 : 0, _item->GetRenderScale(), _item->GetRenderScale());
}

void DropItem::SetItem(float x, float y, float speedX, float speedY, Item* item)
{
	_x = x;
	_y = y;
	_speedX = speedX;
	_speedY = speedY;
	_gravity = 0.5f;
	_item = item;
	_vImages = vector<image*>{ item->GetDropImage() };
	_vImageNames = vector<string>{ item->GetDropImageName() };
}

void DropItem::CheckCollision()
{
	RECT temp;

	if (IntersectRect(&temp, &ENTITYMANAGER->getPlayer()->GetBody(), &_body))
	{
		if (ENTITYMANAGER->getPlayer()->GetInventory()->AddItem(_item))
		{
			SOUNDMANAGER->play("¾ÆÀÌÅÛÈ¹µæ");
			UIFrame* getFrame = UIMANAGER->GetGameFrame()->GetChild("itemGetFrame");
			getFrame->GetVChildFrames().clear();

			UIFrame* itemImage = new UIFrame();
			itemImage->init("image", 100 - (_vImages[_useImage]->getFrameWidth() * _item->GetRenderScale() / 2), 80 - (_vImages[_useImage]->getFrameHeight() * _item->GetRenderScale() / 2), 10, 10, _item->GetDropImageName(), _item->GetRenderScale(), _item->GetRenderScale());
			getFrame->AddFrame(itemImage);

			int nameR = 255, nameG = 255, nameB = 255;
			switch (_item->GetItemClass())
			{
			case ITEMCLASS::IC_NORMAL: nameR = 255, nameG = 255, nameB = 255; break;
			case ITEMCLASS::IC_ADVANCED: nameR = 112, nameG = 146, nameB = 190; break;
			case ITEMCLASS::IC_RARE: nameR = 232, nameG = 239, nameB = 90; break;
			case ITEMCLASS::IC_LEGENDARY: nameR = 237, nameG = 9, nameB = 138; break;
			}

			UIText* itemGet = new UIText();
			itemGet->init("getText", 150, 20, 300, 50, "¾ÆÀÌÅÛ È¹µæ", FONT::PIX, WORDSIZE::WS_MIDDLE, WORDSORT::WSORT_MIDDLE);
			getFrame->AddFrame(itemGet);

			UIText* name = new UIText();
			name->init("name", 150, 70, 300, 50, _item->GetName(), FONT::PIX, WORDSIZE::WS_MIDDLESMALL, WORDSORT::WSORT_MIDDLE, RGB(nameR, nameG, nameB));
			getFrame->AddFrame(name);

			getFrame->SetViewingTimer(100);

			_isDead = true;
		}
	}
}


void DropItem::PixelCollision()
{
	bool isCollide = false;
	bool _leftCollision1 = false;
	bool _leftCollision2 = false;
	bool _RightCollision1 = false;
	bool _RightCollision2 = false;

	image* pixelMapIg = IMAGEMANAGER->findImage("PixelMapIg");
	image* itemImg = _vImages[_useImage];

	float _probeBottom = _y + itemImg->getFrameHeight() * _item->GetRenderScale();

	// ¾Æ·¡
	for (int i = _probeBottom - 15; i < _probeBottom + 5; i++)
	{
		COLORREF color = GetFastPixel(MAPMANAGER->GetPixelGetter(), _x + itemImg->getFrameWidth() / 2, i);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (r == 255 && g == 0 && b == 0 || (r == 0 && g == 0 && b == 255))
		{
			isCollide = true;
			_y = i - _vImages[_useImage]->getFrameHeight() * _item->GetRenderScale();
			_speedY = 0;
			_speedX = _speedX / 10 * 9;
			break;
		}
	}

	// ¿À¸¥ÂÊ
	for (int i = _x + itemImg->getFrameWidth() - 5; i < _x + itemImg->getFrameWidth(); i++)
	{
		COLORREF color = GetFastPixel(MAPMANAGER->GetPixelGetter(), i, itemImg->getFrameHeight() / 2 + _y);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if ((r == 255 && g == 0 && b == 0))
		{
			_x = i - itemImg->getFrameWidth() * _item->GetRenderScale();
			break;
		}
	}

	// ¿ÞÂÊ
	for (int i = _x + 5; i > _x; i--)
	{
		COLORREF color3 = GetFastPixel(MAPMANAGER->GetPixelGetter(), i, itemImg->getFrameHeight() / 2 + _y);
		int r = GetRValue(color3);
		int g = GetGValue(color3);
		int b = GetBValue(color3);

		if ((r == 255 && g == 0 && b == 0))
		{
			_x = i + 5;
			break;
		}
	}
}