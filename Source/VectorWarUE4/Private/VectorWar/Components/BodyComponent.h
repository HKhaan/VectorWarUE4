#pragma once
#include "ECS/Component.h"
#include "VectorWar/gamestate.h"

struct BodyData{
public:
    Position position;
    Velocity velocity;
    int      radius;
};

class BodyComponent: public RollbackComponent<BodyData> {
public:
    RECT _bounds = { (LONG)0, (LONG)0, (LONG)GAME_WIDTH, (LONG)GAME_HEIGHT };
    virtual void Update(Entity* entity) override;
};