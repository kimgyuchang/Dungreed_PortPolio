#include "stdafx.h"
#include "UIManager.h"

HRESULT UIManager::init()
{
	_GameFrame = new UIFrame();
	_GameFrame->init("mainFrame", 0, 0, 1920, 1080, "");
	_GameFrame->SetIsViewing(true);

	UIImage* back = new UIImage();
	back->init("mainFrame_backpack", 70, WINSIZEY - 160, IMAGEMANAGER->findImage("UI_Bag")->getWidth(), IMAGEMANAGER->findImage("UI_Bag")->getHeight(), "UI_Bag", false, 0, 0);
	back->SetIsViewing(true);

	UIText* stage = new UIText();
	stage->init("stage", 700, 20, "STAGE 1", FONT::PIX, WORDSIZE::WS_BIG);
	
	UIText* m = new UIText();
	m->init("m", 1200, 20, "0m", FONT::PIX, WORDSIZE::WS_BIG, WORDSORT::WSORT_RIGHT);
	
	_GameFrame->AddFrame(back);
	_GameFrame->AddFrame(stage);
	_GameFrame->AddFrame(m);

	_PlayerFrame = new UIFrame();
	_PlayerFrame->init("playerFrame", 200, 200, IMAGEMANAGER->findImage("UI_Menu")->getWidth(), IMAGEMANAGER->findImage("UI_Menu")->getHeight(), "UI_Menu");
	_PlayerFrame->SetIsMoveToDrag(true);

	UIFrame* inven = new UIFrame();
	inven->init("playerFrame_inventory", 20, 44, IMAGEMANAGER->findImage("UI_Inven")->getWidth(), IMAGEMANAGER->findImage("UI_Inven")->getHeight(), "UI_Inven");
	inven->SetIsViewing(false);
	_PlayerFrame->AddFrame(inven);
	
	UIFrame* craft = new UIFrame();
	craft->init("playerFrame_craft", 19, 37, IMAGEMANAGER->findImage("UI_Craft")->getWidth(), IMAGEMANAGER->findImage("UI_Craft")->getHeight(), "UI_Craft");
	craft->SetIsViewing(false);
	craft->SetUseOutsideLimit(true);
	_PlayerFrame->AddFrame(craft);
	
	UIFrame* money = new UIFrame();
	money->init("playerFrame_money", 1300, 0, IMAGEMANAGER->findImage("UI_Money")->getWidth(), IMAGEMANAGER->findImage("UI_Money")->getHeight(), "UI_Money");
	money->SetIsViewing(true);
	_PlayerFrame->AddFrame(money);
	
	UIText* moneyText = new UIText();
	moneyText->init("moneyText", IMAGEMANAGER->findImage("UI_Money")->getWidth() - 65, IMAGEMANAGER->findImage("UI_Money")->getHeight() - 55, "0", FONT::PIX, WORDSIZE::WS_BIG, WORDSORT::WSORT_RIGHT, -6);
	moneyText->SetIsViewing(true);
	money->AddFrame(moneyText);
	return S_OK;
}

void UIManager::update()
{
	for (int i = 0; i < _vItemToBag.size(); i++)
	{
		_vItemToBag[i]->update();
	}

	_GameFrame->update();
	_PlayerFrame->update();
}

void UIManager::render(HDC hdc)
{
	for (int i = 0; i < _vItemToBag.size(); i++)
	{
		_vItemToBag[i]->render(hdc);
	}

	_GameFrame->render(hdc);
	_PlayerFrame->render(hdc);
}

void UIManager::release()
{
	for (int i = 0; i < _vItemToBag.size(); i++)
	{
		_vItemToBag[i]->release();
	}

	_GameFrame->release();
	_PlayerFrame->release();
}

POINT UIManager::GetWordFramePosition(char ch)
{
	POINT pt;

	if (isalpha(ch))
	{
		ch = toupper(ch);
	}
	switch (ch)
	{
	case 'A': pt = { 0,0 }; break;
	case 'B': pt = { 1,0 }; break;
	case 'C': pt = { 2,0 }; break;
	case 'D': pt = { 3,0 }; break;
	case 'E': pt = { 4,0 }; break;
	case 'F': pt = { 5,0 }; break;
	case 'G': pt = { 6,0 }; break;
	case 'H': pt = { 7,0 }; break;
	case 'I': pt = { 8,0 }; break;
	case 'J': pt = { 9,0 }; break;
	case 'K': pt = { 10,0 }; break;
	case 'L': pt = { 11,0 }; break;
	case 'M': pt = { 12,0 }; break;
	case 'N': pt = { 13,0 }; break;
	case 'O': pt = { 14,0 }; break;
	case 'P': pt = { 15,0 }; break;
	case 'Q': pt = { 16,0 }; break;
	case 'R': pt = { 17,0 }; break;
	case 'S': pt = { 18,0 }; break;
	case 'T': pt = { 19,0 }; break;
	case 'U': pt = { 20,0 }; break;
	case 'V': pt = { 21,0 }; break;
	case 'W': pt = { 22,0 }; break;
	case 'X': pt = { 23,0 }; break;
	case 'Y': pt = { 24,0 }; break;
	case 'Z': pt = { 25,0 }; break;
	case '1': pt = { 0,1 }; break;
	case '2': pt = { 1,1 }; break;
	case '3': pt = { 2,1 }; break;
	case '4': pt = { 3,1 }; break;
	case '5': pt = { 4,1 }; break;
	case '6': pt = { 5,1 }; break;
	case '7': pt = { 6,1 }; break;
	case '8': pt = { 7,1 }; break;
	case '9': pt = { 8,1 }; break;
	case '0': pt = { 9,1 }; break;
	case '(': pt = { 0,2 }; break;
	case ')': pt = { 1,2 }; break;
	case '%': pt = { 2,2 }; break;
	case '+': pt = { 3,2 }; break;
	case '-': pt = { 4,2 }; break;
	case '=': pt = { 5,2 }; break;
	case '&': pt = { 6,2 }; break;
	case '$': pt = { 7,2 }; break;
	case '/': pt = { 8,2 }; break;
	case '#': pt = { 12,2 }; break;
	case '@': pt = { 13,2 }; break;
	case '?': pt = { 14,2 }; break;
	case '!': pt = { 15,2 }; break;
	case '<': pt = { 16,2 }; break;
	case '>': pt = { 17,2 }; break;
	case ':': pt = { 18,2 }; break;
	case ';': pt = { 19,2 }; break;
	default: pt = { 20,1 }; break;
	}

	return pt;
}
