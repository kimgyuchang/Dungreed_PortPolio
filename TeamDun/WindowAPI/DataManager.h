#pragma once
#include "singletonBase.h"
#include "Object.h"

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
	vector<Object*> _vObjs;
	map<int, GridData*> _mGridData;
public :
	void GetUIBrushToolData();
	void GetMapObjectData();
	map<int, GridData*>& GetGridData() { return _mGridData; }
};

