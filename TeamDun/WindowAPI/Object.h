#pragma once
#include "gameNode.h"

enum OBJECTTYPE
{
	OT_PLAYER, OT_MONSTER, OT_NPC
};

class Object : public gameNode
{
public :
	float		_x;				// 위치 X 
	float		_y;				// 위치 Y
	OBJECTTYPE	_type;			// 오브젝트 타입
	int			_spawnTime;		// 스폰 시간
};

