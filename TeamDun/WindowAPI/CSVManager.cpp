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

//Save
void CSVManager::csvSave(const char* saveFileName, vector<vector<string>> vStr)
{
	HANDLE file;

	char str[10000];
	DWORD write;

	file = CreateFile(saveFileName, GENERIC_WRITE, NULL, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	for (int i = 0; i < vStr.size(); i++)
	{
		for (int j = 0; j < vStr[i].size(); j++)
		{
			string n;
			if (j == vStr[i].size() - 1) n = vStr[i][j];
			else n = vStr[i][j] + ",";
			
			WriteFile(file, n.c_str(), n.length(), &write, NULL);
		}

		if (i != vStr.size() - 1) WriteFile(file, "\n", 1, &write, NULL);
	}

	CloseHandle(file);
}

char* CSVManager::vectorArrayCombine(vector<string> vArray)
{
	char str[10000];

	ZeroMemory(str, sizeof(str));
	for (int i = 0; i < vArray.size(); i++)
	{
		strncat_s(str, 10000, vArray[i].c_str(), vArray[i].length());
		if (i + 1 < vArray.size()) strcat(str, ",");
	}

	return str;
}


// 행, 열의 결과로 Return된다.
vector<vector<string>> CSVManager::csvLoad(const char* loadFileName)
{
	HANDLE file;

	char str[100000] = { 0, };
	DWORD read;

	file = CreateFile(loadFileName, GENERIC_READ, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, str, 100000, &read, NULL);

	CloseHandle(file);

	return charArraySeparationSub(charArraySeparation(str));
}

vector<string> CSVManager::charArraySeparation(char charArray[])
{
	vector<string> vArray;

	char* temp;
	const char* separator = "\n";
	char* token;

	token = strtok(charArray, separator);
	vArray.push_back(token);

	while (NULL != (token = strtok(NULL, separator)))
	{
		vArray.push_back(token);
	}

	return vArray;
}

vector<vector<string>> CSVManager::charArraySeparationSub(vector<string> stringVec)
{
	vector<vector<string>> vvArray;
	for (int i = 0; i < stringVec.size(); i++)
	{
		string subString;

		vector<string> vArray;

		size_t previous = 0, current;
		current = stringVec[i].find(',');
		while (current != string::npos)
		{
			subString = stringVec[i].substr(previous, current - previous);
			if (subString.size() > 0 && subString[subString.size() - 1] == '\r')
			{
				subString.erase(subString.end() - 1);
			}
			vArray.push_back(subString);
			previous = current + 1;
			current = stringVec[i].find(',', previous);
		}

		subString = stringVec[i].substr(previous, current - previous);
		if (subString.size() > 0 && subString[subString.size() - 1] == '\r')
		{
			subString.erase(subString.end() - 1);
		}
		vArray.push_back(subString);
		vvArray.push_back(vArray);
	}

	vvArray.erase(vvArray.begin());
	return vvArray;
}