#include "stdafx.h"
#include "loadingScene.h"

HRESULT loadingScene::init()
{
	_loading = new Loading();
	_loading->init();

	IMAGEMANAGER->addImage("loadingBarFront", "loadingBarFront.bmp", 620, 200);
	IMAGEMANAGER->addImage("loadingBarBack", "loadingBarBack.bmp", 620, 200);

	_background = IMAGEMANAGER->addFrameImage("bgLoadingScene", "Images/LOADING.bmp", WINSIZEX * 6, WINSIZEY, 6, 1);
	_loadingBar = new progressBar;
	_currentGauge = 0;

	_loadingBar->init("loadingBarFront", "loadingBarBack");
	_loadingBar->setPos(410, 210);

	this->loadingImage();
	this->loadingSound();
	this->loadingFont();
	return S_OK;
}

void loadingScene::release()
{
	_loading->release();
	SAFE_DELETE(_loading);
	SAFE_DELETE(_loadingBar);
}

void loadingScene::update()
{
	_loading->update();
	_loadingBar->update();
	this->animation();

	// 이미지 로드가 완료되면 이동
	if (_currentGauge >= _loading->GetLoadItem().size())
	{
		LoadData();
		SCENEMANAGER->loadScene("시작화면");
	}
	
	// 아니라면 계속해서 불러오기
	else
	{
		for (int i = 0; i < 5; i++)
		{
			LoadItem* item = _loading->GetLoadItem()[_currentGauge];
			_loading->LoadingDone(item);
			_currentGauge++;
			if (_currentGauge >= _loading->GetLoadItem().size()) break;
		}
		_loadingBar->setGauge(_loading->GetLoadItem().size(), _currentGauge);
	}
}

void loadingScene::render()
{
	_loading->render();

	_loadingBar->render();
	_background->frameRender(getMemDC(), 0, 0);
	textOut(getMemDC(), _loadingBar->getX() + 250, _loadingBar->getY() + 330, _loading->GetCurKey().c_str(), _loading->GetCurKey().length());

	IMAGEMANAGER->frameRender("number", getMemDC(), 710, 500,(int)((float)_currentGauge /(float)_loading->GetLoadItem().size()*100) % 10, 0);
	if ((int)((float)_currentGauge *(100 / (float)_loading->GetLoadItem().size()) / 10) > 0)
	IMAGEMANAGER->frameRender("number", getMemDC(), 690, 500, (float)_currentGauge *(100/(float)_loading->GetLoadItem().size()) / 10, 0);
}

/// <summary>
/// CSV데이터들을 불러온다
/// </summary>
void loadingScene::LoadData()
{
	DATAMANAGER->GetUIBrushToolGridData();
	DATAMANAGER->GetObjectData();
}

/// <summary>
/// 로딩창의 애니메이션을 관리한다.
/// </summary>
void loadingScene::animation()
{
	_animationCount++;
	if (_animationCount % 10 == 0)
	{
		_animationFrame++;
		if (_animationFrame > _background->getMaxFrameX())
		{
			_animationFrame = 0;
		}
		_background->setFrameX(_animationFrame);
	}
}

void loadingScene::loadingFont()
{
	AddFontResource("Font/HS겨울눈꽃체.ttf");
	AddFontResource("Font/BMYEONSUNG_ttf.ttf");
	AddFontResource("Font/neodgm.ttf");
}

