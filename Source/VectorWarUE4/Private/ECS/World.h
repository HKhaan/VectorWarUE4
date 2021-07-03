#pragma once
#include <vector>
#include <list>
#include <functional>


class Entity;
class World {
public:
    static std::list<Entity*> entities;
    static Entity* CreateEntity();
    static void Update();
    static void Destroy();
    static std::list<int> componentTypes;
};

