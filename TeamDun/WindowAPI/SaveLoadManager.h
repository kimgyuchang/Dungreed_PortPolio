#pragma once

/// <summary>
/// 세이브 및 로드하도록 관리
/// </summary>
class SaveLoadManager : public singletonBase<SaveLoadManager>
{
private :
	
public :
	HRESULT Init();

	// SAVE //
	void SaveData();
	
	// LOAD //
	void LoadData();
	map<string, string> LoadIniFromIni();
};

