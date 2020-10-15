#pragma once
class WormVillage : public Object
{
private :
	bool _isOn;
	bool _renderPlayer;
public :
	virtual HRESULT init(int id, string name, OBJECTTYPE type, vector<string> imgNames);
	virtual void	update();
	virtual	void	release();
	virtual void	render(HDC hdc);
	virtual void	Animation();
	void Activate();

	bool GetRenderPlayer() { return _renderPlayer; }
	bool GetIsOn() { return _isOn; }
};

