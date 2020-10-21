#pragma once
class cameraText
{
private:
	float _x;
	float _y;
	float _xSize;
	float _ySize;
	string _text;
	FONT _font;
	WORDSIZE _size;
	WORDSORT _sort;
	COLORREF _color;
	int _count;
	bool _isDead;

public:
	HRESULT init(float x, float y, float xSize, float ySize, string text, FONT font, WORDSIZE size, WORDSORT sort = WORDSORT::WSORT_LEFT, COLORREF color = RGB(255, 255, 255));
	void update();
	void release();
	void render(HDC hdc);
	void deleteText();

	bool getIsDead() {return _isDead;}


};

