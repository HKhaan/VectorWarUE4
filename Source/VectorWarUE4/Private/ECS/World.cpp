#include "World.h"
#include "Entity.h"
#include "Component.h"

std::list<Entity*> World::entities;
std::list<int> World::componentTypes;

Entity* World::CreateEntity() {
    auto entity = new Entity();
    entities.push_back(entity);
    return entity;
}

void World::Update()  {
    for (auto comp = componentTypes.begin(); comp != componentTypes.end(); comp++)
    {
        for (auto ent = entities.begin(); ent != entities.end(); ent++) {
            auto component = (*ent)->GetComponent(*comp);
            if (component != nullptr)
                component->Update(*ent);
        }
    }
}

void World::Destroy() {
    while(entities.size()>0){
        auto entity = entities.front();
        delete entity;
        entities.pop_front();
    }
    //Todo: clear virtual memory
}

