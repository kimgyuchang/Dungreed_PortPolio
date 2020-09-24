#include "stdafx.h"
#include "loadingScene.h"

HRESULT loadingScene::init()
{
	//로딩클래스 초기화

	_loading = new loading();
	_loading->init();
	//SOUNDMANAGER->addSound("PuzzleBubbleSound", "PuzzleBubbleSound.wav", true, true);
	//SOUNDMANAGER->play("PuzzleBubbleSound",0.1);

	this->loadingImage();
	this->loadingSound();
	this->loadingFont();

	return S_OK;
}

void loadingScene::release()
{
	_loading->release();
	SAFE_DELETE(_loading);
}

void loadingScene::update()
{
	_loading->update();
	
	//로딩완료후 화면 변경
	if (_loading->loadingDone())
	{
		//	SOUNDMANAGER->stop("PuzzleBubbleSound");
		SCENEMANAGER->loadScene("맵씬");
	}
}

void loadingScene::render()
{
	_loading->render();

	textOut(getMemDC(), 10, 10, "로딩화면");

	IMAGEMANAGER->frameRender("number", getMemDC(), 710, 500,(int)((float)_loading->getCurrentGauge() /(float)_loading->getLoadItem().size()*100) % 10, 0);
	if ((int)((float)_loading->getCurrentGauge()*(100 / (float)_loading->getLoadItem().size()) / 10) > 0)
	IMAGEMANAGER->frameRender("number", getMemDC(), 690, 500, (float)_loading->getCurrentGauge()*(100/(float)_loading->getLoadItem().size()) / 10, 0);
}

void loadingScene::loadingFont()
{
	AddFontResource("Font/HS겨울눈꽃체.ttf");
	AddFontResource("Font/BMYEONSUNG_ttf.ttf");
	AddFontResource("Font/neodgm.ttf");
}

