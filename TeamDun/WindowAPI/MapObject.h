#pragma once
/// <summary>
/// 맵툴에서 데이터용으로 사용할 오브젝트
/// </summary>
class MapTool;
class MapObject
{

public :
	int			_id;				// 오브젝트 아이디
	float		_x;					// X
	float		_y;					// Y
	float		_initX;				// 초기 X (줌 용)
	float		_initY;				// 초기 Y (줌 용)
	
	int			_spawnTime;			// 스폰 시간
	int			_page;				// 페이지

	image*		_image;				// 이미지
	int			_animationTimer;	// 애니메이션 타이머
	int			_frameX;			// 애니메이션 프레임 X
	int			_frameY;			// 애니메이션 프레임 Y
	int			_alpha;				// 이미지 알파값
	
	RECT		_body;				// 충돌 바디

	MapTool*	_mapTool;			// 맵 툴 참조용

public :
	HRESULT init(int id, float x, float y, int page);
	void update();
	void render(HDC hdc);
	void release();

	void UpdateBody();
	void Animation();
	void SetZoomPosition();
	void SetSpawnTime(int spawnTime) { _spawnTime = spawnTime; }
};