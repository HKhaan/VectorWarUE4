#pragma once

#include "ECS/Entity.h"

enum ComponentTypes{
    InputReceiverComponentType,
    MovementComponentType,
    BulletSpawnerComponentTypes,
    BulletComponentType,
    ShipComponentType,
    BodyComponentType
};

class ComponentFactory {
public:
    static void AddComponent(Entity* entity, ComponentTypes type);
};


