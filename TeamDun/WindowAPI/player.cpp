#include "stdafx.h"
#include "Player.h"

HRESULT Player::init()
{
	this->_vImages.push_back(IMAGEMANAGER->findImage("baseCharIdle"));//0
	this->_vImages.push_back(IMAGEMANAGER->findImage("baseCharRun")); //1

	_x = 300;
	_y = WINSIZEY / 2;

	_body = RectMake(_x, _y, IMAGEMANAGER->findImage("baseCharIdle")->getFrameWidth(), IMAGEMANAGER->findImage("baseCharIdle")->getFrameHeight());

	_useImage = 0;
	_probeBottom = _y + IMAGEMANAGER->findImage("baseCharIdle")->getFrameHeight();
	_minDamage = 10;
	_maxDamage = 30;
	_power = 10;
	_frameX = 0;
	_frameY = 0;
	_gravity = 0.4f;
	_jumpPower = 7.0f;
	_jumpCount = 0;
	_downJumpTimer = 0;
	_dashTimer = 0;
	_dashSpeed = 0;
	_atkSpeed = 0.f;
	_realAttackSpeed = _atkSpeed * 60;
	_dustEffectCount = 0;
	_isDash = false;
	_leftBack = false;
	_rightBack = false;
	_pixelCenter = POINT{ (long)(_x + _vImages[_useImage]->getWidth() / 2), (long)(_y + _vImages[_useImage]->getHeight() / 2) };
	_bottomCol = false;
	_dashEffect = nullptr;
	_money = 10000;

	_aliceZone = IMAGEMANAGER->findImage("AliceZone");
	_aliceZoneRadius = 144;
	_aliceZoneIn = false;

	_accesoryCount = 4;

	// UI

	for (int i = 0; i < 17; i++) _vToolTips.push_back(CharToolTip());
	_vToolTipsName = vector<string>{ "powerImg", "defImg", "toughImg", "blockImg", "criImg", "criDmgImg", "evadeImg",
		"moveSpeedImg", "atkSpeedImg", "reloadImg", "dashImg", "trueDamageImg", "burnImg",
		"poisonImg", "coldImg", "elecImg", "stunImg" };

	// 예시용
	_selectedWeaponIdx = 0;

	_inven = new Inventory();
	_inven->init();

	_inven->AddItem(new DemonSword(*dynamic_cast<DemonSword*>(DATAMANAGER->GetItemById(4000))));
	_inven->AddItem(new DemonSword(*dynamic_cast<DemonSword*>(DATAMANAGER->GetItemById(4000))));
	_inven->AddItem(new DemonSword(*dynamic_cast<DemonSword*>(DATAMANAGER->GetItemById(4000))));
	_inven->AddItem(new Item(*DATAMANAGER->GetItemById(4001)));
	_inven->AddItem(new Item(*DATAMANAGER->GetItemById(4001)));
	_inven->AddItem(new Item(*DATAMANAGER->GetItemById(4001)));
	_inven->AddItem(new Item(*DATAMANAGER->GetItemById(4002)));
	_inven->AddItem(new Item(*DATAMANAGER->GetItemById(4002)));
	_inven->AddItem(new Item(*DATAMANAGER->GetItemById(4002)));
	_inven->AddItem(new Item(*DATAMANAGER->GetItemById(4003)));
	_inven->AddItem(new Item(*DATAMANAGER->GetItemById(4003)));
	_inven->AddItem(new Item(*DATAMANAGER->GetItemById(4003)));
	_inven->AddItem(new Item(*DATAMANAGER->GetItemById(4004)));
	_inven->AddItem(new Item(*DATAMANAGER->GetItemById(4004)));
	_inven->AddItem(new Item(*DATAMANAGER->GetItemById(4004)));

	return S_OK;

}

