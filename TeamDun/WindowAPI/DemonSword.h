#pragma once
#include "Item.h"

class DemonSlash
{
public :
	float _x;
	float _y;
	float _radius;
	image* _image;
	int _frameX;
	int _animTimer;
	float _angle;
	bool _isDead;
	Item* _parent;

	void init(float x, float y, image* img, int angle);
	void update();
	void animation();
	void render(HDC hdc);
	void SetCollide();
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
	virtual HRESULT init(int id, ITEMTYPE itemType, WEAPONTYPE weaponType, Skill* skill, string name, string description, ITEMCLASS itemClass, float minAtk, float maxAtk, float atkSpeed, int defence, bool useAtkSpeed, int numOfBullet, float reloadTime, Bullet* bullet, float accuracy, int buyPrice, bool isBulletInfinite, vector<string> imageNames, string invenImage);
	virtual void update();
	virtual void render(HDC hdc);
	virtual void release();
	void AttackAnim();
	virtual void Activate();
	void SlashUpdater();
};

