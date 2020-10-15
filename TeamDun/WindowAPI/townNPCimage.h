#pragma once
#include "Object.h"

//상호작용이 필요하지 않은 이미지같은 NPC 전용 클래스 입니다 (타운)

enum TOWNNPCSTATE
{
	TNS_IDLE, TNS_RUN
};
class townNPCimage : public Object
{
private:
	TOWNNPCSTATE	_state;
	bool			_isLeft;
	int				_count;
	int				_index;
public:
	virtual HRESULT init(int id, string name, OBJECTTYPE type, vector<string> imgNames);
	virtual void	update();
	virtual	void	release();
	virtual void	render(HDC hdc);
	virtual void	Animation();
};