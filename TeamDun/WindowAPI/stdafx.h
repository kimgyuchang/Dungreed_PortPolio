// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//
#pragma once

#include <SDKDDKVer.h>

//디버깅용 (주석치면 콘솔창이 사라진다)
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <Windows.h>
// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <stdio.h>
#include <tchar.h>
#include <math.h>
#include <commdlg.h>
#include <io.h>

// C++ 런타임 헤더 파일입니다.
#include <iostream>
#include <filesystem>
using namespace std;

// 자주사용하는 STL
#include <string>
#include <vector>
#include <map>

//=============================================================
//	## 내가 만든 헤더파일을 이곳에 추가한다 ##
//=============================================================
#include "commonMacroFunction.h"
#include "random.h"
#include "util.h"
#include "iniData.h"
#include "inputManager.h"
#include "imageManager.h"
#include "sceneManager.h"
#include "soundManager.h"
#include "CSVManager.h"
#include "UIManager.h"
#include "CameraManager.h"
#include "DataManager.h"
#include "EntityManager.h"
#include "MapManager.h"
#include "EffectManager.h"
#include "ParticleManager.h"

using namespace UTIL;

//=============================================================
//	## 싱글톤을 추가한다 ##
//=============================================================
#define INPUT inputManager::getSingleton() //세미콜론 찍으면 작동안함
#define IMAGEMANAGER imageManager::getSingleton()
#define SCENEMANAGER sceneManager::getSingleton()
#define SOUNDMANAGER soundManager::getSingleton()
#define CSVMANAGER CSVManager::getSingleton()
#define UIMANAGER UIManager::getSingleton()
#define CAMERAMANAGER CameraManager::getSingleton()
#define DATAMANAGER DataManager::getSingleton()
#define ENTITYMANAGER EntityManager::getSingleton()
#define EFFECTMANAGER EffectManager::getSingleton()
#define PARTICLEMANAGER ParticleManager::getSingleton()
#define MAPMANAGER MapManager::getSingleton()
#define RANDOM random::getSingleton()
#define INIDATA iniData::getSingleton()

//=============================================================
//	## 디파인문 ## (윈도우창 초기화)
//=============================================================
#define WINNAME (LPTSTR)(TEXT("Dungreed 경일게임아카데미 프로그래밍 22기 홍승기 이신홍 안샘 김정연"))
#define WINSTARTX	0
#define WINSTARTY	0
#define WINSIZEX	1440
#define WINSIZEY	800
#define WINSTYLE	WS_CAPTION | WS_SYSMENU

//=============================================================
//	## 매크로함수 ## (클래스에서 동적할당된 부분 해제)
//=============================================================
#define SAFE_DELETE(p)		{if(p) {delete (p); (p) = NULL;}}
#define SAFE_DELETE_ARRAY(p)	{if(p) {delete[] (p); (p)  = NULL;}}

//=============================================================
//	## 전역변수 ##
//=============================================================
extern HINSTANCE	_hInstance;
extern HWND			_hWnd; 
extern HWND			_hEdit;
extern HWND			_hMonsterSpawnTime;
extern POINT		_ptMouse;
extern int			_mouseWheel;