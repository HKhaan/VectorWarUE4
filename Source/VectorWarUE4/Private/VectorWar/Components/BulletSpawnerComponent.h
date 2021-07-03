#pragma once
#include "ECS/Component.h"

struct BulletSpawnerData
{
	int cooldown;
};

class BulletSpawnerComponent :public RollbackComponent<BulletSpawnerData>
{
public:
	BulletSpawnerComponent();
	virtual void Update(Entity* entity) override;
	std::vector<Entity*> Bullets;
};
