#pragma once
#include "Object.h"

class NPC : public Object
{
private :
	RECT _interactRect;
	bool _isInteracting;
public :

	virtual HRESULT init(int id, string name, OBJECTTYPE type, vector<string> imgNames);
	virtual void	update();
	virtual	void	release();
	virtual void	render(HDC hdc);
	virtual void	Animation();
	void CollisionInteraction();

	// GETSET //
	RECT GetInteractRect() { return _interactRect; }
	void SetInteractRect(RECT rect) { _interactRect = rect; }

};

