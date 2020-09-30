#pragma once

struct Tile
{
	int		_x;					// X 위치
	int		_y;					// Y 위치
	image* _img;				// IMAGE
	image* _img2;				// IMAGE2
	image* _collisionImage;	// 픽셀충돌 이미지
};

class FieldMap
{
private :
	string					_fileName;
	vector<vector<Tile*>>	_vMapData;
	vector <Object*>		_vObjs;
	vector <RECT>			_vMiniRc;
	
	int						_nextMapIndex[4];
	int						_stage;
public :
	void LoadMap();

	HRESULT init(string fileName);
	virtual void update();
	virtual void release();
	virtual void render(HDC hdc);

	string	GetFileName()			{ return _fileName; }
	void	SetStage(int stage)		{ _stage = stage; }
};

