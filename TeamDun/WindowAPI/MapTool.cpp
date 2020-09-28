#include "stdafx.h"
#include "MapTool.h"
#include "mapScene.h"

HRESULT MapTool::init()
{

	return S_OK;
}

/// <summary>
/// 사이즈에 맞추어 맵 툴의 맵을 초기화시킨다.
/// </summary>

HRESULT MapTool::init(int width, int height)
{
	_zoomHeight = 48;
	_zoomWidth = 48;

	_useTwoLayer;	// FloodFill에서 두 레이어를 모두 사용한다
	_isLayer = true;

	for (int i = 0; i < width; i++)
	{
		vector<Grid*> gridLine;
		for (int j = 0; j < height; j++)
		{
			Grid* grid = new Grid();
			grid->_img = nullptr;
			grid->_img2 = nullptr;
			grid->_width = _zoomWidth;
			grid->_height = _zoomHeight;
			grid->_checkImg = IMAGEMANAGER->findImage("CheckImage");
			grid->_alpha = 70;
			grid->_x = j * (_zoomWidth + 2) + 0;
			grid->_y = i * (_zoomHeight + 2) + 0;
			grid->_xIndex = j;
			grid->_yIndex = i;
			grid->_rc = RectMake(grid->_x, grid->_y, _zoomWidth, _zoomHeight);
			gridLine.push_back(grid);
		}
		_vMapData.push_back(gridLine);
	}

	return S_OK;
}

void MapTool::release()
{
	for (int i = 0; i < _vMapData.size(); i++)
	{
		for (int j = 0; j < _vMapData[i].size(); j++)
		{
			SAFE_DELETE(_vMapData[i][j]);
		}
	}

	for (int i = 0; i < _vObjs.size(); i++)
	{
		SAFE_DELETE(_vObjs[i]);
	}

	SAFE_DELETE(_mapScene);

}

void MapTool::update()
{
	for (int i = 0; i < _vObjs.size(); i++)
	{
		_vObjs[i]->update();
	}
}

/// <summary>
/// 맵툴 내 그리드와의 충돌을 검사한다.
/// </summary>
Grid* MapTool::mouseCollisionCheck()
{
	int xIndex = CAMERAMANAGER->GetAbsoluteX(_ptMouse.x) / _zoomWidth;
	int yIndex = CAMERAMANAGER->GetAbsoluteY(_ptMouse.y) / _zoomHeight;

	for (int i = yIndex - 3; i < yIndex + 3; i++)
	{
		if (i < 0 || i >= _vMapData.size()) continue;
		for (int j = xIndex - 3; j < xIndex + 3; j++)
		{
			if (j < 0 || j >= _vMapData[i].size()) continue;

			if (PtInRect(&_vMapData[i][j]->_rc, CAMERAMANAGER->GetAbsolutePoint(_ptMouse.x, _ptMouse.y))
				&& !PtInRect(&UIMANAGER->GetGameFrame()->GetChild("ShortcutKeyFrame")->GetRect(), _ptMouse)
				&& !PtInRect(&UIMANAGER->GetGameFrame()->GetChild("ShortcutFrame")->GetRect(), _ptMouse)
				&& !PtInRect(&UIMANAGER->GetGameFrame()->GetChild("brushTool")->GetRect(), _ptMouse)
				&& !PtInRect(&UIMANAGER->GetGameFrame()->GetChild("brushTool")->GetChild("gridBtn")->GetRect(), _ptMouse)
				&& !PtInRect(&UIMANAGER->GetGameFrame()->GetChild("brushTool")->GetChild("objBtn")->GetRect(), _ptMouse)
				)
			{
				if (UIMANAGER->GetGameFrame()->GetChild("ShortcutFrame")->GetChild("shortcutBox7")->GetChild("ShortSizeFrame")->GetIsViewing())
				{
					if (!PtInRect(&UIMANAGER->GetGameFrame()->GetChild("ShortcutFrame")->GetChild("shortcutBox7")->GetChild("ShortSizeFrame")->GetRect(), _ptMouse))
					{
						return _vMapData[i][j];
					}
				}
				else
				{
					return _vMapData[i][j];
				}
			}
		}
	}
	return nullptr;
}

