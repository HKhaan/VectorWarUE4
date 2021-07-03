#include "BulletSpawnerComponent.h"


#include "BodyComponent.h"
#include "BulletComponent.h"
#include "InputReceiverComponent.h"
#include "MovementComponent.h"
#include "ECS/World.h"
#include "VectorWar/gamestate.h"
#include "VectorWar/vectorwar.h"

class BulletComponent;

BulletSpawnerComponent::BulletSpawnerComponent()
{
	
	for (int i = 0; i < MAX_BULLETS; i++)
	{
		auto entity = World::CreateEntity();
		ComponentFactory::AddComponent(entity, ComponentTypes::BulletComponentType);
	
		Bullets.push_back(entity);
		ComponentFactory::AddComponent(entity, ComponentTypes::BodyComponentType);
	}
}

void BulletSpawnerComponent::Update(Entity* entity)
{
	auto inputReceiver = (InputReceiverComponent*)entity->GetComponent(ComponentTypes::InputReceiverComponentType);
	auto body = (BodyComponent*)entity->GetComponent(ComponentTypes::BodyComponentType);
	auto movement = (MovementComponent*)entity->GetComponent(ComponentTypes::MovementComponentType);
	if(GetData()->cooldown>=0)
		GetData()->cooldown-=1;
	if (inputReceiver->GetData()->input & INPUT_FIRE && GetData()->cooldown<0)
	{
		for (int i = 0; i < MAX_BULLETS; i++)
		{
			auto bulletComponent = (BulletComponent*)Bullets[i]->GetComponent(ComponentTypes::BulletComponentType);
			if (!bulletComponent->GetData()->active)
			{
				//TODO: Add init to components class and put this there
				auto ship = (ShipComponent*)entity->GetComponent(ComponentTypes::ShipComponentType);
				bulletComponent->owner=ship;
				bulletComponent->GetData()->active = true;
				bulletComponent->GetData()->timer = 0;
				double dx = ::cos(degtorad(movement->GetData()->heading));
				double dy = ::sin(degtorad(movement->GetData()->heading));
				
				auto bulledBody = (BodyComponent*)Bullets[i]->GetComponent(ComponentTypes::BodyComponentType);
				bulledBody->GetData()->position.x = body->GetData()->position.x+ ((SHIP_RADIUS+5) * dx);
				bulledBody->GetData()->position.y = body->GetData()->position.y+ ((SHIP_RADIUS+5) * dy);
				bulledBody->GetData()->velocity.dx = body->GetData()->velocity.dx + (BULLET_SPEED * dx);
				bulledBody->GetData()->velocity.dy = body->GetData()->velocity.dy + (BULLET_SPEED * dy);
				GetData()->cooldown=BULLET_COOLDOWN;
				return;
			}
		}
	}
}
