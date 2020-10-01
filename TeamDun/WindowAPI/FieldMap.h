#pragma once

struct Tile
{
	int		_x;					// X 위치
	int		_y;					// Y 위치
	image* _img;				// IMAGE
	image* _img2;				// IMAGE2
	image* _collisionImage;		// 픽셀충돌 이미지
};

class FieldMap
{
private :
	string					_fileName;			// 파일 이름 (맵 이름)
	vector<vector<Tile*>>	_vMapData;			// 맵 그리드 이중 벡터
	vector<Object*>			_vObjs;				// 해당 방에 존재하는 오브젝트들
	vector<RECT>			_vMiniRc;			// 미니맵용 Rects
												   
	int						_nextMapIndex[4];	// 다음 방의 Vector Index (방향별)
	int						_stage;				// 해당 방의 스테이지
												   
	bool					_isCleared;			// 방의 몬스터를 모두 처리했는지 여부
												
	bool					_isSpawning;		// 스폰 중
	int						_spawnTimer;		// 몬스터 스폰용 타이머

public :
	void LoadMap();

	void MakeDoor(Door* door);

	void PixelCollisionMapGenerate();

	void GridMapGenerate();

	HRESULT init(string fileName);
	virtual void update();
	virtual void release();
	virtual void render(HDC hdc);

	void SpawnMonsters();
	
	// GETSET //
	string	GetFileName()					{ return _fileName; }
	void	SetIsSpawning(bool isSpawning)	{ _isSpawning = isSpawning; }
	void	SetStage(int stage)				{ _stage = stage; }
};