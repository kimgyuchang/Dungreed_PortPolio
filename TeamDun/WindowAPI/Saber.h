#pragma once
#include "Item.h"
class SaberEffect
{
public:
	float _x, _y;
	float _angle;
	Item* _parent;
	Effect* _effect;
	int _radius;

	void init(float x, float y, string imgName, float angle);
	void update();
	void render(HDC hdc);
	void SetCollide();

	Effect* GetEffect() { return _effect; }
};

class Saber : public Item
{
private:
	vector<SaberEffect*> _vSlashes;
	float _baseAngle;
	image* _slashImage;
public:
	virtual HRESULT init(int id, ITEMTYPE itemType, WEAPONTYPE weaponType, Skill* skill, string name, string description, ITEMCLASS itemClass, float minAtk, float maxAtk, float atkSpeed, int defence, bool useAtkSpeed, int numOfBullet, float reloadTime, Bullet* bullet, float accuracy, int buyPrice, bool isBulletInfinite, vector<string> imageNames, string invenImage, string dropImage);
	virtual void update();
	virtual void render(HDC hdc);
	void Activate();
	void SlashUpdater();
	virtual void SetBaseRenderPos();
	void ChangeMap();
};