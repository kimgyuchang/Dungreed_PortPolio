#pragma once
#include "NPC.h"

enum FOOD
{
	F_SOUP, F_STEW, F_BURGER
};
class Restaurant : public NPC
{
private:
	//UIFrame*		_restaurantBase;
	//UIFrame*		_restaurantLabel;
	//UIFrame*		_restaurantFoodBase;
	//UIFrame*		_wholeFoodFrame;
	//UIFrame*		_foodFrame;
	//UIFrame*		_foodFrameSelected;
	//UIFrame*		_exit;
	//UIFrame*		_satiation;
	//UIFrame*		_money;
	//UIFrame*		_foodIcon;

	vector<string>	_vFoodName;
	vector<string>	_vFoodFirstStat;
	vector<string>	_vFoodSecondStat;
	vector<string>	_vFoodThirdStat;
	vector<string>	_vFoodPrice;
	vector<string>	_vFoodHeal;
	vector<string>	_vFoodSatiation;

	RECT			_exitRect;

	FOOD			_food;

public:
	virtual HRESULT init(int id, string name, OBJECTTYPE type, vector<string> imgNames);
	virtual void	update();
	virtual	void	release();
	virtual void	render(HDC hdc);
	virtual void	Activate();

	void			initSecond();
	void			SetRestaurantFood();
	void			BuyFood();
	void			ReNewUI();
	void			Conversation();
};
