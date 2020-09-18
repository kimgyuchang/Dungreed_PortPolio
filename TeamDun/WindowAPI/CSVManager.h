#pragma once
#include "singletonBase.h"
#include <vector>
#include <string>
#include <sstream>

class CSVManager : public singletonBase<CSVManager>
{
public:
    CSVManager();
    ~CSVManager();

    HRESULT init();
    void release();

    void csvSave(const char* saveFileName, vector<vector<string>> vStr);
    vector<vector<string>> csvLoad(const char* loadFileName);
private:
    char* vectorArrayCombine(vector<string> vArray);
    vector<string> charArraySeparation(char charArray[]);
    vector<vector<string>> charArraySeparationSub(vector<string> stringVec);
};