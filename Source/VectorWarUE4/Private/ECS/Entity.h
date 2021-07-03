#pragma once

#include <map>
class Component;
class Entity {
    friend class ComponentFactory;
    friend class World;
private:
    std::map<int, Component*> components;
    Entity() {}
public:
    Component* GetComponent(int componentType);
};