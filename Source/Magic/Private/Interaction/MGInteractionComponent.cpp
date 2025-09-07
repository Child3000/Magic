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
		TraceInteractGuide();
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


void UMGInteractionComponent::TraceInteractGuide()
{
	// Find overlay objects within sphere.
	TArray<FOverlapResult> Overlaps;
	{
		const FVector Origin = GetOwner()->GetActorLocation();
		
		FCollisionQueryParams Params (SCENE_QUERY_STAT(InteractOverlapTrace), false);
		// Ignore actor if desired.
		if (bIgnoreOwningActor)
		{
			Params.AddIgnoredActor(GetOwner());
		}

		GetWorld()->OverlapMultiByObjectType(
			Overlaps,
			Origin, FQuat::Identity,
			CollisionObjectQueryParams,
			FCollisionShape::MakeSphere(Radius),
			Params);
	}

	// Filter out unique actors.
	TArray<AActor*, TInlineAllocator<1>> AffectedActors;
	AffectedActors.Reserve(Overlaps.Num());
	{
		// An actor can have multiple primitive components (collisions),
		// which may generate multiple results that point to the same actor.
		for (FOverlapResult& OverlapResult : Overlaps)
		{
			if (AActor* OverlappedActor = OverlapResult.GetActor())
			{
				AffectedActors.AddUnique(OverlappedActor);
			}
		}
	}
	
	// Find the bests results from interactable actors.
	SetBestResultActor(nullptr);
	{
		const FVector OwnerLocation = GetOwner()->GetActorLocation();
		
		float ShortestDistance = FLT_MAX;
		
		for (AActor* InteractableActor : AffectedActors)
		{
			IMGInteractable* Interactable = Cast<IMGInteractable>(InteractableActor);
			bool bValidInteractable = Interactable && Interactable->IsInteractableNow();
			if (!bValidInteractable)
			{
				continue;
			}
			
			const FVector Location = InteractableActor->GetActorLocation();
			const float Distance = FVector::Dist(OwnerLocation, Location);
			if (Distance < ShortestDistance)
			{
				ShortestDistance = Distance;
				SetBestResultActor(InteractableActor);
			}
		}
	}

	// Update interact guide from selected interactable actor.
	{
		// interactable actor selected.
		if (GetBestResultActor())
		{
			if (_currentInteractGuide != GetBestResultActor())
			{
				// hide previous guide.
				if (IsValid(_currentInteractGuide.GetObject()))
				{
					_currentInteractGuide->OnHideInteractGuide();
				}

				// update current guide.
				_currentInteractGuide = GetBestResultActor();

				// show current guide.
				if (IsValid(_currentInteractGuide.GetObject()))
				{
					_currentInteractGuide->OnShowInteractGuide();
				}
			}
		}
		// interactable actor not found.
		else
		{
			// hide previous guide.
			if (IsValid(_currentInteractGuide.GetObject()))
			{
				_currentInteractGuide->OnHideInteractGuide();
			}

			// reset current guide.
			_currentInteractGuide = nullptr;
		}
	}

	// Display debugging info.
	int32 DebugSphereIndex = 0;
	for (AActor* InteractableActor : AffectedActors)
	{
		DrawDebugSphere(GetWorld(), InteractableActor->GetActorLocation(), Radius, 32, FColor::Orange);
		GEngine->AddOnScreenDebugMessage(DebugSphereIndex++, 0.1f, FColor::Orange,
			FString::Printf(TEXT("Overlapped Actor: %s"), *InteractableActor->GetName()));
	}
}


void UMGInteractionComponent::OnInteract() const
{
	if (AActor* BestResultActor = GetBestResultActor())
	{
		if (IMGInteractable* Interactable = Cast<IMGInteractable>(BestResultActor))
		{
			const FMGInteractorInfo InteractorInfo = FMGInteractorInfo(GetOwner());
			Interactable->Interact(InteractorInfo);
		}
	}
}


void UMGInteractionComponent::SetBestResultActor(AActor* NewActor)
{
	_bestResultActor = NewActor;
}

AActor* UMGInteractionComponent::GetBestResultActor() const
{
	return _bestResultActor.Get();
}