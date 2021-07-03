#pragma once

#include "ECS/Component.h"
struct InputReceiverData{
public:
    InputReceiverData(){
        input=0;
        assignedGamepad=-1;
    }
    int input;
    int assignedGamepad;
};
class InputReceiverComponent: public RollbackComponent<InputReceiverData> {
};