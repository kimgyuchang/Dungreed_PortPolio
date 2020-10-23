#include "stdafx.h"
#include "Trainer.h"

HRESULT Trainer::init(int id, string name, OBJECTTYPE type, vector<string> imgNames)
{
	NPC::init(id, name, type, imgNames);

	_npcName = "정연";
	_vConvTexts = vector<string>
	{
		"자네 왔군! 훈련할 텐가?",
	};
	_vSelectTexts = vector<string>
	{
		"훈련장",
		"아무것도"
	};

	_useConv = true;
	_useSelect = true;

	_isOpen = false;

	return S_OK;
}

void Trainer::update()
{
	NPC::update();
	if (_selectFrame->GetIsViewing() && _isUsing)
	{
		Conversation();
	}
}

void Trainer::Conversation()
{
	if (PtInRect(&_selectFrame->GetChild("selected1")->GetRect(), _ptMouse))
	{
		_selectFrame->GetChild("selected1")->SetImage(IMAGEMANAGER->findImage("SelectedFrame"));
		if (INPUT->GetIsLButtonClicked())
		{
			_selectFrame->SetIsViewing(false);
			_convFrame->SetIsViewing(false);
			_isOpen = true;
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

	if (_isOpen)
	{
		_isOpen = false;
		this->Activate();
	}
}

void Trainer::initSecond()
{
	_interactionImage = IMAGEMANAGER->findImage("Keyboard_F");
	_convFrame = UIMANAGER->GetGameFrame()->GetChild("convFrame");
	_selectFrame = UIMANAGER->GetGameFrame()->GetChild("selectFrame");
}

void Trainer::release()
{
	NPC::release();
}

void Trainer::render(HDC hdc)
{
	NPC::render(hdc);
}

void Trainer::Activate()
{
	_isActivating = !_isActivating;
	SOUNDMANAGER->play("인벤토리열기");
	UIMANAGER->GetGameFrame()->GetChild("allTraitFrame")->ToggleIsViewing();
	UIMANAGER->GetGameFrame()->GetChild("traitToolTip")->SetIsViewing(false);
	_isUsing = UIMANAGER->GetGameFrame()->GetChild("allTraitFrame")->GetIsViewing();

	ENTITYMANAGER->getPlayer()->ReInitTraitUI();
}

void Trainer::Animation()
{
	NPC::Animation();
}