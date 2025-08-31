// Copyright Bear Child

#pragma once

#include "CoreMinimal.h"
#include "Character/MGCharacterBase.h"
#include "Interaction/MGInteractGuide.h"
#include "MGMonster.generated.h"

UCLASS()
class MAGIC_API AMGMonster : public AMGCharacterBase, public IMGInteractGuide
{
	GENERATED_BODY()

public:
	AMGMonster();
private:
	#pragma region [INTERACT GUIDE]

	UPROPERTY(EditAnywhere, Category="Interact Guide")
	TObjectPtr<UMaterialInterface> InteractGuideOverlayMat;

	virtual void OnShowInteractGuide() override;

	virtual void OnHideInteractGuide() override;
	
	void ApplyOverlayMaterials(UMaterialInterface* material) const;
	
	#pragma endregion
};
