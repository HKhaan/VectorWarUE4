#include "MovementComponent.h"
#include "ECS/Entity.h"
#include "InputReceiverComponent.h"
#include "ComponentFactory.h"
#include <math.h>


#include "BodyComponent.h"
#include "VectorWar/vectorwar.h"




void MovementComponent::Update(Entity* entity) {
    auto inputReceiver=(InputReceiverComponent*)entity->GetComponent(ComponentTypes::InputReceiverComponentType);
    if(inputReceiver!=nullptr){
        
        if (inputReceiver->GetData()->input & INPUT_ROTATE_RIGHT) {
            GetData()->heading = (GetData()->heading + ROTATE_INCREMENT) % 360;
        } else if (inputReceiver->GetData()->input & INPUT_ROTATE_LEFT) {
            GetData()->heading = (GetData()->heading - ROTATE_INCREMENT + 360) % 360;
        } 

        if (inputReceiver->GetData()->input & INPUT_THRUST) {
            GetData()->thrust = SHIP_THRUST;
        } else if (inputReceiver->GetData()->input & INPUT_BREAK) {
            GetData()->thrust = -SHIP_THRUST;
        } else {
            GetData()->thrust = 0;
        }


        if (GetData()->thrust) {
            double dx = GetData()->thrust * ::cos(degtorad(GetData()->heading));
            double dy = GetData()->thrust * ::sin(degtorad(GetData()->heading));
            auto body=(BodyComponent*)entity->GetComponent(ComponentTypes::BodyComponentType);
            UE_LOG(LogTemp,Warning,TEXT("dx:%f - dy:%f"));
            body->GetData()->velocity.dx += dx;
            body->GetData()->velocity.dy += dy;
            double mag = sqrt(body->GetData()->velocity.dx * body->GetData()->velocity.dx +
                              body->GetData()->velocity.dy * body->GetData()->velocity.dy);
            if (mag > SHIP_MAX_THRUST) {
                body->GetData()->velocity.dx = (body->GetData()->velocity.dx * SHIP_MAX_THRUST) / mag;
                body->GetData()->velocity.dy = (body->GetData()->velocity.dy * SHIP_MAX_THRUST) / mag;
            }
        }
       

    }
}
