// Copyright Bear Child

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Object.h"
#include "MGObjectTagAsset.generated.h"

/**
 * A container to hold an unique set of tags.
 */
UCLASS(Blueprintable, BlueprintType)
class MAGIC_API UMGObjectTagAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Tags")
	FGameplayTagContainer TagContainer;
};