/// <summary>
/// 맵을 CSV 파일로 세이브한다.
/// </summary>
void MapTool::SaveData(string name)
{
	vector<vector<string>> stringData;

	stringData.push_back(vector<string>());
	for (int i = 0; i < _vMapData[0].size(); i++) stringData[0].push_back("-1");

	for (int i = 0; i < _vMapData.size(); i++)
	{
		stringData.push_back(vector<string>());
		for (int j = 0; j < _vMapData[i].size(); j++)
		{
			if (_vMapData[i][j]->_img) stringData[i + 1].push_back(_vMapData[i][j]->_img->getKey());
			else stringData[i + 1].push_back("-1");
		}
	}

	CSVMANAGER->csvSave("Data/MapData/" + name + ".mapData", stringData);

	vector<vector<string>> stringData2;

	stringData2.push_back(vector<string>());
	for (int i = 0; i < _vMapData[0].size(); i++) stringData2[0].push_back("-1");

	for (int i = 0; i < _vMapData.size(); i++)
	{
		stringData2.push_back(vector<string>());
		for (int j = 0; j < _vMapData[i].size(); j++)
		{
			if (_vMapData[i][j]->_img2) stringData2[i + 1].push_back(_vMapData[i][j]->_img2->getKey());
			else stringData2[i + 1].push_back("-1");
		}
	}

	CSVMANAGER->csvSave("Data/MapData/" + name + "2.mapData", stringData2);

	vector<vector<string>> stringData3;
	stringData3.push_back(vector<string>{"ID", "x", "y", "spawnTime"});
	for (int i = 0; i < _vObjs.size(); i++)
	{
		stringData3.push_back(vector<string>());
		stringData3[stringData3.size() - 1].push_back(to_string(_vObjs[i]->_id));
		stringData3[stringData3.size() - 1].push_back(to_string(_vObjs[i]->_x / _zoomWidth * 48));
		stringData3[stringData3.size() - 1].push_back(to_string(_vObjs[i]->_y / _zoomHeight * 48));
		stringData3[stringData3.size() - 1].push_back(to_string(_vObjs[i]->_spawnTime));
	}

	CSVMANAGER->csvSave("Data/MapData/" + name + "_Objs.mapData", stringData3);
}

/// <summary>
/// 이전 작업때 사용한 맵 데이터를 저장한다 (실행취소용)
/// </summary>
void MapTool::EveSaveData()
{
	for (int i = 0; i < _vMapData.size(); i++)
	{
		for (int j = 0; j < _vMapData[i].size(); j++)
		{
			//if(_vMapData[i][j]->_vBeforeImg.size() >0 && _vMapData[i][j]->_vBeforeImg[_vMapData[i][j]->_vBeforeImg.size()-1] != _vMapData[i][j]->_img)
			_vMapData[i][j]->_vBeforeImg.push_back(_vMapData[i][j]->_img);
			_vMapData[i][j]->_vBeforeImg2.push_back(_vMapData[i][j]->_img2);
		}
	}
}

