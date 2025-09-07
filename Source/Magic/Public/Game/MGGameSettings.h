// Copyright Bear Child

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "MGGameSettings.generated.h"

/**
 * 
 */
UCLASS(DefaultConfig, Config=Game)
class MAGIC_API UMGGameSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UMGGameSettings();

public:
	UPROPERTY(Config, EditAnywhere)
	TSoftObjectPtr<UMaterialInterface> DefaultInteractGuideOverrideMat; 
};
