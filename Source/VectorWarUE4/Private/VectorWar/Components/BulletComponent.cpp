#include "BulletComponent.h"

#include "BodyComponent.h"
#include "InputReceiverComponent.h"
#include "ShipComponent.h"
#include "ECS/World.h"

void BulletComponent::Update(Entity* entity)
{
	if (GetData()->active)
	{
		UE_LOG(LogTemp, Warning, TEXT("----"));

		auto body = (BodyComponent*)entity->GetComponent(BodyComponentType);
		UE_LOG(LogTemp, Warning, TEXT("pos %f  -  %f"), body->GetData()->position.x, body->GetData()->position.y);
		body->GetData()->position.x += body->GetData()->velocity.dx;
		body->GetData()->position.y += body->GetData()->velocity.dy;
		UE_LOG(LogTemp, Warning, TEXT("vel %f  -  %f"), body->GetData()->velocity.dx, body->GetData()->velocity.dy);
		GetData()->timer++;
		if (GetData()->timer>BULLET_DIE_TIMER)
		{
			GetData()->active = false;
		}
		else
		{
			for (auto ent = World::entities.begin(); ent != World::entities.end(); ent++)
			{
				auto ship = (ShipComponent*)(*ent)->GetComponent(ShipComponentType);
				if (ship != nullptr)
				{
					auto shipBody = (BodyComponent*)(*ent)->GetComponent(BodyComponentType);
					
					if (distance(&body->GetData()->position, &shipBody->GetData()->position) < SHIP_RADIUS)
					{
						owner->GetData()->score++;
						GetData()->active = false;
						shipBody-=BULLET_DAMAGE;
					}
				}
			}
		}
	}
}
