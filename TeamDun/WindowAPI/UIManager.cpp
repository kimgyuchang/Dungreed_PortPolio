#include "stdafx.h"
#include "UIManager.h"

/// <summary>
/// 게임에서 사용될 UI들을 초기화시킨다. 던그리드는 씬이 여러개이기 때문에 _GameFrame 메인으로 두고 씬마다 UIManager를 새롭게 Init한다.
/// </summary>
HRESULT UIManager::init()
{
	_GameFrame = new UIFrame();
	_GameFrame->init("mainFrame", 0, 0, 1920, 1080, "");
	_GameFrame->SetIsViewing(true);

	// TEXT 테스트용
	UIText* text;

	/*text = new UIText();
	text->init("testText", 600, 500, 300, 50, 
		"텍스트 테스트용입니다. 글자는 SMALLEST, 정렬은 왼쪽, 색은 흰색, 애니메이션은 빠름입니다.", 
		FONT::PIX, WORDSIZE::WS_SMALLEST, WORDSORT::WSORT_LEFT, RGB(255,255,255), true, WORDANIMATIONSPEED::WAS_FAST);
	_GameFrame->AddFrame(text);

	text = new UIText();
	text->init("testText", 600, 550, 300, 50, 
		"텍스트 테스트용입니다. 글자는 SMALLEST, 정렬은 가운데, 색은 주황색, 애니메이션은 중간입니다.", 
		FONT::PIX, WORDSIZE::WS_SMALLEST, WORDSORT::WSORT_MIDDLE, RGB(243, 151, 101), true, WORDANIMATIONSPEED::WAS_MIDDLE);
	_GameFrame->AddFrame(text);

	text = new UIText();
	text->init("testText", 600, 600, 300, 50, 
		"텍스트 테스트용입니다. 글자는 SMALLEST, 정렬은 오른쪽, 색은 보라색, 애니메이션은 느림입니다.", 
		FONT::PIX, WORDSIZE::WS_SMALLEST, WORDSORT::WSORT_RIGHT, RGB(200, 191, 231), true, WORDANIMATIONSPEED::WAS_SLOW);
	_GameFrame->AddFrame(text);*/

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