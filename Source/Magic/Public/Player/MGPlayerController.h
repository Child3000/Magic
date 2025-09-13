// Copyright Bear Child

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MGPlayerController.generated.h"

class AMGProjectileBase;
struct FInputActionValue;
class UInputAction;
class UInputMappingContext;
/**
 * 
 */
UCLASS()
class MAGIC_API AMGPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AMGPlayerController();
	
protected:
	virtual void BeginPlay() override;
	
	virtual void SetupInputComponent() override;

	virtual void PlayerTick(float DeltaTime) override;
	
private:
	#pragma region [INPUT]
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")	
	TObjectPtr<UInputMappingContext> MagicContext;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> FireAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> SprintAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> JumpAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> InteractAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UInputAction> DashAction;
	
	void InputMove(const FInputActionValue& Value);
	
	void InputFire(const FInputActionValue& Value);

	void InputStartSprint(const FInputActionValue& Value);

	void InputStopSprint(const FInputActionValue& Value);

	void InputStartJump(const FInputActionValue& Value);
	void InputDash(const FInputActionValue& Value);

	void InputStopJump(const FInputActionValue& Value);

	void InputInteract(const FInputActionValue& Value);
	
	#pragma endregion
};
