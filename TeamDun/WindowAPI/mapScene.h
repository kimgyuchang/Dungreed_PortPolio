#pragma once
#include "uibrushTool.h"
#include "MapTool.h"
enum BRUSHTYPE
{
	BT_NOFUNC, BT_PAINT, BT_ERASE, BT_FILLRECT, BT_FLOODFILL
};

class mapScene : public gameNode
{
private:
	// UI BRUSH 관련 //
	uibrushTool*	_uiBrushTool;

	// MAP TOOL 관련 //
	MapTool*		_mapTool;
	image*			_targetImage;
	MapObject*		_targetObject;

	// FILL RANGE 관련 //
	bool			_isFillClicked;
	POINT			_clickedPointOne;
	POINT			_clickedPointTwo;

	// 초기 사이즈 설정 관련 //
	int				_heightNum;
	int				_widthNum;
	bool			_isSettingPage;

	// 회전 관련 (테스트용) //
	int				_rotateTester;
	int				_rotTimer;

	POINT			_pivot;

	// 몬스터 관련 //
	bool			_isMonsterSettingOn;
	char			_spawnTime[100];
	int				_currentMonsterIndex;

	// 세이브 로드용 //
	bool			_isEditorViewing;
	char			_fileName[128];
	bool			_isLoad;

	// 클릭 관련 //
	bool			_isLeftClicked;
	bool			_isRightClicked;
	bool			_isEnterPressed;
	BRUSHTYPE		_brushType;
	
	// UI 관련 //
	bool			_isSizeAdjustOpened;
public :
	HRESULT init();
	void UIInit();
	void release();
	void update();
	void SetMonsterPage();
	void InMonsterSetPage();
	void PlaceObject();
	void EraseObject();
	void InputCheck();
	void SetMapSize();
	void CallSaveEditor();
	void RemovePaint();
	void UpdateFillSquareRange();
	void ToolMovePage();
	void FillSquareRange();
	void CheckShortCutBtnCollision();
	void DoClickByType();
	void PaintSaver();
	void EraseSaver();
	void Paint();
	void FloodFill();
	void FillAll();
	void GetUiBrush();
	void CallLoadEditor();
	void AddMapLine(int type);
	void Undo();
	void render();
	void CameraMove();
	void SaveLoadMap();
	void ShortcutKey();
	void SwitchSizeFrame();
	
	// GETSET //
	image* GetTargetImage() { return _targetImage; }
	void SetTargetImage(image* img) { _targetImage = img; }
	MapObject* GetTargetObject() { return _targetObject; }
	void SetTargetObject(MapObject* obj) { _targetObject = obj; }

	void SaveShortcutKey();
	void LoadShortcutKey();
	void SetLayer();
	void ZoomInOut();
};

