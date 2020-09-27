#pragma once
#include "gameNode.h"
#include "progressBar.h"

//로드아이템 종류
enum LOAD_KIND
{
	LOAD_KIND_IMAGE_0,			//빈비트맵 이미지
	LOAD_KIND_IMAGE_1,			//일반 이미지
	LOAD_KIND_IMAGE_2,			//일반 이미지(좌표)
	LOAD_KIND_FRAMEIMAGE_0,		//프레임 이미지
	LOAD_KIND_FRAMEIMAGE_1,		//프레임 이미지(좌표)
	LOAD_KIND_SOUND,			//사운드
	LOAD_KIND_END
};

//이미지 리소스 구조체
struct tagImageResource
{
	string		keyName;		// 이미지 키값
	const char* fileName;		// 이미지 파일이름
	int			x;				// 위치 좌표 x
	int			y;				// 위치 좌표 y
	int			width;			// 가로 길이
	int			height;			// 세로 길이
	int			frameX;			// 프레임 x
	int			frameY;			// 프레임 y
	bool		isTrans;		// 배경 제거 여부
	COLORREF	transColor;		// 색
	bool		isRotate;		// 회전 여부
};

//사운드 리소스 구조체
struct tagSoundResource
{
	string	keyName;	// 사운드 키값
	string	fileName;	// 사운드 파일이름
	bool	isBGM;		// bgm 여부
	bool	isLoop;		// 루프 여부
};

/// <summary>
/// 로드 아이템은 로드할 대상(사운드 / 이미지)의 정보를 저장하고 있다.
/// </summary>
class LoadItem
{
private:
	LOAD_KIND			_kind;				// 로딩종류
	tagImageResource	_imageResource;		// 이미지 정보
	tagSoundResource	_soundResource;		// 사운드 정보

public:
	HRESULT init(string keyName, string soundName, bool bgm, bool loop);
	HRESULT init(string strKey, int width, int height);
	HRESULT init(string strKey, const char* fileName, int width, int height, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	HRESULT init(string strKey, const char* fileName, float x, float y, int width, int height, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	HRESULT init(string strKey, const char* fileName, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor = RGB(255,0,255), bool isRotate = false);
	HRESULT init(string strKey, const char* fileName, float x, float y, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor = RGB(255,0,255), bool isRotate = false);
	
	// GETSET //
	LOAD_KIND			getLoadKind()		{ return _kind; }
	tagImageResource	getImageResource()	{ return _imageResource; }
	tagSoundResource	getSoundResource()	{ return _soundResource; }
};

/// <summary>
/// 로딩 클래스는 로딩 씬에서 사용될 로딩 프로세스를 포함하고 있다.
/// </summary>
class Loading : public gameNode
{
private:

	// 로드 아이템 관련 //
	typedef vector<LoadItem*>			vLoadItem;			// 로드 아이템 정보를 담음 (이미지 및 사운드)
	typedef vector<LoadItem*>::iterator viLoadItem;			// 벡터 ITR
	vLoadItem							_vLoadItem;			// 로드 아이템 벡터
	string								_curKey;			// 현재 로드 아이템의 키값

public:
	HRESULT init();
	void release();
	void update();
	void render();
	
	void LoadSound(string keyName, string soundName, bool bgm, bool loop);
	void LoadNormalImage(string strKey, int width, int height);
	void LoadNormalImage(string strKey, const char* fileName, int width, int height, bool isTrans = false, COLORREF transColor = RGB(0,0,0));
	void LoadNormalImage(string strKey, const char* fileName, float x, float y, int width, int height, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	void LoadFrameImage(string strKey, const char* fileName, int width, int height, int frameX, int frameY, bool isTrans = true, COLORREF transColor = RGB(255,255,255), bool isRotate = false);
	void LoadFrameImage(string strKey, const char* fileName, float x, float y, int width, int height, int frameX, int frameY, bool isTrans = true, COLORREF transColor = RGB(255,255,255), bool isRotate = false);
	void LoadingDone(LoadItem* item);

	// GETSET //
	string		GetCurKey()		{ return _curKey; }
	vLoadItem	GetLoadItem()	{ return _vLoadItem; }
};

