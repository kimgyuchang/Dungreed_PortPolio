#pragma once


class Treasure : public NPC
{
private:

	int treasureType;
public:
	virtual HRESULT init(int id, string name, OBJECTTYPE type, vector<string> imgNames);
	virtual void	update();
	virtual	void	release();
	virtual void	render(HDC hdc);
	virtual void	Animation();
	virtual void	initSecond();
	virtual void	Activate();
};

