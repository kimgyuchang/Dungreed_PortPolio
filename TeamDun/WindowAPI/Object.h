#pragma once

enum OBJECTTYPE
{
	OT_PLAYER, OT_MONSTER, OT_NPC, OT_OBSTACLE, OT_BREAKABLE
};

class Object 
{
private :
	float			_x;				// 위치 X 
	float			_y;				// 위치 Y
	OBJECTTYPE		_type;			// 오브젝트 타입
	int				_spawnTime;		// 스폰 시간
	vector<image*>	_vImages;		// 이미지들

public :
	// GETSET //
	int GetX() { return _x; }
	void SetX(int x) { _x = x; }
	int GetY() { return _y; }
	void SetY(int y) { _y = y; }
	OBJECTTYPE GetType() { return _type; }
	void SetType(OBJECTTYPE type) { _type = type; }
	image* GetImage(int index) { return _vImages[index]; }
	void Setimage(int index, image* img) { _vImages[index] = img; }
};