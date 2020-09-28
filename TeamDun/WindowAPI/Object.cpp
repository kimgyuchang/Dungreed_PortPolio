#include "stdafx.h"
#include "Object.h"

HRESULT Object::init(int id, string name, OBJECTTYPE type, vector<string> imgNames)
{
    _id = id;
    _name = name;
    _type = type;
    
    for (int i = 0; i < imgNames.size(); i++)
    {
        if (imgNames[i] != ".")
        {
            _vImages.push_back(IMAGEMANAGER->findImage(imgNames[i]));
        }
    }

    _x = 0;
    _y = 0;
    _spawnTime = 0;
    
    _frameX = 0;
    _frameY = 0;
    _useImage = 0;
    return S_OK;
}

void Object::update()
{
}

void Object::release()
{
}

void Object::render(HDC hdc)
{
}
