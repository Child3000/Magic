// Copyright Bear Child


#include "Character/MagicMonster.h"

#include "Components/CapsuleComponent.h"


AMagicMonster::AMagicMonster()
{
	PrimaryActorTick.bCanEverTick = false;
	GetCapsuleComponent()->SetCollisionProfileName("Monster");
	GetMesh()->SetCollisionProfileName("NoCollision");
}

void AMagicMonster::OnShowInteractGuide()
{
	// UE_LOGFMT(LogMagicMonster, Log, "Show Interact Guide {0}", GetName());
	if (InteractGuideOverlayMat)
	{
		ApplyOverlayMaterials(InteractGuideOverlayMat);
	}
}

void AMagicMonster::OnHideInteractGuide()
{
	// UE_LOGFMT(LogMagicMonster, Log, "Hide Interact Guide {0}", GetName());
	if (InteractGuideOverlayMat)
	{
		ApplyOverlayMaterials(nullptr);
	}
}

void AMagicMonster::ApplyOverlayMaterials(UMaterialInterface* material) const
{
	GetMesh()->SetOverlayMaterial(material);
	Weapon->SetOverlayMaterial(material);
}

