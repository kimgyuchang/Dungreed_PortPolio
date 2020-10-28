#include "stdafx.h"
#include "CSVManager.h"

CSVManager::CSVManager()
{
}

CSVManager::~CSVManager()
{
}

HRESULT CSVManager::init()
{
	return S_OK;
}

void CSVManager::release()
{
}

/// <summary>
/// CSV 형태로 SAVE해줌
/// </summary>
void CSVManager::csvSave(string saveFileName, vector<vector<string>> vStr)
{
	HANDLE file;

	char str[10000];
	DWORD write;

	file = CreateFile(saveFileName.c_str(), GENERIC_WRITE, NULL, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	for (int i = 0; i < vStr.size(); i++)
	{
		for (int j = 0; j < vStr[i].size(); j++) // 전체를 돌며
		{
			string n;
			if (j == vStr[i].size() - 1) n = vStr[i][j];
			else n = vStr[i][j] + ","; // ,로 데이터를 구분하는 방식으로 넣는다.
			
			WriteFile(file, n.c_str(), n.length(), &write, NULL);
		}

		if (i != vStr.size() - 1) WriteFile(file, "\n", 1, &write, NULL); // 끝으로 줄넘김을 넣어줌
	}

	CloseHandle(file);
}

/// <summary>
/// 벡터를 스트링으로 만들어 리턴
/// </summary>
char* CSVManager::vectorArrayCombine(vector<string> vArray)
{
	char str[10000];

	ZeroMemory(str, sizeof(str));
	for (int i = 0; i < vArray.size(); i++)
	{
		strncat_s(str, 10000, vArray[i].c_str(), vArray[i].length());
		if (i + 1 < vArray.size()) strcat(str, ","); // 벡터에 ,를 
	}

	return str;
}


// 행, 열의 결과로 Return된다.
vector<vector<string>> CSVManager::csvLoad(string loadFileName)
{
	HANDLE file;

	char str[100000] = { 0, };
	DWORD read;

	file = CreateFile(loadFileName.c_str(), GENERIC_READ, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	bool canReadFile = ReadFile(file, str, 100000, &read, NULL);
	if (!canReadFile && read == 0) // 찾지 못했을 경우
	{
		return vector<vector<string>>(); // 사이즈 0/0의 데이터를 리턴
	}
	
	CloseHandle(file);

	return charArraySeparationSub(charArraySeparation(str)); // 찾을경우 2중 벡터로 된 데이터 저장
}

/// <summary>
/// 배열로 받은 것을 (행 / 열 데이터 통합) 벡터에 넣는다.
/// </summary>
vector<string> CSVManager::charArraySeparation(char charArray[])
{
	vector<string> vArray;

	char* temp;
	const char* separator = "\n";
	char* token;

	token = strtok(charArray, separator); // 행마다 잘라서
	vArray.push_back(token); // 이를 순차적으로 모두 넣는다.

	while (NULL != (token = strtok(NULL, separator)))
	{
		vArray.push_back(token);
	}

	return vArray;
}

// 1중 벡터로 받은 것을 (행 / 열 데이터) 2중 벡터로 넣는다.
vector<vector<string>> CSVManager::charArraySeparationSub(vector<string> stringVec)
{
	vector<vector<string>> vvArray;
	
	// 전체 행을 돌며
	for (int i = 0; i < stringVec.size(); i++)
	{
		string subString;

		vector<string> vArray;

		size_t previous = 0, current;
		current = stringVec[i].find(',');
		
		// 마지막 열을 제외한 나머지 열 추가
		while (current != string::npos)
		{
			subString = stringVec[i].substr(previous, current - previous); // ,로 나눠 넣는다.
			if (subString.size() > 0 && subString[subString.size() - 1] == '\r')
			{
				subString.erase(subString.end() - 1);
			}
			vArray.push_back(subString);
			previous = current + 1;
			current = stringVec[i].find(',', previous);
		}

		// 마지막 열 추가
		subString = stringVec[i].substr(previous, current - previous); // 다 끝났으면 마지막 열까지 잘 처리한다.
		if (subString.size() > 0 && subString[subString.size() - 1] == '\r')
		{
			subString.erase(subString.end() - 1);
		}
		vArray.push_back(subString); 

		vvArray.push_back(vArray); // 이를 2중 벡터에 넣는다.
	}

	vvArray.erase(vvArray.begin()); // 첫 행은 데이터 라벨이기 때문에, 지운다.
	return vvArray;
}