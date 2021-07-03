#pragma once
#include "ShipComponent.h"
#include "ECS/Component.h"
#include "VectorWar/gamestate.h"

struct BulledData{
	BulledData()
	{
		active=false;
		timer=0;
	}
	bool active;
	int timer;
};
class BulletComponent : public RollbackComponent<BulledData>
{
public:
	ShipComponent* owner;
	virtual void Update(Entity* entity) override;
};