/// <summary>
/// 맵을 CSV 파일로 로드한다.
/// </summary>
void MapTool::LoadData(string name)
{
	vector<vector<string>> stringData = CSVMANAGER->csvLoad("Data/MapData/" + name + ".mapData");
	vector<vector<string>> stringData2 = CSVMANAGER->csvLoad("Data/MapData/" + name + "2.mapData");
	if (stringData.size() == 0 && stringData2.size() == 0) return;
	_vMapData.clear();

	for (int i = 0; i < stringData.size(); i++)
	{
		vector<Grid*> gridLine;
		for (int j = 0; j < stringData[i].size(); j++)
		{
			Grid* grid = new Grid();
			if (stringData[i][j] == "-1") grid->_img = nullptr;
			else grid->_img = IMAGEMANAGER->findImage(stringData[i][j]);

			if (stringData2[i][j] == "-1") grid->_img2 = nullptr;
			else grid->_img2 = IMAGEMANAGER->findImage(stringData2[i][j]);
			grid->_x = j * _zoomWidth + 0;
			grid->_y = i * _zoomHeight + 0;
			grid->_checkImg = IMAGEMANAGER->findImage("CheckImage");
			grid->_xIndex = j;
			grid->_yIndex = i;
			grid->_alpha = 70;
			grid->_checkImg = IMAGEMANAGER->findImage("CheckImage");
			grid->_rc = RectMake(grid->_x, grid->_y, _zoomWidth, _zoomHeight);
			gridLine.push_back(grid);

		}
		_vMapData.push_back(gridLine);
	}

	_vObjs.clear();
	vector<vector<string>> objData = CSVMANAGER->csvLoad("Data/MapData/" + name + "_Objs.mapData");
	for (int i = 0; i < objData.size(); i++)
	{
		MapObject* obj = new MapObject();
		obj->init(stoi(objData[i][0]), stoi(objData[i][1]) * _zoomWidth / 48, stoi(objData[i][2]) * _zoomHeight / 48, 0);
		obj->_initX = stoi(objData[i][1]);
		obj->_initY = stoi(objData[i][2]);
		obj->_spawnTime = stoi(objData[i][3]);
		obj->_alpha = 255;
		obj->_mapTool = this;
		_vObjs.push_back(obj);
	}
}

/// <summary>
/// 이전 작업때 사용한 맵 데이터를 가져온다. (실행취소용)
/// </summary>
void MapTool::EveLoadData()
{
	for (int i = 0; i < _vMapData.size(); i++)
	{
		for (int j = 0; j < _vMapData[i].size(); j++)
		{
			if (_vMapData[i][j]->_vBeforeImg.size() > 0)
			{
				_vMapData[i][j]->_img = _vMapData[i][j]->_vBeforeImg[_vMapData[i][j]->_vBeforeImg.size() - 1];
				_vMapData[i][j]->_vBeforeImg.erase(_vMapData[i][j]->_vBeforeImg.end() - 1);
			}
			if (_vMapData[i][j]->_vBeforeImg2.size() > 0)
			{
				_vMapData[i][j]->_img2 = _vMapData[i][j]->_vBeforeImg2[_vMapData[i][j]->_vBeforeImg2.size() - 1];
				_vMapData[i][j]->_vBeforeImg2.erase(_vMapData[i][j]->_vBeforeImg2.end() - 1);
			}
		}
	}
}

/// <summary>
/// 맵 툴에 행 한 줄을 추가한다.
/// </summary>
void MapTool::MapLineAddRow()
{
	vector<Grid*> gridLine;
	for (int j = 0; j < _vMapData[0].size(); j++)
	{
		Grid* grid = new Grid();
		grid->_img = nullptr;
		grid->_x = j * (_zoomWidth + (2 * _zoomWidth / 48));
		grid->_y = _vMapData.size() * (_zoomHeight + (2 * _zoomHeight / 48));
		grid->_xIndex = j;
		grid->_yIndex = _vMapData.size();
		grid->_checkImg = IMAGEMANAGER->findImage("CheckImage");
		grid->_alpha = 70;
		grid->_rc = RectMake(grid->_x, grid->_y, _zoomWidth, _zoomHeight);
		gridLine.push_back(grid);
	}

	_vMapData.push_back(gridLine);
}

/// <summary>
/// 맵 툴에 열 한 줄을 추가한다.
/// </summary>
void MapTool::MapLineAddCol()
{
	for (int i = 0; i < _vMapData.size(); i++)
	{
		Grid* grid = new Grid();
		grid->_img = nullptr;
		grid->_x = _vMapData[i].size() * (_zoomWidth + (2 * _zoomWidth / 48));
		grid->_y = i * (_zoomWidth + (2 * _zoomHeight / 48));
		grid->_xIndex = _vMapData[i].size();
		grid->_yIndex = i;
		grid->_checkImg = IMAGEMANAGER->findImage("CheckImage");
		grid->_alpha = 70;
		grid->_rc = RectMake(grid->_x, grid->_y, _zoomWidth, _zoomHeight);
		_vMapData[i].push_back(grid);
	}
}

