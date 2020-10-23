#include "stdafx.h"
#include "Skill.h"
#include "Item.h"

HRESULT Skill::init()
{
    return S_OK;
}

void Skill::update()
{
}

void Skill::release()
{
}

void Skill::render(HDC hdc)
{
}

void Skill::Activate()
{
}

void Skill::CoolTimeChecker()
{
    if (_curCoolTime > 0)
    {
        _curCoolTime--;
    }
}
