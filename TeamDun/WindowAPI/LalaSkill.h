#pragma once
#include "Skill.h"
class LalaSkill : public Skill
{
private:
public:
	HRESULT init();
	virtual void update();
	virtual void release();
	virtual void render(HDC hdc);

	void Activate();
};
