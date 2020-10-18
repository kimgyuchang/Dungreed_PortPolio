#include "stdafx.h"
#include "StageDoor.h"

void StageDoor::Activate()
{
	MAPMANAGER->GetStageChanger()->MoveStage(MAPMANAGER->GetCurStageNum() != 2 ? MAPMANAGER->GetCurStageNum() + 1 : 0);
}
