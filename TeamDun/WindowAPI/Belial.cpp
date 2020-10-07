#include "stdafx.h"
#include "Belial.h"

HRESULT Belial::init(int id, string name, OBJECTTYPE type, vector<string> imgNames)
{
	Enemy::init(id, name, type, imgNames);
	_angle = 0;
	_state = ES_IDLE;
	_PatternTime = 0;
	_bulletFireTimer = 0;
	_fireAngle = 0;
	_bossBack = IMAGEMANAGER->findImage("SkellBossBack");


	_firstSwordX = 20;
	_firstSwordY = 200;
	_makeSwordTimer = 0;
	_swordCount = 0;
	_swordEndCount = 0;
	_makeSword = false;
	_shootSword = false;
	_shootSwordTimer = 0;


	_leftHandle.ig = IMAGEMANAGER->findImage("SkellBossLeftHandIdle");
	_leftHandle.frameX = 0;
	_leftHandle.frameY = 0;
	_leftHandle.Timer = 0;
	_leftHandle.state = ES_IDLE;

	_RightHandle.ig = IMAGEMANAGER->findImage("SkellBossRightHandIdle");
	_RightHandle.frameX = 0;
	_RightHandle.frameY = 0;
	_RightHandle.Timer = 0;
	_RightHandle.state = ES_IDLE;
	return S_OK;
}

void Belial::SetAfterSpawn()
{
	_leftHandle.x = _x - 288;
	_leftHandle.y = _y + 200;

	_RightHandle.x = _x + 370;
	_RightHandle.y = _y;

	_leftHandle.CenterX = _leftHandle.x + _leftHandle.ig->getFrameWidth() / 2;
	_leftHandle.CenterY = _leftHandle.y + _leftHandle.ig->getFrameHeight() / 2;
	_RightHandle.CenterX = _RightHandle.x + _leftHandle.ig->getFrameWidth() / 2;
	_RightHandle.CenterY = _RightHandle.y + _leftHandle.ig->getFrameHeight() / 2;
}

