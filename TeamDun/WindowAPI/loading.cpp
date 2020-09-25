#include "stdafx.h"
#include "loading.h"

/////////////////////////////// LOADITEM 관련 //////////////////////////////////////////////

/// <summary>
/// 초기화 - 사운드
/// </summary>
HRESULT LoadItem::init(string keyName, string soundName, bool bgm, bool loop)
{
	_kind = LOAD_KIND_SOUND;

	_soundResource.keyName = keyName;
	_soundResource.fileName = soundName;
	_soundResource.isBGM = bgm;
	_soundResource.isLoop = loop;

	return S_OK;
}

/// <summary>
/// 초기화 - 이미지 1 (기본)
/// </summary>
HRESULT LoadItem::init(string strKey, int width, int height)
{
	//로딩종류 초기화
	_kind = LOAD_KIND_IMAGE_0;

	//이미지 구조체 초기화
	_imageResource.keyName = strKey;
	_imageResource.width = width;
	_imageResource.height = height;

	return S_OK;
}

/// <summary>
/// 초기화 - 이미지 2 (파일 이름 및 날리기 여부 추가)
/// </summary>
HRESULT LoadItem::init(string strKey, const char * fileName, int width, int height, bool isTrans, COLORREF transColor)
{
	//로딩종류 초기화
	_kind = LOAD_KIND_IMAGE_1;

	//이미지 구조체 초기화
	_imageResource.keyName = strKey;
	_imageResource.fileName = fileName;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.isTrans = isTrans;
	_imageResource.transColor = transColor;

	return S_OK;
}

/// <summary>
/// 초기화 - 이미지 3 (사용할 좌표 추가)
/// </summary>
HRESULT LoadItem::init(string strKey, const char * fileName, float x, float y, int width, int height, bool isTrans, COLORREF transColor)
{
	//로딩종류 초기화
	_kind = LOAD_KIND_IMAGE_2;

	//이미지 구조체 초기화
	_imageResource.keyName = strKey;
	_imageResource.fileName = fileName;
	_imageResource.x = x;
	_imageResource.y = y;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.isTrans = isTrans;
	_imageResource.transColor = transColor;

	return S_OK;
}

/// <summary>
/// 초기화 - 프레임 이미지 1 (기본)
/// </summary>
HRESULT LoadItem::init(string strKey, const char * fileName, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor, bool isRotate)
{
	//로딩종류 초기화
	_kind = LOAD_KIND_FRAMEIMAGE_0;

	//이미지 구조체 초기화
	_imageResource.keyName = strKey;
	_imageResource.fileName = fileName;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.frameX = frameX;
	_imageResource.frameY = frameY;
	_imageResource.isTrans = isTrans;
	_imageResource.transColor = transColor;
	_imageResource.isRotate = isRotate;

	return S_OK;
}

/// <summary>
/// 초기화 - 프레임 이미지 2 (사용할 좌표 추가)
/// </summary>
HRESULT LoadItem::init(string strKey, const char * fileName, float x, float y, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor, bool isRotate)
{
	//로딩종류 초기화
	_kind = LOAD_KIND_FRAMEIMAGE_1;

	//이미지 구조체 초기화
	_imageResource.keyName = strKey;
	_imageResource.fileName = fileName;
	_imageResource.x = x;
	_imageResource.y = y;
	_imageResource.width = width;
	_imageResource.height = height;
	_imageResource.frameX = frameX;
	_imageResource.frameY = frameY;
	_imageResource.isTrans = isTrans;
	_imageResource.transColor = transColor;
	_imageResource.isRotate = isRotate;
	return S_OK;
}

/////////////////////////////// LOADING 관련 //////////////////////////////////////////////

HRESULT Loading::init()
{
	return S_OK;
}

void Loading::release()
{
	for (int i = 0; i < _vLoadItem.size(); i++) SAFE_DELETE(_vLoadItem[i]);
}

void Loading::update()
{
}

void Loading::render()
{
}

/// <summary>
/// 로드 - 사운드
/// </summary>
void Loading::LoadSound(string keyName, string soundName, bool bgm, bool loop)
{
	LoadItem*item = new LoadItem;
	item->init(keyName, soundName, bgm, loop); // 적합한 초기화를 해준 뒤
	_vLoadItem.push_back(item);	// vLoadItem에 추가
}

