#pragma once
#include "NPC.h"

class Restaurant : public NPC
{
private:
	UIFrame*		_restaurantBase;
	UIFrame*		_restaurantLabel;
	UIFrame*		_restaurantFoodBase;
	UIFrame*		_wholeFoodFrame;
	UIFrame*		_foodFrame;
	UIFrame*		_foodFrameSelected;

	vector<string>	_vFoodName;
	vector<string>	_vFoodFirstStat;
	vector<string>	_vFoodSecondStat;
	vector<string>	_vFoodThirdStat;

public:
	virtual HRESULT init(int id, string name, OBJECTTYPE type, vector<string> imgNames);
	virtual void	update();
	virtual	void	release();
	virtual void	render(HDC hdc);
	virtual void	Activate();

	void			SetRestaurantFood();
	void			BuyFood();
	void			ReNewUI();
};
