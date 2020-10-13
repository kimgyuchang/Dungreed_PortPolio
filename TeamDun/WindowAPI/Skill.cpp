#include "stdafx.h"
#include "Skill.h"

HRESULT Skill::init(int id, string name, float coolTime, string description, string imageName)
{
    _id = id;
    _name = name;
    _coolTime = coolTime;
    _description = description;
    _imageName = imageName;
    _image = IMAGEMANAGER->findImage(imageName);

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