void Player::update()
{
	if (!UIMANAGER->GetGameFrame()->GetChild("InventoryFrame")->GetIsViewing() &&
		!UIMANAGER->GetGameFrame()->GetChild("DungeonShopBase")->GetIsViewing() &&
		!UIMANAGER->GetGameFrame()->GetChild("allMapFrame")->GetIsViewing()
		)
		// 잡다한 UI가 OFF일때
	{
		if (INPUT->GetIsRButtonClicked())		//마우스 오른쪽 버튼을 눌렀을때
		{
			_isDash = true;
			_dashPoint = _ptMouse;
			_jumpPower = 0;
		}

		if (INPUT->GetKeyDown('X'))				//X키를 눌렀을때
		{
			ENTITYMANAGER->makeBullet("BatBullet", "BatBulletHit", BT_NOCOL, _x, _y, getAngle(CAMERAMANAGER->GetRelativeX(_x), CAMERAMANAGER->GetRelativeY(_y), _ptMouse.x, _ptMouse.y), 10, 600, true);
		}   //플레이어의 x,y좌표를 받아와서 플레이어와 마우스 좌표 간의 각도를 구한후 그 거리만큼 총알이 날아가게끔

		if (CAMERAMANAGER->GetRelativeX(_x + IMAGEMANAGER->findImage("baseCharIdle")->getFrameWidth() / 2) >= _ptMouse.x)
		{	//플레이어의 중점+이미지 가로길이의 반이 마우스 x좌표보다 크거나 같을때
			_isLeft = true;		//왼쪽을 바라보게
		}

		else
		{
			_isLeft = false;	//오른쪽을 바라보게
		}

		this->pixelCollision();
		if (_isDash)			//대쉬 상태
		{
			this->dash();		//대쉬를 해야하므로 dash함수 실행
		}
		else
		{
			this->Move();		//대쉬 상태가 아니므로 Move함수 실행
		}



		_realAttackSpeed--;
		if (INPUT->GetKey(VK_LBUTTON))
		{
			if (_weapons[_selectedWeaponIdx] != nullptr && _realAttackSpeed < 0)
			{
				_realAttackSpeed = _atkSpeed * 60;
				_weapons[_selectedWeaponIdx]->Activate();
			}
		}
		Animation();
	}

	else // 잡다한 UI가 ON
	{
		_inven->update();
		this->pixelCollision();
	}

	SwitchWeapon();
	if (_weapons[_selectedWeaponIdx] != nullptr) _weapons[_selectedWeaponIdx]->update();
	if (_subWeapons[_selectedWeaponIdx] != nullptr) _subWeapons[_selectedWeaponIdx]->update();
	for (int i = 0; i < _vAccessories.size(); i++)
	{
		_vAccessories[i]->update();
	}

	CheckAliceZone();
	UpdateCharPage();
}

void Player::SwitchWeapon()
{
	if (_mouseWheel != 0)
	{
		if (_weapons[_selectedWeaponIdx] != nullptr)
		{
			_weapons[_selectedWeaponIdx]->SetisAttacking(false);
			_weapons[_selectedWeaponIdx]->SetRenderAngle(0);
		}
		if (_subWeapons[_selectedWeaponIdx] != nullptr)
		{
			_subWeapons[_selectedWeaponIdx]->SetisAttacking(false);
			_subWeapons[_selectedWeaponIdx]->SetRenderAngle(0);
		}
	
		_realAttackSpeed = 0;

		_selectedWeaponIdx = _selectedWeaponIdx == 0 ? 1 : 0;
		_inven->SwitchWeapon(_selectedWeaponIdx);
	}
}

void Player::CheckAliceZone()
{
	vector<Object*> objs = MAPMANAGER->GetPlayMap()->GetObjects();

	bool zoneInHere = false;
	for (int i = 0; i < objs.size(); i++)
	{
		if (objs[i]->GetType() == OBJECTTYPE::OT_MONSTER && dynamic_cast<Enemy*>(objs[i])->GetIsSpawned())
		{
			if (UTIL::interactRectArc(objs[i]->GetBody(), POINT{ (long)(_x + _vImages[_useImage]->getFrameWidth() / 2), (long)(_y + _vImages[_useImage]->getFrameHeight() / 2) }, _aliceZoneRadius, -PI / 4, PI / 4))
			{
				_aliceZoneIn = true;
				zoneInHere = true;
				break;
			}

			//if (UTIL::interactRectArc(objs[i]->GetBody(), POINT{ (long)(_x + _vImages[_useImage]->getFrameWidth() / 2), 
			//	(long)(_y + _vImages[_useImage]->getFrameHeight() / 2) }, _aliceZoneRadius, -PI / 4, PI / 4))
		}
	}

	if (!zoneInHere)
	{
		_aliceZoneIn = false;
	}
}

void Player::release()
{
	_inven->release();
}

