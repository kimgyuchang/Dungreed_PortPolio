#pragma once
#include  "Item.h"
class GreatBow : public Item
{
private:
	int _animCount;
	int _finalAnimCount;
	int _renderFrontCount;
	

	int _frameTimer;

	int _chargeCount;
	float _Speed;
	float _Power;
	float _range;
	bool _isReady;
	bool _isBowSound;

public:
	virtual HRESULT init(int id, ITEMTYPE itemType, WEAPONTYPE weaponType, Skill* skill, string name, string description, ITEMCLASS itemClass, float minAtk, float maxAtk, float atkSpeed, int defence, bool useAtkSpeed, int numOfBullet, float reloadTime, Bullet* bullet, float accuracy, int buyPrice, bool isBulletInfinite, vector<string> imageNames, string invenImage, string dropImage);
	virtual void update();
	virtual void render(HDC hdc);
	virtual void release();
	void FireBullet();

	void AttackAnim();
	virtual void Activate();
	virtual void ActivateAlways();
	virtual void SetBaseRenderPos();



};
