#pragma once
#include "Item.h"

class DemonSlash
{
public :
	float _x;
	float _y;
	float _radius;
	int _frameY;
	float _angle;
	Item* _parent;
	Effect* _effect;

	void init(float x, float y, int frameY, string imgName, float angle);
	void update();
	void render(HDC hdc);
	void SetCollide();

	Effect* GetEffect() { return _effect; }
};

class DemonSword : public Item
{
private :
	int _animCount;
	int _finalAnimCount;
	int _renderFrontCount;
	bool _isLeftAttack;
	image* _slashImage;
	vector<DemonSlash*> _vSlashes;
public :
	virtual HRESULT init(int id, ITEMTYPE itemType, WEAPONTYPE weaponType, Skill* skill, string name, string description, ITEMCLASS itemClass, float minAtk, float maxAtk, float atkSpeed, int defence, bool useAtkSpeed, int numOfBullet, float reloadTime, Bullet* bullet, float accuracy, int buyPrice, bool isBulletInfinite, vector<string> imageNames, string invenImage, string dropImage);
	virtual void update();
	virtual void render(HDC hdc);
	virtual void release();
	void AttackAnim();
	virtual void Activate();
	void SlashUpdater();
	virtual void ChangeMap();
	virtual void SetBaseRenderPos();
};

