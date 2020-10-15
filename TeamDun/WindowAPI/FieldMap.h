#pragma once

struct Tile
{
	int		_x;					// X 위치
	int		_y;					// Y 위치
	image* _img;				// IMAGE
	image* _img2;				// IMAGE2
	image* _collisionImage;		// 픽셀충돌 이미지
};

enum FIELDMAPTYPE
{
	FMT_ENTER, FMT_END, FMT_RESTAURANT, FMT_SHOP, FMT_TEMPLE, FMT_NORMAL
};
class Portal;
class FieldMap
{
private :
	int						_xIndex;			// 위치 X
	int						_yIndex;			// 위치 Y
	string					_fileName;			// 파일 이름 (맵 이름)
	vector<vector<Tile*>>	_vMapData;			// 맵 그리드 이중 벡터
	vector<Object*>			_vObjs;				// 해당 방에 존재하는 오브젝트들
	vector<RECT>			_vMiniRc;			// 미니맵용 Rects
	vector<RECT>			_vMiniObjRc;		// 미니맵용 오브젝트 Rects
	image*					_backImageEtc;		// 기타 패턴 이미지
	image*					_backImageMain;		// 메인 배경이미지
	image*					_townBackgroundImg;	// 타운 백그라운드 이미지
	image*					_townMountainImg;	// 타운 산 이미지
	image*					_townGrassImg;		// 타운 풀 이미지
	FIELDMAPTYPE			_mapType;			// 맵 타입
	int						_nextMapIndex[4];	// 다음 방의 Vector Index (방향별)
	POINT					_mapMovePos[4];		// 이 방으로 도착할때의 플레이어 위치
	int						_stage;				// 해당 방의 스테이지
												   
	bool					_isCleared;			// 방의 몬스터를 모두 처리했는지 여부	
	bool					_isSpawning;		// 스폰 중
	bool					_mapGenVisited;		// 맵 제작시 플러드필 체크용 
	bool					_visited;			// 방문했는지 여부
	int						_spawnTimer;		// 몬스터 스폰용 타이머
	
	Portal*					_portal;			// 이 맵의 포탈

public :
	void LoadMap();

	void LoadObject();

	void MakeNearTileCollision(Door* door, bool isActivate);

	void MakeDoor(Door* door);
	void PixelCollisionMapGenerate();
	void GridMapGenerate();

	HRESULT init(string fileName);
	virtual void update();
	virtual void release();
	virtual void render(HDC hdc);

	void DoorParticleGenerate();

	void ShotObject();
	void ChangePlayerByDirection(DIRECTION dir);
	void SetDoorSpawning();
	void SpawnMonsters();
	void CheckNoMonsterInMap();
	void EraseDeathObject();
	
	// GETSET //
	int					GetMapSizeY()					{ return _vMapData.size(); }
	int					GetMapSizeX()					{ return _vMapData[0].size(); }
	int					GetXIndex()						{ return _xIndex; }
	int					GetYIndex()						{ return _yIndex; }
	string				GetFileName()					{ return _fileName; }
	bool				GetIsCleared()					{ return _isCleared; }
	vector<Object*>&	GetObjects()					{ return _vObjs; }	
	FIELDMAPTYPE		GetFieldMapType()				{ return _mapType; }
	int					GetStage()						{ return _stage; }
	POINT				GetMovePos(DIRECTION dir)		{ return _mapMovePos[(int)dir]; }		
	int					GetNextMapIndex(DIRECTION dir)	{ return _nextMapIndex[(int)dir]; }
	bool				GetMapGenVisited()				{ return _mapGenVisited; }
	bool				GetVisited()					{ return _visited; }
	Portal*				GetPortal()						{ return _portal; }

	void	SetXIndex(int index)						{ _xIndex = index; }
	void	SetYIndex(int index)						{ _yIndex = index; }
	void	SetIsSpawning(bool isSpawning)				{ _isSpawning = isSpawning; }
	void	SetStage(int stage)							{ _stage = stage; }
	void	SetFieldType(FIELDMAPTYPE type)				{ _mapType = type; }
	void	SetNextMapIndex(DIRECTION dir, int index)	{ _nextMapIndex[(int)dir] = index; }
	void	SetMovePos(DIRECTION dir, POINT pos)		{ _mapMovePos[(int)dir] = pos; }
	void	SetMapGenVisited(bool visit)				{ _mapGenVisited = visit; }
	void	SetVisited(bool visit)						{ _visited = visit; }
	void	SetPortal(Portal* portal)					{ _portal = portal; }
};