// Copyright Bear Child

#pragma once

#include "CoreMinimal.h"
#include "MGCharacterBase.h"
#include "MGCharacter.generated.h"

class UMGPlayerWidget;
class UMGAttributeComponent;
class UMGInteractionComponent;
class UMGActionComponent;
class AMGProjectileBase;
class UCameraComponent;
class USpringArmComponent;

UCLASS()
class MAGIC_API AMGCharacter : public AMGCharacterBase
{
	GENERATED_BODY()

public:
	AMGCharacter();

	void StartJump();

	void StopJump();

	void Dash();
	
	void StartFireProjectile();

	void StartSprint();

	void StopSprint();

	void Interact();

	UFUNCTION(BlueprintCallable)
	UMGAttributeComponent* GetAttributeComponent() const;

protected:
	virtual void BeginPlay() override;
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	TObjectPtr<USpringArmComponent> SpringArmComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	TObjectPtr<UCameraComponent> CameraComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	TObjectPtr<UMGActionComponent> ActionComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	TObjectPtr<UMGInteractionComponent> InteractionComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	TObjectPtr<UMGAttributeComponent> AttributeComp;

	// UI Begin
private:
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	TSubclassOf<UMGPlayerWidget> PlayerWidgetClass;

	UPROPERTY()
	TObjectPtr<UMGPlayerWidget> PlayerWidget;
	// UI End
};
