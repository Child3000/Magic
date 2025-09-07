// Copyright Bear Child


#include "Character/MGMonster.h"

#include "Components/CapsuleComponent.h"


AMGMonster::AMGMonster()
{
	PrimaryActorTick.bCanEverTick = false;
	GetCapsuleComponent()->SetCollisionProfileName("Monster");
	GetMesh()->SetCollisionProfileName("NoCollision");
}


bool AMGMonster::IsInteractableNow()
{
	return false;
}

