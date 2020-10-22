#include "stdafx.h"
#include "StrawberryFountain.h"

HRESULT StrawberryFountain::init(int id, string name, OBJECTTYPE type, vector<string> imgNames)
{
	NPC::init(id, name, type, imgNames);

	_npcName = "딸기 분수";
	_vConvTexts = vector<string>
	{
		"맛있어보이는 딸기 분수다. 건강해질것 같다.",
		"이미 말라버렸다."
	};
	_vSelectTexts = vector<string>
	{
		"먹는다.",
		"먹지 않는다."
	};

	_isTalked = false;
	_useConv = true;
	_useSelect = true;
	_isActivated = false;

	return S_OK;
}

void StrawberryFountain::update()
{
	NPC::update();
	if (_selectFrame->GetIsViewing() && _isUsing)
	{
		Conversation();
	}
}

void StrawberryFountain::SetConvUI()
{
	dynamic_cast<UIText*>(_convFrame->GetChild("name"))->SetText(_npcName);
	dynamic_cast<UIText*>(_convFrame->GetChild("text"))->SetText(_vConvTexts[0]);
	dynamic_cast<UIText*>(_convFrame->GetChild("text"))->SetCntPos(0);

	if (!_isTalked)
	{
		dynamic_cast<UIText*>(_selectFrame->GetChild("selected1")->GetChild("text"))->SetText(_vSelectTexts[0]);
		dynamic_cast<UIText*>(_selectFrame->GetChild("selected2")->GetChild("text"))->SetText(_vSelectTexts[1]);
		_selectFrame->GetChild("selected1")->SetImage(nullptr);
		_selectFrame->GetChild("selected2")->SetImage(nullptr);
	}
	else
	{
		dynamic_cast<UIText*>(_convFrame->GetChild("text"))->SetText(_vConvTexts[1]);
		_selectFrame->SetIsViewing(false);
	}
}

void StrawberryFountain::Conversation()
{
	if (PtInRect(&_selectFrame->GetChild("selected1")->GetRect(), _ptMouse))
	{
		_selectFrame->GetChild("selected1")->SetImage(IMAGEMANAGER->findImage("SelectedFrame"));
		if (INPUT->GetIsLButtonClicked())
		{
			_selectFrame->SetIsViewing(false);
			_convFrame->SetIsViewing(false);
			this->Activate();
			_isTalked = true;
			_useSelect = false;
		}
	}
	else _selectFrame->GetChild("selected1")->SetImage(nullptr);

	if (PtInRect(&_selectFrame->GetChild("selected2")->GetRect(), _ptMouse))
	{
		_selectFrame->GetChild("selected2")->SetImage(IMAGEMANAGER->findImage("SelectedFrame"));
		if (INPUT->GetIsLButtonClicked())
		{
			_selectFrame->SetIsViewing(false);
			_convFrame->SetIsViewing(false);
			_isUsing = false;
		}
	}
	else _selectFrame->GetChild("selected2")->SetImage(nullptr);
}

void StrawberryFountain::initSecond()
{
	_interactionImage = IMAGEMANAGER->findImage("Keyboard_F");
	_convFrame = UIMANAGER->GetGameFrame()->GetChild("convFrame");
	_selectFrame = UIMANAGER->GetGameFrame()->GetChild("selectFrame");
}

void StrawberryFountain::release()
{
	NPC::release();
}

void StrawberryFountain::render(HDC hdc)
{
	NPC::render(hdc);
}

void StrawberryFountain::Activate()
{
	if (!_isActivated)
	{
		dynamic_cast<UIText*>(UIMANAGER->GetGameFrame()->GetChild("descriptionText"))->SetText("건강해졌지만, 배불러진 느낌이 듭니다.");
		dynamic_cast<UIText*>(UIMANAGER->GetGameFrame()->GetChild("descriptionText"))->SetColor(RGB(208, 162, 0));
		dynamic_cast<UIText*>(UIMANAGER->GetGameFrame()->GetChild("descriptionText"))->SetViewingTimer(180);

		_isActivating = !_isActivating;
		SOUNDMANAGER->play("NPC_레스토랑_호록");

		int satiety = ENTITYMANAGER->getPlayer()->GetSatiety() + 20;
		if (satiety > ENTITYMANAGER->getPlayer()->GetMaxSatiety())
			satiety = ENTITYMANAGER->getPlayer()->GetMaxSatiety();
		ENTITYMANAGER->getPlayer()->SetSatiety(satiety);

		int hp = ENTITYMANAGER->getPlayer()->GetHP() + 35;
		if (hp > ENTITYMANAGER->getPlayer()->GetMaxHp())
			hp = ENTITYMANAGER->getPlayer()->GetMaxHp();
		ENTITYMANAGER->getPlayer()->SetHp(hp);

		_useImage = 1;
		_isUsing = true;
		_isActivated = true;
	}

	else
	{
		_isActivating = !_isActivating;
	}
}

void StrawberryFountain::Animation()
{
	NPC::Animation();
}