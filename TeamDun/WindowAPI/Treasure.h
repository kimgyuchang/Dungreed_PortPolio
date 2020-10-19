#pragma once
enum TREASURETYPE
{
	TST_GRAY, TST_BROWN, TST_BLUE, TST_GOLD, TST_LEGENDARY, TST_BOSS
};

class Treasure : public NPC
{
private:
	TREASURETYPE	_treasureType;
	bool			_isOpened;
	float			_speedY;
	float			_gravity;
public:
	virtual HRESULT init(int id, string name, OBJECTTYPE type, vector<string> imgNames);
	virtual void	update();
	virtual	void	release();
	virtual void	render(HDC hdc);
	virtual void	Animation();
	virtual void	initSecond();
	virtual void	Activate();

	void Move();

	void PixelCollision();

	// GETSET //
	TREASURETYPE GetTreasureType() { return _treasureType; }
	bool GetIsOpened() { return _isOpened; }
	void SetTreasureType(TREASURETYPE type) { _treasureType = type; }
};

