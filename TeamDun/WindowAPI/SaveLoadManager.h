#pragma once
class SaveLoadManager : public singletonBase<SaveLoadManager>
{
private :
	
public :
	HRESULT Init();
	void SaveData();
	void LoadData();
	map<string, string> LoadIniFromIni();
	// 데이터 불러오기 //

};

