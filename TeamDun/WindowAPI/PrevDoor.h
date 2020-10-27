#pragma once
#include "NPC.h"
class PrevDoor :
    public NPC
{
private:
	POINT _goPoint;
public:
	virtual HRESULT init(int id, string name, OBJECTTYPE type, vector<string> imgNames);
	virtual void Activate();
	void SetPoint(POINT point) { _goPoint = point; }
	POINT GetPoint() { return _goPoint; }
};
