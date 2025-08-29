// Copyright Bear Child

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MagicPlayerController.generated.h"

struct FInputActionValue;
class UInputAction;
class UInputMappingContext;
/**
 * 
 */
UCLASS()
class MAGIC_API AMagicPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AMagicPlayerController();
	
protected:
	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;
	
private:
	UPROPERTY(EditDefaultsOnly, Category="Input")	
	TObjectPtr<UInputMappingContext> MagicContext;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> MoveAction;

	void OnInputMove(const FInputActionValue& Value);
};
