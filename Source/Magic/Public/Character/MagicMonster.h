// Copyright Bear Child

#pragma once

#include "CoreMinimal.h"
#include "Character/MagicCharacterBase.h"
#include "Interaction/MagicInteractGuide.h"
#include "MagicMonster.generated.h"

UCLASS()
class MAGIC_API AMagicMonster : public AMagicCharacterBase, public IMagicInteractGuide
{
	GENERATED_BODY()

public:
	AMagicMonster();
private:
	#pragma region [INTERACT GUIDE]

	UPROPERTY(EditAnywhere, Category="Interact Guide")
	TObjectPtr<UMaterialInterface> InteractGuideOverlayMat;

	virtual void OnShowInteractGuide() override;

	virtual void OnHideInteractGuide() override;
	
	void ApplyOverlayMaterials(UMaterialInterface* material) const;
	
	#pragma endregion
};
