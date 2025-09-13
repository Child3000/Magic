// Copyright Bear Child


#include "Character/MGMonster.h"

#include "Components/CapsuleComponent.h"
#include "Tag/MGObjectTagComponent.h"


AMGMonster::AMGMonster()
{
	PrimaryActorTick.bCanEverTick = false;
	GetCapsuleComponent()->SetCollisionProfileName("Monster");
	GetMesh()->SetCollisionProfileName("NoCollision");
}

void AMGMonster::BeginPlay()
{
	Super::BeginPlay();
	GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &AMGMonster::OnComponentHit);
}

void AMGMonster::OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if (auto* TagComponent = OtherActor->GetComponentByClass<UMGObjectTagComponent>())
	{
		FString DbgMsg = "Hit: " + OtherActor->GetName();
		UE_LOG(LogTemp, Log, TEXT("%s"), *DbgMsg);
		
		if (RespondToHitObjectTags && TagComponent->HasAnyTags(*RespondToHitObjectTags))
		{
			PlayAnimMontage(BeingHitMontage);
		}
	}
}

