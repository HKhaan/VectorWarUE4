#include "BodyComponent.h"

void BodyComponent::Update(Entity* entity)
{
	//GGPONet::ggpo_log(ggpo, "new ship velocity: (dx:%.4f dy:%2.f).\n", GetData()->velocity.dx, GetData()->velocity.dy);

	GetData()->position.x += GetData()->velocity.dx;
	GetData()->position.y += GetData()->velocity.dy;
	//GGPONet::ggpo_log(ggpo, "new ship position: (dx:%.4f dy:%2.f).\n", GetData()->position.x, GetData()->position.y);

	if (GetData()->position.x - GetData()->radius < _bounds.left ||
        GetData()->position.x + GetData()->radius > _bounds.right) {
		GetData()->velocity.dx *= -1;
		GetData()->position.x += (GetData()->velocity.dx * 2);
        }
	if (GetData()->position.y - GetData()->radius < _bounds.top ||
        GetData()->position.y + GetData()->radius > _bounds.bottom) {
		GetData()->velocity.dy *= -1;
		GetData()->position.y += (GetData()->velocity.dy * 2);
        }

	GetData()->velocity.dy*=0.95f;
	GetData()->velocity.dx*=0.95f;
	GetData()->velocity.dy=roundf(GetData()->velocity.dy*10000)/10000;
	GetData()->velocity.dx=roundf(GetData()->velocity.dx*10000)/10000;
}
