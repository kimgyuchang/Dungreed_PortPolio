#pragma once

/// <summary>
/// UIFrame은 UI의 기초가 될 뼈대이다. UI 텍스트, 스크롤, 이미지 등 UI의 모든 요소가 UIFrame을 상속하게 된다.
/// </summary>
class UIFrame
{
protected:
	// 필수 구성요소 //
	string					_name;				// 이 UI의 이름
	float					_x;					// X 위치
	float					_y;					// Y 위치
	float					_sizeX;				// X 크기
	float					_sizeY;				// Y 크기
	RECT					_interactRect;		// 이 UI가 상호작용 할 RECT
	bool					_isViewing;			// 이 UI가 Render되는지

	image*					_image;				// 이 UI에 넣을 이미지 (없으면 nullptr)
	
	// 부모자식 관련 //
	vector<UIFrame*>		_vChildFrames;		// 자식 프레임들을 벡터에 넣은 것
	map<string, UIFrame*>	_mChildFrames;		// 자식 프레임들을 맵으로 넣은 것 (검색에 이용, NAME이 Key로 들어감)
	bool					_isChild;			// 이 UI가 자식 프레임인지
	UIFrame*				_parent;			// 이 UI의 부모 프레임 (없으면 nullptr)
	
	/// 각종 기능 관련 ///

	// 스크롤 관련 //
	bool					_isOutside;			// 이 프레임이 부모 UI 틀 밖으로 빠져나왔는지 (스크롤에서 주로 사용, 빠져나오면 렌더되지 않음)
	bool					_useOutsideLimit;	// isOutside 변수를 사용할것인지
	
	// 드래그 관련 //
	bool					_isSelected;		// 클릭 등을 통해 선택된 UI인지
	bool					_isMoveToDrag;		// 드래그를 통해 이동할 수 있는	 (true일 경우 따로 set을 통해 체크해줘야함)
	int						_selectTimer;		// 얼마의 시간동안 꾸욱 눌렸는지
	float					_moveStartX;		// 드래그 이동 시작 시 맨 처음 이동 시작할 때의 마우스 포인트 X
	float					_moveStartY;		// 드래그 이동 시작 시 맨 처음 이동 시작할 때의 마우스 포인트 Y
	float					_savedX;			// 드래그 이동 시작 시 맨 처음 이동 시작할 때의 UI 위치 X
	float					_savedY;			// 드래그 이동 시작 시 맨 처음 이동 시작할 때의 UI 위치 Y

	// 렌더 관련 //
	float					_scaleX;			// 확대 스케일 X
	float					_scaleY;			// 확대 스케일 Y
	bool					_renderBeforeParent;// 부모보다 먼저 렌더될 것인지 (부모에 가려짐)

	// 타이머 관련 //
	int						_timer;				// 타이머
	bool					_isSetTimer;		// 타이머 셋팅 여부 
	// 디버깅 관련 //
	bool					_useDebug;

public:
	virtual HRESULT init(string name, float x, float y, float sizeX, float sizeY, string imageName, float scaleX = 1, float scaleY = 1);
	virtual void render(HDC hdc);
	virtual void update();
	virtual void release();

	virtual void AddChildMap(string name, UIFrame* frame) { _mChildFrames[name] = frame; } // 자식 목록 Map에 key = name, value = frame으로 넣는다.
	virtual void ToggleIsViewing();
	virtual void AddFrame(UIFrame* frame);
	
	void MoveFrame(); // 자식 포함 이동
	void MoveFrameChild(float x, float y);
	void CheckIsOutside();
	void MoveFrame(float x, float y);
	void MoveFrameToXY(float x, float y);
	void MoveY(int y) { _y += y; } // 자식 미포함 이동
	void SetIntersectRect() { _interactRect = RectMake(_x, _y, _sizeX*_scaleX, _sizeY*_scaleY); }
	void OperateViewingTimer();
	void SetViewingTimer(int timer) { _isSetTimer = true; _timer = timer; SetIsViewing(true);}

	UIFrame* GetChild(string name) { return _mChildFrames[name]; }
	void RemoveChild(string name) { _mChildFrames.erase(name); }

	float GetX() { return _x; }
	float GetY() { return _y; }
	float GetSizeX() { return _sizeX; }
	float GetSizeY() { return _sizeY; }
	string GetName() { return _name; }
	RECT GetRect() { return _interactRect; }
	vector<UIFrame*>& GetVChildFrames() { return _vChildFrames; }
	image* GetImage() { return _image; }
	float GetScaleX() { return _scaleX; }
	float GetScaleY() { return _scaleY; }

	bool GetIsOutside() { return _isOutside; }
	bool GetIsViewing() { return _isViewing; }
	bool GetUseOutsideLimit() { return _useOutsideLimit; }
	bool GetRenderBeforeParent() { return _renderBeforeParent; }

	void SetX(int x) { _x = x; }
	void SetY(int y) { _y = y; }
	void SetIsViewing(bool isViewing, bool withChild = true);
	void SetUseOutsideLimit(bool outside) { _useOutsideLimit = outside; }
	void SetIsMoveToDrag(bool drag) { _isMoveToDrag = drag; }
	void SetImage(image* target) { _image = target; }
	void SetRenderBeforeParent(bool rbp) { _renderBeforeParent = rbp; }
	void SetScaleX(float x) { _scaleX = x; }
	void SetScaleY(float y) { _scaleY = y; }
	void SetUseDebug(bool useDebug) { _useDebug = useDebug; }
};