void Player::render(HDC hdc)
{
	if (_weapons[_selectedWeaponIdx] != nullptr && _weapons[_selectedWeaponIdx]->GetIsRenderFirst()) _weapons[_selectedWeaponIdx]->render(hdc);
	if (_subWeapons[_selectedWeaponIdx] != nullptr && _subWeapons[_selectedWeaponIdx]->GetIsRenderFirst()) _subWeapons[_selectedWeaponIdx]->render(hdc);
	for (int i = 0; i < _vAccessories.size(); i++)
	{
		if (_vAccessories[i]->GetIsRenderFirst()) _vAccessories[i]->render(hdc);
	}

	switch (_state)
	{
	case PS_IDLE:
		CAMERAMANAGER->FrameRender(hdc, _vImages[_useImage], _x, _y, _frameX, _frameY);
		break;
	case PS_JUMP:
		CAMERAMANAGER->FrameRender(hdc, _vImages[_useImage], _x, _y, _frameX, _frameY);
		break;
	case PS_MOVE:
		CAMERAMANAGER->FrameRender(hdc, _vImages[_useImage], _x, _y, _frameX, _frameY);
		break;
	case PS_DIE:
		break;
	default:
		break;
	}

	if (_weapons[_selectedWeaponIdx] != nullptr && !_weapons[_selectedWeaponIdx]->GetIsRenderFirst()) _weapons[_selectedWeaponIdx]->render(hdc);
	if (_subWeapons[_selectedWeaponIdx] != nullptr && !_subWeapons[_selectedWeaponIdx]->GetIsRenderFirst()) _subWeapons[_selectedWeaponIdx]->render(hdc);
	for (int i = 0; i < _vAccessories.size(); i++)
	{
		if (!_vAccessories[i]->GetIsRenderFirst()) _vAccessories[i]->render(hdc);
	}

	_inven->render(hdc);

	CAMERAMANAGER->FrameRender(hdc, _aliceZone, _x + _vImages[_useImage]->getFrameWidth() / 2 - _aliceZone->getFrameWidth() / 2, _y + _vImages[_useImage]->getFrameHeight() / 2 - _aliceZone->getFrameHeight() / 2, _aliceZoneIn ? 1 : 0, 0);
}

void Player::Animation()
{
	switch (_state)
	{
	case PS_IDLE:
		_useImage = 0;
		break;
	case PS_JUMP:
		_useImage = 1;
		break;
	case PS_MOVE:
		_useImage = 1;
		if (_isJump == false && (_jumpPower == 0 || _jumpPower == -2))
		{
			_dustEffectCount++;
			if (_dustEffectCount % 20 == 0)
			{
				if (_isLeft)
				{
					EFFECTMANAGER->AddEffect(_x + 40, _y + 20, "RunEffect", 5, 0, 1, false, 255);
				}
				else
				{
					EFFECTMANAGER->AddEffect(_x - 40, _y + 20, "RunEffect", 5, 0, 0, false, 255);
				}

			}
		}
		break;
	case PS_DIE:
		break;
	default:
		break;
	}

	if (_isLeft)
	{
		_frameTimer++;
		_frameY = 1;
		if (!_leftBack)
		{
			if (_frameTimer > 5)
			{
				_frameTimer = 0;
				_frameX--;

				if (_frameX < 0)
				{
					_frameX = _vImages[_useImage]->getMaxFrameX();
				}
			}
		}
		else
		{
			if (_frameTimer > 5)
			{
				_frameTimer = 0;
				_frameX++;
				if (_frameX > _vImages[_useImage]->getMaxFrameX())
				{
					_frameX = 0;
				}
			}
		}
	}
	else
	{
		_frameTimer++;
		_frameY = 0;
		if (!_rightBack)
		{

			if (_frameTimer > 5)
			{
				_frameTimer = 0;
				_frameX++;
				if (_frameX > _vImages[_useImage]->getMaxFrameX())
				{
					_frameX = 0;
				}
			}
		}
		else
		{
			if (_frameTimer > 5)
			{
				_frameTimer = 0;
				_frameX--;

				if (_frameX < 0)
				{
					_frameX = _vImages[_useImage]->getMaxFrameX();
				}
			}
		}
	}
}

