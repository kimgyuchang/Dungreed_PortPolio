#pragma once
#include "Object.h"

class GunShop : public Object
{
private:
	UIFrame*		_convFrame;
	string			_npcName;
	vector<string>	_vConvTexts;
	RECT			_interactRect;
	image*			_interactionImage;
	bool			_isInteracting;
	bool			_useConv;
	bool			_isTalked;
	bool			_isActivating;
	int				_random;

public:
	virtual HRESULT init(int id, string name, OBJECTTYPE type, vector<string> imgNames);
	virtual void	update();
	virtual	void	release();
	virtual void	render(HDC hdc);

	virtual void	Activate();
	virtual void	PressActivateKey();
	virtual void	ShowConversation();
	virtual void	SetConvUI();
	virtual void	CollisionInteraction();
	void			initSecond();
};

