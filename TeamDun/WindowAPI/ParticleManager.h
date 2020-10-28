#pragma once
#include "singletonBase.h"
#include "particleGenerator.h"
#include "ObjectPooler.h"

class ParticleManager : public singletonBase <ParticleManager> // 싱글톤 매니저
{
private :
	objectPool<particle>		_opParticle;	// 파티클들을 ObjectPool을 이용해 관리한다
	vector<ParticleGenerator*>	_vGenerators;	// 파티클 생성기의 목록
	vector<particle*>			_vParticles;	// 파티클의 목록
	
public:

	// 기본 //
	virtual void init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);

	// 실질적인 파티클 생성기의 초기화
	
	void AddGenerator(ParticleGenerator* gen);
	particle* AddNewParticle();
	
	// GETSET //
	vector<ParticleGenerator*>& GetGenerators() { return _vGenerators; }
	vector<particle*>&			GetParticles()	{ return _vParticles; }
};