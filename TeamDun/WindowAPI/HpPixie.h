#pragma once
enum PIXIETYPE
{
	SMALL, MIDDLE, LARGE, XLARGE, GREEN
};

class HpPixie : public DropObjs
{
protected:
	PIXIETYPE _pixType;

public:

	HRESULT init(int id, string name, OBJECTTYPE type, vector<string> imgNames);
	void update();
	void release();
	void render(HDC hdc);
	void Animation();
	void CheckCollision();
	
	void SetPixType(PIXIETYPE type) { _pixType = type; }
};


