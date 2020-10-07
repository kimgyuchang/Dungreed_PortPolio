#include "stdafx.h"
#include "particleGenerator.h"

void ParticleGenerator::release()
{
}

void ParticleGenerator::update()
{
	if (!_isOff)
	{
		_genLiveTime--;	// 생성기의 수명
		_genTime--;		// 생성기의 타이머

		if (_genTime < 0) // 타이머가 0보다 작아지면 파티클을 생성한다
		{
			switch (_generateType)
			{
			case REGULARGEN: // 일정 시간 생성 타입
				_genTime = _initGenTime;
				for (int i = 0; i < _multipleGenerate; i++) // _multipleGenerate개 만큼 생성한다
				{
					initParticle(PARTICLEMANAGER->AddNewParticle());
				}
				break;
			case RANDOMGEN: // 랜덤 시간 생성 타입
				_genTime = _initGenTime + RANDOM->range(-_genTimeRandom, _genTimeRandom);
				for (int i = 0; i < _multipleGenerate; i++)
				{
					initParticle(PARTICLEMANAGER->AddNewParticle());
				}
				break;
			case ONETIME: // 1회성 생성 타입
				if (!_isGenerateOnce)
				{
					for (int i = 0; i < _multipleGenerate; i++)
					{
						initParticle(PARTICLEMANAGER->AddNewParticle());
					}
					_isGenerateOnce = true;	// 1회 생성했다는 것을 알림
					_genLiveTime = 0; // 생성한 뒤에는 바로 사라지도록 처리한다
				}
				break;
			}
		}
	}
}

void ParticleGenerator::render(HDC hdc)
{
	// 생성기는 렌더될 일이 없다! 아마도.
}

void ParticleGenerator::initGenerator(GENERATETYPE genType, int genLiveTime, int genTime, int gentimeRandom, int multipleGenerate, vector<string> imageName)
{
	_generateType = genType;
	_genLiveTime = genLiveTime;
	_initGenTime = _genTime = genTime;
	_genTimeRandom = gentimeRandom;
	_multipleGenerate = multipleGenerate;
	_vImageName = imageName;

	initPos();
	initSpeed();
	initAngle();
	initScale();
	initAlpha();
	initTime();

	_isGenerateOnce = false;
}

void ParticleGenerator::initPos(float genX, float genY, float xRandom, float yRandom)
{
	_genX = _particleX = genX;
	_genY = _particleY = genY;
	_particleXRandom = xRandom;
	_particleYRandom = yRandom;
}

void ParticleGenerator::initSpeed(float speedX, float speedY, float speedRandomX, float speedRandomY, float speedChangerX, float speedChangerY)
{
	_xSpeed = speedX;
	_ySpeed = speedY;
	_xSpeedRandom = speedRandomX;
	_ySpeedRandom = speedRandomY;
	_speedChangerX = speedChangerX;
	_speedChangerY = speedChangerY;
}

void ParticleGenerator::initAngle(float angle, float angleRandom, float angleChanger)
{
	_angle = angle;
	_angleRandom = angleRandom;
	_angleChanger = angleChanger;
}

void ParticleGenerator::initScale(float scale, float scaleRandom, float scaleChanger)
{
	_scale = scale;
	_scaleRandom = scaleRandom;
	_scaleChanger = scaleChanger;
}

void ParticleGenerator::initAlpha(float alpha, float alphaRandom, float alphaChanger)
{
	_alpha = alpha;
	_alphaRandom = alphaRandom;
	_alphaChanger = alphaChanger;
}

void ParticleGenerator::initTime(int particleTime, int particleTimeRandom)
{
	_particleTime = particleTime;
	_particleTimeRandom = particleTimeRandom;
}

void ParticleGenerator::initParticle(particle* curParticle)
{
	curParticle->initParticle(
		_particleX + RANDOM->range(-_particleXRandom / 2, _particleXRandom / 2),			// X좌표에 랜덤성 추가
		_particleY + RANDOM->range(-_particleYRandom / 2, _particleYRandom / 2),			// Y좌표에 랜덤성 추가
		_speedChangerX, _speedChangerY,														// 스피드 XY 변화량
		_xSpeed + RANDOM->range(-_xSpeedRandom / 2, _xSpeedRandom / 2),						// X스피드 랜덤성 추가
		_ySpeed + RANDOM->range(-_ySpeedRandom / 2, _ySpeedRandom / 2),						// Y스피드 랜덤성 추가
		_angleChanger,																		// 각도값 변화량
		_angle + RANDOM->range(-_angleRandom / 2, _angleRandom / 2),						// 각도값 랜덤성 추가
		_alphaChanger,																		// 알파값 변화량
		_alpha + RANDOM->range(-_alphaRandom / 2, _alphaRandom / 2),						// 알파값 랜덤성 추가
		_scaleChanger,																		// 크기 XY 변화량
		_scale + RANDOM->range(-_scaleRandom / 2, _scaleRandom / 2),						// 크기 X 랜덤성 추가
		_particleTime + RANDOM->range(-_particleTimeRandom / 2, _particleTimeRandom / 2),	// 파티클 생존 시간에 랜덤성 추가
		_vImageName[RANDOM->range((int)_vImageName.size())]									// 이미지 중 하나를 선택해 파티클에 입력
	);
}