void loadingScene::loadingImage()
{
	// STAGE 1 //
	_loading->loadImage("Stage1_Tile0", "Images/1Floor/Basic_H_Type2_0.bmp", 48, 48, true, RGB(255,0,255));
	_loading->loadImage("Stage1_Tile1", "Images/1Floor/Basic_H_Type2_1.bmp", 48, 48, true, RGB(255,0,255));
	_loading->loadImage("Stage1_Tile2", "Images/1Floor/Basic_H_Type2_2.bmp", 48, 48, true, RGB(255,0,255));
	_loading->loadImage("Stage1_Tile3", "Images/1Floor/Basic_H_Type2_3.bmp", 48, 48, true, RGB(255,0,255));
	_loading->loadImage("Stage1_Tile4", "Images/1Floor/Basic_H_Type2_4.bmp", 48, 48, true, RGB(255,0,255));
	_loading->loadImage("Stage1_Tile5", "Images/1Floor/Basic_H_Type2_5.bmp", 48, 48, true, RGB(255,0,255));
	_loading->loadImage("Stage1_Tile6", "Images/1Floor/Basic_H_Type2_6.bmp", 48, 48, true, RGB(255,0,255));
	_loading->loadImage("Stage1_Tile7", "Images/1Floor/Basic_H_Type2_7.bmp", 48, 48, true, RGB(255,0,255));
	_loading->loadImage("Stage1_Tile8", "Images/1Floor/Basic_H_Type2_8.bmp", 48, 48, true, RGB(255,0,255));

	_loading->loadImage("Stage1_Tile9", "Images/1Floor/BasicStone_BottomCenter.bmp", 48, 48, true, RGB(255,0,255));
	_loading->loadImage("Stage1_Tile10", "Images/1Floor/BasicStone_TopCenter_2.bmp", 48, 48, true, RGB(255,0,255));
	_loading->loadImage("Stage1_Tile11", "Images/1Floor/BasicStone_TopCenter_4.bmp", 48, 48, true, RGB(255,0,255));
	_loading->loadImage("Stage1_Tile12", "Images/1Floor/1FloorTileLeft.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->loadImage("Stage1_Tile13", "Images/1Floor/1FloorTileMiddle.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->loadImage("Stage1_Tile14", "Images/1Floor/1FloorTileRight.bmp", 48, 48, true, RGB(255, 0, 255));

	_loading->loadImage("Stage1_Tile15", "Images/1Floor/Tile_H1.bmp", 48, 48, true, RGB(255,0,255));
	_loading->loadImage("Stage1_Tile16", "Images/1Floor/Tile_H3.bmp", 48, 48, true, RGB(255,0,255));
	_loading->loadImage("Stage1_Tile17", "Images/1Floor/Tile_H4.bmp", 48, 48, true, RGB(255,0,255));
	_loading->loadImage("Stage1_Tile18", "Images/1Floor/Tile_H5.bmp", 48, 48, true, RGB(255,0,255));
	_loading->loadImage("Stage1_Tile19", "Images/1Floor/Tile_H7.bmp", 48, 48, true, RGB(255,0,255));

	_loading->loadImage("Stage1_Tile20", "Images/1Floor/Tile_H9.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->loadImage("Stage1_Tile21", "Images/1Floor/Tile_H10.bmp", 48, 48, true, RGB(255,0,255));
	_loading->loadImage("Stage1_Tile22", "Images/1Floor/Tile_H11.bmp", 48, 48, true, RGB(255,0,255));
	_loading->loadImage("Stage1_Tile23", "Images/1Floor/Tile_H12.bmp", 48, 48, true, RGB(255,0,255));
	_loading->loadImage("Stage1_Tile24", "Images/1Floor/Tile_H14.bmp", 48, 48, true, RGB(255,0,255));

	_loading->loadImage("Stage1_Tile25", "Images/1Floor/Tile_Marble_Stair_BottomLeft.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->loadImage("Stage1_Tile26", "Images/1Floor/Tile_Marble_Stair_BottomRight.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->loadImage("Stage1_Tile27", "Images/1Floor/Tile_Marble_Stair_TopLeft.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->loadImage("Stage1_Tile28", "Images/1Floor/Tile_Marble_Stair_TopRight.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->loadImage("Stage1_Tile29", "Images/1Floor/Tile_Stair_BottomLeft.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->loadImage("Stage1_Tile30", "Images/1Floor/Tile_Stair_BottomRight.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->loadImage("Stage1_Tile31", "Images/1Floor/Tile_Stair_TopLeft.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->loadImage("Stage1_Tile32", "Images/1Floor/Tile_Stair_TopRight.bmp", 48, 48, true, RGB(255, 0, 255));
	
	_loading->loadImage("Stage1_Tile33", "Images/1Floor/Tile_Slim_Bottom.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->loadImage("Stage1_Tile34", "Images/1Floor/Tile_Slim_BottomCenter.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->loadImage("Stage1_Tile35", "Images/1Floor/Tile_Slim_Left.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->loadImage("Stage1_Tile36", "Images/1Floor/Tile_Slim_MiddleRight.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->loadImage("Stage1_Tile37", "Images/1Floor/Tile_Slim_Right.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->loadImage("Stage1_Tile38", "Images/1Floor/Tile_Slim_Top.bmp", 48, 48, true, RGB(255, 0, 255));
	
	_loading->loadImage("Stage1_Tile39", "Images/1Floor/Wall_Basic_0.bmp", 48, 48, true, RGB(255,0,255));
	_loading->loadImage("Stage1_Tile40", "Images/1Floor/Wall_Basic_1.bmp", 48, 48, true, RGB(255,0,255));
	_loading->loadImage("Stage1_Tile41", "Images/1Floor/Wall_Basic_2.bmp", 48, 48, true, RGB(255,0,255));
	_loading->loadImage("Stage1_Tile42", "Images/1Floor/Wall_Basic_3.bmp", 48, 48, true, RGB(255,0,255));
	_loading->loadImage("Stage1_Tile43", "Images/1Floor/Wall_Basic_4.bmp", 48, 48, true, RGB(255,0,255));
	_loading->loadImage("Stage1_Tile44", "Images/1Floor/Wall_Basic_5.bmp", 48, 48, true, RGB(255,0,255));
	_loading->loadImage("Stage1_Tile45", "Images/1Floor/Wall_Basic_12.bmp", 48, 48, true, RGB(255,0,255));
	_loading->loadImage("Stage1_Tile46", "Images/1Floor/Wall_Basic_13.bmp", 48, 48, true, RGB(255,0,255));
	_loading->loadImage("Stage1_Tile47", "Images/1Floor/Wall_Basic_14.bmp", 48, 48, true, RGB(255,0,255));
	
	_loading->loadImage("Stage1_Tile48", "Images/1Floor/Wall_Basic_6.bmp", 48, 48, true, RGB(255,0,255));
	_loading->loadImage("Stage1_Tile49", "Images/1Floor/Wall_Basic_8.bmp", 48, 48, true, RGB(255,0,255));
	_loading->loadImage("Stage1_Tile50", "Images/1Floor/Wall_Basic_15.bmp", 48, 48, true, RGB(255,0,255));
	_loading->loadImage("Stage1_Tile51", "Images/1Floor/Wall_Basic_16.bmp", 48, 48, true, RGB(255,0,255));
	_loading->loadImage("Stage1_Tile52", "Images/1Floor/Wall_Basic_9.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->loadImage("Stage1_Tile53", "Images/1Floor/Wall_Basic_10.bmp", 48, 48, true, RGB(255,0,255));
	_loading->loadImage("Stage1_Tile54", "Images/1Floor/Wall_Basic_11.bmp", 48, 48, true, RGB(255,0,255));
	
	_loading->loadImage("Stage1_Tile55", "Images/1Floor/Wall_Basic_Ceiling_0.bmp", 48, 48, true, RGB(255,0,255));
	_loading->loadImage("Stage1_Tile56", "Images/1Floor/Wall_Basic_Ceiling_1.bmp", 48, 48, true, RGB(255,0,255));
	_loading->loadImage("Stage1_Tile57", "Images/1Floor/Wall_Basic_Ceiling_2.bmp", 48, 48, true, RGB(255,0,255));
	_loading->loadImage("Stage1_Tile58", "Images/1Floor/Wall_Basic_Ceiling_3.bmp", 48, 48, true, RGB(255,0,255));
	_loading->loadImage("Stage1_Tile59", "Images/1Floor/Wall_Basic_Ceiling_4.bmp", 48, 48, true, RGB(255,0,255));
	_loading->loadImage("Stage1_Tile60", "Images/1Floor/Wall_Basic_Ceiling_5.bmp", 48, 48, true, RGB(255,0,255));
	
	_loading->loadImage("Stage1_Tile61", "Images/1Floor/Wall_Type2_StairLeft.bmp", 48, 48, true, RGB(255, 0, 255));
	
	_loading->loadImage("Stage1_Tile62", "Images/1Floor/Wall_Cracked_0.bmp", 48, 48, true, RGB(255,0,255));
	_loading->loadImage("Stage1_Tile63", "Images/1Floor/Wall_Cracked_1.bmp", 48, 48, true, RGB(255,0,255));
	_loading->loadImage("Stage1_Tile64", "Images/1Floor/Wall_Cracked_2.bmp", 48, 48, true, RGB(255,0,255));
	_loading->loadImage("Stage1_Tile65", "Images/1Floor/Wall_Cracked_3.bmp", 48, 48, true, RGB(255,0,255));
	_loading->loadImage("Stage1_Tile66", "Images/1Floor/Wall_Cracked_4.bmp", 48, 48, true, RGB(255,0,255));
	_loading->loadImage("Stage1_Tile67", "Images/1Floor/Wall_Cracked_5.bmp", 48, 48, true, RGB(255,0,255));
	_loading->loadImage("Stage1_Tile68", "Images/1Floor/Wall_Cracked_6.bmp", 48, 48, true, RGB(255,0,255));

	_loading->loadImage("Stage1_Tile69", "Images/1Floor/Wall_H0.bmp", 48, 48, true, RGB(255,0,255));
	_loading->loadImage("Stage1_Tile70", "Images/1Floor/Wall_H1.bmp", 48, 48, true, RGB(255,0,255));
	_loading->loadImage("Stage1_Tile71", "Images/1Floor/Wall_H2.bmp", 48, 48, true, RGB(255,0,255));
	_loading->loadImage("Stage1_Tile72", "Images/1Floor/Wall_H3.bmp", 48, 48, true, RGB(255,0,255));
	_loading->loadImage("Stage1_Tile73", "Images/1Floor/Wall_H4_1.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->loadImage("Stage1_Tile74", "Images/1Floor/Wall_H4_2.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->loadImage("Stage1_Tile75", "Images/1Floor/Wall_H6.bmp", 48, 48, true, RGB(255,0,255));
	_loading->loadImage("Stage1_Tile76", "Images/1Floor/Wall_H8.bmp", 48, 48, true, RGB(255,0,255));
	_loading->loadImage("Stage1_Tile77", "Images/1Floor/Wall_H9.bmp", 48, 48, true, RGB(255,0,255));
	_loading->loadImage("Stage1_Tile78", "Images/1Floor/Wall_H10.bmp", 48, 48, true, RGB(255,0,255));
	_loading->loadImage("Stage1_Tile79", "Images/1Floor/Wall_H11.bmp", 48, 48, true, RGB(255,0,255));
	_loading->loadImage("Stage1_Tile80", "Images/1Floor/Wall_H12.bmp", 48, 48, true, RGB(255,0,255));
	
	// UNUSE UIBASE //
	_loading->loadImage("UIBaseBig", "Images/UI/Base.bmp", 500, 300 , true ,RGB(255,0,255));
	_loading->loadImage("UIBaseMiddle", "Images/UI/Base.bmp", 222*2, 189*2 , true ,RGB(255,0,255));
	_loading->loadImage("UIBaseSmall", "Images/UI/Base.bmp", 222, 189 , true ,RGB(255,0,255));

	// OBJECT //
	_loading->loadImage("BigBox0", "Images/Object/BigBox0.bmp", 69, 48, true, RGB(255,0,255));
	_loading->loadImage("Bone0", "Images/Object/Bone0.bmp", 36, 18, true, RGB(255,0,255));
	_loading->loadImage("Bone1", "Images/Object/Bone1.bmp", 42, 18, true, RGB(255,0,255));
	_loading->loadImage("Box0", "Images/Object/Box0.bmp", 48, 36, true, RGB(255,0,255));
	_loading->loadImage("OakDrum0", "Images/Object/OakDrum0.bmp", 39, 42, true, RGB(255,0,255));
	_loading->loadImage("WormPassage00", "Images/Object/WormPassage00.bmp", 81, 93, true, RGB(255,0,255));
	
	// 미회전 //
	_loading->loadFrameImage("StrawberryFountain0", "Images/Object/StrawberryFountain0.bmp", 480, 96, 5, 1, true, RGB(255,0,255));
	_loading->loadFrameImage("WormPassageEat00", "Images/Object/WormPassageEat00.bmp", 324, 93, 4, 1, true, RGB(255,0,255));
	_loading->loadFrameImage("WormPassageIdle00", "Images/Object/WormPassageIdle00.bmp", 729, 93, 9, 1, true, RGB(255,0,255));

	// 회전 //
	_loading->loadFrameImage("gear", "Images/Object/gear.bmp", 1296, 108, 12, 1, true, RGB(255,0,255), true);
	_loading->loadFrameImage("Gear_Small", "Images/Object/Gear_Small.bmp", 828, 69, 12, 1, true, RGB(255,0,255), true);
	_loading->loadFrameImage("Gear_Small_Small", "Images/Object/Gear_Small_Small.bmp", 612, 51, 12, 1, true, RGB(255,0,255), true);

	// UI //
	_loading->loadImage("UpButton", "Images/UI/FullWindowExitButton_Selected.bmp", 66, 57 , true ,RGB(255,0,255));
	_loading->loadImage("RightButton", "Images/UI/FullWindowExitButton_Selected.bmp", 66, 57 , true ,RGB(255,0,255));
	_loading->loadImage("DownButton", "Images/UI/FullWindowExitButton.bmp", 66, 57 , true ,RGB(255,0,255));
	_loading->loadImage("LeftButton", "Images/UI/FullWindowExitButton.bmp", 66, 57 , true ,RGB(255,0,255));
	_loading->loadImage("mapWidthBox", "Images/UI/AbilityTextBar.bmp", 120, 100 , true ,RGB(255,0,255));
	_loading->loadImage("mapHeightBox", "Images/UI/AbilityTextBar.bmp", 120, 100 , true ,RGB(255,0,255));
	_loading->loadImage("ShortcutKeyGround", "Images/UI/AltarButton1.bmp", 800, 87, true ,RGB(255,0,255));
	_loading->loadImage("ShortcutKey1", "Images/UI/IconGray.bmp", 57, 57, true ,RGB(255,0,255));
	_loading->loadImage("ShortcutKey2", "Images/UI/IconWhite1.bmp", 57, 57, true ,RGB(255,0,255));
	
	_loading->loadImage("AbilityTextBar", "Images/UI/AbilityTextBar.bmp", 33, 54, true ,RGB(255,0,255));
	_loading->loadImage("accessoryZone", "Images/UI/accessoryZone.bmp", 96, 75, true ,RGB(255,0,255));
	_loading->loadImage("AltarButton0", "Images/UI/AltarButton0.bmp", 266, 87, true ,RGB(255,0,255));
	_loading->loadImage("AltarButton1", "Images/UI/AltarButton1.bmp", 266, 87, true ,RGB(255,0,255));
	_loading->loadImage("AltarGaugeBase", "Images/UI/AltarGaugeBase.bmp", 116, 21, true ,RGB(255,0,255));
	_loading->loadImage("AnvilCloseButton", "Images/UI/AnvilCloseButton.bmp", 39, 39, true ,RGB(255,0,255));
	_loading->loadImage("AnvilCloseButtonSelected", "Images/UI/AnvilCloseButtonSelected.bmp", 39, 39, true ,RGB(255,0,255));
	_loading->loadImage("AnvilUI", "Images/UI/AnvilUI.bmp", 408, 153, true ,RGB(255,0,255));
	_loading->loadImage("Base", "Images/UI/Base.bmp", 222, 189, true,RGB(255,0,255));
	_loading->loadImage("Base_0", "Images/UI/Base_0.bmp", 333, 396, true ,RGB(255,0,255));
	_loading->loadImage("Base_1", "Images/UI/Base_1.bmp", 333, 51, true ,RGB(255,0,255));
	_loading->loadImage("Base_2", "Images/UI/Base_2.bmp", 339, 51, true ,RGB(255,0,255));
	_loading->loadImage("Base_3", "Images/UI/Base_3.bmp", 579, 396, true ,RGB(255,0,255));
	_loading->loadImage("BasicCursor", "Images/UI/BasicCursor.bmp", 27, 33, true ,RGB(255,0,255));
	_loading->loadImage("BossLifeBack", "Images/UI/BossLifeBack.bmp", 375, 48, true ,RGB(255,0,255));
	_loading->loadImage("BossLifeBase", "Images/UI/BossLifeBase.bmp", 375, 48, true ,RGB(255,0,255));
	_loading->loadImage("BuildCompleteBase_0", "Images/UI/BuildCompleteBase_0.bmp", 176, 98, true ,RGB(255,0,255));
	_loading->loadImage("BuildCompleteBase_1", "Images/UI/BuildCompleteBase_1.bmp", 381, 294, true ,RGB(255,0,255));
	_loading->loadImage("BuildMenu", "Images/UI/BuildMenu.bmp", 858, 105, true ,RGB(255,0,255));
	_loading->loadImage("BuildMenu_Selected", "Images/UI/BuildMenu_Selected.bmp", 858, 105, true ,RGB(255,0,255));
	_loading->loadImage("Choice", "Images/UI/Choice.bmp", 27, 27, true ,RGB(255,0,255));
	_loading->loadImage("Clear", "Images/UI/Clear.bmp", 192, 30, true ,RGB(255,0,255));
	_loading->loadImage("CostumeBack", "Images/UI/CostumeBack.bmp", 222, 297, true ,RGB(255,0,255));
	_loading->loadImage("CostumeBase_0", "Images/UI/CostumeBase_0.bmp", 960, 87, true ,RGB(255,0,255));
	_loading->loadImage("CostumeBase_1", "Images/UI/CostumeBase_1.bmp", 960, 150, true ,RGB(255,0,255));
	_loading->loadImage("CostumeEquipped", "Images/UI/CostumeEquipped.bmp", 204, 285, true ,RGB(255,0,255));
	_loading->loadImage("CostumeLocked", "Images/UI/CostumeLocked.bmp", 204, 285, true ,RGB(255,0,255));
	_loading->loadImage("CostumeOver", "Images/UI/CostumeOver.bmp", 204, 285, true ,RGB(255,0,255));
	_loading->loadImage("CostumeUnlocked", "Images/UI/CostumeUnlocked.bmp", 204, 285, true ,RGB(255,0,255));
	_loading->loadImage("DashBase", "Images/UI/DashBase.bmp", 27, 24, true ,RGB(255,0,255));
	_loading->loadImage("DashBaseLeftEnd", "Images/UI/DashBaseLeftEnd.bmp", 6, 24, true ,RGB(255,0,255));
	_loading->loadImage("DashBaseRightEnd", "Images/UI/DashBaseRightEnd.bmp", 6, 24, true ,RGB(255,0,255));
	_loading->loadImage("DashCount", "Images/UI/DashCount.bmp", 27, 12, true ,RGB(255,0,255));
	_loading->loadImage("DashCountBase_0", "Images/UI/DashCountBase_0.bmp", 33, 24, true ,RGB(255,0,255));
	_loading->loadImage("DemensionVault0", "Images/UI/DemensionVault0.bmp", 99, 99, true ,RGB(255,0,255));
	_loading->loadImage("DemensionVault1", "Images/UI/DemensionVault1.bmp", 99, 99, true ,RGB(255,0,255));
	_loading->loadImage("DungeonMenu 1", "Images/UI/DungeonMenu 1.bmp", 960, 120, true ,RGB(255,0,255));
	_loading->loadImage("DungeonMenu 2", "Images/UI/DungeonMenu 2.bmp", 12, 337, true ,RGB(255,0,255));
	_loading->loadImage("DungeonShopBase", "Images/UI/DungeonShopBase.bmp", 366, 564, true ,RGB(255,0,255));
	_loading->loadImage("Empty", "Images/UI/Empty.bmp", 96, 96, true ,RGB(255,0,255));
	_loading->loadImage("EndurancePain", "Images/UI/EndurancePain.bmp", 51, 51, true ,RGB(255,0,255));
	_loading->loadImage("EquippedWeaponBase", "Images/UI/EquippedWeaponBase.bmp", 102, 72, true ,RGB(255,0,255));
	_loading->loadImage("FullWindowExitButton", "Images/UI/FullWindowExitButton.bmp", 66, 57, true ,RGB(255,0,255));
	_loading->loadImage("FullWindowExitButton_Selected", "Images/UI/FullWindowExitButton_Selected.bmp", 66, 57, true ,RGB(255,0,255));
	_loading->loadImage("IconGray", "Images/UI/IconGray.bmp", 57, 57, true ,RGB(255,0,255));
	_loading->loadImage("IconWhite #16786", "Images/UI/IconWhite #16786.bmp", 57, 57, true ,RGB(255,0,255));
	_loading->loadImage("IconWhite", "Images/UI/IconWhite.bmp", 57, 57, true ,RGB(255,0,255));
	_loading->loadImage("IconWhite_Trans", "Images/UI/IconWhite_Trans.bmp", 57, 57, true ,RGB(255,0,255));
	_loading->loadImage("IconYellow_Trans", "Images/UI/IconYellow_Trans.bmp", 57, 57, true ,RGB(255,0,255));
	_loading->loadImage("OptionArrow0", "Images/UI/OptionArrow0.bmp", 51, 33, true ,RGB(255,0,255));
	_loading->loadImage("OptionArrow1", "Images/UI/OptionArrow1.bmp", 51, 33, true ,RGB(255,0,255));
	_loading->loadImage("Result_0", "Images/UI/Result_0.bmp", 432, 45, true ,RGB(255,0,255));
	_loading->loadImage("Result_1", "Images/UI/Result_1.bmp", 432, 147, true ,RGB(255,0,255));
	_loading->loadImage("Result_2", "Images/UI/Result_2.bmp", 150, 45, true ,RGB(255,0,255));
	_loading->loadImage("ScrollRect", "Images/UI/ScrollRect.bmp", 906, 396, true ,RGB(255,0,255));
	_loading->loadImage("SlotDeleteButton", "Images/UI/SlotDeleteButton.bmp", 186, 51, true ,RGB(255,0,255));
	_loading->loadImage("SlotDeleteButton_Rev", "Images/UI/SlotDeleteButton_Rev.bmp", 51, 186, true ,RGB(255,0,255));

	// MAPTOOL 미리보기 //
	_loading->loadImage("CheckImage", "Images/GridBound.bmp", 48, 48, true, RGB(255, 0, 255));
	_loading->loadImage("CheckImageRed", "Images/GridBoundRed.bmp", 48, 48, true, RGB(255, 0, 255));
}

void loadingScene::loadingSound()
{
}
