#include "ComponentFactory.h"
#include "InputReceiverComponent.h"
#include <map>

#include "BodyComponent.h"
#include "BulletComponent.h"
#include "BulletSpawnerComponent.h"
#include "MovementComponent.h"
#include "ShipComponent.h"
#include "ECS/Entity.h"
#include "ECS/World.h"
//#include <algorithm>

void ComponentFactory::AddComponent(Entity* entity, ComponentTypes type)
{
	//TODO: check if already exists
	switch (type)
	{
	case ComponentTypes::InputReceiverComponentType:
		{
			auto comp = new InputReceiverComponent();
			entity->components[type] = comp;
			break;
		}
	case ComponentTypes::MovementComponentType:
		{
			auto comp = new MovementComponent();
			entity->components[type] = comp;
			break;
		}
	case ComponentTypes::BodyComponentType:
		{
			auto comp = new BodyComponent();
			entity->components[type] = comp;
			break;
		}
	case ComponentTypes::BulletSpawnerComponentTypes:
		{
			auto comp = new BulletSpawnerComponent();
			entity->components[type] = comp;
			break;
		}
	case ComponentTypes::BulletComponentType:
		{
			auto comp = new BulletComponent();
			entity->components[type] = comp;
			break;
		}
	case ComponentTypes::ShipComponentType:
		{
			auto comp = new ShipComponent();
			entity->components[type] = comp;
			break;
		}
	default:
		break;
	}
	if (!(std::find(World::componentTypes.begin(), World::componentTypes.end(), type) !=
		World::componentTypes.end()))
		World::componentTypes.push_back(type);
	//std::sort(World::componentTypes.begin(), World::componentTypes.end());
}
