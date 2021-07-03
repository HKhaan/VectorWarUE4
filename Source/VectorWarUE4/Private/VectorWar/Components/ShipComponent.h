#pragma once
#include "ECS/Component.h"
#include "VectorWar/gamestate.h"

struct ShipData
{
public:
	ShipData()
	{
		health=STARTING_HEALTH;
		assignedPlayer=0;
		score=0;
	}
	int health;
	int assignedPlayer;
	int32 score;
};
class ShipComponent: public  RollbackComponent<ShipData>
{
	
};
