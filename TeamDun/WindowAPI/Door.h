#pragma once
#include "Object.h"
#include "particleGenerator.h"

class Door : public Object
{
private :
	DIRECTION			_dir;
	bool				_isActivated;	// 활성화된 상태라면
	bool				_isSpawning;	// 스폰되어서 보이는 상태라면
	ParticleGenerator*	_pGenerator;	// 파티클 제네레이터

public :

	virtual HRESULT init(int id, string name, OBJECTTYPE type, vector<string> imgNames);
	virtual void	update();
	virtual	void	release();
	virtual void	render(HDC hdc);
	virtual void	Animation();

	void SetPGenerator();

	void SetGeneratorIsOff(bool isOff);

	// GETSET //
	void				SetDirection(DIRECTION dir)		{ _dir = dir; }
	void				SetIsActivated(bool isActive)	{ _isActivated = isActive; }
	void				SetIsSpawning(bool isSpawn)		{ _isSpawning = isSpawn; }
	DIRECTION			GetDirection()					{ return _dir; }
	bool				GetIsActivated()				{ return _isActivated; }
	ParticleGenerator*	GetPGenerator()					{ return _pGenerator; }
};

