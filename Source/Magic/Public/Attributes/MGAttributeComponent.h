// Copyright Bear Child

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Utility/MGMath.h"
#include "MGAttributeComponent.generated.h"


USTRUCT(BlueprintType)
struct FHealthChangedInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MinHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Ratio;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Percent;

	FHealthChangedInfo()
	{
		Set(0, 0, 0);
	}
	
	void Set(float health, float maxHealth, float minHealth)
	{
		const float ratio = FMath::Clamp(FMGMath::SafeDivide(health - minHealth, maxHealth - minHealth), 0, 1);
		const float percent = ratio * 100.0f;
		Set(health, maxHealth, minHealth, ratio, percent);
	}

	void Set(float health, float maxHealth, float minHealth, float ratio, float percent)
	{
		Health = health;
		MaxHealth = maxHealth;
		MinHealth = minHealth;
		Ratio = ratio;
		Percent = percent;
	}
};

// Event Begin
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature, const FHealthChangedInfo&);
// Event End

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MAGIC_API UMGAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UMGAttributeComponent();

protected:
	virtual void BeginPlay() override;


	// Attributes Begin
public:
	UFUNCTION(BlueprintCallable)
	void SetHealth(float NewHealth);

	UFUNCTION(BlueprintCallable)
	void AddHealth(float HealthDelta);

	void RegisterCall_OnHealthChanged(FOnHealthChangedSignature::FDelegate&& Delegate);
	
protected:
	FOnHealthChangedSignature OnHealthChanged;
	
	FHealthChangedInfo MakeHealthChangedInfo() const;
	
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Attributes", meta=(AllowPrivateAccess=true))
	float Health;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Attributes", meta=(AllowPrivateAccess=true))
	float MaxHealth;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Attributes", meta=(AllowPrivateAccess=true))
	float MinHealth;
	
	// Attributes End
};
