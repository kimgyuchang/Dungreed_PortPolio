#pragma once
#include "NPC.h"

class Boutique : public NPC
{
private:
	bool			_isOpen;
public:
	virtual HRESULT init(int id, string name, OBJECTTYPE type, vector<string> imgNames);
	virtual void	update();
	virtual	void	release();
	virtual void	render(HDC hdc);
			void	Activate();
			void EscapeChecker();
	virtual void	Animation();

	void			Conversation();
	void			initSecond();
};