#include "stdafx.h"
#include "StageDoor.h"

void StageDoor::Activate()
{
	if (MAPMANAGER->GetCurStageNum() == 2) ENTITYMANAGER->getPlayer()->ReturnToHome();
	else MAPMANAGER->GetStageChanger()->MoveStage(MAPMANAGER->GetCurStageNum() != 2 ? MAPMANAGER->GetCurStageNum() + 1 : 0);
}
