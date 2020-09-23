#pragma once

enum OBJECTTYPE
{
	OT_PLAYER, OT_MONSTER, OT_NPC, OT_OBSTACLE, OT_BREAKABLE, OT_ETC
};

class Object 
{
private :
	int				_id;			// ID
	string			_name;			// 이름
	OBJECTTYPE		_type;			// 오브젝트 타입
	vector<image*>	_vImages;		// 이미지들
	float			_x;				// 위치 X 
	float			_y;				// 위치 Y
	int				_spawnTime;		// 스폰 시간

public :

	virtual HRESULT init(int id, string name, OBJECTTYPE type, vector<string> imgNames);
	virtual void	update();
	virtual	void	release();
	virtual void	render(HDC hdc);

	// GETSET //
	string GetName() { return _name; }
	void SetName(string name) { _name = name; }
	int GetX() { return _x; }
	void SetX(int x) { _x = x; }
	int GetY() { return _y; }
	void SetY(int y) { _y = y; }
	OBJECTTYPE GetType() { return _type; }
	void SetType(OBJECTTYPE type) { _type = type; }
	image* GetImage(int index) { return _vImages[index]; }
	void Setimage(int index, image* img) { _vImages[index] = img; }
};