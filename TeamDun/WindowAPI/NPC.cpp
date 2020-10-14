#include "stdafx.h"
#include "NPC.h"

HRESULT NPC::init(int id, string name, OBJECTTYPE type, vector<string> imgNames)
{
	Object::init(id, name, type, imgNames);
	_isInteracting = false;
	_isActivating = false;

	return S_OK;
}

/// <summary>
/// DATAMANAGER에서 불러온 후 init 가능한 것들만 init한다.
/// </summary>
void NPC::initSecond()
{
	_interactionImage = IMAGEMANAGER->findImage("Keyboard_F");
	_convFrame = UIMANAGER->GetGameFrame()->GetChild("convFrame");
	_selectFrame = UIMANAGER->GetGameFrame()->GetChild("selectFrame");
}

void NPC::release()
{
}

void NPC::update()
{
	CollisionInteraction();
	PressActivateKey();
	Animation();
}

void NPC::CollisionInteraction()
{
	_interactRect = RectMake(_x - 50, _y - 50, _vImages[_useImage]->getFrameWidth() + 100, _vImages[_useImage]->getFrameHeight() + 100);

	RECT temp;
	if (IntersectRect(&temp, &_interactRect, &ENTITYMANAGER->getPlayer()->GetBody()))
	{
		_isInteracting = true;
	}

	else
	{
		_isInteracting = false;
	}
}

/// <summary>
/// 키를 통해 상호작용을 시작한다.
/// </summary>
void NPC::PressActivateKey()
{
	if (_isInteracting && INPUT->GetKeyDown('F'))
	{
		ShowConversation();
	}
}

/// <summary>
/// 대화를 On/Off한다.
/// </summary>
void NPC::ShowConversation()
{
	if (_useConv && !_isActivating)
	{
		SetConvUI();
		_convFrame->ToggleIsViewing();

		if(_useSelect) _selectFrame->ToggleIsViewing();
	}

	else
	{
		Activate();
	}
}

/// <summary>
/// 대화창의 텍스트 내용물들을 수정한다.
/// </summary>
void NPC::SetConvUI()
{
	dynamic_cast<UIText*>(_convFrame->GetChild("name"))->SetText(_npcName);
	dynamic_cast<UIText*>(_convFrame->GetChild("text"))->SetText(_vConvTexts[RANDOM->range((int)_vConvTexts.size())]);
	dynamic_cast<UIText*>(_convFrame->GetChild("text"))->SetCntPos(0);

	if (_useSelect)
	{
		dynamic_cast<UIText*>(_selectFrame->GetChild("selected1")->GetChild("text"))->SetText(_vSelectTexts[0]);
		dynamic_cast<UIText*>(_selectFrame->GetChild("selected2")->GetChild("text"))->SetText(_vSelectTexts[1]);
		_selectFrame->GetChild("selected1")->SetImage(nullptr);
		_selectFrame->GetChild("selected2")->SetImage(nullptr);
	}
}

/// <summary>
/// 대화를 진행한다. 이때 선택지를 누르는 것에 대한 반응도 추가된다.
/// </summary>
void NPC::Conversation()
{
	// 각자 구현 필요
}

/// <summary>
/// 본격적인 상호작용의 진행
/// </summary>
void NPC::Activate()
{
	// 각자 구현 필요
}

void NPC::render(HDC hdc)
{
	Object::render(hdc);

	if (_isInteracting)
	{
		CAMERAMANAGER->Render(hdc, _interactionImage, _x + _vImages[_useImage]->getFrameWidth() / 2, _y - 50);
	}
}

void NPC::Animation()
{
	_frameTimer++;

	if (_frameTimer > 5)
	{
		_frameTimer = 0;
		_frameX++;

		if (_frameX >= _vImages[_useImage]->getMaxFrameX()) _frameX = 0;
	}
}