/// <summary>
/// 맵 툴에 행 한 줄을 삭제한다.
/// </summary>
void MapTool::MapLineRemoveRow()
{
	if (_vMapData.size() > 1)
	{
		_vMapData.erase(_vMapData.end() - 1);
	}
}

/// <summary>
/// 맵 툴에 열 한 줄을 삭제한다.
/// </summary>
void MapTool::MapLineRemoveCol()
{
	if (_vMapData[0].size() > 1)
	{
		for (int i = 0; i < _vMapData.size(); i++)
		{
			_vMapData[i].erase(_vMapData[i].end() - 1);
		}
	}
}

/// <summary>
/// 처음부터 끝까지 전체를 타겟 이미지로 덮어씌운다.
/// </summary>
void MapTool::FillAll()
{
	if (_isLayer)
	{
		for (int i = 0; i < _vMapData.size(); i++)
		{
			for (int j = 0; j < _vMapData[i].size(); j++)
			{
				_vMapData[i][j]->_img = _mapScene->GetTargetImage();
			}
		}
	}
	else
	{
		for (int i = 0; i < _vMapData.size(); i++)
		{
			for (int j = 0; j < _vMapData[i].size(); j++)
			{
				_vMapData[i][j]->_img2 = _mapScene->GetTargetImage();
			}
		}
	}
}

/// <summary>
/// FloodFill을 통해 범위를 채운다.
/// </summary>
/// <param name="targetImage">채울 이미지</param>
/// <param name="indexX">현재 검사대상인 X Index</param>
/// <param name="indexY">현재 검사대상인 Y Index</param>

