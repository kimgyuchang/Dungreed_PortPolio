#pragma once
#include "singletonBase.h"
#include "Stage.h"
#include "StageChanger.h"

/// <summary>
/// GetFastPixel을 하기 위한 비트맵 데이터 저장용 PixelGetter
/// </summary>
class PixelGetter 
{
public :
	BYTE* pData;
	BITMAP bmInfo;
	int mapSize;
	int byteSize;
};

class MapManager : public singletonBase<MapManager>
{
private:

	int						_uidCount;			// UID NUMBER
	vector<FieldMap*>		_vOriginMaps;		// 데이터로 불러온 맵들

	Stage*					_stage;				// 현재 스테이지
	int						_curStageNum;		// 현재 스테이지 번호
	int						_currentMap;		// 현재 맵
	FIELDMAPTYPE			_prevMapType;		// 이전 맵 타입
	int						_prevMapIndex;		// 이전 맵 번호

	// MAP UI 관련 //
	int						_moveClickTimer;	
	POINT					_recentMousePos;
	PixelGetter*			_pixelGetter;
	bool					_portalOn;
	bool					_portalAnimOn;
	UIFrame*				_mapFrame;
	Portal*					_currentPortal;
	vector<vector<string>>	_mapData;
	StageChanger*			_stageChanger;

	// 스테이지 지나가는 텍스트 //
	float					_stageNameSpeedX;
	float					_stageNameGravity;
	UIText*					_stageNameText;
	bool					_stageTextMoving;
	int						_textMovingStartTimer;
	int						_textMovingMoveTimer;

public:
	// 기본 //
	HRESULT init();
	void update();
	void GameResetter();
	void MapRandomChanger();
	void release();
	void render(HDC hdc);
	
	// 스테이지 & 맵 변경 //
	void ClearStage(int cntStage);
	void MoveStage(int stageNum);
	void ChangeMap(int index);
	void SetPrevMapVariables();
	void ClearChangeMapVectors();
	void AdjustFirstVisitMap();
	void ChangeMapBGM(FIELDMAPTYPE prevMapType);
	void CameraLimitChecker();
	void GenerateMapParticle();

	// UI //
	void UsePortalMap();
	void ReNewMapUI();
	void SetMapUIOnOff();
	void DungeonMapUIMover();
	void MoveStageText();

	// GETSET //
	int					GetCurrentMap()		{ return _currentMap; }
	FieldMap*			GetPlayMap()		{ return _stage->GetMaps()[_currentMap]; }
	vector<FieldMap*>&	GetMaps()			{ return _vOriginMaps; }
	PixelGetter*		GetPixelGetter()	{ return _pixelGetter; }
	bool				GetPortalOn()		{ return _portalOn; }
	bool				GetPortalAnimOn()	{ return _portalAnimOn; }
	Portal*				GetCurrentPortal()	{ return _currentPortal; }
	int					GetCurStageNum()	{ return _curStageNum; }
	StageChanger*		GetStageChanger()	{ return _stageChanger; }
	int					GetUid()			{ return _uidCount; }
	
	void		SetUid(int uid)				{ _uidCount = uid; }
	void 		SetCurrentMap(int map)		{ _currentMap = map; }
	void		SetPortalOn(bool on)		{ _portalOn = on; }
	void		SetCurrentPortal(Portal* p) { _currentPortal = p; }
	void		SetPortalAnimOn(bool on)	{ _portalAnimOn = on; }
};


