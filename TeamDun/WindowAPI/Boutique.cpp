#include "stdafx.h"
#include "Boutique.h"

HRESULT Boutique::init(int id, string name, OBJECTTYPE type, vector<string> imgNames)
{
	NPC::init(id, name, type, imgNames);

	_npcName = "승기";
	_vConvTexts = vector<string>
	{
		"옷 갈아입을 준비는 되셨습니까?",
	};
	_vSelectTexts = vector<string>
	{
		"의상실",
		"아무것도"
	};

	_useConv = true;
	_useSelect = true;
	_isUsing = false;
	_isOpen = false;

	return S_OK;
}

void Boutique::update()
{
	NPC::update();
	if (_selectFrame->GetIsViewing() && _isUsing)
	{
		Conversation();
	}

	if (UIMANAGER->GetGameFrame()->GetChild("warDrobeFrame")->GetIsViewing()) EscapeChecker();
}

void Boutique::Conversation()
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

void Boutique::initSecond()
{
	_interactionImage = IMAGEMANAGER->findImage("Keyboard_F");
	_convFrame = UIMANAGER->GetGameFrame()->GetChild("convFrame");
	_selectFrame = UIMANAGER->GetGameFrame()->GetChild("selectFrame");
}

void Boutique::release()
{
	NPC::release();
}

void Boutique::render(HDC hdc)
{
	NPC::render(hdc);
}


void Boutique::Activate()
{
	_isActivating = !_isActivating;
	SOUNDMANAGER->play("인벤토리열기");
	UIMANAGER->GetGameFrame()->GetChild("warDrobeFrame")->ToggleIsViewing();
	_isUsing = UIMANAGER->GetGameFrame()->GetChild("warDrobeFrame")->GetIsViewing();

	for (int i = 0; i < 13; i++)
	{
		UIMANAGER->GetGameFrame()->GetChild("warDrobeFrame")->GetChild("Base")->GetChild("CostumeOver" + to_string(i))->SetIsViewing(false);
	}
}

void Boutique::EscapeChecker()
{
	if (INPUT->GetIsEscapeKeyPressed())
	{
		SOUNDMANAGER->play("인벤토리열기");
		_isActivating = false;
		_isUsing = false;
		UIMANAGER->GetGameFrame()->GetChild("warDrobeFrame")->SetIsViewing(false);

		for (int i = 0; i < 13; i++)
		{
			UIMANAGER->GetGameFrame()->GetChild("warDrobeFrame")->GetChild("Base")->GetChild("CostumeOver" + to_string(i))->SetIsViewing(false);
		}
	}
}

void Boutique::Animation()
{
	NPC::Animation();
}