// Copyright Bear Child


#include "Interaction/MGInteractionComponent.h"

#include "Engine/OverlapResult.h"
#include "Interaction/MGInteractable.h"
#include "Interaction/MGInteractorInfo.h"


UMGInteractionComponent::UMGInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	Radius = 200.0f;
	bIgnoreOwningActor = true;
	
	// by default we affect all 'dynamic' objects.
	AddCollisionChannelToAffect(ECC_Pawn);
	AddCollisionChannelToAffect(ECC_PhysicsBody);
	AddCollisionChannelToAffect(ECC_Vehicle);
	AddCollisionChannelToAffect(ECC_Destructible);
	AddCollisionChannelToAffect(ECC_WorldDynamic);
	UpdateCollisionObjectQueryParams();
}


void UMGInteractionComponent::BeginPlay()
{
	Super::BeginPlay();
}


void UMGInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                            FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!GetOwner())
	{
		return;
	}
	
	if (IsActive())
	{
		const FVector Origin = GetOwner()->GetActorLocation();

		// Find objects within the sphere.
		TArray<FOverlapResult> Overlaps;
		
		FCollisionQueryParams Params (SCENE_QUERY_STAT(InteractOverlapTrace), false);

		// Ignore actor if desired.
		if (bIgnoreOwningActor)
		{
			Params.AddIgnoredActor(GetOwner());
		}
		
		GetWorld()->OverlapMultiByObjectType(
			Overlaps,
			Origin,FQuat::Identity,
			CollisionObjectQueryParams,
			FCollisionShape::MakeSphere(Radius),
			Params);

		// An actor can have multiple primitive components (collisions),
		// which may generate multiple results that point to the same actor.
		TArray<AActor*, TInlineAllocator<1>> AffectedActors;
		AffectedActors.Reserve(Overlaps.Num());

		for (FOverlapResult& OverlapResult : Overlaps)
		{
			if (AActor* OverlappedActor = OverlapResult.GetActor())
			{
				AffectedActors.AddUnique(OverlappedActor);
			}
		}
		
		int32 DebugSphereIndex = 0;
		for (AActor* AffectedActor : AffectedActors)
		{
			if (IMGInteractable* Interactable = Cast<IMGInteractable>(AffectedActor))
			{
				const FMGInteractorInfo InteractorInfo = FMGInteractorInfo(GetOwner());
				Interactable->Interact(InteractorInfo);
			}

			DrawDebugSphere(GetWorld(), AffectedActor->GetActorLocation(), Radius, 32, FColor::Orange);
			GEngine->AddOnScreenDebugMessage(DebugSphereIndex++, 0.1f, FColor::Orange,
				FString::Printf(TEXT("Overlapped Actor: %s"), *AffectedActor->GetName()));
		}
	}
}

void UMGInteractionComponent::AddCollisionChannelToAffect(enum ECollisionChannel CollisionChannel)
{
	EObjectTypeQuery ObjectType = UEngineTypes::ConvertToObjectType(CollisionChannel);
	if(ObjectType != ObjectTypeQuery_MAX)
	{
		AddObjectTypeToAffect(ObjectType);
	}
}

void UMGInteractionComponent::AddObjectTypeToAffect(TEnumAsByte<enum EObjectTypeQuery> ObjectType)
{
	ObjectTypesToAffect.AddUnique(ObjectType);
	UpdateCollisionObjectQueryParams();
}

void UMGInteractionComponent::RemoveObjectTypeToAffect(TEnumAsByte<enum EObjectTypeQuery> ObjectType)
{
	ObjectTypesToAffect.Remove(ObjectType);
	UpdateCollisionObjectQueryParams();
}

void UMGInteractionComponent::UpdateCollisionObjectQueryParams()
{
	CollisionObjectQueryParams = FCollisionObjectQueryParams(ObjectTypesToAffect);
}
