// Copyright Bear Child

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Interaction/MagicInteractGuide.h"
#include "MagicPlayerController.generated.h"

class AMagicProjectileBase;
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

	virtual void PlayerTick(float DeltaTime) override;
	
private:
	#pragma region [INPUT]
	
	UPROPERTY(EditDefaultsOnly, Category="Input")	
	TObjectPtr<UInputMappingContext> MagicContext;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UInputAction> FireAction;
	
	void InputMove(const FInputActionValue& Value);
	
	void InputFire(const FInputActionValue& Value);

	#pragma endregion
	
	#pragma region [HIGHLIGHT]

	// track the actor that is currently pointing at.
	TScriptInterface<IMagicInteractGuide> CurrentGuide = nullptr;

	// called per frame from PlayerTick, which runs on locally-controlled player side only.
	void CursorTrace();

	#pragma endregion
};
