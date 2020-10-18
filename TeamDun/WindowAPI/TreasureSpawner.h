#pragma once
class TreasureSpawner : public Object
{
private:
	bool		_isOff;
public:
	virtual HRESULT init(int id, string name, OBJECTTYPE type, vector<string> imgNames);
	virtual void	update();
	virtual	void	release();
	virtual void	render(HDC hdc);
	void SpawnTreasure();

	// GETSET //
	bool		GetIsOff() { return _isOff; }
	void		SetIsOff(bool isOff) { _isOff = isOff; }
};

