#pragma once
#include "NPC.h"

class Inventory;
class Shop : public NPC
{
protected :

	UIFrame*		_shopBase;
	UIFrame*		_invenFrame;
	UIFrame*		_checkSellFrame;

	vector<Item*>	_vItemList;
	Inventory*		_inven;

	Item*			_selectedItem;
	int				_index;

	int				_toolTipIndex;
	Item*			_curToolTipItem;
	int				_toolTipFinalY;
	
public :

	virtual HRESULT init(int id, string name, OBJECTTYPE type, vector<string> imgNames);
	void Conversation();
	virtual void	update();
	virtual	void	release();
	virtual void	render(HDC hdc);
	virtual void	Animation();
	virtual void	initSecond();
	virtual void	Activate();
	void InitToolTipItem(Item* item);
	string OptionString(SubOption* option);

	void SetShopItem();
	void ReNewUI();
	void SellItem();
	void RenewCheckUI();
	void CheckToSell();
	void ActivateSell();
	void BuyItem();
};

