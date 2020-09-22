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
	image		_img;				// 이미지

	int			_animationTimer;	// 애니메이션 타이머
	int			_frameX;			// 애니메이션 프레임 X
	int			_frameY;			// 애니메이션 프레임 Y

private :
	void Animation();
	void SetSpawnTime(int spawnTime) { _spawnTime = spawnTime; }
};