void Player::Move()
{
	_isJump = false;				//처음은 점프상태가 아니기때문에
	if (INPUT->GetKey('A'))			//A키를 눌렀을 때
	{
		_leftBack = false;			//던그리드는 마우스 좌표로 방향을 표시
		if (!_isLeft)
		{
			_rightBack = true;
		}

		_state = PS_MOVE;			//이미지 상태 이동상태로
		_x -= 5;
		_body = RectMake(_x, _y, IMAGEMANAGER->findImage("baseCharIdle")->getFrameWidth(), IMAGEMANAGER->findImage("baseCharIdle")->getFrameHeight());
	}
	if (INPUT->GetKeyUp('A'))		//A키를 눌렀다가 뗏을때
	{
		_state = PS_IDLE;			//이미지 상태 대기상태로
	}
	if (INPUT->GetKey('D'))
	{
		if (_isLeft)
		{
			_leftBack = true;
		}
		_rightBack = false;
		_state = PS_MOVE;
		_x += 5;
		_body = RectMake(_x, _y, IMAGEMANAGER->findImage("baseCharIdle")->getFrameWidth(), IMAGEMANAGER->findImage("baseCharIdle")->getFrameHeight());
	}
	if (INPUT->GetKeyUp('D'))
	{
		_state = PS_IDLE;
	}

	if (_jumpCount == 0 || _jumpCount == 1)	//점프를 안했거나 한번했을때
	{

		if (INPUT->GetKeyDown(VK_SPACE) && !_downJump)	//스페이스바를 누르고 아래로 점프한게 아닐때
		{
			_isJump = true;
			_jumpPower = 11;
			_y -= _jumpPower;
			_probeBottom = _y + IMAGEMANAGER->findImage("baseCharIdle")->getFrameHeight();
			_jumpCount++;
		}
		if (INPUT->GetKey('S') && _isJump)	//S키를 눌렀는데 점프상태일 때
		{
			_downJump = true;
			_jumpPower = -2;
			_jumpCount++;
		}
	}

	if (_downJump)							//다운 점프 상태일 때
	{
		_downJumpTimer++;
		if (_downJumpTimer > 20)
		{
			_downJumpTimer = 0;
			_downJump = false;
		}
	}
}

