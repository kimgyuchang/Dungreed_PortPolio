#include "stdafx.h"
#include "ParticleManager.h"

void ParticleManager::init()
{
	_opParticle.SetSize(4000); // ObjectPooler 초기화 (4000개를 미리 생성해놓음)
}

void ParticleManager::release()
{
	for (int i = 0; i < _vGenerators.size(); i++)
	{
		_vGenerators[i]->release();
		SAFE_DELETE(_vGenerators[i]);
	}

	for (int i = 0; i < _vParticles.size(); i++)
	{
		_vParticles[i]->release();
		SAFE_DELETE(_vParticles[i]);
	}

	releaseSingleton();
}

void ParticleManager::update()
{
	for (int i = 0; i < _vGenerators.size(); i++) // 생성기들의 업데이트
	{
		_vGenerators[i]->update();

		if (_vGenerators[i]->_genLiveTime < 0) // 수명이 지난 생성기를 제거한다
		{
			_vGenerators.erase(_vGenerators.begin() + i);
			i--;
		}
	}

	for (int i = 0; i < _vParticles.size(); i++) // 파티클들의 업데이트
	{
		_vParticles[i]->update();

		if (_vParticles[i]->_time < 0) // 수명이 지난 파티클을 제거한다
		{
			_opParticle.ReturnObject(_vParticles[i]);	// ObjectPooler에 다시 파티클을 집어넣는다
			_vParticles.erase(_vParticles.begin() + i);	// 해당 파티클을 벡터로부터 제거한다
			i--;
		}
	}
}

void ParticleManager::render(HDC hdc)
{
		
	for (int i = 0; i < _vParticles.size(); i++)
	{
		_vParticles[i]->render(hdc); // 파티클만을 렌더하도록 한다
	}
}

void ParticleManager::AddGenerator(ParticleGenerator* gen)
{
	_vGenerators.push_back(gen);
}

particle* ParticleManager::AddNewParticle()
{
	_vParticles.push_back(_opParticle.PopObject()); // ObjectPooler로부터 파티클을 하나 받아와 파티클 목록에 넣는다
	return _vParticles[_vParticles.size() - 1];		// 방금 넣은 애를 리턴해준다
}
