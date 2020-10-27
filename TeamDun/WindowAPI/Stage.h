#pragma once
#include "FieldMap.h"

class Stage
{
private :
	vector<FieldMap*>			_vMaps;					// 맵 이중 벡터
	FieldMap*					_cntMap;				// 현재 맵
	int							_stage;					// 현재 스테이지
	int							_numOfFloodFillCount;	// 플러드 필 횟수

	// 던전 스테이지
	int							_resturantRoomIdx;		// 레스토랑 인덱스
	int							_startIdx;				// 시작 인덱스
	int							_endIdx;				// 끝 인덱스
public :
	HRESULT init(int stage);
	void update();
	void release();
	void render(HDC hdc);
	int FindSameIndex(int indexX, int indexY, int curIndex);
	int GetConnectedRoomCount(FieldMap* map, int index);
	void AddRooms();
	void SetSpecialRoomPos();
	void CheckFloodFill(int index, int& numOfCheckRoom);
	bool FloodFillStart();
	void AddRoomConnections();
	void SetStageZero();
	void SetStageTwo();
	bool SettingMap();
	void SetFieldMapNumber();
	bool AddLine(FieldMap* map, DIRECTION dir, int index);
	bool CheckCollision();

	vector<FieldMap*>& GetMaps() { return _vMaps; }
	FieldMap* GetMapIndex(int index) { return _vMaps[index]; }
};