void Player::pixelCollision()
{
	//////////////////////////// 픽셀충돌 //////////////////////////////

	bool isCollide = false; // 충돌 했는지 여부
	bool _leftCollision1 = false;
	bool _leftCollision2 = false;
	bool _RightCollision1 = false;
	bool _RightCollision2 = false;
	_bottomCol = false;
	_probeBottom = _y + IMAGEMANAGER->findImage("baseCharIdle")->getFrameHeight();

	image* pixelMapIg = IMAGEMANAGER->findImage("PixelMapIg");
	image* baseCharIg = IMAGEMANAGER->findImage("baseCharIdle");



	for (int i = _probeBottom - 10; i < _probeBottom + 10; i++)
	{
		COLORREF color = GetPixel(pixelMapIg->getMemDC(), _x + baseCharIg->getFrameWidth() / 2, i);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if ((r == 255 && g == 0 && b == 0) && !_isJump) // 빨간색 픽셀충돌용 땅에 닿았다
		{
			isCollide = true; // 충돌했으면 얘를 ON
			_bottomCol = true; // 아래 충돌해있다
			_jumpPower = -2;	  // 떨어질때도 자연스럽게 떨어지게 하기위해 점프파워 초기화


			_y = i - baseCharIg->getFrameHeight();// 올라간다
			_jumpCount = 0;
			break;
		}

		if ((r == 0 && g == 0 && b == 255) && _jumpPower < 0 && _downJump == false && _isDash == false) // 파란색 픽셀충돌용 땅에 닿았고 떨어지는 상태라면
		{
			isCollide = true;		// 충돌했으면 얘를 ON
			_jumpPower = -2;		// 떨어질때도 자연스럽게 떨어지게 하기위해 점프파워 초기화

			_y = i - baseCharIg->getFrameHeight();// 올라간다
			_jumpCount = 0;
			break;
		}
	}
	if (_bottomCol == false)
	{

		for (int i = _y + 15; i > _y - 4; i--)
		{
			COLORREF color = GetPixel(pixelMapIg->getMemDC(), _x + baseCharIg->getFrameWidth() / 2, i);
			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);


			if ((r == 255 && g == 0 && b == 0)) // 빨간색 픽셀충돌용 땅에 닿았다
			{
				_jumpPower = -2;
				_y = i + 5;

				break;
			}
		}
	}
	if (!isCollide) //충돌해있지 않다면
	{
		_y -= _jumpPower;			//중력적용
		_jumpPower -= _gravity;

		if (_jumpPower < -20)		//점프파워가 -20보다 작을때
		{
			_jumpPower = -20;		//더이상 -되지않게 점프파워 값을 고정
		}
		_body = RectMake(_x, _y, baseCharIg->getFrameWidth(), baseCharIg->getFrameHeight());
	}

	for (int i = _x + baseCharIg->getFrameWidth() - 15; i < _x + baseCharIg->getFrameWidth() + 5; i++)
	{
		COLORREF color = GetPixel(pixelMapIg->getMemDC(), i, _probeBottom - 2);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if ((r == 255 && g == 0 && b == 0))
		{
			_RightCollision1 = true;

			if (_RightCollision1 && _RightCollision2)
			{
				_x = i - baseCharIg->getFrameWidth();

			}
			break;
		}

	}
	for (int i = _x + baseCharIg->getFrameWidth() - 15; i < _x + baseCharIg->getFrameWidth() + 5; i++)
	{
		COLORREF color = GetPixel(pixelMapIg->getMemDC(), i, _probeBottom - 40);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if ((r == 255 && g == 0 && b == 0))
		{
			_RightCollision2 = true;

			_x = i - baseCharIg->getFrameWidth();
			break;
		}

	}
	for (int i = _x + baseCharIg->getFrameWidth() - 15; i < _x + baseCharIg->getFrameWidth() + 5; i++)
	{
		COLORREF color = GetPixel(pixelMapIg->getMemDC(), i, _y + 2);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if ((r == 255 && g == 0 && b == 0))
		{

			_x = i - baseCharIg->getFrameWidth();


			break;
		}
	}

	//왼쪽아래
	for (int i = _x + 15; i > _x - 5; i--)
	{
		COLORREF color3 = GetPixel(pixelMapIg->getMemDC(), i, _probeBottom - 2);
		int r = GetRValue(color3);
		int g = GetGValue(color3);
		int b = GetBValue(color3);

		if ((r == 255 && g == 0 && b == 0))
		{
			_leftCollision1 = true;

			if (_leftCollision1 && _leftCollision2)
			{
				_x = i;

			}

			break;
		}
	}
	//왼쪽중간
	for (int i = _x + 15; i > _x - 5; i--)
	{
		COLORREF color3 = GetPixel(pixelMapIg->getMemDC(), i, _probeBottom - 40);
		int r = GetRValue(color3);
		int g = GetGValue(color3);
		int b = GetBValue(color3);

		if ((r == 255 && g == 0 && b == 0))
		{
			_leftCollision2 = true;
			_x = i;

			break;
		}
	}
	//왼쪽위
	for (int i = _x + 15; i > _x - 5; i--)
	{
		COLORREF color3 = GetPixel(pixelMapIg->getMemDC(), i, _y + 2);
		int r = GetRValue(color3);
		int g = GetGValue(color3);
		int b = GetBValue(color3);

		if ((r == 255 && g == 0 && b == 0))
		{
			_x = i;
			break;
		}
	}
	///////////////////////////////////////////////////////////////////////////

	// 포탈 검사
	_pixelCenter = POINT{ (long)(_x + 30), (long)(_y + 30) };

	COLORREF _color = GetPixel(pixelMapIg->getMemDC(), _pixelCenter.x, _pixelCenter.y);
	if (_color == RGB(0, 255, 0))
	{
		MAPMANAGER->ChangeMap(MAPMANAGER->GetCurrentStage(), MAPMANAGER->GetPlayMap()->GetNextMapIndex(DIRECTION::DIR_LEFT));
		MAPMANAGER->GetPlayMap()->ChangePlayerByDirection(DIRECTION::DIR_RIGHT);
	}

	else if (_color == RGB(0, 200, 0))
	{
		MAPMANAGER->ChangeMap(MAPMANAGER->GetCurrentStage(), MAPMANAGER->GetPlayMap()->GetNextMapIndex(DIRECTION::DIR_RIGHT));
		MAPMANAGER->GetPlayMap()->ChangePlayerByDirection(DIRECTION::DIR_LEFT);
	}

	else if (_color == RGB(0, 155, 0))
	{
		MAPMANAGER->ChangeMap(MAPMANAGER->GetCurrentStage(), MAPMANAGER->GetPlayMap()->GetNextMapIndex(DIRECTION::DIR_UP));
		MAPMANAGER->GetPlayMap()->ChangePlayerByDirection(DIRECTION::DIR_DOWN);
	}
	else if (_color == RGB(0, 100, 0))
	{
		MAPMANAGER->ChangeMap(MAPMANAGER->GetCurrentStage(), MAPMANAGER->GetPlayMap()->GetNextMapIndex(DIRECTION::DIR_DOWN));
		MAPMANAGER->GetPlayMap()->ChangePlayerByDirection(DIRECTION::DIR_UP);
	}
}

