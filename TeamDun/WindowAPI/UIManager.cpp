#include "stdafx.h"
#include "UIManager.h"

/// <summary>
/// 게임에서 사용될 UI들을 초기화시킨다. 던그리드는 씬이 여러개이기 때문에 _GameFrame 메인으로 두고 씬마다 UIManager를 새롭게 Init한다.
/// </summary>
HRESULT UIManager::init()
{
	// 사용 예시 (파는마녀에서 사용된 UI [이미지와 데이터가 없어서 실행이 안됨, 어떤 식으로 코드를 써야 하는지만 확인])

	// 게임 전체를 덮는 UI (투명)
	_GameFrame = new UIFrame();
	_GameFrame->init("mainFrame", 0, 0, 1920, 1080, "");
	_GameFrame->SetIsViewing(true);

	// 가방 UI Image
	UIImage* back = new UIImage();
	back->init("mainFrame_backpack", 70, WINSIZEY - 160, IMAGEMANAGER->findImage("UI_Bag")->getWidth(), IMAGEMANAGER->findImage("UI_Bag")->getHeight(), "UI_Bag", false, 0, 0);
	back->SetIsViewing(true);

	// Stage 표시용 UI Text
	UIText* stage = new UIText();
	stage->init("stage", 700, 20, "STAGE 1", FONT::PIX, WORDSIZE::WS_BIG);
	
	// 현재 이동 거리 표시용 UI Text
	UIText* m = new UIText();
	m->init("m", 1200, 20, "0m", FONT::PIX, WORDSIZE::WS_BIG, WORDSORT::WSORT_RIGHT);
	
	// 게임 프레임의 자식으로 가방과 스테이지, 이동 거리를 넣는다.
	_GameFrame->AddFrame(back);	
	_GameFrame->AddFrame(stage);
	_GameFrame->AddFrame(m);

	// 플레이어 프레임 틀
	_PlayerFrame = new UIFrame();
	_PlayerFrame->init("playerFrame", 200, 200, IMAGEMANAGER->findImage("UI_Menu")->getWidth(), IMAGEMANAGER->findImage("UI_Menu")->getHeight(), "UI_Menu");
	_PlayerFrame->SetIsMoveToDrag(true);

	// 인벤토리
	UIFrame* inven = new UIFrame();
	inven->init("playerFrame_inventory", 20, 44, IMAGEMANAGER->findImage("UI_Inven")->getWidth(), IMAGEMANAGER->findImage("UI_Inven")->getHeight(), "UI_Inven");
	inven->SetIsViewing(false);
	
	// 제작
	UIFrame* craft = new UIFrame();
	craft->init("playerFrame_craft", 19, 37, IMAGEMANAGER->findImage("UI_Craft")->getWidth(), IMAGEMANAGER->findImage("UI_Craft")->getHeight(), "UI_Craft");
	craft->SetIsViewing(false);
	craft->SetUseOutsideLimit(true);
	
	// 돈 프레임 틀
	UIFrame* money = new UIFrame();
	money->init("playerFrame_money", 1300, 0, IMAGEMANAGER->findImage("UI_Money")->getWidth(), IMAGEMANAGER->findImage("UI_Money")->getHeight(), "UI_Money");
	money->SetIsViewing(true);
	
	// 플레이어 프레임의 안에 인벤토리와 제작, 돈을 넣는다. 이후 다른 cpp 파일에서 이들의 안에 자식으로 아이템 목록 이미지, 텍스트 등이 들어가게 된다.
	_PlayerFrame->AddFrame(inven);
	_PlayerFrame->AddFrame(craft);
	_PlayerFrame->AddFrame(money);
	
	// 돈 현황 텍스트
	UIText* moneyText = new UIText();
	moneyText->init("moneyText", IMAGEMANAGER->findImage("UI_Money")->getWidth() - 65, IMAGEMANAGER->findImage("UI_Money")->getHeight() - 55, "0", FONT::PIX, WORDSIZE::WS_BIG, WORDSORT::WSORT_RIGHT, -6);
	moneyText->SetIsViewing(true);
	money->AddFrame(moneyText); // 돈 프레임 틀에 자식으로 현재 돈 텍스트를 넣는다.

	return S_OK;
}

/// <summary>
/// UIManager의 모든 UI들을 업데이트한다.
/// </summary>
void UIManager::update()
{
	for (int i = 0; i < _vItemToBag.size(); i++)
	{
		_vItemToBag[i]->update();
	}

	_GameFrame->update();
	_PlayerFrame->update();
}

/// <summary>
/// UIManager의 모든 UI들을 렌더한다.
/// </summary>
void UIManager::render(HDC hdc)
{
	for (int i = 0; i < _vItemToBag.size(); i++)
	{
		_vItemToBag[i]->render(hdc);
	}

	_GameFrame->render(hdc);
	_PlayerFrame->render(hdc);
}

/// <summary>
/// UIManager의 모든 UI들을 릴리즈한다.
/// </summary>
void UIManager::release()
{
	for (int i = 0; i < _vItemToBag.size(); i++)
	{
		_vItemToBag[i]->release();
	}

	_GameFrame->release();
	_PlayerFrame->release();
}