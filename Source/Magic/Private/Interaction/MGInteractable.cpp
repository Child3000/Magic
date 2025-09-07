#include "Interaction/MGInteractable.h"

#include "Game/MGGameSettings.h"


bool IMGInteractable::IsInteractableNow()
{
	return true;
}

void IMGInteractable::Interact(const FMGInteractorInfo& Info)
{
	// Empty implementation.
}

void IMGInteractable::OnShowInteractGuide()
{
	// default implementation.
	if (AActor* Actor = Cast<AActor>(this))
	{
		// get all mesh components from actor.
		TInlineComponentArray<UMeshComponent*> ComponentArray;
		Actor->GetComponents(UMeshComponent::StaticClass(), ComponentArray, false);

		// ensure overlay material is loaded in memory.
		const UMGGameSettings* Setting = GetDefault<UMGGameSettings>();
		UMaterialInterface* OverlayMat = Setting->DefaultInteractGuideOverrideMat.LoadSynchronous();
		
		// apply overlay material.
		for (UMeshComponent* Component : ComponentArray)
		{
			// static mesh setup require to display overlay material correctly.
			if (UStaticMeshComponent* StaticMesh = Cast<UStaticMeshComponent>(Component))
			{
				StaticMesh->bDisallowNanite = true;
			}
			
			Component->SetOverlayMaterial(OverlayMat);
		}
	}

	UE_LOG(LogTemp, Log, TEXT("OnShowInteractGuide Default"));
}


void IMGInteractable::OnHideInteractGuide()
{
	// default implementation.
	if (AActor* Actor = Cast<AActor>(this))
	{
		// get all mesh components from actor.
		TInlineComponentArray<UMeshComponent*> ComponentArray;
		Actor->GetComponents(UMeshComponent::StaticClass(), ComponentArray, false);

		// ensure overlay material is loaded in memory.
		const UMGGameSettings* Setting = GetDefault<UMGGameSettings>();
		UMaterialInterface* OverlayMat = Setting->DefaultInteractGuideOverrideMat.LoadSynchronous();
		
		// unapply overlay material.
		for (UMeshComponent* Component : ComponentArray)
		{
			if (Component->GetOverlayMaterial() == OverlayMat)
			{
				// reset to default value defined in constructor.
				if (UStaticMeshComponent* StaticMesh = Cast<UStaticMeshComponent>(Component))
				{
					StaticMesh->bDisallowNanite = GetDefault<UStaticMeshComponent>()->bDisallowNanite;
				}
				
				Component->SetOverlayMaterial(nullptr);
			}
		}
	}

	UE_LOG(LogTemp, Log, TEXT("OnHideInteractGuide Default"));
	
}