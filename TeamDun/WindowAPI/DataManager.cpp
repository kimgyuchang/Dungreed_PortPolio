#include "stdafx.h"
#include "DataManager.h"

void DataManager::GetUIBrushToolData()
{
	vector<vector<string>> gridData = CSVMANAGER->csvLoad("Data/UIBrushToolGrid.csv");

	for (int i = 0; i < gridData.size(); i++)
	{
		GridData* grid = new GridData();

		grid->_x = stoi(gridData[i][1]);
		grid->_y = stoi(gridData[i][2]);
		grid->_page = stoi(gridData[i][3]);
		grid->_image = IMAGEMANAGER->findImage(gridData[i][4]);
		grid->_name = gridData[i][4];
		
		_mGridData[stoi(gridData[i][0])] = grid;
	}
}


void DataManager::GetMapObjectData()
{
	vector<vector<string>> itemData = CSVMANAGER->csvLoad("Data/MapObjectData.csv");


}