#include "stdafx.h"
#include "StageDoor.h"

void StageDoor::Activate()
{
	MAPMANAGER->AddStage(MAPMANAGER->GetCurStageNum() != 2 ? MAPMANAGER->GetCurStageNum() + 1 : 0);
	MAPMANAGER->ChangeMap(0);
	MAPMANAGER->GetPlayMap()->ChangePlayerByDirection(DIRECTION::DIR_RIGHT);
}