void Belial::update()
{
	Enemy::update();
	if (INPUT->GetKeyDown('B'))
	{
		_state = ES_ATTACK;
		_BelialPattern = BULLET;
		_frameX = 0;
	}
	if (INPUT->GetKeyDown('C'))
	{
		_state = ES_ATTACK;
		_BelialPattern = KNIFE;
		_frameX = 0;
		_makeSword = true;
	}
	if (_isSpawned)
	{
		Animation();
		switch (_state)
		{
		case ES_IDLE:

			Move();

			break;
		case ES_ATTACK:

			Attack();
			switch (_BelialPattern)
			{

			case RAZER:
				break;
			case KNIFE:
				break;
			case BULLET:
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
	}
}

void Belial::release()
{
}

void Belial::render(HDC hdc)
{
	if (_isSpawned)
	{
		if (_BelialPattern == BULLET && _state == ES_ATTACK)
		{
		CAMERAMANAGER->FrameRender(hdc, _bossBack, _x+53, _y+ 215, _frameX, 0);
		}
		else
		{
		CAMERAMANAGER->FrameRender(hdc, _bossBack, _x+53, _y+ 135, _frameX, 0);
		}
		for (int i = 0; i < _vBossSword.size(); i++)
		{
			CAMERAMANAGER->FrameRender(hdc, _vBossSword[i]->ig, _vBossSword[i]->x, _vBossSword[i]->y, _vBossSword[i]->frameX, 0);
		}
		
		Enemy::render(hdc);
		CAMERAMANAGER->FrameRender(hdc, _leftHandle.ig, _leftHandle.x, _leftHandle.y, _leftHandle.frameX, _leftHandle.frameY);
		CAMERAMANAGER->FrameRender(hdc, _RightHandle.ig, _RightHandle.x, _RightHandle.y, _RightHandle.frameX, _RightHandle.frameY);

	}
}



void Belial::Move()
{
	_angle += 0.1f;
	_y += cosf(_angle) * 1;
}

void Belial::Attack()
{
	

	switch (_BelialPattern)
	{
	case RAZER:
		break;
	case KNIFE:
		
		if (_makeSword)
		{
			SetSwordAngle();
			SwordAniMation();
			_makeSwordTimer++;
			if (_makeSwordTimer > 20)
			{
				_makeSwordTimer = 0;
				_firstSwordX += 100;
				

				_swordCount++;
				SetSword();

				if (_swordCount == 6)
				{
					_makeSword = false;
					_shootSword = true;

					_firstSwordX = 100;
					_firstSwordY = 200;
					_swordCount = 0;
				}
			}
		}
		if (_shootSword)
		{
			_shootSwordTimer++;
			for (int i = 0; i < _vBossSword.size(); i++)
			{
				if (_vBossSword[i]->speed == 0 &&_vBossSword[i]->isCol == false)
				{
					_vBossSword[i]->angle = getAngle(_vBossSword[i]->x + _vBossSword[i]->ig->getFrameWidth() / 2, _vBossSword[i]->y + _vBossSword[i]->ig->getFrameHeight() / 2, ENTITYMANAGER->getPlayer()->GetX(), ENTITYMANAGER->getPlayer()->GetY());
					if (_vBossSword[i]->angle < 0)
					{
						_vBossSword[i]->angle += PI2;
					}
					if (_vBossSword[i]->angle >= PI2)
					{
						_vBossSword[i]->angle -= PI2;
					}
					SwordAniMation();
				}
				_vBossSword[i]->x += cosf(_vBossSword[i]->angle)*_vBossSword[i]->speed;
				_vBossSword[i]->y += -sinf(_vBossSword[i]->angle)*_vBossSword[i]->speed;

			}

			if (_shootSwordTimer > 20)
			{
				_shootSwordTimer = 0;
				for (int i = 0; i < _vBossSword.size(); i++)
				{
					
					if (_vBossSword[i]->speed == 0 && _vBossSword[i]->isCol == false)
					{
						_vBossSword[i]->ig = IMAGEMANAGER->findImage("SkellBossSwordFire");
						_vBossSword[i]->speed = 25;
						break;
					}
				}
			}

			SwordPixelCollision();
			EraseSword();
			if (_swordEndCount == 6)
			{
				_swordEndCount = 0;
				_state = ES_IDLE;
				_shootSword = false;
			}
		}
		break;
	case BULLET:
		_bulletFireTimer++;
		_bulletEndTimer++;
		if (_bulletFireTimer > 12)
		{
			_fireAngle += PI / 24;
			for (int i = 0; i < 4; i++)
				ENTITYMANAGER->makeBullet("BatBullet", BT_NOMAL, _x + 110, _y + 270, _fireAngle + i * PI / 2, 4, 1000, true);
			_bulletFireTimer = 0;
		}
		if (_bulletEndTimer > 300)
		{
			_bulletEndTimer = 0;
			_state = ES_IDLE;
		}
		break;
	default:
		break;
	}
}

void Belial::Animation()
{
	switch (_state)
	{
	case ES_IDLE:
		_useImage = 0;

		_count++;

		_frameY = 0;
		if (_count > 3)
		{
			_count = 0;
			_frameX++;
			if (_frameX > _vImages[_useImage]->getMaxFrameX())
			{
				_frameX = 0;

			}
		}
		break;
	case ES_MOVE:
		break;
	case ES_ATTACK:
		switch (_BelialPattern)
		{
		case RAZER:
			break;
		case KNIFE:
			_useImage = 0;

			_count++;

			_frameY = 0;
			if (_count > 3)
			{
				_count = 0;
				_frameX++;
				if (_frameX > _vImages[_useImage]->getMaxFrameX())
				{
					_frameX = _vImages[_useImage]->getMaxFrameX() - 4;
				}
			}
			break;
		case BULLET:
			_useImage = 1;

			_count++;

			_frameY = 0;
			if (_count > 3)
			{
				_count = 0;
				_frameX++;
				if (_frameX > _vImages[_useImage]->getMaxFrameX())
				{
					_frameX = _vImages[_useImage]->getMaxFrameX() -4;
				}
			}
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}

	switch (_leftHandle.state)
	{
	case ES_IDLE:
		_leftHandle.Timer++;
		if (_leftHandle.Timer > 5)
		{
			_leftHandle.Timer = 0;
			_leftHandle.frameX++;
			if (_leftHandle.frameX > _leftHandle.ig->getMaxFrameX())
			{
				_leftHandle.frameX = 0;
			}
		}
		break;
	case ES_ATTACK:

		break;
	default:
		break;
	}



	switch (_RightHandle.state)
	{
	case ES_IDLE:
		_RightHandle.Timer++;
		if (_RightHandle.Timer > 5)
		{
			_RightHandle.Timer = 0;
			_RightHandle.frameX++;
			if (_RightHandle.frameX > _RightHandle.ig->getMaxFrameX())
			{
				_RightHandle.frameX = 0;
			}
		}
		break;

	case ES_ATTACK:

		break;
	default:
		break;
	}
}

void Belial::SetPattern()
{
	int rndPatten = RANDOM->range(0, 2);
	_BelialPattern = (BELIALPATTERN)rndPatten;

}

void Belial::SetSword()
{
	BossSword* _sword = new BossSword;
	_sword->ig = IMAGEMANAGER->findImage("SkellBossSword");
	_sword->x = _firstSwordX;
	_sword->y = _firstSwordY;
	_sword->body = RectMake(_sword->x, _sword->y, _sword->ig->getFrameWidth(), _sword->ig->getFrameHeight());
	_sword->isDead = false;
	_sword->isCol = false;
	_sword->speed = 0;	
	_sword->Timer = 0;

	_vBossSword.push_back(_sword);
}

void Belial::SwordAniMation()
{

	for (int i = 0; i < _vBossSword.size(); i++)
	{
		float a = _vBossSword[i]->angle - PI / 48;
		if (a < 0)
		{
			a += PI2;
		}
		if (a >= PI2)
		{
			a -= PI2;
		}

		_vBossSword[i]->frameX  = a / (PI / 24) ;

		
	}
}

void Belial::SetSwordAngle()
{
	for (int i = 0; i < _vBossSword.size(); i++)
	{
		_vBossSword[i]->angle = getAngle(_vBossSword[i]->x + _vBossSword[i]->ig->getFrameWidth() / 2, _vBossSword[i]->y + _vBossSword[i]->ig->getFrameHeight() / 2, ENTITYMANAGER->getPlayer()->GetX(), ENTITYMANAGER->getPlayer()->GetY());
		if (_vBossSword[i]->angle < 0)
		{
			_vBossSword[i]->angle += PI2;
		}
		if (_vBossSword[i]->angle >= PI2)
		{
			_vBossSword[i]->angle -= PI2;
		}
	}
}

void Belial::SwordPixelCollision()
{
	
	
	image* pixelMapIg = IMAGEMANAGER->findImage("PixelMapIg");
	image* _image = IMAGEMANAGER->findImage("SkellBossSword");
	for (int i = 0; i < _vBossSword.size(); i++)
	{
		COLORREF color1 = GetPixel(pixelMapIg->getMemDC(), _vBossSword[i]->x + _image->getFrameWidth()/2+cosf(_vBossSword[i]->angle)*60 , _vBossSword[i]->y + _image->getFrameHeight() / 2-sinf(_vBossSword[i]->angle) * 60);
		int r1 = GetRValue(color1);
		int g1 = GetGValue(color1);
		int b1 = GetBValue(color1);

		if (r1 == 255 && g1 == 0 && b1 == 0)
		{
			if (_vBossSword[i]->speed != 0)
			{
				_vBossSword[i]->speed = 0;
				_vBossSword[i]->ig = IMAGEMANAGER->findImage("SkellBossSword");
				_vBossSword[i]->isCol = true;

				if (_vBossSword[i]->angle > PI / 4 && _vBossSword[i]->angle <= PI - PI / 4)
				{
					EFFECTMANAGER->AddEffect(_vBossSword[i]->x , _vBossSword[i]->y + _image->getFrameHeight() / 2, "BossSwordHitUp", 3);
				}
				else if (_vBossSword[i]->angle > PI - PI / 4 && _vBossSword[i]->angle <= PI + PI / 4)
				{

					EFFECTMANAGER->AddEffect(_vBossSword[i]->x + _image->getFrameWidth() / 2, _vBossSword[i]->y + _image->getFrameHeight() / 2, "BossSwordHitLeft", 3);
				}
				else if (_vBossSword[i]->angle > PI + PI / 4 && _vBossSword[i]->angle <= PI2 - PI / 4)
				{

					EFFECTMANAGER->AddEffect(_vBossSword[i]->x+ 30, _vBossSword[i]->y + _image->getFrameHeight() / 2, "BossSwordHitDown", 3);
				}
				else
				{
					EFFECTMANAGER->AddEffect(_vBossSword[i]->x + _image->getFrameWidth() / 2, _vBossSword[i]->y + _image->getFrameHeight() / 2, "BossSwordHitRight", 3);

				}
				
			}
		}
	}

}

void Belial::EraseSword()
{
	for (int i = 0; i < _vBossSword.size(); i++)
	{
		if (_vBossSword[i]->isCol == true)
		{
			_vBossSword[i]->Timer++;

			if (_vBossSword[i]->Timer == 150)
			{
				_vBossSword.erase(_vBossSword.begin() + i);

				_swordEndCount++;
			}
		}
	}
}

