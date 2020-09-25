#pragma once
#include "singletonBase.h"
#include "Object.h"
#include "MapObject.h"

struct GridData
{
	string	_name;	// 그리드 이름
	int		_x;		// uiBrushTool에서의 x 좌표 
	int		_y;		// uiBrushTool에서의 y 좌표 
	int		_page;	// uiBrushTool에서의 페이지 
	image*	_image;	// 표현 이미지
};

class DataManager : public singletonBase<DataManager>
{
private :
	map<int, GridData*>		_mGridData;			// 그리드 데이터 맵
	map<int, Object*>		_mObjectData;		// 오브젝트 맵
	map<int, MapObject*>	_mMapObjectData;	// 맵 오브젝트 맵
public :
	
	// 데이터 불러오기 //
	void GetUIBrushToolGridData();
	void GetObjectData();

	// GETSET //
	map<int, GridData*>&	GetGridData()			{ return _mGridData; }
	map<int, MapObject*>&	GetMapObjectData()		{ return _mMapObjectData; }
	Object*					GetObjectById(int id)	{ return _mObjectData[id]; }
};

