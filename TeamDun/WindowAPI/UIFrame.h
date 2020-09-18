#pragma once

class UIFrame
{
protected:
	string				_name;
	float				_x;
	float				_y;
	float				_sizeX;
	float				_sizeY;

	image* _image;
	RECT				_interactRect;
	bool				_isChild;
	bool				_isViewing;
	vector<UIFrame*>	_vChildFrames;
	map<string, UIFrame*> _mChildFrames;
	
	UIFrame* _parent;

	bool				_isSelected;
	bool				_isOutside;
	bool				_useOutsideLimit;
	bool				_isMoveToDrag;
	int					_selectTimer;
	float				_moveStartX;
	float				_moveStartY;
	float				_savedX;
	float				_savedY;


public:

	virtual	HRESULT init(string name, float x, float y, float sizeX, float sizeY, string imageName);
	virtual void render(HDC hdc);
	virtual void update();
	virtual void release();

	virtual void AddChildMap(string name, UIFrame* frame) { _mChildFrames[name] = frame; }
	virtual void ToggleIsViewing();
	virtual void AddFrame(UIFrame* frame);

	UIFrame* GetChild(string name) { return _mChildFrames[name]; }
	float GetX() { return _x; }
	float GetY() { return _y; }
	float GetSizeX() { return _sizeX; }
	float GetSizeY() { return _sizeY; }
	string GetName() { return _name; }
	RECT GetRect() { return _interactRect; }
	vector<UIFrame*>& GetVChildFrames() { return _vChildFrames; }
	image* GetImage() { return _image; }
	bool GetIsOutside() { return _isOutside; }
	bool GetIsViewing() { return _isViewing; }
	bool GetUseOutsideLimit() { return _useOutsideLimit; }
	void SetX(int x) { _x = x; }
	void SetY(int y) { _y = y; }
	void MoveY(int y) { _y += y; }
	void SetIntersectRect() { _interactRect = RectMake(_x, _y, _sizeX, _sizeY); }
	void SetIsViewing(bool isViewing, bool withChild = true);
	void SetUseOutsideLimit(bool outside) { _useOutsideLimit = outside; }
	void SetIsMoveToDrag(bool drag) { _isMoveToDrag = drag; }
	void SetImage(image* target) { _image = target; }
	void MoveFrame();
	void MoveFrameChild(float x, float y);
	void CheckIsOutside();

};
