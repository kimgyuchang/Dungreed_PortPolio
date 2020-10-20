#pragma once
#include "NPC.h"

enum FOODTYPE // À½½Äµé
{
	F_PEASOUP, F_HOTCHICKENSTEW, F_DELUXEBURGER, F_BREAD, F_FRIEDEEG, F_GRILLEDMUSHROOM, F_TOMATOSOUP, F_ONIONSOUP,
	F_VEGETABLESOUP, F_LEMONADE, F_CHOCOLATECOOKIE, F_RASPBERRYCOOKIE, F_GRIFFONEGG, F_GARLICMEATBALL, F_BIBIMBAP,
	F_MINOTAURS, F_COOKEDMEAT, F_STRAWBERRYPIE, F_SEASONINGBIRD, F_BEER, F_PIZZA, F_SALMON, F_SHRIMP, F_EEL, F_ROLL,
	F_SPARKLING, F_SWEETMEATBALL, F_HOTMEATBALL, F_END
};

enum FOODSTATUSTYPE // À½½Ä ½ºÅÈ
{
	FST_POWER, FST_DEF, FST_EVADE, FST_CRIPER, FST_CRIDMG, FST_MAXHP, FST_MAXDASH, FST_FIXEDDMG, FST_ATKSPEED,
	FST_CHARGESPEED, FST_MAXACCSLOT, FST_STRONG, FST_SATIATION, FST_BLOCK, FST_MOVESPEED
};

enum FOODHEAL // Èú
{
	F_HEAL
};

class Food
{
public:
	string					_name;
	string					_imgName;
	string					_soundName;

	image*					_img;

	FOODTYPE				_type;
	vector<FOODHEAL>		_vHeal;
	vector<float>			_vHealPer;
	vector<FOODSTATUSTYPE>	_vStatusType;
	vector<float>			_vStatusNum;

	int						_price;
	int						_satiation;

	bool					_isSoldOut;
};

class Restaurant : public NPC
{
private:
	UIFrame*		_restaurantBase;
	UIFrame*		_foodImg;
	vector<Food*>	_vFoods;

	int				_count;
	int				_scrollTimer;

	bool			_isOpen;
	bool			_foodAlphaAnimOn;
	bool			_foodMoveAnimOn;

	float			_speed;
	float			_x, _y;
	float			_mouseLocation;

public:
	virtual HRESULT init(int id, string name, OBJECTTYPE type, vector<string> imgNames);
	virtual void	update();
	void			MoveFood();
	void			FoodAlphaAnim();
	virtual	void	release();
	virtual void	render(HDC hdc);
	virtual void	Activate();

	void			initSecond();
	void			SetRestaurantFood();
	void			SetSatiationUI();
	void			SetHpUI();
	void			SetHPUI();
	void			BuyFood(Food* food, int index);
	void			ReNewUI();
	void			MoveUI();
	void			Conversation();
};
