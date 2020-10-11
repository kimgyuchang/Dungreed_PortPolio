#pragma once
#include "gameNode.h"
#include "Stage.h"

class gameScene : public gameNode
{
private:
	float					_pivX;
	float					_pivY;
	Player*					_p;
	vector<string>			_vCharName;
	vector<string>			_CharExplanation;
	vector<string>			_CharAbility;
	vector<string>			_CharFirstStat;
	vector<string>			_CharSecondStat;

	int						_scrollTimer;		//스크롤 타이머
	int						_mouseLocation;		//현재 마우스좌표를 저장할 변수
public:
	HRESULT init();
	void initUI();
	void release();
	void update();
	void render();
};

