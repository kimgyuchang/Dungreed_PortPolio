#include "stdafx.h"
#include "Stage.h"


HRESULT Stage::init(int stage)
{
	_stage = stage;
	_numOfFloodFillCount = 0;
	return S_OK;
}

void Stage::update()
{
	_cntMap->update();
}

void Stage::release()
{
}

void Stage::render(HDC hdc)
{
	_cntMap->render(hdc);
}

int Stage::FindSameIndex(int indexX, int indexY, int curIndex)
{
	for (int i = 0; i < _vMaps.size(); i++)
	{
		if (curIndex == i) continue;
		FieldMap* map = _vMaps[i];
		if (map->GetXIndex() == indexX && map->GetYIndex() == indexY)
		{
			return i;
		}
	}

	return -1;
}

int Stage::GetConnectedRoomCount(FieldMap* map, int index)
{
	int numOfNextRoom = 0;
	if (FindSameIndex(map->GetXIndex() + 1, map->GetYIndex(), index) != -1) numOfNextRoom++;
	if (FindSameIndex(map->GetXIndex() - 1, map->GetYIndex(), index) != -1) numOfNextRoom++;
	if (FindSameIndex(map->GetXIndex(), map->GetYIndex() + 1, index) != -1) numOfNextRoom++;
	if (FindSameIndex(map->GetXIndex(), map->GetYIndex() - 1, index) != -1) numOfNextRoom++;

	return numOfNextRoom;
}

void Stage::AddRooms()
{
	int rand[5];
	rand[0] = RANDOM->range(5) + 2;
	for (int i = 1; i < 5; i++) rand[i] = rand[i - 1] + RANDOM->range(5) + 2;

	for (int i = 0; i < MAPMANAGER->GetMaps().size(); i++)
	{
		FieldMap* map = MAPMANAGER->GetMaps()[i];

		if (map->GetStage() == _stage)
		{
			map->SetXIndex(0);
			map->SetYIndex(0);
			_vMaps.push_back(map);
		}
	}

	while (true)
	{
		for (int i = 0; i < _vMaps.size(); i++)
		{
			FieldMap* map = _vMaps[i];

			int n = RANDOM->range(rand[4]);
			if (FindSameIndex(map->GetXIndex(), map->GetYIndex(), i) != -1)
			{
				if (n < rand[0]) map->SetXIndex(map->GetXIndex() - 1);
				else if (n < rand[1]) map->SetXIndex(map->GetXIndex() + 1);
				else if (n < rand[2]) map->SetYIndex(map->GetYIndex() - 1);
				else if (n < rand[3]) map->SetYIndex(map->GetYIndex() + 1);
			}

			if (CheckCollision()) break;
		}

		if (CheckCollision()) break;
	}
}

void Stage::CheckFloodFill(int index, int& numOfCheckRoom)
{
	FieldMap* map = _vMaps[index];
	map->SetMapGenVisited(true);
	for (int i = 0; i < 4; i++)
	{
		int nextIndex = map->GetNextMapIndex((DIRECTION)i);
		if (nextIndex != -1 && !_vMaps[nextIndex]->GetMapGenVisited())
		{
			numOfCheckRoom++;
			CheckFloodFill(nextIndex, numOfCheckRoom);
		}
	}
}

bool Stage::FloodFillStart()
{
	_numOfFloodFillCount++;
	
	int numOfCheckRoom = 1;
	CheckFloodFill(0, numOfCheckRoom);
	
	if (numOfCheckRoom != _vMaps.size()) return false;
	else return true;
}

void Stage::AddRoomConnections()
{
	while (true)
	{
		for (int i = 0; i < _vMaps.size(); i++)
		{
			if (_vMaps.size() == 1) break;
			FieldMap* map = _vMaps[i];

			int numOfNextRoom = GetConnectedRoomCount(map, i);

			while (true)
			{
				int numOfLinedRoom = 0;
				for (int i = 0; i < 4; i++) if (map->GetNextMapIndex((DIRECTION)i) != -1) numOfLinedRoom++;
				if (numOfLinedRoom == numOfNextRoom) break;

				int count = 0;
				for (int j = 0; j < 4; j++)
				{
					int n = RANDOM->range(10);
					if (n < 3)
					{
						if (map->GetNextMapIndex((DIRECTION)j) == -1)
						{
							if (AddLine(map, (DIRECTION)j, i))
								count++;
						}
					}
				}
				if (count != 0) break;
			}
		}

		if (FloodFillStart()) break;
		if (_numOfFloodFillCount > 5) break;
	}
}


bool Stage::SettingMap()
{
	AddRooms();
	AddRoomConnections();

	if (_numOfFloodFillCount > 5) return false;

	for (int i = 0; i < _vMaps.size(); i++)
	{
		_vMaps[i]->LoadObject();
	}

	return true;
}

bool Stage::AddLine(FieldMap* map, DIRECTION dir, int index)
{
	int result;

	switch (dir)
	{
	case DIRECTION::DIR_DOWN:
		result = FindSameIndex(map->GetXIndex(), map->GetYIndex() + 1, index);
		if (result != -1)
		{
			_vMaps[result]->SetNextMapIndex(DIRECTION::DIR_UP, index);
			map->SetNextMapIndex(DIRECTION::DIR_DOWN, result);
			return true;
		}
		break;

	case DIRECTION::DIR_UP:
		result = FindSameIndex(map->GetXIndex(), map->GetYIndex() - 1, index);
		if (result != -1)
		{
			_vMaps[result]->SetNextMapIndex(DIRECTION::DIR_DOWN, index);
			map->SetNextMapIndex(DIRECTION::DIR_UP, result);
			return true;
		}
		break;

	case DIRECTION::DIR_LEFT:
		result = FindSameIndex(map->GetXIndex() - 1, map->GetYIndex(), index);
		if (result != -1)
		{
			_vMaps[result]->SetNextMapIndex(DIRECTION::DIR_RIGHT, index);
			map->SetNextMapIndex(DIRECTION::DIR_LEFT, result);
			return true;
		}
		break;

	case DIRECTION::DIR_RIGHT:
		result = FindSameIndex(map->GetXIndex() + 1, map->GetYIndex(), index);
		if (result != -1)
		{
			_vMaps[result]->SetNextMapIndex(DIRECTION::DIR_LEFT, index);
			map->SetNextMapIndex(DIRECTION::DIR_RIGHT, result);
			return true;
		}
		break;
	}

	return false;
}

bool Stage::CheckCollision()
{
	bool noCollision = true;
	for (int i = 0; i < _vMaps.size(); i++)
	{
		FieldMap* map = _vMaps[i];

		if (FindSameIndex(map->GetXIndex(), map->GetYIndex(), i) != -1)
		{
			noCollision = false;
			break;
		}
	}

	if (noCollision) return true;
	else return false;
}