// Copyright Bear Child

#pragma once

#include "CoreMinimal.h"
#include "MGAction.h"
#include "MGAction_Dash.generated.h"

/*
 * Info required to interpolate the dash over multiple frames.
 */
USTRUCT(BlueprintType)
struct FDashInterpolateInfo
{
	GENERATED_BODY()

	FDashInterpolateInfo():
		StartLocation(FVector::Zero()), EndLocation(FVector::Zero()), Character(nullptr) {}
	
	FDashInterpolateInfo(const FVector& Start, const FVector& End, ACharacter* Character) :
		StartLocation(Start), EndLocation(End), Character(Character) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector StartLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector EndLocation;

	TWeakObjectPtr<ACharacter> Character;
};

/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class MAGIC_API UMGAction_Dash : public UMGAction, public FTickableGameObject
{
	GENERATED_BODY()

public:
	UMGAction_Dash();

protected:
	virtual void ActionStarted_Implementation(AActor* Instigator) override;

	virtual void ActionStopped_Implementation(AActor* Instigator) override;

private:
	void StartTick(const FDashInterpolateInfo& Info);

	void StopTick();

	uint32 TickFlag:1;

	FDashInterpolateInfo DashInfo;

	float CurrentDashTime;

private:
	void ApplyIgnoredInput(ACharacter* Character, bool bIgnored);

	// FTickableGameObject Begin
public:
	virtual void Tick(float DeltaTime) override;

	virtual ETickableTickType GetTickableTickType() const override;

	virtual bool IsTickable() const override;

	virtual UWorld* GetTickableGameObjectWorld() const override;
	
	virtual TStatId GetStatId() const override;
	// FTickableGameObject End

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Action", meta=(AllowPrivateAccess=true))
	float DashMaxTravelDistance;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Action", meta=(AllowPrivateAccess=true, Units="s", ClampMin="0.01"))
	float DashTotalInterval;

	// Montage Begin
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Action", meta=(AllowPrivateAccess=true))
	TObjectPtr<UAnimMontage> DashMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Action", meta=(AllowPrivateAccess=true))
	float DashMontageRate;
	
	FTimerHandle Timer_PlayLoopMontage;

	void StartPlayLoopDashMontage();

	void StopPlayLoopDashMontage();
	
	void PlayDashMontage();

	void StopDashMontage();
	
	// Montage End

};