void Player::dash()
{
	_dashTimer++;

	_x += cosf(getAngle(CAMERAMANAGER->GetRelativeX(_x), CAMERAMANAGER->GetRelativeY(_y), _dashPoint.x, _dashPoint.y)) * 20;
	_y += -sinf(getAngle(CAMERAMANAGER->GetRelativeX(_x), CAMERAMANAGER->GetRelativeY(_y), _dashPoint.x, _dashPoint.y)) * 20;
	_body = RectMake(_x, _y, IMAGEMANAGER->findImage("baseCharIdle")->getFrameWidth(), IMAGEMANAGER->findImage("baseCharIdle")->getFrameHeight());
	_probeBottom = _y + IMAGEMANAGER->findImage("baseCharIdle")->getFrameHeight();


	image* pixelMapIg = IMAGEMANAGER->findImage("PixelMapIg");
	image* baseCharIg = IMAGEMANAGER->findImage("baseCharIdle");


	//대쉬할때만 속도가 바뀌므로 픽셀충돌 범위늘려서 따로검사
	for (int i = _probeBottom - 20; i < _probeBottom + 5; i++)
	{
		COLORREF color = GetPixel(pixelMapIg->getMemDC(), _x + baseCharIg->getFrameWidth() / 2, i);
		int r = GetRValue(color);
		int g = GetGValue(color);				//색깔 값 넣어주기
		int b = GetBValue(color);

		if ((r == 255 && g == 0 && b == 0) && !_isJump) // 빨간색 픽셀충돌용 땅에 닿았다
		{

			_y = i - baseCharIg->getFrameHeight();// 올라간다
			break;
		}
	}
	for (int i = _y + 20; i > _y - 5; i--)
	{
		COLORREF color = GetPixel(pixelMapIg->getMemDC(), _x + baseCharIg->getFrameWidth() / 2, i);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if ((r == 255 && g == 0 && b == 0))
		{
			_y = i;
			break;
		}
	}
	for (int i = _x + baseCharIg->getFrameWidth() - 20; i < _x + baseCharIg->getFrameWidth() + 5; i++)
	{
		COLORREF color = GetPixel(pixelMapIg->getMemDC(), i, _probeBottom - baseCharIg->getFrameHeight() / 2);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);
		if ((r == 255 && g == 0 && b == 0))
		{
			_x = i - baseCharIg->getFrameWidth();
			break;
		}
	}

	for (int i = _x + 20; i > _x - 5; i--)
	{
		COLORREF color3 = GetPixel(pixelMapIg->getMemDC(), i, _probeBottom - baseCharIg->getFrameHeight() / 2);
		int r = GetRValue(color3);
		int g = GetGValue(color3);
		int b = GetBValue(color3);

		if ((r == 255 && g == 0 && b == 0))
		{
			_x = i;
			break;
		}
	}
	if (_dashTimer == 1)
	{
		EFFECTMANAGER->AddEffect(_x, _y, "baseCharEffect", 3, 0, _frameY, false, 150);
	}
	if (_dashTimer == 3)
	{
		EFFECTMANAGER->AddEffect(_x, _y, "baseCharEffect", 3, 0, _frameY, false, 150);
	}
	if (_dashTimer == 5)
	{
		EFFECTMANAGER->AddEffect(_x, _y, "baseCharEffect", 3, 0, _frameY, false, 150);
	}
	if (_dashTimer == 6)
	{
		EFFECTMANAGER->AddEffect(_x, _y, "baseCharEffect", 3, 0, _frameY, false, 150);
	}
	if (_dashTimer == 7)
	{
		EFFECTMANAGER->AddEffect(_x, _y, "baseCharEffect", 3, 0, _frameY, false, 150);
	}
	
	if (_dashTimer >= 10)
	{
		_dashTimer = 0;		//대쉬 타이머 초기화
		_jumpPower = 0;		//점프 파워 초기화
		_isDash = false;	//대쉬상태가 아님
	}
}

