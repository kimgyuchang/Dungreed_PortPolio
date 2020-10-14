#pragma once
#include "Object.h"

class NPC : public Object
{
protected:
	RECT	_interactRect;
	bool	_isInteracting;
	image* _interactionImage;

	// 대화 기능 //
	string	_npcName;
	vector<string> _vConvTexts;
	vector<string> _vSelectTexts;
	bool	 _useConv;
	bool	 _useSelect;
	UIFrame* _convFrame;
	UIFrame* _selectFrame;
	bool	 _isActivating;

public:

	virtual HRESULT init(int id, string name, OBJECTTYPE type, vector<string> imgNames);
	virtual void initSecond();
	virtual void update();
	virtual	void release();
	virtual void ShowConversation();
	virtual void Conversation();
	virtual void render(HDC hdc);
	virtual void Animation();
	virtual void Activate();
	virtual void SetConvUI();

	void CollisionInteraction();
	void PressActivateKey();

	// GETSET //
	RECT GetInteractRect() { return _interactRect; }
	void SetInteractRect(RECT rect) { _interactRect = rect; }
	void SetUseSelect(bool use) { _useSelect = use; }
	void SetUseConv(bool use) { _useConv = use; }
};

