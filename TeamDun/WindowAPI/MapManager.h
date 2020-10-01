#pragma once
#include "singletonBase.h"
#include "FieldMap.h"

class MapManager : public singletonBase<MapManager>
{
private:
	vector<FieldMap*>	_vMaps;
	int					_currentMap;

public:
	HRESULT init();
	void update();
	void release();
	void render(HDC hdc);
	void ChangeMap(int index);

	int GetCurrentMap() { return _currentMap; }
	vector<FieldMap*>& GetMaps() { return _vMaps; }
};

