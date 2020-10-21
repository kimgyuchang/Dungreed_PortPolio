#include "stdafx.h"
#include "SaveLoadManager.h"

HRESULT SaveLoadManager::Init()
{
	return S_OK;
}

void SaveLoadManager::SaveData()
{
	Player* p = ENTITYMANAGER->getPlayer();

	char moveSpeed[30]; sprintf(moveSpeed, "%f", p->GetMoveSpeed());  INIDATA->addData("PLAYER", "moveSpeed", moveSpeed);
	char jumpPower[30]; sprintf(jumpPower, "%f", p->GetJumpPower());  INIDATA->addData("PLAYER", "jumpPower", jumpPower);
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

	INIDATA->saveINI("Data/PlayerSavaData");
}

void SaveLoadManager::LoadData()
{
	Player* p = ENTITYMANAGER->getPlayer();
	
	cout << INIDATA->loadDataInteger("Data/PlayerSaveData", "PLAYER", "initHp") << endl;
	cout << INIDATA->loadDataFloat("Data/PlayerSaveData", "PLAYER",	 "atkSpeed") << endl;

	p->SetMoveSpeed(INIDATA->loadDataFloat("Data/PlayerSaveData", "PLAYER", "moveSpeed"));
	p->SetAtkSpeed(INIDATA->loadDataFloat("Data/PlayerSaveData", "PLAYER", "atkSpeed"));
	p->SetCriPer(INIDATA->loadDataFloat("Data/PlayerSaveData", "PLAYER", "criticalPercent"));
	p->SetCriDamage(INIDATA->loadDataFloat("Data/PlayerSaveData", "PLAYER", "criticalDamage"));
	p->SetMoveSpeedPer(INIDATA->loadDataFloat("Data/PlayerSaveData", "PLAYER", "moveSpeedPer"));
	p->SetJumpPower(INIDATA->loadDataInteger("Data/PlayerSaveData", "PLAYER", "jumpPower"));
	p->SetMaxDashCount(INIDATA->loadDataInteger("Data/PlayerSaveData", "PLAYER", "maxDashCount"));
	p->SetDashRestoreTime(INIDATA->loadDataInteger("Data/PlayerSaveData", "PLAYER", "maxDashCount"));
	p->SetMinDamage(INIDATA->loadDataInteger("Data/PlayerSaveData", "PLAYER", "minDamage"));
	p->SetMaxDamage(INIDATA->loadDataInteger("Data/PlayerSaveData", "PLAYER", "maxDamage"));
	p->SetPower(INIDATA->loadDataInteger("Data/PlayerSaveData", "PLAYER", "power"));
	p->SetTrueDamage(INIDATA->loadDataInteger("Data/PlayerSaveData", "PLAYER", "trueDamage"));
	p->SetDashDamage(INIDATA->loadDataInteger("Data/PlayerSaveData", "PLAYER", "dashDamage"));
	p->SetReloadTime(INIDATA->loadDataInteger("Data/PlayerSaveData", "PLAYER", "reloadTime"));
	p->SetInitHp(INIDATA->loadDataInteger("Data/PlayerSaveData", "PLAYER", "initHp"));
	p->SetDefence(INIDATA->loadDataInteger("Data/PlayerSaveData", "PLAYER", "defence"));
	p->SetEvasion(INIDATA->loadDataInteger("Data/PlayerSaveData", "PLAYER", "evasion"));
	p->SetToughness(INIDATA->loadDataInteger("Data/PlayerSaveData", "PLAYER", "toughness"));
	p->SetBlock(INIDATA->loadDataInteger("Data/PlayerSaveData", "PLAYER", "block"));

	/*
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

	INIDATA->saveINI("DATASAVE");
	*/
}
