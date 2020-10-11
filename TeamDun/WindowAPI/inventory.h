#pragma once
#include "Item.h"

class Player;
class Inventory
{

private :
	vector<Item*> _vInvenItems;
	UIFrame* _InvenFrame;

	int		_invenFullTextTimer;
	bool	_invenFullTextOn;
	int		_invenEqualTextTimer;
	bool	_invenEqualTextOn;

	bool	_leftClicked;
	int		_clickedTarget;
	int		_leftClickTimer;

	Player* _p;

public :

	HRESULT init();
	void update();
	void render(HDC hdc);
	void release();
	
	void UpdateMoney();

	void EquipItem();
	void SwitchItem(int num, Item* item, int index);
	void UnEquipItem();
	bool AddItem(Item* item);
	void ReloadUIImages();
	void OnInvenFullText();
	void OnInvenEqualText();
	void CheckInvenText();
	void SwitchWeapon(int selectedWeapon);
};

