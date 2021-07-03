// Copyright 2020 BwdYeti.

#include "GameStateInterface.h"
#include "vectorwar.h"
#include "VWGameStateBase.h"
#include "Components/BodyComponent.h"
#include "Components/BulletComponent.h"
#include "Components/InputReceiverComponent.h"
#include "Components/MovementComponent.h"
#include "Components/ShipComponent.h"
#include "ECS/World.h"

class ShipComponent;

const GameState GetGameState(const AVWGameStateBase* VWGameState)
{
	// if (VWGameState != nullptr)
	// 	return VWGameState->GetGameState();

	return GameState{0};
}

const NonGameState GetNonGameState(const AVWGameStateBase* VWGameState)
{
	if (VWGameState != nullptr)
		return VWGameState->GetNonGameState();

	return NonGameState{0};
}

int32 UGameStateInterface::ShipCount(const AVWGameStateBase* VWGameState)
{
	int amount = 0;
	for (auto ent : World::entities)
	{
		auto ship = (ShipComponent*)ent->GetComponent(ShipComponentType);
		if (ship != nullptr)
		{
			amount++;
		}
	}
	return amount;
}

int32 UGameStateInterface::BulletCount(const AVWGameStateBase* VWGameState)
{
	return ShipCount(VWGameState) * MAX_BULLETS;
}

FTransform UGameStateInterface::ShipTransform(const AVWGameStateBase* VWGameState, int32 Index)
{
	for (auto ent : World::entities)
	{
		auto ship = (ShipComponent*)ent->GetComponent(ShipComponentType);
		
		if (ship != nullptr && ship->GetData()->assignedPlayer == Index)
		{
			auto body = (BodyComponent*)ent->GetComponent(BodyComponentType);
			auto movement = (MovementComponent*)ent->GetComponent(MovementComponentType);
			if (body != nullptr && movement != nullptr)
			{
				FVector Position = FVector((float)body->GetData()->position.x, (float)body->GetData()->position.y, 0);
				FQuat Rotation = FRotator(0, movement->GetData()->heading - 90, 0).Quaternion();
				FTransform Result = FTransform(Rotation, Position);
				return Result;
			}
		}
	}
	{
		FVector Position = FVector(0, 0, 0);
		FQuat Rotation = FRotator(0, 0, 0).Quaternion();
		FTransform Result = FTransform(Rotation, Position);
		return Result;
	}
}

int32 UGameStateInterface::ShipScore(const AVWGameStateBase* VWGameState, int32 Index)
{
	for (auto ent : World::entities)
	{
		auto ship = (ShipComponent*)ent->GetComponent(ShipComponentType);
		
		if (ship != nullptr && ship->GetData()->assignedPlayer == Index)
		{
			return ship->GetData()->score;
		}
	}
	const Ship Ship = GetGameState(VWGameState)._ships[Index];
	return 0;
}

bool UGameStateInterface::BulletEnabled(const AVWGameStateBase* VWGameState, int32 Index)
{
	int counter = 0;
	for (auto ent : World::entities)
	{
		auto bltComp = (BulletComponent*)ent->GetComponent(BulletComponentType);
		if (bltComp != nullptr)
		{
			if (counter == Index)
			{
				return bltComp->GetData()->active;
			}
			counter++;
		}
	}
	return false;
}

FTransform UGameStateInterface::BulletTransform(const AVWGameStateBase* VWGameState, int32 Index)
{
	int counter = 0;
	for (auto ent : World::entities)
	{
		auto bltComp = (BulletComponent*)ent->GetComponent(BulletComponentType);
		if (bltComp != nullptr)
		{
			if (counter == Index)
			{
				if(!bltComp->GetData()->active)
					break;
				auto body = (BodyComponent*)ent->GetComponent(BodyComponentType);
				if (body != nullptr)
				{
					FVector Position = FVector((float)body->GetData()->position.x, (float)body->GetData()->position.y,
					                           0);
					FQuat Rotation = FQuat::Identity;
					FTransform Result = FTransform(Rotation, Position);
					return Result;
				}
			}
			counter++;
		}
	}
	{
		FVector Position = FVector(0, 0, 0);
		FQuat Rotation = FRotator(0, 0, 0).Quaternion();
		FTransform Result = FTransform(Rotation, Position);
		return Result;
	}
}

Bullet UGameStateInterface::GetBullet(const AVWGameStateBase* VWGameState, int32 Index)
{
	const Ship Ship = GetGameState(VWGameState)._ships[Index / MAX_BULLETS];
	return Ship.bullets[Index % MAX_BULLETS];
}

FPlayerConnectionInfo UGameStateInterface::ConnectionInfo(const AVWGameStateBase* VWGameState, int32 Index)
{
	return GetNonGameState(VWGameState).players[Index];
}

float UGameStateInterface::DisconnectTime(const AVWGameStateBase* VWGameState, int32 Index)
{
	return GetNonGameState(VWGameState).GetDisconnectTime(Index);
}

int32 UGameStateInterface::FrameNumber(const AVWGameStateBase* VWGameState)
{
	return GetNonGameState(VWGameState).now.framenumber;
}

int32 UGameStateInterface::Checksum(const AVWGameStateBase* VWGameState)
{
	return GetNonGameState(VWGameState).now.checksum;
}

int32 UGameStateInterface::PeriodicFrame(const AVWGameStateBase* VWGameState)
{
	return GetNonGameState(VWGameState).periodic.framenumber;
}

int32 UGameStateInterface::PeriodicChecksum(const AVWGameStateBase* VWGameState)
{
	return GetNonGameState(VWGameState).periodic.checksum;
}
