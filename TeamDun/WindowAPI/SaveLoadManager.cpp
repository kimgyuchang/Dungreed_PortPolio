#include "stdafx.h"
#include "SaveLoadManager.h"

HRESULT SaveLoadManager::Init()
{
	return S_OK;
}

/// <summary>
/// 데이터 세이브
/// </summary>
void SaveLoadManager::SaveData()
{
	Player* p = ENTITYMANAGER->getPlayer();

	char moveSpeed[30]; sprintf(moveSpeed, "%f", p->GetMoveSpeed());  INIDATA->addData("player", "moveSpeed", moveSpeed);
	char jumpPower[30]; sprintf(jumpPower, "%f", p->GetJumpPower());  INIDATA->addData("player", "jumpPower", jumpPower);
	char maxDashCount[30]; sprintf(maxDashCount, "%d", p->GetMaxDashCount());  INIDATA->addData("PLAYER", "maxDashCount", maxDashCount);
	char dashRestoreTime[30]; sprintf(dashRestoreTime, "%d", p->GetDashRestoreTime());  INIDATA->addData("PLAYER", "dashRestoreTime", dashRestoreTime);
	char moveSpeedPer[30]; sprintf(moveSpeedPer, "%f", p->GetMoveSpeedPer());  INIDATA->addData("PLAYER", "moveSpeedPer", moveSpeedPer);
	char minDamage[30]; sprintf(minDamage, "%d", p->GetMinDamage());  INIDATA->addData("PLAYER", "minDamage", minDamage);
	char maxDamage[30]; sprintf(maxDamage, "%d", p->GetMaxDamage());  INIDATA->addData("PLAYER", "maxDamage", maxDamage);
	char power[30]; sprintf(power, "%d", p->GetPower());  INIDATA->addData("PLAYER", "power", power);
	char trueDamage[30]; sprintf(trueDamage, "%d", p->GetTrueDamage());  INIDATA->addData("PLAYER", "trueDamage", trueDamage);
	char atkSpeed[30]; sprintf(atkSpeed, "%f", p->GetAtkSpeed());  INIDATA->addData("PLAYER", "atkSpeed", atkSpeed);
	char criticalPercent[30]; sprintf(criticalPercent, "%f", p->GetCriPer());  INIDATA->addData("PLAYER", "criticalPercent", criticalPercent);
	char criticalDamage[30]; sprintf(criticalDamage, "%f", p->GetCriDamage());  INIDATA->addData("PLAYER", "criticalDamage", criticalDamage);
	char dashDamage[30]; sprintf(dashDamage, "%f", p->GetDashDamage());  INIDATA->addData("PLAYER", "dashDamage", dashDamage);
	char reloadTime[30]; sprintf(reloadTime, "%f", p->GetReloadTime());  INIDATA->addData("PLAYER", "reloadTime", reloadTime);
	char initHp[30]; sprintf(initHp, "%d", p->GetInitHp());  INIDATA->addData("PLAYER", "initHp", initHp);
	char defence[30]; sprintf(defence, "%f", p->GetDefence());  INIDATA->addData("PLAYER", "defence", defence);
	char evasion[30]; sprintf(evasion, "%f", p->GetEvasion());  INIDATA->addData("PLAYER", "evasion", evasion);
	char toughness[30]; sprintf(toughness, "%f", p->GetToughness());  INIDATA->addData("PLAYER", "toughness", toughness);
	char block[30]; sprintf(block, "%f", p->GetBlock());  INIDATA->addData("PLAYER", "block", block);
	char finalDamage[30]; sprintf(finalDamage, "%d", p->GetFinalDamage());  INIDATA->addData("PLAYER", "finalDamage", finalDamage);
	char finalDamagePercent[30]; sprintf(finalDamagePercent, "%f", p->GetFinalDamagePer());  INIDATA->addData("PLAYER", "finalDamagePercent", finalDamagePercent);
	char reloadSpeed[30]; sprintf(reloadSpeed, "%f", p->GetReloadSpeed());  INIDATA->addData("PLAYER", "reloadSpeed", reloadSpeed);
	char fireAccuracy[30]; sprintf(fireAccuracy, "%f", p->GetFireAccuracy());  INIDATA->addData("PLAYER", "fireAccuracy", fireAccuracy);
	char atkSpeedPer[30]; sprintf(atkSpeedPer, "%f", p->GetAtkSpeedPer());  INIDATA->addData("PLAYER", "atkSpeedPer", atkSpeedPer);
	char maxHp[30]; sprintf(maxHp, "%d", p->GetMaxHp());  INIDATA->addData("PLAYER", "maxHp", maxHp);
	char maxHpPercent[30]; sprintf(maxHpPercent, "%f", p->GetMaxHpPer());  INIDATA->addData("PLAYER", "maxHpPercent", maxHpPercent);
	char immuneFire[30]; sprintf(immuneFire, "%d", p->GetImmuneFire());  INIDATA->addData("PLAYER", "immuneFire", immuneFire);
	char immuneIce[30]; sprintf(immuneIce, "%d", p->GetImmuneIce());  INIDATA->addData("PLAYER", "immuneIce", immuneIce);
	char immuneElectric[30]; sprintf(immuneElectric, "%d", p->GetImmuneElec());  INIDATA->addData("PLAYER", "immuneElectric", immuneElectric);
	char immunePosion[30]; sprintf(immunePosion, "%d", p->GetImmunePosion());  INIDATA->addData("PLAYER", "immunePosion", immunePosion);
	char immuneStun[30]; sprintf(immuneStun, "%d", p->GetImmuneStun());  INIDATA->addData("PLAYER", "immuneStun", immuneStun);
	char toFire[30]; sprintf(toFire, "%d", p->GetToFire());  INIDATA->addData("PLAYER", "toFire", toFire);
	char toIce[30]; sprintf(toIce, "%d", p->GetToIce());  INIDATA->addData("PLAYER", "toIce", toIce);
	char toElectric[30]; sprintf(toElectric, "%d", p->GetToElec());  INIDATA->addData("PLAYER", "toElectric", toElectric);
	char toPosion[30]; sprintf(toPosion, "%d", p->GetToPosion());  INIDATA->addData("PLAYER", "toPosion", toPosion);
	char toStun[30]; sprintf(toStun, "%d", p->GetToStun());  INIDATA->addData("PLAYER", "toStun", toStun);
	char fireDamage[30]; sprintf(fireDamage, "%d", p->GetFireDamage());  INIDATA->addData("PLAYER", "fireDamage", fireDamage);
	char iceDamage[30]; sprintf(iceDamage, "%d", p->GetIceDamage());  INIDATA->addData("PLAYER", "iceDamage", iceDamage);
	char elecDamage[30]; sprintf(elecDamage, "%d", p->GetElecDamage());  INIDATA->addData("PLAYER", "elecDamage", elecDamage);
	char posionDamage[30]; sprintf(posionDamage, "%d", p->GetPosionDamage());  INIDATA->addData("PLAYER", "posionDamage", posionDamage);
	char stunDamage[30]; sprintf(stunDamage, "%d", p->GetStunDamage());  INIDATA->addData("PLAYER", "stunDamage", stunDamage);
	char maxPoint[30]; sprintf(maxPoint, "%d", p->GetMaxPoint());  INIDATA->addData("PLAYER", "maxPoint", maxPoint);
	char remainPoint[30]; sprintf(remainPoint, "%d", p->GetRemainPoint());  INIDATA->addData("PLAYER", "remainPoint", remainPoint);
		
	char abilityName[7][30];
	char abilityNum[7][30];
	char intNum[7][10];
	for (int i = 0; i < 7; i++)
	{
		sprintf(abilityName[i], "abilityNum");
		sprintf(abilityNum[i], "%d", p->GetSpecialAbilityPoint(i));
		itoa(i, intNum[i], 10);
		INIDATA->addData("PLAYER", strcat(abilityName[i], intNum[i]), abilityNum[i]);
	}

	char specialAbilityName[7][3][30];
	char specialAbilityOn[7][3][30];
	char specialAbilityOnI[7][5];
	char specialAbilityOnJ[3][5];
	for (int i = 0; i < 7; i++)
	{
		itoa(i, specialAbilityOnI[i], 10);
		for (int j = 0; j < 3; j++)
		{
			sprintf(specialAbilityName[i][j], "specialAbilityOn");
			sprintf(specialAbilityOn[i][j], "%d", p->GetSpecialAbilityOn(i, j));
			itoa(j, specialAbilityOnJ[j], 10);
			INIDATA->addData("PLAYER", strcat(strcat(specialAbilityName[i][j], specialAbilityOnI[i]), specialAbilityOnJ[j]), specialAbilityOn[i][j]);
		}
	}

	char maxSatiety[30]; sprintf(maxSatiety, "%d", p->GetMaxSatiety());  INIDATA->addData("PLAYER", "maxSatiety", maxSatiety);
	char money[30]; sprintf(money, "%d", p->GetMoney());  INIDATA->addData("PLAYER", "money", money);
	char level[30]; sprintf(level, "%d", p->GetLevel());  INIDATA->addData("PLAYER", "level", level);
	char clothType[30]; sprintf(clothType, "%d", (int)p->GetClothType());  INIDATA->addData("PLAYER", "clothType", clothType);
	char experience[30]; sprintf(experience, "%d", p->GetExperience());  INIDATA->addData("PLAYER", "experience", experience);
	char goldDrop[30]; sprintf(goldDrop, "%f", p->GetGoldDrop());  INIDATA->addData("PLAYER", "goldDrop", goldDrop);
	char accesoryCount[30]; sprintf(accesoryCount, "%d", p->GetAccesoryCount());  INIDATA->addData("PLAYER", "accesoryCount", accesoryCount);
	char selectedWeaponIdx[30]; sprintf(selectedWeaponIdx, "%d", p->GetSelectedWeaponIdx());  INIDATA->addData("PLAYER", "selectedWeaponIdx", selectedWeaponIdx);
	
	char x[30]; sprintf(x, "%d", p->GetX());  INIDATA->addData("PLAYER", "x", x);
	char y[30]; sprintf(y, "%d", p->GetY());  INIDATA->addData("PLAYER", "y", y);
	char hp[30]; sprintf(hp, "%d", p->GetHP());  INIDATA->addData("PLAYER", "hp", hp);

	char invenItemName[15][30];
	char invenIndexId[15][30];
	char invenId[15][30];
	for (int i = 0; i < 15; i++)
	{
		sprintf(invenItemName[i], "invenId");
		itoa(i, invenIndexId[i], 10);
		if (p->GetInventory()->GetVItemList().size() <= i) sprintf(invenId[i], "%d", -1);
		else sprintf(invenId[i], "%d", p->GetInventory()->GetVItemList()[i]->GetId());
		INIDATA->addData("PLAYER", strcat(invenItemName[i], invenIndexId[i]), invenId[i]);
	}
	
	char weaponZeroId[30]; sprintf(weaponZeroId, "%d", (p->GetWeapon(0) != nullptr ? p->GetWeapon(0)->GetId() : -1) );  INIDATA->addData("PLAYER", "weaponZeroId", weaponZeroId);
	char weaponOneId[30]; sprintf(weaponOneId, "%d", (p->GetWeapon(1) != nullptr ? p->GetWeapon(1)->GetId() : -1) );  INIDATA->addData("PLAYER", "weaponOneId", weaponOneId);
	char subWeaponZeroId[30]; sprintf(subWeaponZeroId, "%d", (p->GetSubWeapon(0) != nullptr ? p->GetSubWeapon(0)->GetId() : -1) );  INIDATA->addData("PLAYER", "subWeaponZeroId", subWeaponZeroId);
	char subWeaponOneId[30]; sprintf(subWeaponOneId, "%d", (p->GetSubWeapon(1) != nullptr ? p->GetSubWeapon(1)->GetId() : -1) );  INIDATA->addData("PLAYER", "subWeaponOneId", subWeaponOneId);

	char accsItemName[8][30];
	char accsIndexId[8][30];
	char accsId[8][30];
	for (int i = 0; i < 8; i++)
	{
		sprintf(accsItemName[i], "accsId");
		itoa(i, accsIndexId[i], 10);
		if (p->GetVAccessories().size() <= i) sprintf(accsId[i], "%d", -1);
		else sprintf(accsId[i], "%d", p->GetAccessory(i)->GetId());
		INIDATA->addData("PLAYER", strcat(accsItemName[i], accsIndexId[i]), accsId[i]);
	}

	INIDATA->saveINI("Data/PlayerSavaData");
}

