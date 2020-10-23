#pragma once
class Item;
class Skill
{
protected:
	int		_id;
	string	_name;
	float	_coolTime;
	float   _curCoolTime;
	string	_description;
	image*	_image;
	string	_imageName;
	Item*	_parent;
public :
	virtual HRESULT init();
	virtual void update();
	virtual void release();
	virtual void render(HDC hdc);
	virtual void Activate();
	void CoolTimeChecker();

	// GETSET //
	int GetId() { return _id; }
	string GetName() { return _name; }
	float GetCoolTime() { return _coolTime; }
	string GetDescription() { return _description; }
	image* GetImage() { return _image; }
	string GetImageName() { return _imageName; }
	Item* GetParent() { return _parent; }
	float GetCurCoolTime() { return _curCoolTime; }

	void SetParent(Item* item) { _parent = item; }
};

