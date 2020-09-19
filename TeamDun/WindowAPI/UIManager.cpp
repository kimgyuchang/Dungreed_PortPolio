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

	return S_OK;
}

/// <summary>
/// UIManager의 모든 UI들을 업데이트한다.
/// </summary>
void UIManager::update()
{
	
	_GameFrame->update();

}

/// <summary>
/// UIManager의 모든 UI들을 렌더한다.
/// </summary>
void UIManager::render(HDC hdc)
{
	

	_GameFrame->render(hdc);
	
}

/// <summary>
/// UIManager의 모든 UI들을 릴리즈한다.
/// </summary>
void UIManager::release()
{
	
	_GameFrame->release();

}