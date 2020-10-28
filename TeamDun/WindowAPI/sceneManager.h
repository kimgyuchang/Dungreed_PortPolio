#pragma once
#include "singletonBase.h"

class gameNode;

class sceneManager : public singletonBase <sceneManager>
{
private:
	typedef map<string, gameNode*> mSceneList;
	typedef map<string, gameNode*>::iterator miSceneList;

private:	
	mSceneList _mSceneList;			//°¢°¢ÀÇ ¾À(È­¸é)µéÀ» ´ã¾ÆµÑ ¸Ê
	gameNode* _currentScene;		//ÇöÀç¾À

public:
	// ±âº» //
	sceneManager() : _currentScene(NULL) {}
	~sceneManager() {}
	HRESULT init();
	void release();
	void update();
	void render();

	// ¾À °ü¸®
	gameNode* addScene(string sceneName, gameNode* scene);
	HRESULT loadScene(string sceneName);

};

