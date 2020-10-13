#pragma once
class Skill
{
private:
	int		_id;
	string	_name;
	float	_coolTime;
	string	_description;
	image*	_image;
	string	_imageName;

public :
	virtual HRESULT init(int id, string name, float coolTime, string description, string imageName);
	virtual void update();
	virtual void release();
	virtual void render(HDC hdc);

	// GETSET //
	int GetId() { return _id; }
	string GetName() { return _name; }
	float GetCoolTime() { return _coolTime; }
	string GetDescription() { return _description; }
	image* GetImage() { return _image; }
	string GetImageName() { return _imageName; }
};

