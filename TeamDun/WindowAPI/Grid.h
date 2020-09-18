#pragma once

class Grid
{
private:
	RECT _rc;
	int _x;
	int _y;
	string _igKey;
	image* _ig;

public:
	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	image* GetImage() { return _ig; }
	RECT GetRect() { return _rc; }
	int GetX() { return _x; }
	int GetY() { return _y; }
	string GetIgKey() { return _igKey; }

	void SetImage(image* ig) { this->_ig = ig; }
	void SetRect(RECT rc) { this->_rc = rc; }
	void SetX(int x) { this->_x = x; }
	void SetY(int y) { this->_y = y; }
	void SetIgKey(string key) { this->_igKey = _igKey; }
};