void MapTool::FloodFill(image* targetImage, int indexX, int indexY)
{
	if (_mapScene->GetTargetImage() == nullptr) return;
	if (_isLayer)
	{
		vector<POINT>FloodFilllist;
		POINT pt;
		pt.x = indexX;
		pt.y = indexY;
		FloodFilllist.push_back(pt);
		if (_vMapData[indexY][indexX]->_img != _mapScene->GetTargetImage())
		{
			_vMapData[indexY][indexX]->_img = _mapScene->GetTargetImage();

			while (FloodFilllist.size() > 0)
			{
				int indexX = FloodFilllist[0].x;
				int indexY = FloodFilllist[0].y;

				if (indexX + 1 < _vMapData[0].size() && targetImage == _vMapData[indexY][indexX + 1]->_img
					&& (_useTwoLayer ? (targetImage == _vMapData[indexY][indexX + 1]->_img2 || nullptr == _vMapData[indexY][indexX + 1]->_img2) : true))
				{
					FloodFilllist.push_back(POINT{ indexX + 1,indexY });
					_vMapData[indexY][indexX + 1]->_img = _mapScene->GetTargetImage();

				}
				if (indexX - 1 >= 0 && targetImage == _vMapData[indexY][indexX - 1]->_img
					&& (_useTwoLayer ? (targetImage == _vMapData[indexY][indexX - 1]->_img2 || nullptr == _vMapData[indexY][indexX - 1]->_img2) : true))
				{
					FloodFilllist.push_back(POINT{ indexX - 1,indexY });
					_vMapData[indexY][indexX - 1]->_img = _mapScene->GetTargetImage();
				}
				if (indexY + 1 < _vMapData.size() && targetImage == _vMapData[indexY + 1][indexX]->_img
					&& (_useTwoLayer ? (targetImage == _vMapData[indexY + 1][indexX]->_img2 || nullptr == _vMapData[indexY + 1][indexX]->_img2) : true))
				{
					FloodFilllist.push_back(POINT{ indexX,indexY + 1 });
					_vMapData[indexY + 1][indexX]->_img = _mapScene->GetTargetImage();
				}
				if (indexY - 1 >= 0 && targetImage == _vMapData[indexY - 1][indexX]->_img
					&& (_useTwoLayer ? (targetImage == _vMapData[indexY - 1][indexX]->_img2 || nullptr == _vMapData[indexY - 1][indexX]->_img2) : true))
				{
					FloodFilllist.push_back(POINT{ indexX,indexY - 1 });
					_vMapData[indexY - 1][indexX]->_img = _mapScene->GetTargetImage();
				}
				FloodFilllist.erase(FloodFilllist.begin());
			}
		}
	}
	else
	{
		vector<POINT>FloodFilllist;
		POINT pt;
		pt.x = indexX;
		pt.y = indexY;
		FloodFilllist.push_back(pt);
		if (_vMapData[indexY][indexX]->_img2 != _mapScene->GetTargetImage())
		{
			_vMapData[indexY][indexX]->_img2 = _mapScene->GetTargetImage();
			while (FloodFilllist.size() > 0)
			{
				int indexX = FloodFilllist[0].x;
				int indexY = FloodFilllist[0].y;

				if (indexX + 1 < _vMapData[0].size() && targetImage == _vMapData[indexY][indexX + 1]->_img2
					&& (_useTwoLayer ? (targetImage == _vMapData[indexY][indexX + 1]->_img || nullptr == _vMapData[indexY][indexX + 1]->_img) : true))
				{
					FloodFilllist.push_back(POINT{ indexX + 1,indexY });
					_vMapData[indexY][indexX + 1]->_img2 = _mapScene->GetTargetImage();

				}
				if (indexX - 1 >= 0 && targetImage == _vMapData[indexY][indexX - 1]->_img2
					&& (_useTwoLayer ? (targetImage == _vMapData[indexY][indexX - 1]->_img || nullptr == _vMapData[indexY][indexX - 1]->_img) : true))
				{
					FloodFilllist.push_back(POINT{ indexX - 1,indexY });
					_vMapData[indexY][indexX - 1]->_img2 = _mapScene->GetTargetImage();

				}
				if (indexY + 1 < _vMapData.size() && targetImage == _vMapData[indexY + 1][indexX]->_img2
					&& (_useTwoLayer ? (targetImage == _vMapData[indexY + 1][indexX]->_img || nullptr == _vMapData[indexY + 1][indexX]->_img) : true))
				{
					FloodFilllist.push_back(POINT{ indexX,indexY + 1 });
					_vMapData[indexY + 1][indexX]->_img2 = _mapScene->GetTargetImage();
				}
				if (indexY - 1 >= 0 && targetImage == _vMapData[indexY - 1][indexX]->_img2
					&& (_useTwoLayer ? (targetImage == _vMapData[indexY - 1][indexX]->_img || nullptr == _vMapData[indexY - 1][indexX]->_img) : true))
				{
					FloodFilllist.push_back(POINT{ indexX,indexY - 1 });
					_vMapData[indexY - 1][indexX]->_img2 = _mapScene->GetTargetImage();
				}
				FloodFilllist.erase(FloodFilllist.begin());
			}
		}
	}

	return;
}

void MapTool::PreviewGridRange(int startIndexX, int startIndexY, int indexX, int indexY, int alpha)
{
	int temp;
	if (indexX < startIndexX)
	{
		temp = startIndexX;
		startIndexX = indexX;
		indexX = temp;
	}
	if (indexY < startIndexY)
	{
		temp = startIndexY;
		startIndexY = indexY;
		indexY = temp;
	}

	for (int i = 0; i < _vMapData.size(); i++)
	{
		for (int j = 0; j < _vMapData[i].size(); j++)
		{
			_vMapData[i][j]->_alpha = 30;
		}
	}
	for (int j = startIndexY; j <= indexY; j++)
	{
		for (int i = startIndexX; i <= indexX; i++)
		{
			_vMapData[j][i]->_alpha = alpha;
		}
	}
}

