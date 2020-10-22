#pragma once
#include "NPC.h"
class StrawberryFountain : public NPC
{
private :
	bool _isTalked;
	bool _isActivated;
public :
	HRESULT init(int id, string name, OBJECTTYPE type, vector<string> imgNames);
	void update();
	void SetConvUI();
	void Conversation();
	void initSecond();
	void release();
	void render(HDC hdc);
	void Activate();
	void Animation();
};

