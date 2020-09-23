#pragma once
#include "singletonBase.h"
#include "Object.h"
#include "MapObject.h"

struct GridData
{
	string _name;
	int _x;
	int _y;
	int _page;
	image* _image;
};

class DataManager : public singletonBase<DataManager>
{
private :
	map<int, GridData*>		_mGridData;
	map<int, Object*>		_mObjs;
	map<int, MapObject*>	_mMapObjectData;
public :
	void GetUIBrushToolGridData();
	void GetObjectData();
	map<int, GridData*>& GetGridData() { return _mGridData; }
	map<int, MapObject*>& GetMapObjectData() { return _mMapObjectData; }
	Object* GetObjectById(int id) { return _mObjs[id]; }
};