void loadingScene::loadingImage()
{
	// STAGE 1 GRID //
	_loading->LoadNormalImage("Stage1_Tile0", "Images/1Floor/Basic_H_Type2_0.bmp", 48, 48, true, RGB(255,0,255));
	_loading->LoadNormalImage("Stage1_Tile1", "Images/1Floor/Basic_H_Type2_1.bmp", 48, 48, true, RGB(255,0,255));
	_loading->LoadNormalImage("Stage1_Tile2", "Images/1Floor/Basic_H_Type2_2.bmp", 48, 48, true, RGB(255,0,255));
	_loading->LoadNormalImage("Stage1_Tile3", "Images/1Floor/Basic_H_Type2_3.bmp", 48, 48, true, RGB(255,0,255));
	_loading->LoadNormalImage("Stage1_Tile4", "Images/1Floor/Basic_H_Type2_4.bmp", 48, 48, true, RGB(255,0,255));
	_loading->LoadNormalImage("Stage1_Tile5", "Images/1Floor/Basic_H_Type2_5.bmp", 48, 48, true, RGB(255,0,255));
	_loading->LoadNormalImage("Stage1_Tile6", "Images/1Floor/Basic_H_Type2_6.bmp", 48, 48, true, RGB(255,0,255));
	_loading->LoadNormalImage("Stage1_Tile7", "Images/1Floor/Basic_H_Type2_7.bmp", 48, 48, true, RGB(255,0,255));
	_loading->LoadNormalImage("Stage1_Tile8", "Images/1Floor/Basic_H_Type2_8.bmp", 48, 48, true, RGB(255,0,255));

	_loading->LoadNormalImage("Stage1_Tile9", "Images/1Floor/BasicStone_BottomCenter.bmp", 48, 48, true, RGB(255,0,255));
	_loading->LoadNormalImage("Stage1_Tile10", "Images/1Floor/BasicStone_TopCenter_2.bmp", 48, 48, true, RGB(255,0,255));
	_loading->LoadNormalImage("Stage1_Tile11", "Images/1Floor/BasicStone_TopCenter_4.bmp", 48, 48, true, RGB(255,0,255));
	_loading->LoadNormalImage("Stage1_Tile12", "Images/1Floor/1FloorTileLeft.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stage1_Tile13", "Images/1Floor/1FloorTileMiddle.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stage1_Tile14", "Images/1Floor/1FloorTileRight.bmp", 48, 48, true, RGB(255, 0, 255));

	_loading->LoadNormalImage("Stage1_Tile15", "Images/1Floor/Tile_H1.bmp", 48, 48, true, RGB(255,0,255));
	_loading->LoadNormalImage("Stage1_Tile16", "Images/1Floor/Tile_H3.bmp", 48, 48, true, RGB(255,0,255));
	_loading->LoadNormalImage("Stage1_Tile17", "Images/1Floor/Tile_H4.bmp", 48, 48, true, RGB(255,0,255));
	_loading->LoadNormalImage("Stage1_Tile18", "Images/1Floor/Tile_H5.bmp", 48, 48, true, RGB(255,0,255));
	_loading->LoadNormalImage("Stage1_Tile19", "Images/1Floor/Tile_H7.bmp", 48, 48, true, RGB(255,0,255));

	_loading->LoadNormalImage("Stage1_Tile20", "Images/1Floor/Tile_H9.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stage1_Tile21", "Images/1Floor/Tile_H10.bmp", 48, 48, true, RGB(255,0,255));
	_loading->LoadNormalImage("Stage1_Tile22", "Images/1Floor/Tile_H11.bmp", 48, 48, true, RGB(255,0,255));
	_loading->LoadNormalImage("Stage1_Tile23", "Images/1Floor/Tile_H12.bmp", 48, 48, true, RGB(255,0,255));
	_loading->LoadNormalImage("Stage1_Tile24", "Images/1Floor/Tile_H14.bmp", 48, 48, true, RGB(255,0,255));

	_loading->LoadNormalImage("Stage1_Tile25", "Images/1Floor/Tile_Marble_Stair_BottomLeft.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stage1_Tile26", "Images/1Floor/Tile_Marble_Stair_BottomRight.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stage1_Tile27", "Images/1Floor/Tile_Marble_Stair_TopLeft.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stage1_Tile28", "Images/1Floor/Tile_Marble_Stair_TopRight.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stage1_Tile29", "Images/1Floor/Tile_Stair_BottomLeft.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stage1_Tile30", "Images/1Floor/Tile_Stair_BottomRight.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stage1_Tile31", "Images/1Floor/Tile_Stair_TopLeft.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stage1_Tile32", "Images/1Floor/Tile_Stair_TopRight.bmp", 48, 48, true, RGB(255, 0, 255));

	_loading->LoadNormalImage("Stage1_Tile33", "Images/1Floor/Tile_Slim_Bottom.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stage1_Tile34", "Images/1Floor/Tile_Slim_BottomCenter.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stage1_Tile35", "Images/1Floor/Tile_Slim_Left.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stage1_Tile36", "Images/1Floor/Tile_Slim_MiddleRight.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stage1_Tile37", "Images/1Floor/Tile_Slim_Right.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stage1_Tile38", "Images/1Floor/Tile_Slim_Top.bmp", 48, 48, true, RGB(255, 0, 255));

	_loading->LoadNormalImage("Stage1_Tile39", "Images/1Floor/Wall_Basic_0.bmp", 48, 48, true, RGB(255,0,255));
	_loading->LoadNormalImage("Stage1_Tile40", "Images/1Floor/Wall_Basic_1.bmp", 48, 48, true, RGB(255,0,255));
	_loading->LoadNormalImage("Stage1_Tile41", "Images/1Floor/Wall_Basic_2.bmp", 48, 48, true, RGB(255,0,255));
	_loading->LoadNormalImage("Stage1_Tile42", "Images/1Floor/Wall_Basic_3.bmp", 48, 48, true, RGB(255,0,255));
	_loading->LoadNormalImage("Stage1_Tile43", "Images/1Floor/Wall_Basic_4.bmp", 48, 48, true, RGB(255,0,255));
	_loading->LoadNormalImage("Stage1_Tile44", "Images/1Floor/Wall_Basic_5.bmp", 48, 48, true, RGB(255,0,255));
	_loading->LoadNormalImage("Stage1_Tile45", "Images/1Floor/Wall_Basic_12.bmp", 48, 48, true, RGB(255,0,255));
	_loading->LoadNormalImage("Stage1_Tile46", "Images/1Floor/Wall_Basic_13.bmp", 48, 48, true, RGB(255,0,255));
	_loading->LoadNormalImage("Stage1_Tile47", "Images/1Floor/Wall_Basic_14.bmp", 48, 48, true, RGB(255,0,255));

	_loading->LoadNormalImage("Stage1_Tile48", "Images/1Floor/Wall_Basic_6.bmp", 48, 48, true, RGB(255,0,255));
	_loading->LoadNormalImage("Stage1_Tile49", "Images/1Floor/Wall_Basic_8.bmp", 48, 48, true, RGB(255,0,255));
	_loading->LoadNormalImage("Stage1_Tile50", "Images/1Floor/Wall_Basic_15.bmp", 48, 48, true, RGB(255,0,255));
	_loading->LoadNormalImage("Stage1_Tile51", "Images/1Floor/Wall_Basic_16.bmp", 48, 48, true, RGB(255,0,255));
	_loading->LoadNormalImage("Stage1_Tile52", "Images/1Floor/Wall_Basic_9.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stage1_Tile53", "Images/1Floor/Wall_Basic_10.bmp", 48, 48, true, RGB(255,0,255));
	_loading->LoadNormalImage("Stage1_Tile54", "Images/1Floor/Wall_Basic_11.bmp", 48, 48, true, RGB(255,0,255));

	_loading->LoadNormalImage("Stage1_Tile55", "Images/1Floor/Wall_Basic_Ceiling_0.bmp", 48, 48, true, RGB(255,0,255));
	_loading->LoadNormalImage("Stage1_Tile56", "Images/1Floor/Wall_Basic_Ceiling_1.bmp", 48, 48, true, RGB(255,0,255));
	_loading->LoadNormalImage("Stage1_Tile57", "Images/1Floor/Wall_Basic_Ceiling_2.bmp", 48, 48, true, RGB(255,0,255));
	_loading->LoadNormalImage("Stage1_Tile58", "Images/1Floor/Wall_Basic_Ceiling_3.bmp", 48, 48, true, RGB(255,0,255));
	_loading->LoadNormalImage("Stage1_Tile59", "Images/1Floor/Wall_Basic_Ceiling_4.bmp", 48, 48, true, RGB(255,0,255));
	_loading->LoadNormalImage("Stage1_Tile60", "Images/1Floor/Wall_Basic_Ceiling_5.bmp", 48, 48, true, RGB(255,0,255));

	_loading->LoadNormalImage("Stage1_Tile61", "Images/1Floor/Wall_Type2_StairLeft.bmp", 48, 48, true, RGB(255, 0, 255));

	_loading->LoadNormalImage("Stage1_Tile62", "Images/1Floor/Wall_Cracked_0.bmp", 48, 48, true, RGB(255,0,255));
	_loading->LoadNormalImage("Stage1_Tile63", "Images/1Floor/Wall_Cracked_1.bmp", 48, 48, true, RGB(255,0,255));
	_loading->LoadNormalImage("Stage1_Tile64", "Images/1Floor/Wall_Cracked_2.bmp", 48, 48, true, RGB(255,0,255));
	_loading->LoadNormalImage("Stage1_Tile65", "Images/1Floor/Wall_Cracked_3.bmp", 48, 48, true, RGB(255,0,255));
	_loading->LoadNormalImage("Stage1_Tile66", "Images/1Floor/Wall_Cracked_4.bmp", 48, 48, true, RGB(255,0,255));
	_loading->LoadNormalImage("Stage1_Tile67", "Images/1Floor/Wall_Cracked_5.bmp", 48, 48, true, RGB(255,0,255));
	_loading->LoadNormalImage("Stage1_Tile68", "Images/1Floor/Wall_Cracked_6.bmp", 48, 48, true, RGB(255,0,255));

	_loading->LoadNormalImage("Stage1_Tile69", "Images/1Floor/Wall_H0.bmp", 48, 48, true, RGB(255,0,255));
	_loading->LoadNormalImage("Stage1_Tile70", "Images/1Floor/Wall_H1.bmp", 48, 48, true, RGB(255,0,255));
	_loading->LoadNormalImage("Stage1_Tile71", "Images/1Floor/Wall_H2.bmp", 48, 48, true, RGB(255,0,255));
	_loading->LoadNormalImage("Stage1_Tile72", "Images/1Floor/Wall_H3.bmp", 48, 48, true, RGB(255,0,255));
	_loading->LoadNormalImage("Stage1_Tile73", "Images/1Floor/Wall_H4_1.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stage1_Tile74", "Images/1Floor/Wall_H4_2.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stage1_Tile75", "Images/1Floor/Wall_H6.bmp", 48, 48, true, RGB(255,0,255));
	_loading->LoadNormalImage("Stage1_Tile76", "Images/1Floor/Wall_H8.bmp", 48, 48, true, RGB(255,0,255));
	_loading->LoadNormalImage("Stage1_Tile77", "Images/1Floor/Wall_H9.bmp", 48, 48, true, RGB(255,0,255));
	_loading->LoadNormalImage("Stage1_Tile78", "Images/1Floor/Wall_H10.bmp", 48, 48, true, RGB(255,0,255));
	_loading->LoadNormalImage("Stage1_Tile79", "Images/1Floor/Wall_H11.bmp", 48, 48, true, RGB(255,0,255));
	_loading->LoadNormalImage("Stage1_Tile80", "Images/1Floor/Wall_H12.bmp", 48, 48, true, RGB(255,0,255));

	_loading->LoadNormalImage("Stage1_Tile81", "Images/1Floor/Cave_1.bmp", 48, 48, true, RGB(255,0,255));
	_loading->LoadNormalImage("Stage1_Tile82", "Images/1Floor/Cave_2.bmp", 48, 48, true, RGB(255,0,255));
	_loading->LoadNormalImage("Stage1_Tile83", "Images/1Floor/Ceil_1.bmp", 48, 48, true, RGB(255,0,255));
	_loading->LoadNormalImage("Stage1_Tile84", "Images/1Floor/Ceil_2.bmp", 48, 48, true, RGB(255,0,255));
	_loading->LoadNormalImage("Stage1_Tile85", "Images/1Floor/Ceil_3.bmp", 48, 48, true, RGB(255,0,255));
	_loading->LoadNormalImage("Stage1_Tile86", "Images/1Floor/Ceil_4.bmp", 48, 48, true, RGB(255,0,255));
	_loading->LoadNormalImage("Stage1_Tile87", "Images/1Floor/Pillar_1.bmp", 48, 48, true, RGB(255,0,255));
	_loading->LoadNormalImage("Stage1_Tile88", "Images/1Floor/Pillar_2.bmp", 48, 48, true, RGB(255,0,255));
	_loading->LoadNormalImage("Stage1_Tile89", "Images/1Floor/Pillar_3.bmp", 48, 48, true, RGB(255,0,255));
	_loading->LoadNormalImage("Stage1_Tile90", "Images/1Floor/Pillar_4.bmp", 48, 48, true, RGB(255,0,255));
	_loading->LoadNormalImage("Stage1_Tile91", "Images/1Floor/Pillar_5.bmp", 48, 48, true, RGB(255,0,255));
	_loading->LoadNormalImage("Stage1_Tile92", "Images/1Floor/Pillar_6.bmp", 48, 48, true, RGB(255,0,255));
	_loading->LoadNormalImage("Stage1_Tile93", "Images/1Floor/Wall_Chain_1.bmp", 48, 48, true, RGB(255,0,255));
	_loading->LoadNormalImage("Stage1_Tile94", "Images/1Floor/Wall_Chain_2.bmp", 48, 48, true, RGB(255,0,255));
	_loading->LoadNormalImage("Stage1_Tile95", "Images/1Floor/Wall_Basic_Statue_Bottom_0.bmp", 48, 48, true, RGB(255,0,255));
	_loading->LoadNormalImage("Stage1_Tile96", "Images/1Floor/Wall_Basic_Statue_Bottom_1.bmp", 48, 48, true, RGB(255,0,255));
	_loading->LoadNormalImage("Stage1_Tile97", "Images/1Floor/Wall_Basic_Statue_Bottom_2.bmp", 48, 48, true, RGB(255,0,255));
	_loading->LoadNormalImage("Stage1_Tile98", "Images/1Floor/Wall_Basic_Statue_Bottom_3.bmp", 48, 48, true, RGB(255,0,255));
	_loading->LoadNormalImage("Stage1_Tile99", "Images/1Floor/Wall_Sewer_Botom.bmp", 48, 48, true, RGB(255,0,255));
	_loading->LoadNormalImage("Stage1_Tile100", "Images/1Floor/Wall_Sewer_Botom_1.bmp", 48, 48, true, RGB(255,0,255));
	_loading->LoadNormalImage("Stage1_Tile101", "Images/1Floor/Wall_Sewer_Round_0.bmp", 48, 48, true, RGB(255,0,255));
	_loading->LoadNormalImage("Stage1_Tile102", "Images/1Floor/Wall_Sewer_Round_1.bmp", 48, 48, true, RGB(255,0,255));
	_loading->LoadNormalImage("Stage1_Tile103", "Images/1Floor/Wall_Sewer_Round_2.bmp", 48, 48, true, RGB(255,0,255));
	_loading->LoadNormalImage("Stage1_Tile104", "Images/1Floor/Wall_Sewer_Round_3.bmp", 48, 48, true, RGB(255,0,255));
	_loading->LoadNormalImage("Stage1_Tile105", "Images/1Floor/wallLeft_1.bmp", 48, 48, true, RGB(255,0,255));
	_loading->LoadNormalImage("Stage1_Tile106", "Images/1Floor/wallLeft_2.bmp", 48, 48, true, RGB(255,0,255));
	_loading->LoadNormalImage("Stage1_Tile107", "Images/1Floor/wallLeft_3.bmp", 48, 48, true, RGB(255,0,255));
	_loading->LoadNormalImage("Stage1_Tile108", "Images/1Floor/wallLeft_4.bmp", 48, 48, true, RGB(255,0,255));
	
	// STAGE ALL GRID //
	_loading->LoadNormalImage("HivePlarformTile", "Images/AllFloor/HivePlarformTile.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("OneWayPlatform", "Images/AllFloor/OneWayPlatform.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("SecondFloor_0", "Images/AllFloor/SecondFloor_0.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("SecondFloor_1", "Images/AllFloor/SecondFloor_1.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("SecondFloor_2", "Images/AllFloor/SecondFloor_2.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("SecondFloor_3", "Images/AllFloor/SecondFloor_3.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("WoodenBridge_0", "Images/AllFloor/WoodenBridge_0.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("WoodenBridge_1", "Images/AllFloor/WoodenBridge_1.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("WoodenBridge_2", "Images/AllFloor/WoodenBridge_2.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("WoodenBridge_3", "Images/AllFloor/WoodenBridge_3.bmp", 48, 48, true, RGB(255, 0, 255));


	// OBJECT //
	_loading->LoadNormalImage("BigBox0", "Images/Object/BigBox0.bmp", 69, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Bone0", "Images/Object/Bone0.bmp", 36, 18, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Bone1", "Images/Object/Bone1.bmp", 42, 18, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Box0", "Images/Object/Box0.bmp", 48, 36, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("OakDrum0", "Images/Object/OakDrum0.bmp", 39, 42, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Skull0", "Images/1Floor/Skull0.bmp", 30, 21, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Skull1", "Images/1Floor/Skull1.bmp", 45, 21, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stone_1", "Images/AllFloor/Stone_1.bmp", 60, 33, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stone_2", "Images/AllFloor/Stone_2.bmp", 60, 33, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Stone_3", "Images/AllFloor/Stone_3.bmp", 60, 33, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Table0", "Images/AllFloor/Table0.bmp", 135, 45, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("TortureTable_0", "Images/AllFloor/TortureTable_0.bmp", 135, 57, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("TortureTable_1", "Images/AllFloor/TortureTable_1.bmp", 135, 57, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("TortureTable1_0", "Images/AllFloor/TortureTable1_0.bmp", 33, 18, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("TortureTable1_1", "Images/AllFloor/TortureTable1_1.bmp", 42, 18, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("DungeonSign", "Images/villageFloor/DungeonSign.bmp", 60, 66, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("Door_Down", "Images/Object/Door_Down.bmp", 4416, 58, 23, 1, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("Door_Up", "Images/Object/Door_Up.bmp", 4416, 58, 23, 1, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("Door_Left", "Images/Object/Door_Left.bmp", 1656, 240, 23, 1, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("Door_Right", "Images/Object/Door_Right.bmp", 1656, 240, 23, 1, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Door_Down_Idle", "Images/Object/Door_Down_Idle.bmp", 192, 58, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Door_Up_Idle", "Images/Object/Door_Up_Idle.bmp", 192, 58, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Door_Left_Idle", "Images/Object/Door_Left_Idle.bmp", 72, 240, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Door_Right_Idle", "Images/Object/Door_Right_Idle.bmp", 72, 240, true, RGB(255, 0, 255));

	// STAGE 1 //
	_loading->LoadNormalImage("Door0_Closed", "Images/1Floor/Door0_Closed.bmp", 171, 195, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Door0_Open", "Images/1Floor/Door0_Open.bmp", 171, 195, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("Torch0", "Images/1Floor/Torch0.bmp", 528, 75, 8, 1, true, RGB(255, 0, 255));

	// NPC //
	_loading->LoadFrameImage("StrawberryFountain0", "Images/Object/StrawberryFountain0.bmp", 384, 96, 4, 1, true, RGB(255,0,255));
	_loading->LoadNormalImage("StrawberryFountain1", "Images/Object/StrawberryFountain1.bmp", 96, 96, true, RGB(255,0,255));
	_loading->LoadNormalImage("WormPassage00", "Images/Object/WormPassage00.bmp", 81, 93, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("WormPassageEat00", "Images/Object/WormPassageEat00.bmp", 324, 93, 4, 1, true, RGB(255,0,255));
	_loading->LoadFrameImage("WormPassageIdle00", "Images/Object/WormPassageIdle00.bmp", 729, 93, 9, 1, true, RGB(255,0,255));
	_loading->LoadFrameImage("PinkTresureClosed00", "Images/Object/PinkTresureClosed00.bmp", 396, 63, 12, 1, true, RGB(255,0,255));
	_loading->LoadFrameImage("PinkTresureOpened00", "Images/Object/PinkTresureOpened00.bmp", 396, 63, 12, 1, true, RGB(255,0,255));
	_loading->LoadFrameImage("PinkTresureOpened00", "Images/Object/PinkTresureOpened00.bmp", 396, 63, 12, 1, true, RGB(255,0,255));
	_loading->LoadNormalImage("RareTresureClosed", "Images/Object/RareTresureClosed.bmp", 93, 54, true, RGB(255,0,255));
	_loading->LoadNormalImage("RareTresureOpened", "Images/Object/RareTresureOpened.bmp", 93, 54, true, RGB(255,0,255));
	_loading->LoadNormalImage("GrayTresureClosed", "Images/Object/GrayTresureClosed.bmp", 63, 45, true, RGB(255,0,255));
	_loading->LoadNormalImage("GrayTresureOpen", "Images/Object/GrayTresureOpen.bmp", 63, 45, true, RGB(255,0,255));
	_loading->LoadNormalImage("StashClosed", "Images/Object/StashClosed.bmp", 84, 48, true, RGB(255,0,255));
	_loading->LoadNormalImage("StashOpened", "Images/Object/StashOpened.bmp", 84, 48, true, RGB(255,0,255));
	_loading->LoadNormalImage("YellowTresureClosed", "Images/Object/YellowTresureClosed.bmp", 117, 69, true, RGB(255,0,255));
	_loading->LoadNormalImage("YellowTresureOpened", "Images/Object/YellowTresureOpened.bmp", 117, 69, true, RGB(255,0,255));

	// OBSTACLE //
	_loading->LoadFrameImage("gear", "Images/Object/gear.bmp", 1296, 108, 12, 1, true, RGB(255,0,255), true);
	_loading->LoadFrameImage("Gear_Small", "Images/Object/Gear_Small.bmp", 828, 69, 12, 1, true, RGB(255,0,255), true);
	_loading->LoadFrameImage("Gear_Small_Small", "Images/Object/Gear_Small_Small.bmp", 612, 51, 12, 1, true, RGB(255,0,255), true);
	_loading->LoadFrameImage("SpikePlatform1", "Images/1Floor/SpikePlatform1.bmp", 288, 48, 6, 1, true, RGB(255,0,255));
	_loading->LoadNormalImage("Spike", "Images/AllFloor/Spike.bmp", 48, 48, true, RGB(255,0,255));

	// ETC //
	_loading->LoadNormalImage("SpawnMonsterPos", "Images/Etc/SpawnMonsterPos.bmp", 48, 48, true, RGB(255, 0, 255));

	// UI //  
	_loading->LoadNormalImage("UIBaseBig", "Images/UI/Base.bmp", 500, 300, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("UIBaseMiddle", "Images/UI/Base.bmp", 222 * 2, 189 * 2, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("UIBaseSmall", "Images/UI/Base.bmp", 222, 189, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("UpButton", "Images/UI/FullWindowExitButton_Selected.bmp", 66, 57 , true ,RGB(255,0,255));
	_loading->LoadNormalImage("RightButton", "Images/UI/FullWindowExitButton_Selected.bmp", 66, 57 , true ,RGB(255,0,255));
	_loading->LoadNormalImage("DownButton", "Images/UI/FullWindowExitButton.bmp", 66, 57 , true ,RGB(255,0,255));
	_loading->LoadNormalImage("LeftButton", "Images/UI/FullWindowExitButton.bmp", 66, 57 , true ,RGB(255,0,255));
	_loading->LoadNormalImage("mapWidthBox", "Images/UI/AbilityTextBar.bmp", 120, 100 , true ,RGB(255,0,255));
	_loading->LoadNormalImage("mapHeightBox", "Images/UI/AbilityTextBar.bmp", 120, 100 , true ,RGB(255,0,255));
	_loading->LoadNormalImage("ShortcutKeyGround", "Images/UI/AltarButton1.bmp", 800, 87, true ,RGB(255,0,255));
	_loading->LoadNormalImage("ShortcutKey1", "Images/UI/IconGray.bmp", 57, 57, true ,RGB(255,0,255));
	_loading->LoadNormalImage("ShortcutKey2", "Images/UI/IconWhite1.bmp", 57, 57, true ,RGB(255,0,255));
	_loading->LoadNormalImage("AbilityTextBar", "Images/UI/AbilityTextBar.bmp", 33, 54, true ,RGB(255,0,255));
	_loading->LoadNormalImage("accessoryZone", "Images/UI/accessoryZone.bmp", 96, 75, true ,RGB(255,0,255));
	_loading->LoadNormalImage("AltarButton0", "Images/UI/AltarButton0.bmp", 300, 90, true ,RGB(255,0,255));
	_loading->LoadNormalImage("AltarButton1", "Images/UI/AltarButton1.bmp", 266, 87, true ,RGB(255,0,255));
	_loading->LoadNormalImage("AltarGaugeBase", "Images/UI/AltarGaugeBase.bmp", 116, 21, true ,RGB(255,0,255));
	_loading->LoadNormalImage("AnvilCloseButton", "Images/UI/AnvilCloseButton.bmp", 39, 39, true ,RGB(255,0,255));
	_loading->LoadNormalImage("AnvilCloseButtonSelected", "Images/UI/AnvilCloseButtonSelected.bmp", 39, 39, true ,RGB(255,0,255));
	_loading->LoadNormalImage("AnvilUI", "Images/UI/AnvilUI.bmp", 408, 153, true ,RGB(255,0,255));
	_loading->LoadNormalImage("Base", "Images/UI/Base.bmp", 222, 189, true,RGB(255,0,255));
	_loading->LoadNormalImage("Base_0", "Images/UI/Base_0.bmp", 333, 396, true ,RGB(255,0,255));
	_loading->LoadNormalImage("Base_1", "Images/UI/Base_1.bmp", 333, 51, true ,RGB(255,0,255));
	_loading->LoadNormalImage("Base_2", "Images/UI/Base_2.bmp", 339, 51, true ,RGB(255,0,255));
	_loading->LoadNormalImage("Base_3", "Images/UI/Base_3.bmp", 579, 396, true ,RGB(255,0,255));
	_loading->LoadNormalImage("BasicCursor", "Images/UI/BasicCursor.bmp", 27, 33, true ,RGB(255,0,255));
	_loading->LoadNormalImage("BossLifeBack", "Images/UI/BossLifeBack.bmp", 375, 48, true ,RGB(255,0,255));
	_loading->LoadNormalImage("BossLifeBase", "Images/UI/BossLifeBase.bmp", 375, 48, true ,RGB(255,0,255));
	_loading->LoadNormalImage("BuildCompleteBase_0", "Images/UI/BuildCompleteBase_0.bmp", 176, 98, true ,RGB(255,0,255));
	_loading->LoadNormalImage("BuildCompleteBase_1", "Images/UI/BuildCompleteBase_1.bmp", 381, 294, true ,RGB(255,0,255));
	_loading->LoadNormalImage("BuildMenu", "Images/UI/BuildMenu.bmp", 858, 105, true ,RGB(255,0,255));
	_loading->LoadNormalImage("BuildMenu_Selected", "Images/UI/BuildMenu_Selected.bmp", 858, 105, true ,RGB(255,0,255));
	_loading->LoadNormalImage("Choice", "Images/UI/Choice.bmp", 27, 27, true ,RGB(255,0,255));
	_loading->LoadNormalImage("Clear", "Images/UI/Clear.bmp", 192, 30, true ,RGB(255,0,255));
	_loading->LoadNormalImage("CostumeBack", "Images/UI/CostumeBack.bmp", 222, 297, true ,RGB(255,0,255));
	_loading->LoadNormalImage("CostumeBase_0", "Images/UI/CostumeBase_0.bmp", 960, 87, true ,RGB(255,0,255));
	_loading->LoadNormalImage("CostumeBase_1", "Images/UI/CostumeBase_1.bmp", 960, 150, true ,RGB(255,0,255));
	_loading->LoadNormalImage("CostumeEquipped", "Images/UI/CostumeEquipped.bmp", 204, 285, true ,RGB(255,0,255));
	_loading->LoadNormalImage("CostumeLocked", "Images/UI/CostumeLocked.bmp", 204, 285, true ,RGB(255,0,255));
	_loading->LoadNormalImage("CostumeOver", "Images/UI/CostumeOver.bmp", 204, 285, true ,RGB(255,0,255));
	_loading->LoadNormalImage("CostumeUnlocked", "Images/UI/CostumeUnlocked.bmp", 204, 285, true ,RGB(255,0,255));
	_loading->LoadNormalImage("DashBase", "Images/UI/DashBase.bmp", 27, 24, true ,RGB(255,0,255));
	_loading->LoadNormalImage("DashBaseLeftEnd", "Images/UI/DashBaseLeftEnd.bmp", 6, 24, true ,RGB(255,0,255));
	_loading->LoadNormalImage("DashBaseRightEnd", "Images/UI/DashBaseRightEnd.bmp", 6, 24, true ,RGB(255,0,255));
	_loading->LoadNormalImage("DashCount", "Images/UI/DashCount.bmp", 27, 12, true ,RGB(255,0,255));
	_loading->LoadNormalImage("DashCountBase_0", "Images/UI/DashCountBase_0.bmp", 33, 24, true ,RGB(255,0,255));
	_loading->LoadNormalImage("DemensionVault0", "Images/UI/DemensionVault0.bmp", 99, 99, true ,RGB(255,0,255));
	_loading->LoadNormalImage("DemensionVault1", "Images/UI/DemensionVault1.bmp", 99, 99, true ,RGB(255,0,255));
	_loading->LoadNormalImage("DungeonMenu 1", "Images/UI/DungeonMenu 1.bmp", 960, 120, true ,RGB(255,0,255));
	_loading->LoadNormalImage("DungeonMenu 2", "Images/UI/DungeonMenu 2.bmp", 12, 337, true ,RGB(255,0,255));
	_loading->LoadNormalImage("DungeonShopBase", "Images/UI/DungeonShopBase.bmp", 366, 564, true ,RGB(255,0,255));
	_loading->LoadNormalImage("Empty", "Images/UI/Empty.bmp", 96, 96, true ,RGB(255,0,255));
	_loading->LoadNormalImage("EndurancePain", "Images/UI/EndurancePain.bmp", 51, 51, true ,RGB(255,0,255));
	_loading->LoadNormalImage("EquippedWeaponBase", "Images/UI/EquippedWeaponBase.bmp", 102, 72, true ,RGB(255,0,255));
	_loading->LoadNormalImage("ExplorationFailure.korean", "Images/UI/ExplorationFailure.korean.bmp", 960, 108, true ,RGB(255,0,255));
	_loading->LoadNormalImage("ExplorationSuccess.korean", "Images/UI/ExplorationSuccess.korean.bmp", 960, 108, true ,RGB(255,0,255));
	_loading->LoadNormalImage("FullWindowExitButton", "Images/UI/FullWindowExitButton.bmp", 66, 57, true ,RGB(255,0,255));
	_loading->LoadNormalImage("FullWindowExitButton_Selected", "Images/UI/FullWindowExitButton_Selected.bmp", 66, 57, true ,RGB(255,0,255));
	_loading->LoadNormalImage("IconGray", "Images/UI/IconGray.bmp", 57, 57, true ,RGB(255,0,255));
	_loading->LoadNormalImage("IconWhite 1", "Images/UI/IconWhite 1.bmp", 57, 57, true ,RGB(255,0,255));
	_loading->LoadNormalImage("IconWhite", "Images/UI/IconWhite.bmp", 57, 57, true ,RGB(255,0,255));
	_loading->LoadNormalImage("IconWhite_Trans", "Images/UI/IconWhite_Trans.bmp", 57, 57, true ,RGB(255,0,255));
	_loading->LoadNormalImage("IconYellow_Trans", "Images/UI/IconYellow_Trans.bmp", 57, 57, true ,RGB(255,0,255));
	_loading->LoadNormalImage("OptionArrow0", "Images/UI/OptionArrow0.bmp", 51, 33, true ,RGB(255,0,255));
	_loading->LoadNormalImage("OptionArrow1", "Images/UI/OptionArrow1.bmp", 51, 33, true ,RGB(255,0,255));
	_loading->LoadNormalImage("Result_0", "Images/UI/Result_0.bmp", 432, 45, true ,RGB(255,0,255));
	_loading->LoadNormalImage("Result_1", "Images/UI/Result_1.bmp", 432, 147, true ,RGB(255,0,255));
	_loading->LoadNormalImage("Result_2", "Images/UI/Result_2.bmp", 150, 45, true ,RGB(255,0,255));
	_loading->LoadNormalImage("ScrollRect", "Images/UI/ScrollRect.bmp", 906, 396, true ,RGB(255,0,255));
	_loading->LoadNormalImage("SlotDeleteButton", "Images/UI/SlotDeleteButton.bmp", 186, 51, true ,RGB(255,0,255));
	_loading->LoadNormalImage("SlotDeleteButton_Rev", "Images/UI/SlotDeleteButton_Rev.bmp", 51, 186, true ,RGB(255,0,255));
	_loading->LoadNormalImage("AbilityBackground_0", "Images/UI/AbilityBackground_0.bmp", 192, 345, true ,RGB(255,0,255));
	_loading->LoadNormalImage("AbilityBackground_1", "Images/UI/AbilityBackground_1.bmp", 174, 339, true ,RGB(255,0,255));
	_loading->LoadNormalImage("AbilityBackground_Arcane", "Images/UI/AbilityBackground_Arcane.bmp", 174, 342, true ,RGB(255,0,255));
	_loading->LoadNormalImage("AbilityBackground_Greed", "Images/UI/AbilityBackground_Greed.bmp", 186, 348, true ,RGB(255,0,255));
	_loading->LoadNormalImage("AbilityBackground_Patience", "Images/UI/AbilityBackground_Patience.bmp", 174, 333, true ,RGB(255,0,255));
	_loading->LoadNormalImage("AbilityBackground_Swiftness", "Images/UI/AbilityBackground_Swiftness.bmp", 180, 357, true ,RGB(255,0,255));
	_loading->LoadNormalImage("AbilityBackground_Wrath", "Images/UI/AbilityBackground_Wrath.bmp", 198, 351, true ,RGB(255,0,255));
	_loading->LoadNormalImage("AbilityTItle", "Images/UI/AbilityTItle.bmp", 960, 96, true ,RGB(255,0,255));
	_loading->LoadNormalImage("accessory", "Images/UI/accessory.bmp", 57, 57, true ,RGB(255,0,255));
	_loading->LoadNormalImage("accessorySelect", "Images/UI/accessorySelect.bmp", 57, 57, true ,RGB(255,0,255));
	_loading->LoadNormalImage("InventoryBase_2", "Images/UI/InventoryBase_2.bmp", 369, 564, true ,RGB(255,0,255));
	_loading->LoadNormalImage("Item_0", "Images/UI/Item_0.bmp", 351, 438, true ,RGB(255,0,255));
	_loading->LoadNormalImage("Item_1", "Images/UI/Item_1.bmp", 351, 438, true ,RGB(255,0,255));
	_loading->LoadNormalImage("Item_2", "Images/UI/Item_2.bmp", 351, 438, true ,RGB(255,0,255));
	_loading->LoadNormalImage("JournalTitle", "Images/UI/JournalTitle.bmp", 243, 69, true ,RGB(255,0,255));
	_loading->LoadNormalImage("KeyMappingButtonOn", "Images/UI/KeyMappingButtonOn.bmp", 141, 57, true ,RGB(255,0,255));
	_loading->LoadNormalImage("KeyMappingButtonSelect", "Images/UI/KeyMappingButtonSelect.bmp", 141, 57, true ,RGB(255,0,255));
	_loading->LoadNormalImage("KeyMappingHead", "Images/UI/KeyMappingHead.bmp", 315, 51, true ,RGB(255,0,255));
	_loading->LoadNormalImage("Label", "Images/UI/Label.bmp", 960, 96, true ,RGB(255,0,255));
	_loading->LoadNormalImage("LevelUp", "Images/UI/LevelUp.bmp", 339, 135, true ,RGB(255,0,255));
	_loading->LoadNormalImage("LevelUpAltar", "Images/UI/LevelUpAltar.bmp", 247, 26, true ,RGB(255,0,255));
	_loading->LoadNormalImage("list_Item_1", "Images/UI/list_Item_1.bmp", 522, 87, true ,RGB(255,0,255));
	_loading->LoadNormalImage("list_Item", "Images/UI/list_Item.bmp", 534, 363, true ,RGB(255,0,255));
	_loading->LoadNormalImage("list_Set", "Images/UI/list_Set.bmp", 534, 363, true ,RGB(255,0,255));
	_loading->LoadNormalImage("MainLogo", "Images/UI/MainLogo.bmp", 468, 225, true ,RGB(255,0,255));
	_loading->LoadNormalImage("MapBase_1_0", "Images/UI/MapBase_1_0.bmp", 1440, 96, true ,RGB(255,0,255));
	_loading->LoadNormalImage("MapBase_1_1", "Images/UI/MapBase_1_1.bmp", 780, 396, true ,RGB(255,0,255));
	_loading->LoadNormalImage("MisticAnvil", "Images/UI/MisticAnvil.bmp", 195, 162, true ,RGB(255,0,255));
	_loading->LoadNormalImage("MisticPot", "Images/UI/MisticPot.bmp", 180, 240, true ,RGB(255,0,255));
	_loading->LoadNormalImage("Mouse_L", "Images/UI/Mouse_L.bmp", 33, 42, true ,RGB(255,0,255));
	_loading->LoadNormalImage("Mouse_L_Drag", "Images/UI/Mouse_L_Drag.bmp", 75, 84, true ,RGB(255,0,255));
	_loading->LoadNormalImage("Mouse_Move", "Images/UI/Mouse_Move.bmp", 75, 84, true ,RGB(255,0,255));
	_loading->LoadNormalImage("Mouse_R", "Images/UI/Mouse_R.bmp", 33, 42, true ,RGB(255,0,255));
	_loading->LoadNormalImage("Mouse_R_Dash", "Images/UI/Mouse_R_Dash.bmp", 51, 42, true ,RGB(255,0,255));
	_loading->LoadNormalImage("Mouse_Wheel", "Images/UI/Mouse_Wheel.bmp", 33, 42, true ,RGB(255,0,255));
	_loading->LoadNormalImage("Mouse_WheelClick", "Images/UI/Mouse_WheelClick.bmp", 33, 42, true ,RGB(255,0,255));
	_loading->LoadNormalImage("OptionArrow1White", "Images/UI/OptionArrow1White.bmp", 51, 33, true ,RGB(255,0,255));
	_loading->LoadNormalImage("OptionBase2", "Images/UI/OptionBase2.bmp", 960, 90, true ,RGB(255,0,255));
	_loading->LoadNormalImage("OptionSoundBar", "Images/UI/OptionSoundBar.bmp", 339, 15, true ,RGB(255,0,255));
	_loading->LoadNormalImage("PlayerLifeBack", "Images/UI/PlayerLifeBack.bmp", 222, 48, true ,RGB(255,0,255));
	_loading->LoadNormalImage("PlayerLifeBase_1", "Images/UI/PlayerLifeBase_1.bmp", 222, 48, true ,RGB(255,0,255));
	_loading->LoadNormalImage("RedPill", "Images/UI/RedPill.bmp", 198, 198, true ,RGB(255,0,255));
	_loading->LoadNormalImage("RedWarningOnHit_0", "Images/UI/RedWarningOnHit_0.bmp", 480, 540, true ,RGB(255,0,255));
	_loading->LoadNormalImage("RedWarningOnHit_1", "Images/UI/RedWarningOnHit_1.bmp", 480, 540, true ,RGB(255,0,255));
	_loading->LoadNormalImage("ReloadFX0", "Images/UI/ReloadFX0.bmp", 81, 27, true ,RGB(255,0,255));
	_loading->LoadNormalImage("ReloadFX1", "Images/UI/ReloadFX1.bmp", 81, 27, true ,RGB(255,0,255));
	_loading->LoadNormalImage("ReloadFX2", "Images/UI/ReloadFX2.bmp", 81, 27, true ,RGB(255,0,255));
	_loading->LoadNormalImage("ReloadFX3", "Images/UI/ReloadFX3.bmp", 81, 27, true ,RGB(255,0,255));
	_loading->LoadNormalImage("ReloadPoint", "Images/UI/ReloadPoint.bmp", 9, 21, true ,RGB(255,0,255));
	_loading->LoadNormalImage("RestaurantLifeBase", "Images/UI/RestaurantLifeBase.bmp", 165, 48, true ,RGB(255,0,255));
	_loading->LoadNormalImage("RestaurantLifeBaseBack", "Images/UI/RestaurantLifeBaseBack.bmp", 165, 48, true ,RGB(255,0,255));
	_loading->LoadNormalImage("RestaurantMenu", "Images/UI/RestaurantMenu.bmp", 297, 57, true ,RGB(255,0,255));
	_loading->LoadNormalImage("RestaurantMenu_Selected", "Images/UI/RestaurantMenu_Selected.bmp", 297, 57, true ,RGB(255,0,255));
	_loading->LoadNormalImage("RestaurantMenu_Withoutmoney", "Images/UI/RestaurantMenu_Withoutmoney.bmp", 297, 57, true ,RGB(255,0,255));
	_loading->LoadNormalImage("RestaurantMenu_Withoutmoney_Selected", "Images/UI/RestaurantMenu_Withoutmoney_Selected.bmp", 297, 57, true ,RGB(255,0,255));
	_loading->LoadNormalImage("RestaurantTabl_Withoutmoney_Selected", "Images/UI/RestaurantMenu_Withoutmoney_Selected.bmp", 297, 57, true ,RGB(255,0,255));
	_loading->LoadNormalImage("RestaurantTable0", "Images/UI/RestaurantTable0.bmp", 573, 390, true ,RGB(255,0,255));
	_loading->LoadNormalImage("RestaurantTable1", "Images/UI/RestaurantTable1.bmp", 573, 390, true ,RGB(255,0,255));
	_loading->LoadNormalImage("RestaurantTable2", "Images/UI/RestaurantTable2.bmp", 573, 390, true ,RGB(255,0,255));
	_loading->LoadFrameImage("Right", "Images/UI/Right.bmp", 270, 48, 5, 1, true ,RGB(255,0,255));
	_loading->LoadNormalImage("Room", "Images/UI/Room.bmp", 72, 72, true ,RGB(255,0,255));
	_loading->LoadNormalImage("ScroolBarBase", "Images/UI/ScroolBarBase.bmp", 21, 9, true ,RGB(255,0,255));
	_loading->LoadNormalImage("ScroolBarHandle", "Images/UI/ScroolBarHandle.bmp", 9, 9, true ,RGB(255,0,255));
	_loading->LoadNormalImage("Set_0", "Images/UI/Set_0.bmp", 351, 438, true ,RGB(255,0,255));
	_loading->LoadNormalImage("Set_1", "Images/UI/Set_1.bmp", 351, 438, true ,RGB(255,0,255));
	_loading->LoadNormalImage("Set_2", "Images/UI/Set_2.bmp", 351, 438, true ,RGB(255,0,255));
	_loading->LoadNormalImage("ShieldBase", "Images/UI/ShieldBase.bmp", 156, 27, true ,RGB(255,0,255));
	_loading->LoadNormalImage("ShootingCursor1", "Images/UI/ShootingCursor1.bmp", 57, 57, true ,RGB(255,0,255));
	_loading->LoadNormalImage("ShootingCursor2", "Images/UI/ShootingCursor2.bmp", 63, 63, true ,RGB(255,0,255));
	_loading->LoadNormalImage("ShopBase", "Images/UI/ShopBase.bmp", 366, 564, true ,RGB(255,0,255));
	_loading->LoadNormalImage("ShopItem", "Images/UI/ShopItem.bmp", 321, 69, true ,RGB(255,0,255));
	_loading->LoadNormalImage("ShopItem_Selected", "Images/UI/ShopItem_Selected.bmp", 321, 69, true ,RGB(255,0,255));
	_loading->LoadNormalImage("Skill_0", "Images/UI/Skill_0.bmp", 318, 165, true ,RGB(255,0,255));
	_loading->LoadNormalImage("SlotBase", "Images/UI/SlotBase.bmp", 288, 429, true ,RGB(255,0,255));
	_loading->LoadNormalImage("SlotBase_Selected", "Images/UI/SlotBase_Selected.bmp", 288, 429, true ,RGB(255,0,255));
	_loading->LoadNormalImage("StashBase", "Images/UI/StashBase.bmp", 360, 540, true ,RGB(255,0,255));
	_loading->LoadNormalImage("TeamLogo0", "Images/UI/TeamLogo0.bmp", 177, 192, true ,RGB(255,0,255));
	_loading->LoadNormalImage("TeamLogo1", "Images/UI/TeamLogo1.bmp", 177, 192, true ,RGB(255,0,255));
	_loading->LoadNormalImage("TeamLogo2", "Images/UI/TeamLogo2.bmp", 177, 192, true ,RGB(255,0,255));
	_loading->LoadNormalImage("TextBox", "Images/UI/TextBox.bmp", 36, 36, true ,RGB(255,0,255));
	_loading->LoadNormalImage("Tip", "Images/UI/Tip.bmp", 153, 42, true ,RGB(255,0,255));
	_loading->LoadNormalImage("Title", "Images/UI/Title.bmp", 960, 96, true ,RGB(255,0,255));
	_loading->LoadNormalImage("town", "Images/UI/town.bmp", 696, 120, true ,RGB(255,0,255));
	_loading->LoadNormalImage("Tutorial_Altar", "Images/UI/Tutorial_Altar.bmp", 210, 222, true ,RGB(255,0,255));
	_loading->LoadNormalImage("Tutorial_DashAttack", "Images/UI/Tutorial_DashAttack.bmp", 144, 180, true ,RGB(255,0,255));
	_loading->LoadNormalImage("Tutorial_GoToTownPortal", "Images/UI/Tutorial_GoToTownPortal.bmp", 231, 144, true ,RGB(255,0,255));
	_loading->LoadNormalImage("Tutorial_Wheel", "Images/UI/Tutorial_Wheel.bmp", 87, 117, true ,RGB(255,0,255));
	_loading->LoadNormalImage("UnlockMessage", "Images/UI/UnlockMessage.bmp", 3, 93, true ,RGB(255,0,255));
	_loading->LoadNormalImage("WeaponSelect0", "Images/UI/WeaponSelect0.bmp", 141, 90, true ,RGB(255,0,255));
	_loading->LoadNormalImage("WeaponSelect1", "Images/UI/WeaponSelect1.bmp", 141, 90, true ,RGB(255,0,255));
	_loading->LoadNormalImage("X", "Images/UI/X.bmp", 39, 39, true ,RGB(255,0,255));
	_loading->LoadNormalImage("예시", "Images/UI/예시.bmp", 960, 540, true ,RGB(255,0,255));
	_loading->LoadNormalImage("ScreenCover", "Images/UI/ScreenCover.bmp", 1440, 800, true ,RGB(255,0,255));
	_loading->LoadNormalImage("Room_Line_LR", "Images/UI/Room_Line_LR.bmp", 42, 8, true ,RGB(255,0,255));
	_loading->LoadNormalImage("Room_Line_UD", "Images/UI/Room_Line_UD.bmp", 8, 42, true ,RGB(255,0,255));
	_loading->LoadNormalImage("Room_Selected", "Images/UI/Room_Selected.bmp", 72, 72, true ,RGB(255,0,255));
	
	_loading->LoadNormalImage("CheckImage", "Images/GridBound.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("CheckImageRed", "Images/GridBoundRed.bmp", 48, 48, true, RGB(255, 0, 255));


	
	// ICON //
	_loading->LoadNormalImage("brushCursor", "Images/UI/ICON/Brush.bmp", 35, 35, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("paintCursor", "Images/UI/ICON/paintCursor.bmp", 27, 33, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("eraserCursor", "Images/UI/ICON/eraserIcon.bmp", 30, 27, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("fillIcon", "Images/UI/ICON/fillIcon.bmp", 36, 44, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("loadIcon", "Images/UI/ICON/loadIcon.bmp", 50, 50, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("loadIcon", "Images/UI/ICON/loadIcon.bmp", 50, 50, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("saveIcon", "Images/UI/ICON/saveIcon.bmp", 50, 50, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("fillRectIcon", "Images/UI/ICON/fillRectIcon.bmp", 50, 50, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("floodFillIcon", "Images/UI/ICON/floodFillIcon.bmp", 50, 50, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("sizeUpDownIcon", "Images/UI/ICON/SizeUpDown.bmp", 50, 50, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("undoIcon", "Images/UI/ICON/Undo.bmp", 50, 50, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("colMinusIcon", "Images/UI/ICON/ColMinus.bmp", 50, 50, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("colPlusIcon", "Images/UI/ICON/ColPlus.bmp", 50, 50, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("rowMinusIcon", "Images/UI/ICON/RowMinus.bmp", 50, 50, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("rowPlusIcon", "Images/UI/ICON/RowPlus.bmp", 50, 50, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("paintIcon", "Images/UI/ICON/paint.bmp", 45, 46, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("eraseIcon", "Images/UI/ICON/eraseIcon.bmp", 40, 40, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Exit", "Images/UI/ICON/Exit.bmp", 48, 48, true, RGB(255, 0, 255));

	// TOWN //
	_loading->LoadNormalImage("bridgeTileLeft1", "Images/villageFloor/townBridge/1.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("bridgeTileLeft2", "Images/villageFloor/townBridge/2.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("bridgeTileLeft3", "Images/villageFloor/townBridge/3.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("bridgeTileLeft4", "Images/villageFloor/townBridge/4.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("bridgeTileLeft5", "Images/villageFloor/townBridge/5.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("bridgeTileLeft6", "Images/villageFloor/townBridge/6.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("bridgeTileLeft7", "Images/villageFloor/townBridge/7.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("bridgeTileLeft8", "Images/villageFloor/townBridge/8.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("bridgeTileLeft9", "Images/villageFloor/townBridge/9.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("bridgeTileLeft10", "Images/villageFloor/townBridge/10.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("bridgeTileLeft11", "Images/villageFloor/townBridge/11.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("bridgeTileLeft12", "Images/villageFloor/townBridge/12.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("bridgeTileLeft13", "Images/villageFloor/townBridge/13.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("bridgeTileLeft14", "Images/villageFloor/townBridge/14.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("bridgeTileLeft15", "Images/villageFloor/townBridge/15.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("bridgeTileLeft16", "Images/villageFloor/townBridge/16.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("bridgeTileLeft17", "Images/villageFloor/townBridge/17.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("bridgeTileLeft18", "Images/villageFloor/townBridge/18.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("bridgeTileLeft19", "Images/villageFloor/townBridge/19.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("bridgeTileLeft20", "Images/villageFloor/townBridge/20.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("bridgeTileLeft21", "Images/villageFloor/townBridge/21.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("bridgeTileLeft22", "Images/villageFloor/townBridge/22.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("bridgeTileLeft23", "Images/villageFloor/townBridge/23.bmp", 48, 48, true, RGB(255, 0, 255));

	_loading->LoadNormalImage("bridgeTileRight1", "Images/villageFloor/townBridge/24.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("bridgeTileRight2", "Images/villageFloor/townBridge/25.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("bridgeTileRight3", "Images/villageFloor/townBridge/26.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("bridgeTileRight4", "Images/villageFloor/townBridge/27.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("bridgeTileRight5", "Images/villageFloor/townBridge/28.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("bridgeTileRight6", "Images/villageFloor/townBridge/29.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("bridgeTileRight7", "Images/villageFloor/townBridge/30.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("bridgeTileRight8", "Images/villageFloor/townBridge/31.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("bridgeTileRight9", "Images/villageFloor/townBridge/32.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("bridgeTileRight10", "Images/villageFloor/townBridge/33.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("bridgeTileRight11", "Images/villageFloor/townBridge/34.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("bridgeTileRight12", "Images/villageFloor/townBridge/35.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("bridgeTileRight13", "Images/villageFloor/townBridge/36.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("bridgeTileRight14", "Images/villageFloor/townBridge/37.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("bridgeTileRight15", "Images/villageFloor/townBridge/38.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("bridgeTileRight16", "Images/villageFloor/townBridge/39.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("bridgeTileRight17", "Images/villageFloor/townBridge/40.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("bridgeTileRight18", "Images/villageFloor/townBridge/41.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("bridgeTileRight19", "Images/villageFloor/townBridge/42.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("bridgeTileRight20", "Images/villageFloor/townBridge/43.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("bridgeTileRight21", "Images/villageFloor/townBridge/44.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("bridgeTileRight22", "Images/villageFloor/townBridge/45.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("bridgeTileRight23", "Images/villageFloor/townBridge/46.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("bridgeTileRight24", "Images/villageFloor/townBridge/47.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("bridgeTileRight25", "Images/villageFloor/townBridge/48.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("bridgeTileRight26", "Images/villageFloor/townBridge/49.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("bridgeTileRight27", "Images/villageFloor/townBridge/50.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("bridgeTileRight28", "Images/villageFloor/townBridge/51.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("bridgeTileRight29", "Images/villageFloor/townBridge/52.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("bridgeTileRight30", "Images/villageFloor/townBridge/53.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("bridgeTileRight31", "Images/villageFloor/townBridge/54.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("bridgeTileRight32", "Images/villageFloor/townBridge/55.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("bridgeTileRight33", "Images/villageFloor/townBridge/56.bmp", 48, 48, true, RGB(255, 0, 255));

	_loading->LoadNormalImage("bridgeSecondFloor1", "Images/villageFloor/townBridge/secondFloor_0.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("bridgeSecondFloor2", "Images/villageFloor/townBridge/secondFloor_1.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("bridgeSecondFloor3", "Images/villageFloor/townBridge/secondFloor_2.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("bridgeSecondFloor4", "Images/villageFloor/townBridge/secondFloor_3.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("townBasicStair1", "Images/villageFloor/townBridge/Town_LeftStair.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("townBasicStair2", "Images/villageFloor/townBridge/Town_RightStair.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("townBasicStair3", "Images/villageFloor/townBridge/TownBasic_StairL.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("townBasicStair4", "Images/villageFloor/townBridge/TownBasic_StairR.bmp", 48, 48, true, RGB(255, 0, 255));

	_loading->LoadNormalImage("dirtFloor1", "Images/villageFloor/townBridge/Dirt_H_0.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("dirtFloor2", "Images/villageFloor/townBridge/Dirt_H_1.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("dirtFloor3", "Images/villageFloor/townBridge/Dirt_H_2.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("dirtFloor4", "Images/villageFloor/townBridge/Dirt_H_3.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("dirtFloor5", "Images/villageFloor/townBridge/Dirt_H_4.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("dirtFloor6", "Images/villageFloor/townBridge/Dirt_H_5.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("dirtFloor7", "Images/villageFloor/townBridge/Dirt_H_12.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("dirtFloor8", "Images/villageFloor/townBridge/Dirt_H_13.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("dirtFloor9", "Images/villageFloor/townBridge/Dirt_H_StairL.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("dirtFloor10", "Images/villageFloor/townBridge/Dirt_H_StairL2.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("dirtFloor11", "Images/villageFloor/townBridge/Dirt_H_StairR.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("dirtFloor12", "Images/villageFloor/townBridge/Dirt_H_StairR2.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("dirtFloor13", "Images/villageFloor/townBridge/DirtToBaicT2_H_0.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("dirtFloor14", "Images/villageFloor/townBridge/DirtToBaicT2_H_1.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("dirtFloor15", "Images/villageFloor/townBridge/DirtToTown_H_0.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("dirtFloor16", "Images/villageFloor/townBridge/DirtToTown_H_1.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("dirtFloor17", "Images/villageFloor/townBridge/DirtToGrass_H_0.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("dirtFloor18", "Images/villageFloor/townBridge/DirtToGrass_H_1.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("dirtFloor19", "Images/villageFloor/townBridge/Grass_H_1.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("dirtFloor20", "Images/villageFloor/townBridge/Grass_H_1_1.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("dirtFloor21", "Images/villageFloor/townBridge/Grass_H_1_2.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("dirtFloor22", "Images/villageFloor/townBridge/Grass_H_1_3.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("dirtFloor23", "Images/villageFloor/townBridge/Grass_H_1_4.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("dirtFloor24", "Images/villageFloor/townBridge/Grass_H_1_5.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("dirtFloor25", "Images/villageFloor/townBridge/Grass_H_StairL.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("dirtFloor26", "Images/villageFloor/townBridge/Grass_H_StairR.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("dirtFloor27", "Images/villageFloor/townBridge/Grass_H_StairL2.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("dirtFloor28", "Images/villageFloor/townBridge/Grass_H_StairR2.bmp", 48, 48, true, RGB(255, 0, 255));

	// MONSTER //
	_loading->LoadFrameImage("SealStone", "Images/Monster/SealStone.bmp", 768, 96, 8, 1, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("AbyssBansheeIdle", "Images/Monster/AbyssBansheeIdle.bmp", 360, 132, 6, 2, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("AbyssBansheeAttack", "Images/Monster/AbyssBansheeAttack.bmp", 726, 132, 11, 2, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("BansheeIdle", "Images/Monster/BansheeIdle.bmp", 360, 132, 6, 2, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("BansheeAttack", "Images/Monster/BansheeAttack.bmp", 360, 132, 6, 2, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("BatRedIdle", "Images/Monster/BatRedIdle.bmp", 558, 120, 6, 2, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("BatRedAttack", "Images/Monster/BatRedAttack.bmp", 930, 120, 10, 2, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("BatIdle", "Images/Monster/BatIdle.bmp", 558, 120, 6, 2, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("BombBat", "Images/Monster/BombBat.bmp", 342, 72, 6, 2, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("BombBatExplosionBegin", "Images/Monster/BombBatExplosionBegin.bmp", 1377, 81, 18, 1, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("GiantBat", "Images/Monster/GiantBat.bmp", 1239, 210, 7, 2, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("GiantBatAttack", "Images/Monster/GiantBatAttack.bmp", 1770, 234, 10, 2, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("RedGiantBat", "Images/Monster/RedGiantBat.bmp", 1239, 210, 7, 2, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("RedGiantBatAttack", "Images/Monster/RedGiantBatAttack.bmp", 1770, 234, 10, 2, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("LilithIdle", "Images/Monster/LilithIdle.bmp", 936, 156, 12, 2, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("LilithCatch", "Images/Monster/LilithCatch.bmp", 78, 156, 1, 2, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("LilithMove", "Images/Monster/LilithMove.bmp", 468, 156, 6, 2, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("LittleGhost", "Images/Monster/LittleGhost.bmp", 360, 120, 6, 2, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("LittleGhostAttack", "Images/Monster/LittleGhostAttack.bmp", 180, 120, 3, 2, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("SkelIdle", "Images/Monster/SkelIdle.bmp", 42, 114, 1, 2, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("SkelWalk", "Images/Monster/SkelWalk.bmp", 252, 114, 6, 2, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("SkelCorpse", "Images/Monster/SkelCorpse.bmp", 33, 24, 1, 1, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("SkelDogIdle", "Images/Monster/SkelDogIdle.bmp", 300, 108, 5, 2, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("SkelDogRun", "Images/Monster/SkelDogRun.bmp", 420, 108, 7, 2, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("SkelDogDie", "Images/Monster/SkelDogDie.bmp", 60, 108, 1, 2, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("BigWhiteSkelIdle", "Images/Monster/BigWhiteSkelIdle.bmp", 594, 288, 6, 2, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("BigWhiteSkelMove", "Images/Monster/BigWhiteSkelMove.bmp", 594, 288, 6, 2, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("BigWhiteSkelAttack", "Images/Monster/BigWhiteSkelAttack.bmp", 2196, 288, 12, 2, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("MinotaursIdle", "Images/Monster/MinotaursIdle.bmp", 936, 228, 6, 2, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("MinotaursCharge", "Images/Monster/MinotaursCharge.bmp", 1272, 216, 8, 2, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("MinotaursAttack", "Images/Monster/MinotaursAttack.bmp", 1176, 300, 7, 2, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("SkellBossIdle", "Images/Monster/Boss/SkellBossIdle.bmp", 2100, 285, 10, 1, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("SkellBossAttack", "Images/Monster/Boss/SkellBossAttack.bmp", 2100, 384, 10, 1, true, RGB(255, 0, 255));

	// BULLET //
	_loading->LoadFrameImage("BatBullet", "Images/Monster/Bullet/BatBullet.bmp", 210, 42, 5, 1, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("BatBulletHit", "Images/Monster/Bullet/BatBulletHit.bmp", 546, 78, 7, 1, true, RGB(255, 0, 255));

	// EFFECT //
	_loading->LoadFrameImage("monsterSpawnEffect", "Images/Etc/monsterSpawnEffect.bmp", 1302, 93, 14, 1, true, RGB(255, 0, 255));

	// MINIMAP //
	_loading->LoadNormalImage("MiniMapPixel", "Images/MiniMapPixel.bmp", 5, 5);

	// COLLISIONIMAGE //
	_loading->LoadNormalImage("Half", "Images/GridPixelCollision/Half.bmp", 48, 96, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Half_Red_CollisionStairLeft", "Images/GridPixelCollision/Half_Red_CollisionStairLeft.bmp", 48, 96, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Half_Red_CollisionStairRight", "Images/GridPixelCollision/Half_Red_CollisionStairRight.bmp", 48, 96, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("HalfPlatformSecondFloor", "Images/GridPixelCollision/HalfPlatformSecondFloor.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("HalfPlatformStone", "Images/GridPixelCollision/HalfPlatformStone.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("HalfPlatformWood", "Images/GridPixelCollision/HalfPlatformWood.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("No_Collision", "Images/GridPixelCollision/No_Collision.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Red_CollisionAll", "Images/GridPixelCollision/Red_CollisionAll.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Red_CollisionStairLeft", "Images/GridPixelCollision/Red_CollisionStairLeft.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Red_CollisionStairLeft_2", "Images/GridPixelCollision/Red_CollisionStairLeft_2.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Red_CollisionStairRight", "Images/GridPixelCollision/Red_CollisionStairRight.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Red_CollisionStairRight_2", "Images/GridPixelCollision/Red_CollisionStairRight_2.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Blue_CollisionStairLeft", "Images/GridPixelCollision/Blue_CollisionStairLeft.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Blue_CollisionStairRight", "Images/GridPixelCollision/Blue_CollisionStairRight.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("VillageHalf", "Images/GridPixelCollision/VillageHalf.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Green_CollisionAll", "Images/GridPixelCollision/Green_CollisionAll.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Green_CollisionAll2", "Images/GridPixelCollision/Green_CollisionAll2.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Green_CollisionAll3", "Images/GridPixelCollision/Green_CollisionAll3.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->LoadNormalImage("Green_CollisionAll4", "Images/GridPixelCollision/Green_CollisionAll4.bmp", 48, 48, true, RGB(255, 0, 255));
	
	_loading->LoadFrameImage("baseCharIdle", "Images/player/baseCharIdle.bmp", 285, 132, 5, 2, true, RGB(255, 0, 255));
	_loading->LoadFrameImage("baseCharRun", "Images/player/baseCharRun.bmp", 504, 132, 8, 2, true, RGB(255, 0, 255));

	_loading->LoadNormalImage("PixelMapIg", "Images/PixelMapIg.bmp", 9600, 9600, true, RGB(255, 255, 255));
	_loading->LoadNormalImage("MiniMapGroundIg", "Images/PixelMapIg.bmp", 9600, 9600, true, RGB(255, 255, 255));
	_loading->LoadNormalImage("Layer1MapIg", "Images/PixelMapIg.bmp", 9600, 9600, true, RGB(255, 255, 255));
	_loading->LoadNormalImage("Layer2MapIg", "Images/PixelMapIg.bmp", 9600, 9600, true, RGB(255, 255, 255));
}

void loadingScene::loadingSound()
{
}
