#pragma once

/// <summary>
/// 맵툴에서 데이터용으로 사용할 오브젝트
/// </summary>
class MapObject
{
public :
	int			_id;				// 오브젝트 아이디
	float		_x;					// X
	float		_y;					// Y
	int			_spawnTime;			// 스폰 시간
	int			_page;				// 페이지

	image*		_image;
	int			_animationTimer;	// 애니메이션 타이머
	int			_frameX;			// 애니메이션 프레임 X
	int			_frameY;			// 애니메이션 프레임 Y
	int			_alpha;

public :
	HRESULT init(int id, float x, float y, int page);
	void update();
	void render(HDC hdc);
	void release();

	void Animation();
	void SetSpawnTime(int spawnTime) { _spawnTime = spawnTime; }
};