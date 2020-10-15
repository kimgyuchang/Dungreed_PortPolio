#pragma once
#include "NPC.h"
class Portal : public NPC
{
private:
	bool	_isOn;
	bool	_isUp;
	int		_destination;
public:
	virtual HRESULT init(int id, string name, OBJECTTYPE type, vector<string> imgNames);
	virtual void	update();
	virtual	void	release();
	virtual void	render(HDC hdc);
	void MoveMap(int stage);
	virtual void initSecond();
	virtual void	Animation();
	virtual void	Activate();

	// GETSET //
	void SetIsOn(bool isOn) { _isOn = isOn; }
	void SetIsUp(bool isUp) { _isUp = isUp; }
	void SetDestination(int dest) { _destination = dest; }
};

