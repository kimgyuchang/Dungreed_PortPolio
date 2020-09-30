#pragma once
#include "singletonBase.h"
#include "FieldMap.h"

class MapManager : public singletonBase<MapManager>
{
private:
	vector<FieldMap*>	_vMaps;

public:
	HRESULT init();
	void update();
	void release();
	void render(HDC hdc);

	vector<FieldMap*>& GetMaps() { return _vMaps; }
};

