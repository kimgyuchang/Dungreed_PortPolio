#pragma once
#include "singletonBase.h"
#include "Stage.h"

class PixelGetter 
{

public :
	BYTE* pData;
	BITMAP bmInfo;
};

class MapManager : public singletonBase<MapManager>
{
private:
	vector<FieldMap*>	_vOriginMaps;	// 데이터로 불러온 맵들

	vector<Stage*>		_vStage;		// 스테이지 데이터
	int					_currentMap;	// 현재 맵
	int					_currentStage;	// 현재 스테이지
	
	// MAP UI 관련 //
	int					_moveClickTimer;
	POINT				_recentMousePos;
	PixelGetter*		_pixelGetter;

public:
	HRESULT init();
	void update();
	void SetMapUIOnOff();
	void GenerateMapParticle();
	void DungeonMapUIMover();
	void ReNewMapUI();
	void release();
	void render(HDC hdc);
	void ChangeMap(int stage, int index);

	// GETSET //
	int					GetCurrentStage()	{ return _currentStage; }
	int					GetCurrentMap()		{ return _currentMap; }
	FieldMap*			GetPlayMap()		{ return _vStage[_currentStage]->GetMaps()[_currentMap]; }
	vector<FieldMap*>&	GetMaps()			{ return _vOriginMaps; }
	PixelGetter*		GetPixelGetter()	{ return _pixelGetter; }
	int			SetCurrentStage(int stage)	{ _currentStage = stage; }
	int			SetCurrentMap(int map)		{ _currentMap = map; }
};