/// <summary>
/// 캐릭터 페이지가 켜져있을때 계속해서 업데이트해준다.
/// </summary>
void Player::UpdateCharPage()
{
	UIFrame* charFrame = UIMANAGER->GetGameFrame()->GetChild("charFrame");
	if (charFrame->GetIsViewing())
	{
		dynamic_cast<UIText*>(charFrame->GetChild("powerText"))->SetText(to_string(_minDamage) + " ~ " + to_string(_maxDamage) + " (" + to_string(_power) + ") ");
		dynamic_cast<UIText*>(charFrame->GetChild("defText"))->SetText(to_string_with_precision(_defence, 0));
		dynamic_cast<UIText*>(charFrame->GetChild("toughText"))->SetText(to_string_with_precision(_toughness, 0));
		dynamic_cast<UIText*>(charFrame->GetChild("blockText"))->SetText(to_string_with_precision(_block, 0));
		dynamic_cast<UIText*>(charFrame->GetChild("criText"))->SetText(to_string_with_precision(_criticalPercent, 0));
		dynamic_cast<UIText*>(charFrame->GetChild("criDmgText"))->SetText(to_string_with_precision(_criticalDamage, 0));
		dynamic_cast<UIText*>(charFrame->GetChild("evadeText"))->SetText(to_string_with_precision(_evasion, 0));
		dynamic_cast<UIText*>(charFrame->GetChild("moveSpeedText"))->SetText(to_string_with_precision(_moveSpeed,2));
		dynamic_cast<UIText*>(charFrame->GetChild("atkSpeedText"))->SetText(to_string_with_precision(_atkSpeed, 2));
		dynamic_cast<UIText*>(charFrame->GetChild("reloadText"))->SetText(to_string_with_precision(_reloadTime,1));
		dynamic_cast<UIText*>(charFrame->GetChild("dashText"))->SetText(to_string_with_precision(_dashDamage, 0));
		dynamic_cast<UIText*>(charFrame->GetChild("trueDamageText"))->SetText(to_string_with_precision(_trueDamage, 0));
		dynamic_cast<UIText*>(charFrame->GetChild("burnText"))->SetText(to_string_with_precision(_fireDamage, 0));
		dynamic_cast<UIText*>(charFrame->GetChild("poisonText"))->SetText(to_string_with_precision(_posionDamage, 0));
		dynamic_cast<UIText*>(charFrame->GetChild("coldText"))->SetText(to_string_with_precision(_iceDamage, 0));
		dynamic_cast<UIText*>(charFrame->GetChild("elecText"))->SetText(to_string_with_precision(_elecDamage, 0));
		dynamic_cast<UIText*>(charFrame->GetChild("stunText"))->SetText(to_string_with_precision(_stunDamage, 0));
	
		CharPageToolTipOn();
	}
}

/// <summary>
/// 캐릭터 페이지의 툴팁을 온오프하고 내용물을 바꾼다.
/// </summary>
void Player::CharPageToolTipOn()
{
	UIFrame* charFrame = UIMANAGER->GetGameFrame()->GetChild("charFrame");
	charFrame->GetChild("toolTipFrame")->SetIsViewing(false);

	for (int i = 0; i < _vToolTipsName.size(); i++)
	{
		if (PtInRect(&charFrame->GetChild(_vToolTipsName[i])->GetRect(), _ptMouse))
		{
			ReInitTooltip(i);
			SetToolTipFrame(_ptMouse.x - charFrame->GetChild("toolTipFrame")->GetX(), _ptMouse.y - charFrame->GetChild("toolTipFrame")->GetY(), i);
			charFrame->GetChild("toolTipFrame")->SetIsViewing(true);
		}
	}
}

