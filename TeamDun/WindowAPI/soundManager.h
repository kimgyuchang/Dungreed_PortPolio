#pragma once
#include "singletonBase.h"
#include "FMOD/inc/fmod.hpp"
#pragma comment (lib, "FMOD/lib/fmodex_vc.lib")
using namespace FMOD;

//사용할 사운드버퍼, 여유롭게 사용해줘야 함
#define SOUNDBUFFER 450

/// <summary>
/// 사운드를 관리하는 사운드매니저, FMOD를 사용.
/// </summary>
class soundManager : public singletonBase <soundManager>
{
private:
	typedef map<string, Sound**> arrSound;
	typedef map<string, Sound**>::iterator arrSoundIter;

private:
	System*			_system;		//시스템 클래스
	Sound**			_sound;			//사운드 클래스
	Channel**		_channel;		//채널 클래스

	arrSound		_mTotalSound;	//맵에 담아둘 사운드들

	vector<string>	_vStarts;		// 재생 대기중인 애들
	vector<string>	_bgmStrings;	// BGM 스트링 목록
	int				_fadeOutCount;	// 페이드 아웃 카운트
	int				_fadeInCount;	// 페이드 인 카운트
public:

	// 기본 //
	HRESULT init();
	void release();
	void update();

	// 기능 //
	void addSound(string keyName, string soundName, bool bgm = false, bool loop = false);
	void play(string keyName, float volume = 0.5f, bool useOverlapVolumeDown = false, bool useFadeIn = true);
	void stop(string keyName);
	void pause(string keyName);
	void resume(string keyName);
	bool isPlaySound(string keyName);
	bool isPauseSound(string keyName);
	void StopAllBGM(bool useFadeIN = true);
	void FadeInBGM();
	void FadeOutBGM();
};