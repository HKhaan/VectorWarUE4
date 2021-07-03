#include "Entity.h"
Component *Entity::GetComponent(int componentType)  {
    if (components.count(componentType) == 0)
        return nullptr;
    return components.find(componentType)->second;
}