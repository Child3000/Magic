// Copyright Bear Child

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Interaction/MGInteractGuide.h"
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
	
	void InputMove(const FInputActionValue& Value);
	
	void InputFire(const FInputActionValue& Value);

	void InputStartSprint(const FInputActionValue& Value);

	void InputStopSprint(const FInputActionValue& Value);

	void InputStartJump(const FInputActionValue& Value);

	void InputStopJump(const FInputActionValue& Value);
	
	#pragma endregion
	
	#pragma region [HIGHLIGHT]

	// track the actor that is currently pointing at.
	TScriptInterface<IMGInteractGuide> CurrentGuide = nullptr;

	// called per frame from PlayerTick, which runs on locally-controlled player side only.
	void CursorTrace();

	#pragma endregion
};
