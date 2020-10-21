#pragma once
#include "singletonBase.h"
#include "Object.h"

#include "objHeaderCollector.h"

struct GridData
{
	string	_name;		// 그리드 이름
	int		_x;			// uiBrushTool에서의 x 좌표 
	int		_y;			// uiBrushTool에서의 y 좌표 
	int		_page;		// uiBrushTool에서의 페이지 
	image*	_image;		// 표현 이미지
	image*	_colImage;	// 충돌 이미지
};

class DataManager : public singletonBase<DataManager>
{
private :
	map<string, GridData*>	_mGridDataByName;	// 그리드 데이터 맵 (이름으로 가져오기)
	map<int, GridData*>		_mGridData;			// 그리드 데이터 맵
	map<int, Object*>		_mObjectData;		// 오브젝트 맵
	map<int, MapObject*>	_mMapObjectData;	// 맵 오브젝트 맵
	map<int, Item*>			_mMapItemData;		// 아이템 맵

	int	_itemMaxId;
	int _itemMinId;

public :
	HRESULT Init();
	// 데이터 불러오기 //
	void GetUIBrushToolGridData();
	void GetObjectData();
	void GetItemData();
	int GetItemSize();
	Item * GetItemByIndex(int index);
	Item* GetItemById(int id);

	// GETSET //
	map<int, GridData*>&	GetGridData()					{ return _mGridData; }
	GridData*				GetGridDataByName(string name)	{ return _mGridDataByName[name]; }
	map<int, MapObject*>&	GetMapObjectData()				{ return _mMapObjectData; }
	Object*					GetObjectById(int id)			{ return _mObjectData[id]; }
	map<int, Item*>&		GetMapItemData()				{return _mMapItemData; }
	
	int						GetItemMaxId()					{ return _itemMaxId; }
	int						GetItemMinId()					{ return _itemMinId; }
};

