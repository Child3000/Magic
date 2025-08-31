// Copyright Bear Child


#include "Character/MGMonster.h"

#include "Components/CapsuleComponent.h"


AMGMonster::AMGMonster()
{
	PrimaryActorTick.bCanEverTick = false;
	GetCapsuleComponent()->SetCollisionProfileName("Monster");
	GetMesh()->SetCollisionProfileName("NoCollision");
}

void AMGMonster::OnShowInteractGuide()
{
	// UE_LOGFMT(LogMagicMonster, Log, "Show Interact Guide {0}", GetName());
	if (InteractGuideOverlayMat)
	{
		ApplyOverlayMaterials(InteractGuideOverlayMat);
	}
}

void AMGMonster::OnHideInteractGuide()
{
	// UE_LOGFMT(LogMagicMonster, Log, "Hide Interact Guide {0}", GetName());
	if (InteractGuideOverlayMat)
	{
		ApplyOverlayMaterials(nullptr);
	}
}

void AMGMonster::ApplyOverlayMaterials(UMaterialInterface* material) const
{
	GetMesh()->SetOverlayMaterial(material);
	Weapon->SetOverlayMaterial(material);
}

