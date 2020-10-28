#include "stdafx.h"
#include "sceneManager.h"
#include "gameNode.h"

HRESULT sceneManager::init()
{
	return S_OK;
}

void sceneManager::release()
{
	for (auto scene : _mSceneList)
	{
		scene.second->release();
		SAFE_DELETE(scene.second);
	}
}

void sceneManager::update()
{
	if (_currentScene) _currentScene->update(); // 현재의 씬만 업데이트
}

void sceneManager::render()
{
	if (_currentScene) _currentScene->render(); // 현재의 씬만 렌더
}

/// <summary>
/// 이름과 Scene class를 받아 맵에 추가한다.
/// </summary>
gameNode * sceneManager::addScene(string sceneName, gameNode * scene)
{
	if (!scene) return NULL;
	_mSceneList.insert(make_pair(sceneName, scene));

	return scene;
}

/// <summary>
/// 이름을 받아 해당 씬으로 변경한다.
/// </summary>
HRESULT sceneManager::loadScene(string sceneName)
{
	miSceneList find = _mSceneList.find(sceneName);

	if (find == _mSceneList.end()) return E_FAIL;
	if (find->second == _currentScene) return E_FAIL;
	if (SUCCEEDED(find->second->init()))
	{
		_currentScene = find->second;
		return S_OK;
	}

	return E_NOTIMPL;
}