/// <summary>
/// 로드 - 이미지 1 (기본)
/// </summary>
void Loading::LoadNormalImage(string strKey, int width, int height)
{
	LoadItem* item = new LoadItem;
	item->init(strKey, width, height);
	_vLoadItem.push_back(item);
}

/// <summary>
/// 로드 - 이미지 2 (파일 이름 및 날리기 여부 추가)
/// </summary>
void Loading::LoadNormalImage(string strKey, const char * fileName, int width, int height, bool isTrans, COLORREF transColor)
{
	LoadItem* item = new LoadItem;
	item->init(strKey, fileName, width, height, isTrans, transColor);
	_vLoadItem.push_back(item);
}

/// <summary>
/// 로드 - 이미지 3 (사용할 좌표 추가)
/// </summary>
void Loading::LoadNormalImage(string strKey, const char * fileName, float x, float y, int width, int height, bool isTrans, COLORREF transColor)
{
	LoadItem* item = new LoadItem;
	item->init(strKey, fileName, x, y, width, height, isTrans, transColor);
	_vLoadItem.push_back(item);
}

/// <summary>
/// 로드 - 프레임 이미지 1 (기본)
/// </summary>
void Loading::LoadFrameImage(string strKey, const char * fileName, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor, bool isRotate)
{
	LoadItem* item = new LoadItem;
	item->init(strKey, fileName, width, height, frameX, frameY, isTrans, transColor, isRotate);
	
	_vLoadItem.push_back(item);
}

/// <summary>
/// 로드 - 프레임 이미지 2 (사용할 좌표 추가)
/// </summary>
void Loading::LoadFrameImage(string strKey, const char * fileName, float x, float y, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor, bool isRotate)
{
	LoadItem* item = new LoadItem;
	item->init(strKey, fileName, width, x, y, height, frameX, frameY, isTrans, transColor, isRotate);
	_vLoadItem.push_back(item);
}

/// <summary>
/// 해당 아이템의 타입에 맞추어 IMAGEMANAGER나 SOUNDMANAGER에 추가하는 작업을 실시한다.
/// </summary>
void Loading::LoadingDone(LoadItem* item)
{
	// 아이템의 타입에 맞추어 ADD 작업이 이뤄진다.
	switch (item->getLoadKind())
	{
		case LOAD_KIND_IMAGE_0:
		{
			tagImageResource img = item->getImageResource();
			IMAGEMANAGER->addImage(img.keyName, img.width, img.height);
			_curKey = img.keyName;
		}
		break;
		
		case LOAD_KIND_IMAGE_1:
		{
			tagImageResource img = item->getImageResource();
			IMAGEMANAGER->addImage(img.keyName, img.fileName, img.width, img.height, img.isTrans, img.transColor);
			_curKey = img.keyName;
		}
		break;
		
		case LOAD_KIND_IMAGE_2:
		{
			tagImageResource img = item->getImageResource();
			IMAGEMANAGER->addImage(img.keyName, img.fileName, img.x, img.y, img.width, img.height, img.isTrans, img.transColor);
			_curKey = img.keyName;
		}
		break;
		
		case LOAD_KIND_FRAMEIMAGE_0:
		{
			tagImageResource img = item->getImageResource();
			IMAGEMANAGER->addFrameImage(img.keyName, img.fileName, img.width, img.height, img.frameX, img.frameY, img.isTrans, img.transColor);
			_curKey = img.keyName;
			if (img.isRotate) IMAGEMANAGER->MakeRotateImage(_curKey); // 회전한다면 회전까지 해준다.
		}
		break;
		
		case LOAD_KIND_FRAMEIMAGE_1:
		{
			tagImageResource img = item->getImageResource();
			IMAGEMANAGER->addFrameImage(img.keyName, img.fileName, img.x, img.y, img.width, img.height, img.frameX, img.frameY, img.isTrans, img.transColor);
			_curKey = img.keyName;
			if (img.isRotate) IMAGEMANAGER->MakeRotateImage(_curKey); // 회전한다면 회전까지 해준다.
		}
		break;

		case LOAD_KIND_SOUND:
		{
			tagSoundResource sound = item->getSoundResource();
			SOUNDMANAGER->addSound(sound.keyName, sound.fileName, sound.isBGM, sound.isLoop);
			_curKey = sound.keyName;
		}
		break;
	}
}


