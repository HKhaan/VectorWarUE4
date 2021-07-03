#pragma once


#include "ECS/Component.h"

struct MovementData{
public:
    MovementData(){
        heading=0;
        thrust=0;
    }
    int heading;
    float thrust;
};

class MovementComponent: public RollbackComponent<MovementData> {
public:
    virtual void Update(Entity* entity) override;
};