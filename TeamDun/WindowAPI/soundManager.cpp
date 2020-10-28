#include "stdafx.h"
#include "soundManager.h"

HRESULT soundManager::init()
{
	//FMOD 시스템을 생성한다
	System_Create(&_system);

	//사운드, 채널수 설정
	_system->init(SOUNDBUFFER, FMOD_INIT_NORMAL, 0);

	//사운드, 채널 클래스 동적할당
	_sound = new Sound * [SOUNDBUFFER];
	_channel = new Channel * [SOUNDBUFFER];

	//메모리 초기화
	memset(_sound, 0, sizeof(Sound*) * SOUNDBUFFER);
	memset(_channel, 0, sizeof(Channel*) * SOUNDBUFFER);

	//Fade In / Out
	_fadeOutCount = 0;
	_fadeInCount = 0;
	return S_OK;
}

void soundManager::release()
{
	//사운드 및 채널 삭제
	if (_sound != NULL || _channel != NULL)
	{
		for (int i = 0; i < SOUNDBUFFER; i++)
		{
			if (_channel != NULL)
			{
				if (_channel[i]) _channel[i]->stop();
			}
			if (_sound != NULL)
			{
				if (_sound[i]) _sound[i]->release();
			}
		}
	}

	//메모리 지우기
	SAFE_DELETE_ARRAY(_sound);
	SAFE_DELETE_ARRAY(_channel);

	//시스템 닫기
	if (_system != NULL)
	{
		_system->release();
		_system->close();
	}
}

void soundManager::update()
{
	_system->update();
	FadeOutBGM();
	FadeInBGM();
}

/// <summary>
/// 사운드 추가
/// </summary>
void soundManager::addSound(string keyName, string soundName, bool bgm, bool loop)
{

	if (loop) // BGM에 주로 사용하는 Loop
	{
		if (bgm)
		{
			_system->createStream(soundName.c_str(), FMOD_LOOP_NORMAL, 0, &_sound[_mTotalSound.size()]); // 한개의 파일만을 사용
			_bgmStrings.push_back(soundName);
		}
		else // 효과음 Loop는 거의 없다.
		{
			_system->createSound(soundName.c_str(), FMOD_LOOP_NORMAL, 0, &_sound[_mTotalSound.size()]);
			_bgmStrings.push_back(soundName);
		}
	}
	else // 효과음에 주로 사용하는 No Loop
	{
		_system->createSound(soundName.c_str(), FMOD_DEFAULT, 0, &_sound[_mTotalSound.size()]);
	}

	_mTotalSound.insert(make_pair(keyName, &_sound[_mTotalSound.size()]));	//맵에 사운드를 키값과 함께 담아둔다
}

/// <summary>
/// 사운드를 재생
/// </summary>
void soundManager::play(string keyName, float volume, bool useOverlapVolumeDown, bool useFadeIn)
{
	int count = 0;
	arrSoundIter iter = _mTotalSound.begin();
	for (iter; iter != _mTotalSound.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			//사운드 플레이
			_system->playSound(FMOD_CHANNEL_FREE, *iter->second, false, &_channel[count]);

			FMOD_MODE mode;
			_channel[count]->getMode(&mode);
			if (mode == 131274) // LOOP하는애면 (BGM)
			{
				_vStarts.push_back(keyName);
				if(useFadeIn) _channel[count]->setVolume(0); // 페이드인을 사용하는 경우 초기 사운드를 0으로
				else _channel[count]->setVolume(0.5f); // 아니면 default 값으로
			} 

			else // 효과음이면
			{
				if (useOverlapVolumeDown) // 사운드 겹칠 시 음량 다운 사용한다면
				{
					if(isPlaySound(keyName)) // 재생중인 사운드면
						_channel[count]->setVolume(volume * 0.5f); // 좀 더 작은 사운드로 겹쳐 재생되도록
					else
						_channel[count]->setVolume(volume); // 그냥 재생하도록
				}
				else
				{
					_channel[count]->setVolume(volume);
				}
			}

			break;
		}
	}
}

/// <summary>
/// 사운드를 중지한다
/// </summary>
void soundManager::stop(string keyName)
{
	int count = 0;
	arrSoundIter iter = _mTotalSound.begin();
	for (iter; iter != _mTotalSound.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			//사운드 정지
			_channel[count]->stop();
		}
	}
}