/// <summary>
/// 데이터 로드
/// </summary>
void SaveLoadManager::LoadData()
{
	Player* p = ENTITYMANAGER->getPlayer();
	map<string, string> dataMap = LoadIniFromIni();


	if (p->GetSelectedWeaponIdx() == 0)
	{
		if (p->GetWeapon(0) != nullptr)
		{
			p->GetWeapon(0)->EquipUnEquipStatus(false);
			p->SetWeapon(0, nullptr);
		}

		if (p->GetSubWeapon(0) != nullptr)
		{
			p->GetSubWeapon(0)->EquipUnEquipStatus(false);
			p->SetSubWeapon(0, nullptr);
		}
	}

	if (p->GetSelectedWeaponIdx() == 1)
	{
		if (p->GetWeapon(1) != nullptr)
		{
			p->GetWeapon(1)->EquipUnEquipStatus(false);
			p->SetWeapon(1, nullptr);
		}

		if (p->GetSubWeapon(1) != nullptr)
		{
			p->GetSubWeapon(1)->EquipUnEquipStatus(false);
			p->SetSubWeapon(1, nullptr);
		}
	}

	for (int i = 0; i < p->GetVAccessories().size(); i++)
	{
		p->GetVAccessories()[i]->EquipUnEquipStatus(false);
		p->GetVAccessories().erase(p->GetVAccessories().begin());
		i--;
	}

	p->GetInventory()->GetVItemList().clear();

	p->SetMoveSpeed(stof(dataMap["moveSpeed"]));
	p->SetJumpPower(stof(dataMap["jumpPower"]));
	p->SetMaxDashCount(stoi(dataMap["maxDashCount"]));
	p->SetDashRestoreTime(stoi(dataMap["dashRestoreTime"]));
	p->SetMoveSpeedPer(stof(dataMap["moveSpeedPer"]));
	p->SetMinDamage(stoi(dataMap["minDamage"]));
	p->SetMaxDamage(stoi(dataMap["maxDamage"]));
	p->SetPower(stoi(dataMap["power"]));
	p->SetTrueDamage(stoi(dataMap["trueDamage"]));
	p->SetAtkSpeed(stof(dataMap["atkSpeed"]));
	p->SetCriDamage(stof(dataMap["criticalDamage"]));
	p->SetCriPer(stof(dataMap["criticalPercent"]));
	p->SetDashDamage(stof(dataMap["dashDamage"]));
	p->SetReloadTime(stof(dataMap["reloadTime"]));
	p->SetInitHp(stof(dataMap["initHp"]));
	p->SetDefence(stof(dataMap["defence"]));
	p->SetEvasion(stof(dataMap["evasion"]));
	p->SetToughness(stof(dataMap["toughness"]));
	p->SetBlock(stof(dataMap["block"]));
	p->SetFinalDamage(stod(dataMap["finalDamage"]));
	p->SetReloadSpeed(stof(dataMap["reloadSpeed"]));
	p->SetFireAccuracy(stof(dataMap["fireAccuracy"]));
	p->SetAtkSpeedPer(stof(dataMap["atkSpeedPer"]));
	p->SetMaxHp(stoi(dataMap["maxHp"]));
	p->SetMaxHpPer(stof(dataMap["maxHpPercent"]));
	p->SetImmuneFire(stoi(dataMap["immuneFire"]));
	p->SetImmuneIce(stoi(dataMap["immuneIce"]));
	p->SetImmuneElec(stoi(dataMap["immuneElectric"]));
	p->SetImmunePosion(stoi(dataMap["immunePosion"]));
	p->SetImmuneStun(stoi(dataMap["immuneStun"]));
	p->SetToFire(stoi(dataMap["toFire"]));
	p->SetToIce(stoi(dataMap["toIce"]));
	p->SetToElec(stoi(dataMap["toElectric"]));
	p->SetToPosion(stoi(dataMap["toPosion"]));
	p->SetToStun(stoi(dataMap["toStun"]));
	p->SetFireDamage(stoi(dataMap["fireDamage"]));
	p->SetIceDamage(stoi(dataMap["iceDamage"]));
	p->SetElecDamage(stoi(dataMap["elecDamage"]));
	p->SetPosionDamage(stoi(dataMap["posionDamage"]));
	p->SetStunDamage(stoi(dataMap["stunDamage"]));
	p->SetMaxPoint(stoi(dataMap["maxPoint"]));
	p->SetRemainPoint(stoi(dataMap["remainPoint"]));
	for (int i = 0; i < 7; i++) p->SetSpecialAbilityNum(i, (stoi(dataMap["abilityNum" + to_string(i)])));
	for (int i = 0; i < 7; i++)
		for (int j = 0; j < 3; j++)
			p->SetSpecialAbilityOn((stoi(dataMap["specialAbilityOn" + to_string(i) + to_string(j)])), i, j);
	p->SetMaxSatiety(stoi(dataMap["maxSatiety"]));
	p->SetMoney(stoi(dataMap["money"]));
	p->SetLevel(stoi(dataMap["level"]));
	p->SetClothType((CLOTHTYPE)stoi(dataMap["clothType"]));
	p->SetExperience(stoi(dataMap["experience"]));
	p->SetGoldDrop(stof(dataMap["goldDrop"]));
	p->SetAccesoryCount(stoi(dataMap["accesoryCount"]));
	p->GetInventory()->SetInventoryAccesoryUI();
	p->GetInventory()->ReloadUIImages();
	p->SetSelectedWeaponIdx(stoi(dataMap["selectedWeaponIdx"]));
	p->SetX(stoi(dataMap["x"]));
	p->SetY(stoi(dataMap["y"]));
	p->SetHp(stoi(dataMap["hp"]));

	for (int i = 0; i < 15; i++)
	{
		if(stoi(dataMap["invenId" + to_string(i)]) != -1)
			p->GetInventory()->AddItem(DATAMANAGER->GetItemById(stoi(dataMap["invenId" + to_string(i)])));
	}

	if(stoi(dataMap["weaponZeroId"]) != -1) p->SetWeapon(0, DATAMANAGER->GetItemById(stoi(dataMap["weaponZeroId"])));
	if(stoi(dataMap["weaponOneId"]) != -1) p->SetWeapon(1, DATAMANAGER->GetItemById(stoi(dataMap["weaponOneId"])));
	if(stoi(dataMap["subWeaponZeroId"]) != -1) p->SetSubWeapon(0, DATAMANAGER->GetItemById(stoi(dataMap["subWeaponZeroId"])));
	if(stoi(dataMap["subWeaponOneId"]) != -1) p->SetSubWeapon(1, DATAMANAGER->GetItemById(stoi(dataMap["subWeaponOneId"])));

	for (int i = 0; i < 8; i++)
	{
		if (stoi(dataMap["accsId" + to_string(i)]) != -1)
		{
			cout << DATAMANAGER->GetItemById(stoi(dataMap["accsId" + to_string(i)]))->GetName() << endl;
			p->GetVAccessories().push_back(DATAMANAGER->GetItemById(stoi(dataMap["accsId" + to_string(i)])));
		}
	}
	
	p->DashUICheck();
	p->GetInventory()->SetInventoryAccesoryUI();
	p->GetInventory()->ReloadUIImages();

	switch (ENTITYMANAGER->getPlayer()->GetClothType())
	{
	case CLOTHTYPE::PC_NORMAL:					
		ENTITYMANAGER->getPlayer()->Setimage(0, IMAGEMANAGER->findImage("baseCharIdle"));
		ENTITYMANAGER->getPlayer()->Setimage(1, IMAGEMANAGER->findImage("baseCharRun"));		 
		ENTITYMANAGER->getPlayer()->Setimage(2, IMAGEMANAGER->findImage("baseCharDie"));
		break;
	case CLOTHTYPE::PC_METAL:				
		ENTITYMANAGER->getPlayer()->Setimage(0, IMAGEMANAGER->findImage("sheetingIdle"));
		ENTITYMANAGER->getPlayer()->Setimage(1, IMAGEMANAGER->findImage("sheetingRun")); 
		ENTITYMANAGER->getPlayer()->Setimage(2, IMAGEMANAGER->findImage("sheetingDie"));
		break;
	case CLOTHTYPE::PC_GUNNER:	
		ENTITYMANAGER->getPlayer()->Setimage(0, IMAGEMANAGER->findImage("gunmanIdle"));
		ENTITYMANAGER->getPlayer()->Setimage(1, IMAGEMANAGER->findImage("gunmanRun"));
		ENTITYMANAGER->getPlayer()->Setimage(2, IMAGEMANAGER->findImage("gunmanDie"));
		break;
	case CLOTHTYPE::PC_ALICE:				
		ENTITYMANAGER->getPlayer()->Setimage(0, IMAGEMANAGER->findImage("aliceIdle"));
		ENTITYMANAGER->getPlayer()->Setimage(1, IMAGEMANAGER->findImage("aliceRun"));
		ENTITYMANAGER->getPlayer()->Setimage(2, IMAGEMANAGER->findImage("aliceDie"));
		break;
	case CLOTHTYPE::PC_HONGRYAN:			
		ENTITYMANAGER->getPlayer()->Setimage(0, IMAGEMANAGER->findImage("redlotusIdle"));
		ENTITYMANAGER->getPlayer()->Setimage(1, IMAGEMANAGER->findImage("redlotusRun")); 
		ENTITYMANAGER->getPlayer()->Setimage(2, IMAGEMANAGER->findImage("redlotusDie"));
		break;
	case CLOTHTYPE::PC_IKINABEAR:			 
		ENTITYMANAGER->getPlayer()->Setimage(0, IMAGEMANAGER->findImage("lkinabearIdle"));
		ENTITYMANAGER->getPlayer()->Setimage(1, IMAGEMANAGER->findImage("lkinabearRun")); 
		ENTITYMANAGER->getPlayer()->Setimage(2, IMAGEMANAGER->findImage("lkinabearDie"));
		break;
	case CLOTHTYPE::PC_RIDERH:				 
		ENTITYMANAGER->getPlayer()->Setimage(0, IMAGEMANAGER->findImage("riderHIdle"));
		ENTITYMANAGER->getPlayer()->Setimage(1, IMAGEMANAGER->findImage("riderHRun")); 
		ENTITYMANAGER->getPlayer()->Setimage(2, IMAGEMANAGER->findImage("riderHDie"));
		break;
	case CLOTHTYPE::PC_CRIMINAL:			 
		ENTITYMANAGER->getPlayer()->Setimage(0, IMAGEMANAGER->findImage("criminalldle"));
		ENTITYMANAGER->getPlayer()->Setimage(1, IMAGEMANAGER->findImage("criminalRun")); 
		ENTITYMANAGER->getPlayer()->Setimage(2, IMAGEMANAGER->findImage("criminalDie"));
		break;
	case CLOTHTYPE::PC_PICKKING:			
		ENTITYMANAGER->getPlayer()->Setimage(0, IMAGEMANAGER->findImage("pickIdle"));
		ENTITYMANAGER->getPlayer()->Setimage(1, IMAGEMANAGER->findImage("pickRun")); 
		ENTITYMANAGER->getPlayer()->Setimage(2, IMAGEMANAGER->findImage("pickDie"));
		break;
	case CLOTHTYPE::PC_FATGUY:				
		ENTITYMANAGER->getPlayer()->Setimage(0, IMAGEMANAGER->findImage("fastoIdle"));
		ENTITYMANAGER->getPlayer()->Setimage(1, IMAGEMANAGER->findImage("fastoRun")); 
		ENTITYMANAGER->getPlayer()->Setimage(2, IMAGEMANAGER->findImage("fastoDie"));
		break;
	case CLOTHTYPE::PC_HORSESWORD:			
		ENTITYMANAGER->getPlayer()->Setimage(0, IMAGEMANAGER->findImage("horsemanIdle"));
		ENTITYMANAGER->getPlayer()->Setimage(1, IMAGEMANAGER->findImage("horsemanRun")); 
		ENTITYMANAGER->getPlayer()->Setimage(2, IMAGEMANAGER->findImage("horsemanDie"));
		break;
	case CLOTHTYPE::PC_HUMANLASLEY:			 
		ENTITYMANAGER->getPlayer()->Setimage(0, IMAGEMANAGER->findImage("humanlasleyIdle"));
		ENTITYMANAGER->getPlayer()->Setimage(1, IMAGEMANAGER->findImage("humanlasleyRun")); 
		ENTITYMANAGER->getPlayer()->Setimage(2, IMAGEMANAGER->findImage("humanlaselyDie"));
		break;
	case CLOTHTYPE::PC_MASTERCHEF:			
		ENTITYMANAGER->getPlayer()->Setimage(0, IMAGEMANAGER->findImage("masterchefIdle"));
		ENTITYMANAGER->getPlayer()->Setimage(1, IMAGEMANAGER->findImage("masterchefRun")); 
		ENTITYMANAGER->getPlayer()->Setimage(2, IMAGEMANAGER->findImage("masterchefDie"));
		break;
	}
}


/// <summary>
/// ini로 데이터 로드하여 맵 데이터로 반환
/// </summary>
/// <returns></returns>
map<string, string> SaveLoadManager::LoadIniFromIni()
{
	HANDLE file;
	char str[100000] = { 0, };
	DWORD read;

	file = CreateFile("Data/PlayerSavaData.ini", GENERIC_READ, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	bool cannotRead = ReadFile(file, str, 100000, &read, NULL);

	map<string, string> checkMap;

	const char* separator = "\n";
	char* token;

	token = strtok(str, separator); // 한 줄씩 불러와
	while (NULL != (token = strtok(NULL, separator)))
	{
		string subString, subString2;
		string tokenString = token;
		size_t current;
		current = tokenString.find('='); // =마다 데이터 나누어
		subString = tokenString.substr(0, current);
		subString2 = tokenString.substr(current + 1, tokenString.size());
		checkMap[subString] = subString2; // 좌측 데이터를 키, 우측 데이터를 값으로
	}
	CloseHandle(file);
	return checkMap;
}