/// <summary>
/// 몇번째 스탯인가에 따라 툴팁 내용을 알맞게 수정한다.
/// </summary>
void Player::ReInitTooltip(int n)
{
	switch (n)
	{
	case 0:
		_vToolTips[0].init("powerImg", "무기공격력 (위력)", "\"위력\"은 무기 공격력을 기반으로 추가 피해량에 영향을 줍니다.", "현재 위력: " + to_string(_power) + "(데미지 보너스)", 3.0f, 1.7f);
		break;
	case 1:
		_vToolTips[1].init("defImg", "방어력", "받는 피해를 경감시켜줍니다.", "피해감소량: " + to_string_with_precision(_realDefence, 1) + "%", 3.0f, 1.7f);
		break;

	case 2:
		_vToolTips[2].init("toughImg", "강인함", "강인함 수치에 따라 고정값의 피해를 경감시켜줍니다.", "", 3.0f, 1.3f);
		break;

	case 3:
		_vToolTips[3].init("blockImg", "막기", "적의 공격을 막을 수 있는 확률을 증가시킵니다.", "막기 확률: " + to_string_with_precision(_block, 0) + "%", 3.0f, 1.7f);
		break;

	case 4:
		_vToolTips[4].init("criImg", "크리티컬", "적에게 치명적인 피해를 입힐 수 있는 기회가 늘어납니다.", "크리티컬 확률: " + to_string_with_precision(_realCriticalPercent, 1) + "%", 3.0f, 1.7f);
		break;

	case 5 :
		_vToolTips[5].init("criDmgImg", "크리티컬 데미지", "크리티컬 추가 피해량을 나타냅니다.", "", 3.0f, 1.3f);
		break;

	case 6:
		_vToolTips[6].init("evadeImg", "회피", "적의 공격을 회피할 수 있는 확률을 증가시킵니다.", "회피 확률: " + to_string_with_precision(_realEvasion, 1) + "%", 3.0f, 1.3f);
		break;

	case 7:
		_vToolTips[7].init("moveSpeedImg", "이동속도", "더 빠르게 움직이게 해줍니다.", "", 3.0f, 1.3f);
		break;

	case 8:
		_vToolTips[8].init("atkSpeedImg", "공격속도", "1초에 공격할 수 있는 횟수를 나타냅니다.", "", 3.0f, 1.3f);
		break;

	case 9:
		_vToolTips[9].init("reloadImg", "재장전속도", "재장전 시 걸리는 속도를 나타냅니다.", "", 3.0f, 1.3f);
		break;

	case 10:
		_vToolTips[10].init("dashImg", "대쉬 공격력", "대쉬 공격력은 무기 공격력의 %로 계산됩니다.", "", 3.0f, 1.3f);
		break;

	case 11:
		_vToolTips[11].init("trueDamageImg", "고정 데미지", "적의 방어력 등을 무시하고 고정된 피해를 입힙니다", "", 3.0f, 1.3f);
		break;

	case 12:
		_vToolTips[12].init("burnImg", "화상 피해 강화", "적을 불태워 짧은시간동안 데미지를 줍니다.", "", 3.0f, 1.3f);
		break;

	case 13:
		_vToolTips[13].init("poisonImg", "중독 피해 강화", "적을 중독시켜 긴 시간동안 데미지를 줍니다.", "", 3.0f, 1.3f);
		break;

	case 14:
		_vToolTips[14].init("coldImg", "추위 피해 강화", "적을 느리게 만듭니다.", "", 3.0f, 1.3f);
		break;

	case 15:
		_vToolTips[15].init("elecImg", "감전 피해 강화", "적의 방어력을 무효화 시킵니다.", "", 3.0f, 1.3f);
		break;

	case 16:
		_vToolTips[16].init("stunImg", "기절 피해 강화", "적을 일시적으로 행동불능으로 만듭니다.", "", 3.0f, 1.3f);
		break;

	}
}

/// <summary>
/// 툴팁의 내용물을 바꾸고, 위치를 알맞게 수정한다.
/// </summary>
void Player::SetToolTipFrame(float x, float y, int index)
{
	UIFrame* toolTipFrame = UIMANAGER->GetGameFrame()->GetChild("charFrame")->GetChild("toolTipFrame");
	toolTipFrame->MoveFrameChild(x, y);
	toolTipFrame->SetScaleX(_vToolTips[index].scaleX);
	toolTipFrame->SetScaleY(_vToolTips[index].scaleY);

	dynamic_cast<UIText*>(toolTipFrame->GetChild("title"))->SetText(_vToolTips[index].title);
	dynamic_cast<UIText*>(toolTipFrame->GetChild("discription"))->SetText(_vToolTips[index].description);
	dynamic_cast<UIText*>(toolTipFrame->GetChild("additional"))->SetText(_vToolTips[index].additionalDescription);
}