/// <summary>
/// x부터 x1, y부터 y1까지의 범위를 채운다.
/// </summary>
void MapTool::GridRange(float x, float y, float x1, float y1)
{
	int temp;
	if (x1 < x)
	{
		temp = x;
		x = x1;
		x1 = temp;
	}

	if (y1 < y)
	{
		temp = y;
		y = y1;
		y1 = temp;
	}
	if (_isLayer)
	{
		for (int i = x; i <= x1; i++)
		{
			for (int j = y; j <= y1; j++)
			{
				_vMapData[j][i]->_img = _mapScene->GetTargetImage();
			}
		}
	}
	else
	{
		for (int i = x; i <= x1; i++)
		{
			for (int j = y; j <= y1; j++)
			{
				_vMapData[j][i]->_img2 = _mapScene->GetTargetImage();
			}
		}
	}
}

void MapTool::SetMap()
{
	for (int i = 0; i < _vMapData.size(); i++)
	{
		for (int j = 0; j < _vMapData[i].size(); j++)
		{
			_vMapData[i][j]->_x = j * (_zoomWidth + (2 * _zoomWidth / 48)) + 0;
			_vMapData[i][j]->_y = i * (_zoomHeight + (2 * _zoomHeight / 48)) + 0;
			_vMapData[i][j]->_rc = RectMake(_vMapData[i][j]->_x, _vMapData[i][j]->_y, _zoomWidth, _zoomHeight);
		}
	}

	for (int i = 0; i < _vObjs.size(); i++)
	{
		_vObjs[i]->SetZoomPosition();
	}
}

void MapTool::render()
{
	for (int i = ((CAMERAMANAGER->GetPivotY() - (WINSIZEY / 2)) / (_zoomHeight == 0 ? 48 : _zoomHeight)); i < ((CAMERAMANAGER->GetPivotY() + (WINSIZEY / 2)) / (_zoomHeight == 0 ? 48 : _zoomHeight)); i++)
	{
		if (i < 0 || i >= _vMapData.size()) continue;
		for (int j = ((CAMERAMANAGER->GetPivotX() - (WINSIZEX / 2)) / (_zoomWidth == 0 ? 48 : _zoomWidth)); j < ((CAMERAMANAGER->GetPivotX() + (WINSIZEX / 2)) / (_zoomWidth == 0 ? 48 : _zoomWidth)); j++)
		{
			if (j < 0 || j >= _vMapData[i].size()) continue;
			if (_vMapData[i][j]->_img2) CAMERAMANAGER->StretchAlphaRender(getMemDC(), _vMapData[i][j]->_img2, _vMapData[i][j]->_x, _vMapData[i][j]->_y, (_zoomWidth == 0 ? 48 : _zoomWidth) / 48, (_zoomHeight == 0 ? 48 : _zoomHeight) / 48, _isLayer ? 100 : 255);
			if (_vMapData[i][j]->_img) CAMERAMANAGER->StretchAlphaRender(getMemDC(), _vMapData[i][j]->_img, _vMapData[i][j]->_x, _vMapData[i][j]->_y, (_zoomWidth == 0 ? 48 : _zoomWidth) / 48, (_zoomHeight == 0 ? 48 : _zoomHeight) / 48, _isLayer ? 255 : 100);
			string str = to_string(i) + " " + to_string(j);
			CAMERAMANAGER->StretchAlphaRender(getMemDC(), _vMapData[i][j]->_checkImg, _vMapData[i][j]->_x, _vMapData[i][j]->_y, (_zoomWidth == 0 ? 48 : _zoomWidth) / 48, (_zoomHeight == 0 ? 48 : _zoomHeight) / 48, _vMapData[i][j]->_alpha);
		}
	}

	for (int i = 0; i < _vObjs.size(); i++)
	{
		_vObjs[i]->render(getMemDC());
	}
}