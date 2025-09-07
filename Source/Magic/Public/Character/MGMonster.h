// Copyright Bear Child

#pragma once

#include "CoreMinimal.h"
#include "Character/MGCharacterBase.h"
#include "Interaction/MGInteractable.h"
#include "MGMonster.generated.h"

UCLASS()
class MAGIC_API AMGMonster : public AMGCharacterBase, public IMGInteractable
{
	GENERATED_BODY()

public:
	AMGMonster();

protected:
	virtual bool IsInteractableNow() override;
};