/// <summary>
/// 사운드를 일시정지한다
/// </summary>
void soundManager::pause(string keyName)
{
	int count = 0;
	arrSoundIter iter = _mTotalSound.begin();
	for (iter; iter != _mTotalSound.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			//사운드 일시정지
			_channel[count]->setPaused(true);
		}
	}
}

/// <summary>
/// 사운드를 재개한다
/// </summary>
void soundManager::resume(string keyName)
{
	int count = 0;
	arrSoundIter iter = _mTotalSound.begin();
	for (iter; iter != _mTotalSound.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			//사운드 다시재생
			_channel[count]->setPaused(false);
		}
	}
}

/// <summary>
/// 현재 사운드가 플레이중인지 확인한다.
/// </summary>
bool soundManager::isPlaySound(string keyName)
{
	bool isPlay;
	int count = 0;
	arrSoundIter iter = _mTotalSound.begin();
	for (iter; iter != _mTotalSound.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			//사운드 정지
			_channel[count]->getPaused(&isPlay);
			break;
		}
	}
	return !isPlay;
}

/// <summary>
/// 현재 사운드가 일시정지중인지 확인한다.
/// </summary>
bool soundManager::isPauseSound(string keyName)
{
	bool isPause;
	int count = 0;
	arrSoundIter iter = _mTotalSound.begin();
	for (iter; iter != _mTotalSound.end(); ++iter, count++)
	{
		if (keyName == iter->first)
		{
			//사운드 일시정지
			_channel[count]->getPaused(&isPause);
			break;
		}
	}
	return isPause;
}

/// <summary>
/// 모든 BGM을 정지해주는 기능
/// </summary>
void soundManager::StopAllBGM(bool useFadeIn)
{
	_vStarts.clear();

	_fadeOutCount = 150;
	if(useFadeIn) _fadeInCount = 150;
}

/// <summary>
/// BGM 페이드 인
/// </summary>
void soundManager::FadeInBGM()
{
	if (_fadeInCount > 0 && _fadeOutCount == 0)
	{
		int count = 0;
		for (int i = 0; i < _vStarts.size(); i++)
		{
			_fadeInCount--;

			arrSoundIter iter = _mTotalSound.begin();
			for (iter; iter != _mTotalSound.end(); ++iter, count++)
			{
				FMOD_MODE mode;
				_channel[count]->getMode(&mode);
				if (mode == 131274) // LOOP하는애면 (BGM)
				{
					for (int i = 0; i < _vStarts.size(); i++) // 감소시키지 않을 애들 리스트
					{
						if (_vStarts[i].compare(iter->first) == 0)
						{
							float volume;
							_channel[count]->getVolume(&volume);

							if (volume < 50)
							{
								_channel[count]->setVolume(volume + 0.5f / 150); // 현재 볼륨에서 천천히 음량을 높인다.
							}
						}
					}
				}
			}
		}

		if (_fadeInCount == 0)
		{
			_vStarts.clear();
		}
	}

}

/// <summary>
/// BGM 페이드 아웃
/// </summary>
void soundManager::FadeOutBGM()
{
	int count = 0;

	if (_fadeOutCount > 0)
	{
		_fadeOutCount--;

		arrSoundIter iter = _mTotalSound.begin();
		for (iter; iter != _mTotalSound.end(); ++iter, count++)
		{
			bool playSound = false;
			FMOD_MODE mode;
			_channel[count]->getMode(&mode);
			if (mode == 131274) // LOOP하는애면 (BGM)
			{
				for (int i = 0; i < _vStarts.size(); i++) // 감소시키지 않을 애들 리스트
				{
					if (_vStarts[i].compare(iter->first) == 0) 
					{
						playSound = true;
						break;
					}
				}

				if (playSound)
				{
					continue;
				}

				else
				{
					float volume;
					_channel[count]->getVolume(&volume);

					if (volume > 0)
					{
						_channel[count]->setVolume(volume - 0.5f / 150); // 현재 볼륨에서 천천히 음량을 줄인다.
					}
				}
			}
		}
	}
}